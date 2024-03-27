#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "Profile.h"
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>


class ProfileManager
{
public:
    ProfileManager();

    QList<Profile*> getProfiles();
    void addProfile(Profile* profile);
    void removeProfile(Profile* profile);
    void saveProfiles(Profile* profile);
    QList<Profile*> loadAllProfiles();

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
