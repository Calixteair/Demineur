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

    navbar = new QWidget(this);
    navbar->setFixedHeight(50);
    navbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    navbar->setContentsMargins(0, 0, 0, 0);
    navbar->setObjectName("navbar");
    navbar->setStyleSheet("QWidget#navbar { background-color: rgb(50, 50, 50); }");
    QHBoxLayout *navbarLayout = new QHBoxLayout(navbar);
    QPushButton *homeButton = new QPushButton("Accueil", navbar);
    //homeButton->setStyleSheet("QPushButton { color: white; }");
    QMenu *settingsMenu = new QMenu("Paramètres", navbar);
    settingsMenu->adjustSize();
    //settingsMenu->setStyleSheet("QPushButton { color: white; }");
    QPushButton *helpButton = new QPushButton("Aide", navbar);
    //helpButton->setStyleSheet("QPushButton { color: white; }");
    navbarLayout->addWidget(homeButton);
    navbarLayout->addWidget(settingsMenu);
    navbarLayout->addWidget(helpButton);

    // Définir la navbar comme barre de menus
    setMenuWidget(navbar);

    connect(homeButton, &QPushButton::clicked, this, &MainWindow::openMainWindow);
    connect(helpButton, &QPushButton::clicked, []() {
        RulesDialog dialog;
        dialog.exec();
    });


    // Créer le menu déroulant "Paramètres"

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

    nextSong = new QAction("Next music", this);
    QObject::connect(nextSong, &QAction::triggered, [this]() {
        playlist->next();
    });

    prevSong = new QAction("Previous music", this);
    QObject::connect(prevSong, &QAction::triggered, [this]() {
        playlist->previous();
    });

    settingsMenu->addAction(nextSong);
    settingsMenu->addAction(prevSong);
    



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

    playlist = new QMediaPlaylist(this);
    playlist->addMedia(QUrl("qrc:/music/let-the-games-begin-21858.mp3"));
    playlist->addMedia(QUrl("qrc:/music/neon-gaming-128925.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer(this);
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