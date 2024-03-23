// MainMenu.cpp
#include "MainMenu.h"
#include "ProfileList.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QPixmap>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    // image de du logo
    QLabel *logo = new QLabel;
    QPixmap logoPixmap("img/mine.png");
    logo->setPixmap(logoPixmap);
    layout->addWidget(logo);

    playButton = new QPushButton("Jouer en solo", this);
    profileButton = new QPushButton("Profil", this);
    leaderboardButton = new QPushButton("Leaderboard", this);


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