#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QTime>
#include "headerFiles/Controllers/ProfileManager.h"


class Profile;
class ProfileManager;

class Leaderboard : public QObject
{
    Q_OBJECT
public:
    Leaderboard(ProfileManager* profileManager, QObject *parent = nullptr); 



    // Méthode pour trier le leaderboard en fonction du paramètre spécifié
    void sortByParameter(int mode, QList<Profile*> &profiles);


signals:

private:
    ProfileManager* profileManager;
};

#endif // LEADERBOARD_H
