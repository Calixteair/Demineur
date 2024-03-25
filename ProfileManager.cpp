#include "ProfileManager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "Profile.h"
#include <QList>
#include <QString>
#include <QImage>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDate>
#include <QStandardPaths>
#include <QDir>

ProfileManager::ProfileManager()
{
    // Charger les profils à partir du fichier lors de la création du gestionnaire de profils
    loadProfiles("profiles.dat");
}

QList<Profile*> ProfileManager::getProfiles() const
{
    return profiles;
}

void ProfileManager::addProfile(Profile* profile)
{
    profiles.append(profile);
}

void ProfileManager::removeProfile(Profile* profile)
{
    profiles.removeOne(profile);
    delete profile; // Assurez-vous de libérer la mémoire du profil supprimé
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
                recordsJson["easy"] = 0;
                recordsJson["medium"] = 0;
                recordsJson["hard"] = 0;
                recordsJson["custom"] = 0;
                profileJson["records"] = recordsJson;

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

void ProfileManager::loadProfiles(const QString& filePath)
{
    QFile file(filePath);
    qDebug() << "Loading profiles from file: " << filePath;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File opened successfully";
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 2)
            {
                QString name = parts[0];
                QString avatarPath = parts[1];
                Profile* profile = new Profile(name, avatarPath);
                addProfile(profile);
            }
        }
        file.close();
    }
    else
    {
        qWarning() << "Impossible d'ouvrir le fichier pour chargement des profils : " << filePath;
    }
}
