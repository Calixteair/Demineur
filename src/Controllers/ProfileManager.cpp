#include "headerFiles/Controllers/ProfileManager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "headerFiles/Models/Profile.h"
#include <QList>
#include <QString>
#include <QImage>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDate>
#include <QStandardPaths>
#include <QTime>
#include <QDir>
//uuid
#include <QUuid>

ProfileManager::ProfileManager()

    
{
    profiles = QList<Profile*>();
    profile = nullptr;
    profileSelected = false;
}

QList<Profile*> ProfileManager::getProfiles()
{
    profiles = loadAllProfiles();
    return profiles;
}

void ProfileManager::addProfile(Profile* profile)
{
    profiles.append(profile);
}

void ProfileManager::removeProfile(Profile* profile)
{
    
    
    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";
    QString profilePath = profilesPath + "/" + profile->getName();

    if (QDir(profilePath).exists())
    {
        QDir(profilePath).removeRecursively();
        profiles.removeOne(profile);
        qDebug() << "Profile deleted successfully";
    }
    else
    {
        qDebug() << "Profile does not exist";
    }

}

void ProfileManager::updaterecord(Profile* profile, QTime time, int mode){
    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";
    QString profilePath = profilesPath + "/" + profile->getName();
    QFile file(profilePath + "/profiles.json");

    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jsonError);

        if (jsonError.error != QJsonParseError::NoError)
        {
            qWarning() << "Erreur lors de l'analyse du fichier JSON : " << jsonError.errorString();
            return;
        }
        QJsonObject profileJson = doc.object();
        QJsonObject recordsJson = profileJson["records"].toObject();

        // Mettre à jour les enregistrements dans recordsJson
        recordsJson[QString::number(mode)] = time.toString("hh:mm:ss");

        // Mettre à jour l'objet "records" dans profileJson
        profileJson["records"] = recordsJson;

        // Réécrire profileJson dans le document JSON
        doc.setObject(profileJson);

        // Réécrire le document JSON dans le fichier
        file.resize(0); // Effacer le contenu existant
        file.write(doc.toJson());
        file.close();

        profile->setRecord(mode, time);

        qDebug() << "Record updated successfully";

        
    }
    else
    {
        qWarning() << "Impossible d'ouvrir le fichier pour charger les profils : " << "profiles.dat";
    }

}

void ProfileManager::changeName(Profile* profile, QString newName)
{
    qDebug() << "Changing profile name";
    
    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";
    
    QString profilePath = profilesPath + "/" + profile->getName();
    
    QString newProfilePath = profilesPath + "/" + newName;
    QString oldAvatarPath = newProfilePath + "/avatar_" + profile->getName() + ".png";
    QString newAvatarPath = newProfilePath + "/avatar_" + newName + ".png";
    
    if (QDir(profilePath).exists())
    {
        QDir().rename(profilePath, newProfilePath);
        profile->setName(newName);

        // update le json 
        QFile file(newProfilePath + "/profiles.json");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonParseError jsonError;
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jsonError);

            if (jsonError.error != QJsonParseError::NoError)
            {
                qWarning() << "Erreur lors de l'analyse du fichier JSON : " << jsonError.errorString();
                return;
            }

            QJsonObject profileJson = doc.object();
            profileJson["name"] = newName;

            QJsonDocument newDoc(profileJson);
            file.close();

            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                file.write(newDoc.toJson());
            }
            else
            {
                qWarning() << "Impossible d'ouvrir le fichier pour sauvegarde des profils : " << "profiles.dat";
            }
            // changer le nom de l'avatar
            qDebug() << "changement du nom de l'avatar";
            qDebug() << oldAvatarPath;
            qDebug() << newAvatarPath;
            QFile::rename(oldAvatarPath, newAvatarPath);
        }
        else
        {
            qWarning() << "Impossible d'ouvrir le fichier pour charger les profils : " << "profiles.dat";
        }

        qDebug() << "Profile renamed successfully";
    }
    else
    {
        qDebug() << "Profile does not exist";
    }
}

void ProfileManager::changeAvatar(Profile* profile, QString newAvatarPath)
{
    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";
    QString profilePath = profilesPath + "/" + profile->getName();
    qDebug() << profilePath;
    qDebug() << profile->getName();
    
    QString newAvatarDest = profilePath + "/avatar_" + profile->getName() + ".png";
    qDebug() << newAvatarDest;

    //remove old avatar
    QFile::remove(newAvatarDest);


    if (QFile::copy(newAvatarPath, newAvatarDest))
    {
        qDebug() << "Avatar copied successfully";
    }
    else
    {
        qDebug() << "Error copying avatar: ";
    }
}




