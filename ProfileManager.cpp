#include "ProfileManager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "Profile.h"
#include <QList>
#include <QString>
#include <QImage>


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
    QFile file("profiles.dat");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Saving profiles to file: ";
        QTextStream out(&file);
        // save le profile dans le fichier
        QString name = profile->getName();
        QImage image = profile->getAvatar().toImage();
        if (!image.isNull()) {
            QString fileName = "avatar_" + profile->getName() + ".png";
            image.save(fileName);
            out << profile->getName() << "," << fileName << "\n";
        } else {
            qDebug() << "Failed to convert avatar to image.";
        }
        file.close();
    }
    else
    {
        qWarning() << "Impossible d'ouvrir le fichier pour sauvegarde des profils : " << "profiles.dat";
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
