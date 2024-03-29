#include "headerFiles/Models/Leaderboard.h"
#include "headerFiles/Models/Profile.h"
#include "headerFiles/Controllers/ProfileManager.h"

#include <algorithm>

Leaderboard::Leaderboard(ProfileManager* profileManager, QObject *parent)
    : QObject(parent), profileManager(profileManager) {
    // Autres initialisations si nécessaire...
}



void Leaderboard::sortByParameter(int mode, QList<Profile*> &profiles) {
    // Effectuez le tri sur la QList de profils en fonction du mode spécifié
    if (mode == 0) {
        // Tri par le premier enregistrement (mode 0)
        std::sort(profiles.begin(), profiles.end(), [](const Profile* a, const Profile* b) {
            if (a->getRecord(0) == QTime(0, 0, -1)) {
                return false;
            }
            if (b->getRecord(0) == QTime(0, 0, -1)) {
                return true;
            }
            return a->getRecord(0) < b->getRecord(0);
        });
    } else if (mode == 1) {
        // Tri par le deuxième enregistrement (mode 1)
        std::sort(profiles.begin(), profiles.end(), [](const Profile* a, const Profile* b) {
            if (a->getRecord(1) == QTime(0, 0, -1)) {
                return false;
            }
            if (b->getRecord(1) == QTime(0, 0, -1)) {
                return true;
            }
            return a->getRecord(1) < b->getRecord(1);
        });
    } else if (mode == 2) {
        // Tri par le troisième enregistrement (mode 2)
        std::sort(profiles.begin(), profiles.end(), [](const Profile* a, const Profile* b) {
            if (a->getRecord(2) == QTime(0, 0, -1)) {
                return false;
            }
            if (b->getRecord(2) == QTime(0, 0, -1)) {
                return true;
            }
            return a->getRecord(2) < b->getRecord(2);
        });
    } else if (mode == 3) {
        // Tri par le nombre de parties jouées (mode 3)
        std::sort(profiles.begin(), profiles.end(), [](const Profile* a, const Profile* b) {
            return a->getPartiesJouer() > b->getPartiesJouer();
        });
    } else if (mode == 4) {
        // Tri par le nombre de parties gagnées (mode 4)
        std::sort(profiles.begin(), profiles.end(), [](const Profile* a, const Profile* b) {
            return a->getPartiesGagner() > b->getPartiesGagner();
        });
    } else if (mode == 5) {
        // Tri par le nombre de parties perdues (mode 5)
        std::sort(profiles.begin(), profiles.end(), [](const Profile* a, const Profile* b) {
            return a->getPartiesPerdu() > b->getPartiesPerdu();
        });
    }
}

