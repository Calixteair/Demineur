// MainWindow.cpp
#include "MainWindow.h"
#include "DifficultyWindow.h"
#include "MainMenu.h"
#include <QStackedWidget>
#include <QDebug>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Création du menu principal
    mainMenu = new MainMenu(this);

    // navbar
    QWidget *navbar = new QWidget;
    QHBoxLayout *navbarLayout = new QHBoxLayout;
    QPushButton *homeButton = new QPushButton("Accueil");
    QPushButton *settingsButton = new QPushButton("Paramètres");
    QPushButton *helpButton = new QPushButton("Aide");
    navbarLayout->addWidget(homeButton);
    navbarLayout->addWidget(settingsButton);
    navbarLayout->addWidget(helpButton);
    navbar->setLayout(navbarLayout);
    setMenuWidget(navbar);

    connect(homeButton, &QPushButton::clicked, this, &MainWindow::openMainWindow);

    // Widget central
    stackedWidget = new QStackedWidget;
    difficultyWindow = new DifficultyWindow;
    stackedWidget->addWidget(mainMenu);
    stackedWidget->addWidget(difficultyWindow);
    setCentralWidget(stackedWidget);

    // Taille de la fenêtre
    resize(400, 300);

    QObject::connect(mainMenu, &MainMenu::playClicked, this, &MainWindow::openDifficultyWindow);
    QObject::connect(mainMenu, &MainMenu::profileClicked, this, &MainWindow::openProfileWindow);
    QObject::connect(mainMenu, &MainMenu::leaderboardClicked, this, &MainWindow::openLeaderboardWindow);
}

MainWindow::~MainWindow()
{
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
