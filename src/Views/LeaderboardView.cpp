#include "headerFiles/Models/Leaderboard.h"
#include "headerFiles/Views/LeaderboardView.h"
#include "headerFiles/Controllers/ProfileManager.h"
#include <QLabel>
#include <QPushButton>
#include <QDebug>


LeaderboardView::LeaderboardView(ProfileManager* profileManager, QWidget *parent) 
    : QWidget(parent), profileManager(profileManager), m_leaderboard(profileManager)
{
    m_layout = new QVBoxLayout(this);

    m_button_layout = new QHBoxLayout(this);
    m_layout->addLayout(m_button_layout);

    m_leaderboard_view = new QVBoxLayout(this);
    m_layout->addLayout(m_leaderboard_view);

    // Créer les boutons de tri
    QStringList buttonNames = {"Easy", "Medium", "Hard", "Total Games", "Games Won", "Games Lost"};
    for (const QString &name : buttonNames) {
        QPushButton *sortByButton = new QPushButton("Sort by " + name);
        connect(sortByButton, &QPushButton::clicked, this, &LeaderboardView::sortByParameter);
        m_button_layout->addWidget(sortByButton);
    }

    // Créer un QLabel pour afficher le leaderboard
    m_leaderboard_view->addWidget(new QLabel("Leaderboard"));

    // Afficher la liste des profils
    updateLeaderboard();
}

void LeaderboardView::sortByParameter() {
    QPushButton *buttonclic = qobject_cast<QPushButton*>(sender());
    if (buttonclic) {
        QString buttonText = buttonclic->text();
        QString parameterName = buttonText.mid(8); // Supprimer "Sort by " du texte du bouton
        int mode = 0; // Mode de tri par défaut
        if (parameterName == "Easy") {
            mode = 0;
        } else if (parameterName == "Medium") {
            mode = 1;
        } else if (parameterName == "Hard") {
            mode = 2;
        } else if (parameterName == "Total Games") {
            mode = 3;
        } else if (parameterName == "Games Won") {
            mode = 4;
        } else if (parameterName == "Games Lost") {
            mode = 5;
        }
        updateDisplay(mode);
        // reactiver tous les boutons
        for (int i = 0; i < m_button_layout->count(); ++i) {
            QPushButton *button = qobject_cast<QPushButton*>(m_button_layout->itemAt(i)->widget());
            if (button) {
                button->setEnabled(true);
            }
        }

        buttonclic->setEnabled(false);
    }
}

void LeaderboardView::updateLeaderboard() {
    updateDisplay(0); // Mettre à jour l'affichage avec le mode de tri par défaut
}

void LeaderboardView::updateDisplay(int mode) {
    // Tri des profils en fonction du mode spécifié
    updateListe();
   m_leaderboard.sortByParameter(mode, profilesSorted);

    // Supprimer les anciennes entrées du layout
    QLayoutItem *child;
    while ((child = m_layout->takeAt(2)) != nullptr) {
        delete child->widget();
        delete child;
    }

    
    int index = 1; // Index pour affichage
    for (Profile *profile : profilesSorted) {
        QLabel *indexLabel = new QLabel(QString::number(index)); // Afficher l'index
        m_layout->addWidget(indexLabel);

        QLabel *nameLabel = new QLabel(profile->getName()); // Afficher le nom du profil
        m_layout->addWidget(nameLabel);

        QLabel *parameterLabel; // Afficher le paramètre utilisé pour le tri
        if (mode == 0) {
            parameterLabel = new QLabel(profile->getRecord(0).toString()); // Afficher le temps pour le mode 0
        } else if (mode == 1) {
            parameterLabel = new QLabel(profile->getRecord(1).toString()); // Afficher le nombre pour le mode 1
        } else if (mode == 2) {
            parameterLabel = new QLabel(profile->getRecord(2).toString()); // Afficher le nombre pour le mode 1
        }  
        else if (mode == 3) {
            parameterLabel = new QLabel(QString::number(profile->getPartiesJouer())); // Afficher le nombre pour le mode 1
        }  
        else if (mode == 4) {
            parameterLabel = new QLabel(QString::number(profile->getPartiesGagner())); // Afficher le nombre pour le mode 1
        }  
        else if (mode == 5) {
            parameterLabel = new QLabel(QString::number(profile->getPartiesPerdu())); // Afficher le nombre pour le mode 1
        }

        m_layout->addWidget(parameterLabel);

        index++; // Incrémenter l'index pour chaque profil
    }
}

void LeaderboardView::updateListe() {
    profilesSorted.clear();
    QList<Profile*> profiles = profileManager->getProfiles();
    for (int i = 0; i < profiles.size(); ++i) {
        profilesSorted.append(profiles[i]);
    }
}



