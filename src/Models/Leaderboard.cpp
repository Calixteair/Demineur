#include "headerFiles/Models/Leaderboard.h"
#include "headerFiles/Models/Profile.h"
#include "headerFiles/Controllers/ProfileManager.h"

#include <algorithm>

Leaderboard::Leaderboard(ProfileManager* profileManager, QObject *parent)
    : QObject(parent), profileManager(profileManager) {
    // Autres initialisations si nécessaire...
}

void Leaderboard::addProfile(Profile *profile) {
    LeaderboardEntry entry;
    entry.avatarPath = profile->getAvatarPath();
    entry.name = profile->getName();
    // Utilisez ici le paramètre souhaité pour classer les joueurs
    // Par exemple, si le paramètre est un temps en QTime :
    entry.parameterValue = profile->getRecord(0); // Utilisez le premier record comme paramètre par défaut
    entry.parameterValueInt = profile->getRecord(0).msecsSinceStartOfDay();
    m_leaderboardEntries.append(entry);
    m_leaderboardEntriesInt.append(entry);
}

bool compareEntries(const Leaderboard::LeaderboardEntry &a, const Leaderboard::LeaderboardEntry &b) {
    // Modifiez cette fonction de comparaison selon le paramètre souhaité
    return a.parameterValue < b.parameterValue;
}
void Leaderboard::sortByParameter(int mode) {
    // Supposons que vous ayez déjà les données nécessaires pour le tri dans votre classe Leaderboard
    if (mode == 0) {
        // Effectuez le tri par paramètre de temps
        std::sort(m_leaderboardEntries.begin(), m_leaderboardEntries.end(), [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
            return a.parameterValue < b.parameterValue;
        });
    } else if (mode == 1) {
        // Effectuez le tri par paramètre entier
        std::sort(m_leaderboardEntries.begin(), m_leaderboardEntries.end(), [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
            return a.parameterValueInt < b.parameterValueInt;
        });
    }
}

QVector<Leaderboard::LeaderboardEntry> Leaderboard::getLeaderboardEntries() const {
    return m_leaderboardEntries;
}
