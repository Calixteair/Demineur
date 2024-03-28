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
#include <iostream>
// uuid
#include <QUuid>

ProfileManager::ProfileManager()

{
    profiles = QList<Profile *>();
    profile = nullptr;
    profileSelected = false;
}

QList<Profile *> ProfileManager::getProfiles()
{
    profiles = loadAllProfiles();
    return profiles;
}

void ProfileManager::addProfile(Profile *profile)
{
    profiles.append(profile);
}

void ProfileManager::removeProfile(Profile *profile)
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

void ProfileManager::updaterecord(Profile *profile, QTime time, int mode)
{
    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";
    QString profilePath = profilesPath + "/" + profile->getName();
    QFile file(profilePath + "/profiles.json");
    profile->setRecord(mode, time);

    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {

        QJsonObject profileJson;
        // QJsonObject recordsJson = profileJson["records"].toObject();
        profileJson["name"] = profile->getName();

        QJsonObject recordsJson;
        recordsJson["easy"] = profile->getRecord(0).toString("hh:mm:ss");
        recordsJson["medium"] = profile->getRecord(1).toString("hh:mm:ss");
        recordsJson["hard"] = profile->getRecord(2).toString("hh:mm:ss");
        recordsJson["custom"] = profile->getRecord(3).toString("hh:mm:ss");

        profileJson["records"] = recordsJson;

        profileJson["uuid"] = profile->getUuid();

        profileJson["partiesJouer"] = profile->getPartiesJouer();
        profileJson["partiesGagner"] = profile->getPartiesGagner();
        profileJson["partiesPerdu"] = profile->getPartiesPerdu();

        profileJson["dateCreated"] = QDate::currentDate().toString("yyyy-MM-dd");

        QJsonDocument doc(profileJson);
        file.write(doc.toJson());

        qDebug() << "Record updated successfully";
    }
    else
    {
        qWarning() << "Impossible d'ouvrir le fichier pour charger les profils : "
                   << "profiles.dat";
    }
}

void ProfileManager::changeName(Profile *profile, QString newName)
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
                qWarning() << "Impossible d'ouvrir le fichier pour sauvegarde des profils : "
                           << "profiles.dat";
            }
            // changer le nom de l'avatar
            qDebug() << "changement du nom de l'avatar";
            qDebug() << oldAvatarPath;
            qDebug() << newAvatarPath;
            QFile::rename(oldAvatarPath, newAvatarPath);
        }
        else
        {
            qWarning() << "Impossible d'ouvrir le fichier pour charger les profils : "
                       << "profiles.dat";
        }

        qDebug() << "Profile renamed successfully";
    }
    else
    {
        qDebug() << "Profile does not exist";
    }
}

void ProfileManager::changeAvatar(Profile *profile, QString newAvatarPath)
{
    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";
    QString profilePath = profilesPath + "/" + profile->getName();
    qDebug() << profilePath;
    qDebug() << profile->getName();

    QString newAvatarDest = profilePath + "/avatar_" + profile->getName() + ".png";
    qDebug() << newAvatarDest;

    // remove old avatar
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

void ProfileManager::saveProfiles(Profile *profile)

{
    // verifier si le dossier profiles existe

    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";
    QString profilePath = profilesPath + "/" + profile->getName();

    if (QDir(profilePath).exists())
    {
        qDebug() << "Profile already exists";
        return;
    }
    else
    {
        try
        {
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
                recordsJson["easy"] = "";
                recordsJson["medium"] = "";
                recordsJson["hard"] = "";
                recordsJson["custom"] = "";
                profileJson["records"] = recordsJson;
                profileJson["partiesJouer"] = 0;
                profileJson["partiesGagner"] = 0;
                profileJson["partiesPerdu"] = 0;
                profileJson["dateCreated"] = QDate::currentDate().toString("yyyy-MM-dd");

                QJsonDocument doc(profileJson);
                file.write(doc.toJson());
            }
            else
            {
                qWarning() << "Impossible d'ouvrir le fichier pour sauvegarde des profils : "
                           << "profiles.dat";
            }
        }
        catch (const std::exception &e)
        {
            qDebug() << "Error creating profiles directory: " << e.what();
        }
    
    }
}
QList<Profile *> ProfileManager::loadAllProfiles()
{
    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";

    QList<Profile *> profilesList;

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

            profile->setRecord(0, easyRecord);
            profile->setRecord(1, mediumRecord);
            profile->setRecord(2, hardRecord);
            profile->setRecord(3, customRecord);

            profile->setUuid(profileJson["uuid"].toString());

            profile->setPartiesJouer(profileJson["partiesJouer"].toInt());
            profile->setPartiesGagner(profileJson["partiesGagner"].toInt());
            profile->setPartiesPerdu(profileJson["partiesPerdu"].toInt());

            std::cout << profile->getPartiesJouer() << " " << profile->getPartiesGagner() << " " << profile->getPartiesPerdu() << std::endl;


            QString avatarPath = profilePath + "/avatar_" + profileFolder + ".png";
            profile->setAvatarPath(avatarPath);

            profilesList.append(profile);

            file.close();
        }
        else
        {
            qWarning() << "Impossible d'ouvrir le fichier pour charger les profils : "
                       << "profiles.dat";
        }
    }

    return profilesList;
}

