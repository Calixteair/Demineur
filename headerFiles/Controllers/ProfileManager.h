#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "headerFiles/Models/Profile.h"
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QTime>


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
    void updaterecord(Profile* profile, QTime time , int record);
    void addGame(int col, int row, int mines, QTime time , bool win);
    void refreshProfileinFile(Profile* profile);
    bool getProfileSelected();
    QList<Profile*> getProfilesList();

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
