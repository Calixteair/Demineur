// difficultywindow.cpp
#include "DifficultyWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

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
    difficultyLayout->addWidget(beginnerButton);
    difficultyLayout->addWidget(intermediateButton);
    difficultyLayout->addWidget(expertButton);
    difficultyLayout->addWidget(customButton);
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
