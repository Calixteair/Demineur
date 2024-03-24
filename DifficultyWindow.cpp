// DifficultyWindow.cpp

#include "DifficultyWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QDebug>

DifficultyWindow::DifficultyWindow(QWidget *parent) : QWidget(parent)
{
    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout;

    // Boutons de sélection de difficulté
    QHBoxLayout *difficultyLayout = new QHBoxLayout;
    QPushButton *beginnerButton = new QPushButton("8x8, 10 mines");
    QPushButton *intermediateButton = new QPushButton("16x16, 40 mines");
    QPushButton *expertButton = new QPushButton("30x16, 99 mines");
    QPushButton *customButton = new QPushButton("Personnalisé");
    QPushButton *loadGameButton = new QPushButton("Charger une partie");

    connect(beginnerButton, &QPushButton::clicked, this, [=]() {
        launchDemineurView(8, 8, 10);
    });
    connect(intermediateButton, &QPushButton::clicked, this, [=]() {
        launchDemineurView(16, 16, 40);
    });
    connect(expertButton, &QPushButton::clicked, this, [=]() {
        launchDemineurView(30, 16, 99);
    });
    connect(customButton, &QPushButton::clicked, this, [=]() {
        // Mettez en œuvre la logique pour permettre à l'utilisateur de définir une configuration personnalisée
    });

    connect (loadGameButton, &QPushButton::clicked, this, [=]() {
        // Demande un fichier en utilisant QFileDialog pour charger une partie sauvegardée

        QString fileName = QFileDialog::getOpenFileName(this, "Charger une partie", QDir::homePath(), "Fichiers de sauvegarde (*.sav)");

        if (!fileName.isEmpty()) {
            loadGame(fileName);

        }

    });

    difficultyLayout->addWidget(beginnerButton);
    difficultyLayout->addWidget(intermediateButton);
    difficultyLayout->addWidget(expertButton);
    difficultyLayout->addWidget(customButton);
    difficultyLayout->addWidget(loadGameButton);

    layout->addLayout(difficultyLayout);

    // Bouton basculant pour la limite de temps
    QHBoxLayout *timeLimitLayout = new QHBoxLayout;
    QLabel *timeLimitLabel = new QLabel("Limite de temps:");
    QCheckBox *timeLimitCheckbox = new QCheckBox;
    timeLimitLayout->addWidget(timeLimitLabel);
    timeLimitLayout->addWidget(timeLimitCheckbox);
    layout->addLayout(timeLimitLayout);

    setLayout(layout);
}

void DifficultyWindow::launchDemineurView(int rows, int cols, int mines)
{
    // Émettre le signal pour demander l'affichage de la vue du démineur
    
    emit demineurViewRequested(rows, cols, mines);    
    qDebug() << "Lancement de la vue du démineur";
}

void DifficultyWindow::loadGame(QString filePath)
{
    // Implémentez la logique pour charger une partie sauvegardée
    qDebug() << "Chargement de la partie à partir de: " << filePath;

    emit demineurViewRequestedWithFile(filePath);

}


