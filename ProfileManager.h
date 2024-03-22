#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "Profile.h"
#include <QList>

class ProfileManager
{
public:
    ProfileManager();

    QList<Profile*> getProfiles() const;
    void addProfile(Profile* profile);
    void removeProfile(Profile* profile);
    void saveProfiles(Profile* profile);
    void loadProfiles(const QString& filePath);

private:
    QList<Profile*> profiles;
};

#endif // PROFILEMANAGER_H
