#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "headerFiles/Models/Profile.h"
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>


class ProfileManager
{
public:
    Profile *curentProfile;
    ProfileManager();
    bool profileSelected;

    QList<Profile*> getProfiles();
    void addProfile(Profile* profile);
    void removeProfile(Profile* profile);
    void saveProfiles(Profile* profile);
    QList<Profile*> loadAllProfiles();
    void changeName(Profile* profile, QString newName);
    void changeAvatar(Profile* profile, QString newAvatarPath);

private:
    QList<Profile*> profiles;
    QJsonObject *uuidJson;
    QJsonObject *profileJson;
    QJsonObject *recordsJson;
    QJsonObject *partiesJouerJson;
    QJsonObject *partiesGagnerJson;
    QJsonObject *partiesPerduJson;
    Profile *profile;
};

#endif // PROFILEMANAGER_H
