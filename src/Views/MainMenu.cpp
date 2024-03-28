// MainMenu.cpp
#include "../headerFiles/Views/MainMenu.h"
#include "../headerFiles/Views/ProfileList.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QPixmap>
#include <QUrl>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Centrer les éléments dans le layout

    // image de du logo
    QLabel *logo = new QLabel(this);
    QPixmap logoPixmap(":/img/mine.png");
    logo->setPixmap(logoPixmap.scaled(200, 200, Qt::KeepAspectRatio)); // Redimensionner l'image du logo
    logo->setAlignment(Qt::AlignCenter); // Centrer l'image dans le layout
    layout->addWidget(logo);

    playButton = new QPushButton("Jouer en solo", this);
    profileButton = new QPushButton("Profil", this);
    leaderboardButton = new QPushButton("Leaderboard", this);

     playButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px 24px; text-align: center; text-decoration: none; font-size: 16px; margin: 4px 2px;  border-radius: 12px; }");
    profileButton->setStyleSheet("QPushButton { background-color: #008CBA; color: white; border: none; padding: 10px 24px; text-align: center; text-decoration: none;  font-size: 16px; margin: 4px 2px;  border-radius: 12px; }");
    leaderboardButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; border: none; padding: 10px 24px; text-align: center; text-decoration: none;  font-size: 16px; margin: 4px 2px; border-radius: 12px; }");


   

    layout->addWidget(playButton);
    layout->addWidget(profileButton);
    layout->addWidget(leaderboardButton);

    QObject::connect(playButton, &QPushButton::clicked, this, &MainMenu::onPlayButtonClicked);
    QObject::connect(profileButton, &QPushButton::clicked, this, &MainMenu::onProfileButtonClicked);
    QObject::connect(leaderboardButton, &QPushButton::clicked, this, &MainMenu::onLeaderboardButtonClicked);

}


void MainMenu::onPlayButtonClicked()
{
    // Implémentez votre fonctionnalité lorsque le bouton "Jouer en solo" est cliqué
    qDebug() << "Ouverture de la fenêtre de sélection de difficulté";
    emit playClicked();
}

void MainMenu::onProfileButtonClicked()
{
    // Implémentez votre fonctionnalité lorsque le bouton "Profil" est cliqué
    qDebug() << "Ouverture de la fenêtre de profil";
    emit profileClicked();
}

void MainMenu::onLeaderboardButtonClicked()
{
    // Implémentez votre fonctionnalité lorsque le bouton "Leaderboard" est cliqué
    qDebug() << "Ouverture du leaderboard";
    emit leaderboardClicked();
}