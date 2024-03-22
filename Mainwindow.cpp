// mainwindow.cpp
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout;

    // Titre
    QLabel *titleLabel = new QLabel("Démineur");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Logo
    QLabel *logoLabel = new QLabel;
    QPixmap logoPixmap(":/img/mine.png"); // Chemin vers votre image
    logoLabel->setPixmap(logoPixmap);
    logoLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(logoLabel);

    // Boutons du menu
    QPushButton *playButton = new QPushButton("Jouer en solo");
    layout->addWidget(playButton);

    QPushButton *profileButton = new QPushButton("Profil");
    layout->addWidget(profileButton);

    QPushButton *leaderboardButton = new QPushButton("Leaderboard");
    layout->addWidget(leaderboardButton);

    // Widget central
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}