void ProfileManager::saveProfiles(Profile* profile)

{
    //verifier si le dossier profiles existe

    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";
    QString profilePath = profilesPath + "/" + profile->getName();

    if (QDir(profilePath).exists())
    {
        qDebug() << "Profile already exists";
        return;
    }else{
        try {
            QDir().mkpath(profilesPath + "/" + profile->getName());
            qDebug() << "Profile created successfully";
            profilesPath = profilesPath + "/" + profile->getName();
            qDebug() << profilesPath;

            QFile file(profilesPath + "/profiles.json");

            QString avatarSrc = profile->getAvatarPath();
            QString avatarDest = profilePath + "/avatar_" + profile->getName() + ".png";

            if (QFile::copy(avatarSrc, avatarDest))
            {
                qDebug() << "Avatar copied successfully";
            }
            else
            {
                qDebug() << "Error copying avatar";
            }


            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                /// {name: "name", records: {easy: 0, medium: 0, hard: 0, custom: 0}, dateCreated: "date}
                
                QJsonObject profileJson;
                profileJson["name"] = profile->getName();

                QJsonObject recordsJson;
                QJsonObject uuidJson;

                uuidJson["uuid"] = QUuid::createUuid().toString();
                QTime time;
                time.setHMS(0,0,0);
                recordsJson["easy"] = time.toString("hh:mm:ss");
                recordsJson["medium"] = time.toString("hh:mm:ss");
                recordsJson["hard"] = time.toString("hh:mm:ss");
                recordsJson["custom"] = time.toString("hh:mm:ss");
                profileJson["records"] = recordsJson;
                QJsonObject partiesJouerJson;
                QJsonObject partiesGagnerJson;
                QJsonObject partiesPerduJson;
                partiesJouerJson["partiesJouer"] = 0;
                partiesGagnerJson["partiesGagner"] = 0;
                partiesPerduJson["partiesPerdu"] = 0;
                profileJson["dateCreated"] = QDate::currentDate().toString("yyyy-MM-dd");

                QJsonDocument doc(profileJson);
                file.write(doc.toJson());
            }
            else
            {
                qWarning() << "Impossible d'ouvrir le fichier pour sauvegarde des profils : " << "profiles.dat";
            }

        } catch (const std::exception& e) {
            qDebug() << "Error creating profiles directory: " << e.what();
        }
    }

    
}
QList<Profile*> ProfileManager::loadAllProfiles()
{
    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";

    QList<Profile*> profilesList;

    QDir profilesDir(profilesPath);
    QStringList profileFolders = profilesDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString &profileFolder : profileFolders)
    {
        QString profilePath = profilesPath + "/" + profileFolder;
        QFile file(profilePath + "/profiles.json");

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonParseError jsonError;
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jsonError);

            if (jsonError.error != QJsonParseError::NoError)
            {
                qWarning() << "Erreur lors de l'analyse du fichier JSON : " << jsonError.errorString();
                continue;
            }

            QJsonObject profileJson = doc.object();

            profile = new Profile();
            profile->setName(profileJson["name"].toString());

            QJsonObject recordsJson = profileJson["records"].toObject();
            // QTime fromString("hh:mm:ss")
            QTime easyRecord = QTime::fromString(recordsJson["easy"].toString(), "hh:mm:ss");
            QTime mediumRecord = QTime::fromString(recordsJson["medium"].toString(), "hh:mm:ss");
            QTime hardRecord = QTime::fromString(recordsJson["hard"].toString(), "hh:mm:ss");
            QTime customRecord = QTime::fromString(recordsJson["custom"].toString(), "hh:mm:ss");

            profile->setRecord(1, easyRecord);
            profile->setRecord(2, mediumRecord);
            profile->setRecord(3, hardRecord);
            profile->setRecord(4, customRecord);


            profile->setUuid(profileJson["uuid"].toString());

            profile->setPartiesJouer(profileJson["partiesJouer"].toInt());
            profile->setPartiesGagner(profileJson["partiesGagner"].toInt());
            profile->setPartiesPerdu(profileJson["partiesPerdu"].toInt());

            QString avatarPath = profilePath + "/avatar_" + profileFolder + ".png";
            profile->setAvatarPath(avatarPath);


            profilesList.append(profile);

            file.close();
        }
        else
        {
            qWarning() << "Impossible d'ouvrir le fichier pour charger les profils : " << "profiles.dat";
        }
    }

    return profilesList;
}