void ProfileManager::addGame(int col, int row, int mines, QTime time, bool win)
{

    if (profileSelected)
    {
        if (win)
        {
            curentProfile->setPartiesGagner(curentProfile->getPartiesGagner() + 1);


             if (col == 8 && row == 8 && mines == 10)
        {
            QTime currentRecord = curentProfile->getRecord(0);
            if (currentRecord.toString().toStdString().empty()  || time < currentRecord)
            {
                 std::cout << "Addgame" << time.toString().toStdString() << std::endl;

                curentProfile->setRecord(0, time);
            }
        }
        else if (col == 16 && row == 16 && mines == 40)
        {
            QTime currentRecord = curentProfile->getRecord(1);
            if (currentRecord.toString().toStdString().empty() || time < currentRecord)
            {
                curentProfile->setRecord(1, time);
            }
        }
        else if (col == 16 && row == 30 && mines == 99)
        {
            QTime currentRecord = curentProfile->getRecord(2);
            if (currentRecord.toString().toStdString().empty()  || time < currentRecord)
            {
                curentProfile->setRecord(2, time);
            }
        }
        else
        {
            QTime currentRecord = curentProfile->getRecord(3);
            if (currentRecord.isNull() || time < currentRecord)
            {
                curentProfile->setRecord(3, time);
            }
        }


        }
        else
        {
            curentProfile->setPartiesPerdu(curentProfile->getPartiesPerdu() + 1);
        }
        curentProfile->setPartiesJouer(curentProfile->getPartiesJouer() + 1);

       

        refreshProfileinFile(curentProfile);
    }
}

void ProfileManager::refreshProfileinFile(Profile *profile)
{

    QString profilesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles";
    QString profilePath = profilesPath + "/" + profile->getName();

    QFile file(profilePath + "/profiles.json");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonObject profileJson;
        profileJson["name"] = profile->getName();

        QJsonObject recordsJson;
        recordsJson["easy"] = profile->getRecord(0).toString("hh:mm:ss");
        recordsJson["medium"] = profile->getRecord(1).toString("hh:mm:ss");
        recordsJson["hard"] = profile->getRecord(2).toString("hh:mm:ss");
        recordsJson["custom"] = profile->getRecord(3).toString("hh:mm:ss");

        profileJson["records"] = recordsJson;

        profileJson["uuid"] = profile->getUuid();

        profileJson["partiesJouer"] = profile->getPartiesJouer();
        profileJson["partiesGagner"] = profile->getPartiesGagner();
        profileJson["partiesPerdu"] = profile->getPartiesPerdu();

        profileJson["dateCreated"] = QDate::currentDate().toString("yyyy-MM-dd");

        QJsonDocument doc(profileJson);
        file.write(doc.toJson());
    }
    else
    {
        qWarning() << "Impossible d'ouvrir le fichier pour sauvegarde des profils : "
                   << "profiles.dat";
    }
}

bool ProfileManager::getProfileSelected()
{
    return profileSelected;
}
