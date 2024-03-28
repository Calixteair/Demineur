#include "headerFiles/Models/Leaderboard.h"
#include "headerFiles/Views/LeaderboardView.h"
#include "headerFiles/Controllers/ProfileManager.h"

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
    QList<Profile*> profiles = profileManager->getProfiles();
    for (int i = 0; i < profiles.size(); ++i) {
        QLabel *indexLabel = new QLabel(QString::number(i + 1));
        QLabel *nameLabel = new QLabel(profiles[i]->getName());
        QLabel *paramLabel = new QLabel(QString::number(profiles[i]->getRecord(0).msecsSinceStartOfDay())); // Utilisez le premier record comme paramètre par défaut
        QHBoxLayout *profileLayout = new QHBoxLayout;
        profileLayout->addWidget(indexLabel);
        profileLayout->addWidget(nameLabel);
        profileLayout->addWidget(paramLabel);
        m_leaderboard_view->addLayout(profileLayout);
    }
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
        m_leaderboard.sortByParameter(mode);
        updateDisplay();
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
    QList<Profile*> profiles = profileManager->getProfiles();
    for (int i = 0; i < profiles.size(); ++i) {
        QLabel *paramLabel = qobject_cast<QLabel*>(m_layout->itemAt(i + 2)->layout()->itemAt(2)->widget());
        paramLabel->setText(QString::number(profiles[i]->getRecord(0).msecsSinceStartOfDay())); // Utilisez le premier record comme paramètre par défaut
    }
}

void LeaderboardView::updateDisplay() {

    // Supprimer les anciennes entrées
    QLayoutItem *child;
    while ((child = m_layout->takeAt(2)) != nullptr) {
        delete child->widget();
        delete child;
    }
    

    // Afficher les nouvelles entrées triées
    QVector<Leaderboard::LeaderboardEntry> entries = m_leaderboard.getLeaderboardEntries();
    for (const auto &entry : entries) {
        QLabel *label = new QLabel;
        label->setText(QString("%1 - %2").arg(entry.rank).arg(entry.name));
        m_layout->addWidget(label);
    }
}



