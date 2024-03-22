// MainWindow.cpp
#include "MainWindow.h"
#include "DifficultyWindow.h"
#include "RulesDialogue.h"
#include "MainMenu.h"
#include <QStackedWidget>
#include <QDebug>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
#include <QSlider>
#include <QWidgetAction>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Création du menu principal
    mainMenu = new MainMenu(this);

    // navbar
    QWidget *navbar = new QWidget;
    QHBoxLayout *navbarLayout = new QHBoxLayout;
    QPushButton *homeButton = new QPushButton("Accueil");
    QPushButton *helpButton = new QPushButton("Aide");
    navbarLayout->addWidget(homeButton);
    
    navbarLayout->addWidget(helpButton);
    navbar->setLayout(navbarLayout);
    setMenuWidget(navbar);

    connect(homeButton, &QPushButton::clicked, this, &MainWindow::openMainWindow);
    connect(helpButton, &QPushButton::clicked, []() {
        RulesDialog dialog;
        dialog.exec();
    });


    // Créer le menu déroulant "Paramètres"
    settingsMenu = new QMenu("Paramètres", this);

    // Créer l'action "Mute"
    muteAction = new QAction("Mute", this);
    muteAction->setCheckable(true);
    muteAction->setChecked(false);
    QObject::connect(muteAction, &QAction::triggered, this, &MainWindow::toggleMute);
    settingsMenu->addAction(muteAction);

    // Créer le contrôle du volume
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    QObject::connect(volumeSlider, &QSlider::valueChanged, this, &MainWindow::setVolume);

    // Créer une action pour le curseur de volume
    QWidgetAction *volumeAction = new QWidgetAction(this);
    volumeAction->setDefaultWidget(volumeSlider);

    // Ajouter l'action du curseur de volume au menu déroulant
    settingsMenu->addAction(volumeAction);

    QMenuBar *menuBar = new QMenuBar;
    menuBar->addMenu(settingsMenu);

    navbarLayout->addWidget(menuBar);
    

    // Widget central
    stackedWidget = new QStackedWidget;
    difficultyWindow = new DifficultyWindow;
    stackedWidget->addWidget(mainMenu);
    stackedWidget->addWidget(difficultyWindow);
    setCentralWidget(stackedWidget);

    // Taille de la fenêtre
    resize(400, 300);

    // Musique de fond

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/let-the-games-begin-21858.mp3"));
    playlist->addMedia(QUrl("qrc:/music/neon-gaming-128925.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();

    // Connexion des signaux et des slots
    QObject::connect(mainMenu, &MainMenu::playClicked, this, &MainWindow::openDifficultyWindow);
    QObject::connect(mainMenu, &MainMenu::profileClicked, this, &MainWindow::openProfileWindow);
    QObject::connect(mainMenu, &MainMenu::leaderboardClicked, this, &MainWindow::openLeaderboardWindow);
}

MainWindow::~MainWindow()
{
    delete playlist;
    delete music;
}

void MainWindow::openDifficultyWindow()
{
    qDebug() << "Ouverture de la fenêtre de sélection de difficulté";
    stackedWidget->setCurrentWidget(difficultyWindow);
}

void MainWindow::openProfileWindow()
{
    qDebug() << "Ouverture de la fenêtre de profil";
}

void MainWindow::openLeaderboardWindow()
{
    qDebug() << "Ouverture de la fenêtre de leaderboard";
}

void MainWindow::openMainWindow()
{
    qDebug() << "Ouverture de la fenêtre de jeu";
    stackedWidget->setCurrentWidget(mainMenu);
}

void MainWindow::toggleMute()
{
    qDebug() << "Mute activé : " << muteAction->isChecked();
    music->setMuted(muteAction->isChecked());
}

void MainWindow::setVolume(int volume)
{
    
    qDebug() << "Volume réglé à " << volume;
    // Ici, implémentez la logique pour régler le volume de la musique de fond

    music->setVolume(volume);


}