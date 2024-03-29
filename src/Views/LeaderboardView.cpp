#include "headerFiles/Models/Leaderboard.h"
#include "headerFiles/Views/LeaderboardView.h"
#include "headerFiles/Controllers/ProfileManager.h"
#include <QLabel>
#include <QPushButton>
#include <QPixmap>



LeaderboardView::LeaderboardView(ProfileManager* profileManager, QWidget *parent) 
    : QWidget(parent), profileManager(profileManager), m_leaderboard(profileManager)
{
    m_layout = new QVBoxLayout(this);

    m_button_layout = new QHBoxLayout(); // Créez le QHBoxLayout sans parent
    m_layout->addLayout(m_button_layout); // Ajoutez-le à m_layout ici

    // Initialisez les membres indexHeader, avatarHeader, nameHeader et parameterHeader
    indexHeader = new QLabel("Rank", this);
    avatarHeader = new QLabel("Avatar", this);
    nameHeader = new QLabel("Name", this);
    parameterHeader = new QLabel("Parameter", this);

    // Initialisez headerLayout
    headerLayout = new QHBoxLayout();

    // Créer les boutons de tri
    QStringList buttonNames = {"Easy", "Medium", "Hard", "Total Games", "Games Won", "Games Lost"};
    for (const QString &name : buttonNames) {
        QPushButton *sortByButton = new QPushButton("Sort by " + name);
        connect(sortByButton, &QPushButton::clicked, this, &LeaderboardView::sortByParameter);
        m_button_layout->addWidget(sortByButton);
    }

    // Paramètres de style pour les en-têtes
    QString headerStyle = "font-weight: bold;";
    
    indexHeader->setAlignment(Qt::AlignCenter);
    avatarHeader->setAlignment(Qt::AlignCenter);
    nameHeader->setAlignment(Qt::AlignCenter);
    parameterHeader->setAlignment(Qt::AlignCenter);



    // Appliquez le style aux en-têtes
    indexHeader->setStyleSheet(headerStyle);
    avatarHeader->setStyleSheet(headerStyle);
    nameHeader->setStyleSheet(headerStyle);
    parameterHeader->setStyleSheet(headerStyle);

    // Ajoutez les en-têtes au layout
    headerLayout->addWidget(indexHeader);
    headerLayout->addWidget(avatarHeader);
    headerLayout->addWidget(nameHeader);
    headerLayout->addWidget(parameterHeader);
    m_layout->addLayout(headerLayout);

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
        updateDisplay(mode, parameterName);
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
    updateDisplay(0, "Easy" ); // Mettre à jour l'affichage avec le mode de tri par défaut
}

void LeaderboardView::updateDisplay(int mode, QString parameterName) {
    // Tri des profils en fonction du mode spécifié
    updateListe();
    m_leaderboard.sortByParameter(mode, profilesSorted);
    

    // Supprimer les anciennes entrées du layout
    QLayoutItem *child;
    while ((child = m_layout->takeAt(2)) != nullptr) {
        delete child->widget();
        delete child;
    }


    // Création de la rangée pour les noms de colonnes


    parameterHeader->setText("Parametre : " + parameterName);




    
   // Affichage des profils
    int index = 1; // Index pour affichage
    for (Profile *profile : profilesSorted) {
        // Créer un widget pour afficher les informations du profil
        QWidget *profileWidget = new QWidget();
        QHBoxLayout *profileLayout = new QHBoxLayout(profileWidget);
        
        // Affichage de l'index
        
        QLabel *indexLabel = new QLabel(QString::number(index));
        if (index == 1) {
            // afficher cup.png dans les source qrc
            QPixmap cupPixmap(":/img/cup.png");
            // Créer un QLabel pour afficher l'image
            QLabel *cupLabel = new QLabel;
            cupLabel->setPixmap(cupPixmap.scaled(50, 50));
            cupLabel->setAlignment(Qt::AlignCenter);
            profileLayout->addWidget(cupLabel);
        }
        if (index == 2) {
            indexLabel->setStyleSheet("font-weight: bold;");
            indexLabel->setStyleSheet("color: grey;");
            //augmenter la police
            QFont font = indexLabel->font();
            font.setPointSize(20);
            indexLabel->setFont(font);
            indexLabel->setAlignment(Qt::AlignCenter);

        }
        if (index == 3) {
            indexLabel->setStyleSheet("font-weight: bold;");
            indexLabel->setStyleSheet("color: #8B4513;");
            //augmenter la police
            QFont font = indexLabel->font();
            font.setPointSize(15);
            indexLabel->setFont(font);

            indexLabel->setAlignment(Qt::AlignCenter);
        }
        if (index > 1){
            profileLayout->addWidget(indexLabel);

        }
        
        

        QLabel *avatarLabel = new QLabel;
        QPixmap avatarPixmap(profile->getAvatarPath());
        avatarLabel->setPixmap(avatarPixmap.scaled(50, 50));
        avatarLabel->setAlignment(Qt::AlignCenter);
        profileLayout->addWidget(avatarLabel);
        
        QLabel *nameLabel = new QLabel(profile->getName());
        nameLabel->setAlignment(Qt::AlignCenter);
        profileLayout->addWidget(nameLabel);
        
        // Affichage du paramètre utilisé pour le tri
        QLabel *parameterLabel = new QLabel();
        parameterLabel->setAlignment(Qt::AlignCenter);
        if (mode == 0) {
            parameterLabel->setText(profile->getRecord(0).toString());
            if (profile->getRecord(0) == QTime(0, 0, -1)) {
                parameterLabel->setText("N/A");
            }
        } else if (mode == 1) {
            parameterLabel->setText(profile->getRecord(1).toString());
            if (profile->getRecord(1) == QTime(0, 0, -1)) {
                parameterLabel->setText("N/A");
            }
        } else if (mode == 2) {
            parameterLabel->setText(profile->getRecord(2).toString());
            if (profile->getRecord(2) == QTime(0, 0, -1)) {
                parameterLabel->setText("N/A");
            }
        } else if (mode == 3) {
            parameterLabel->setText(QString::number(profile->getPartiesJouer()));
        } else if (mode == 4) {
            parameterLabel->setText(QString::number(profile->getPartiesGagner()));
        } else if (mode == 5) {
            parameterLabel->setText(QString::number(profile->getPartiesPerdu()));
        }
        profileLayout->addWidget(parameterLabel);


        QFrame *line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        m_layout->addWidget(line);

        
        // Ajouter le widget du profil au layout principal
        m_layout->addWidget(profileWidget);
        
        // Incrémenter l'index pour chaque profil
        index++;
    }
}

void LeaderboardView::updateListe() {
    profilesSorted.clear();
    QList<Profile*> profiles = profileManager->getProfiles();
    for (int i = 0; i < profiles.size(); ++i) {
        profilesSorted.append(profiles[i]);
    }
}







