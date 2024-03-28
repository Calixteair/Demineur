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

    // Structure de données pour stocker les informations du leaderboard
    struct LeaderboardEntry {
        int rank;
        QString avatarPath;
        QString name;
        QTime parameterValue; // Paramètre utilisé pour classer les joueurs
        int parameterValueInt;

    };
    

    // Méthode pour ajouter un profil au leaderboard
    void addProfile(Profile *profile);

    // Méthode pour trier le leaderboard en fonction du paramètre spécifié
    void sortByParameter(int mode);

    // Méthode pour récupérer les entrées du leaderboard
    QVector<LeaderboardEntry> getLeaderboardEntries() const;

signals:

private:
    ProfileManager* profileManager;
    QVector<LeaderboardEntry> m_leaderboardEntries;
    QVector<LeaderboardEntry> m_leaderboardEntriesInt;
};

#endif // LEADERBOARD_H
