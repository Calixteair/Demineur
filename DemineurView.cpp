#include <QMessageBox> // Ajout de l'inclusion pour utiliser QMessageBox
#include "DemineurView.h"

DemineurView::DemineurView(int rows, int cols, int mines, QWidget *parent) :
    QWidget(parent), demineur(new Demineur(rows, cols, mines))
{
    gridLayout = new QGridLayout;
    setLayout(gridLayout);
    createGrid(rows, cols);
}



void DemineurView::createGrid(int nbLigne, int nbColonne) {
    for(int i = 0; i < nbLigne; i++) {
        for(int j = 0; j < nbColonne; j++) {
            QPushButton *button = new QPushButton;
            button->setFixedSize(50, 50);
            gridLayout->addWidget(button, i, j);
            buttons.push_back(button);
            QObject::connect(button, &QPushButton::clicked, [this, i, j]() {
                play(i, j);
            });
            QObject::connect(button, &QPushButton::clicked, [this, i, j]() { // Correction du signal connecté
                marquerCase(i, j);
            });
        }
    }
}

void DemineurView::updateGrid() {
    for(int i = 0; i < demineur->getNbLignes(); i++) {
        for(int j = 0; j < demineur->getNbColonnes(); j++) {
            updateButton(i, j);
        }
    }
}

void DemineurView::updateButton(int x, int y) {
    QPushButton *button = buttons[x * demineur->getNbColonnes() + y];
    if(demineur->getCellState(x,y) == 0) {
        button->setText("");
    } else if(demineur->getCellState(x,y) == 1) {
        button->setText(QString::number(demineur->getCellValue(x,y)));
    } else if(demineur->getCellState(x,y) == 2) {
        button->setText("F");
    }
}

void DemineurView::play(int x, int y) {
    if(demineur->play(x, y)) {
        updateGrid();
    } else {
        if(demineur->getState() == Demineur::GAGNE) {
            showWin();
        } else {
            showLoose();
        }
    }
}

void DemineurView::marquerCase(int x, int y) {
    demineur->marquerCase(x, y);
    updateButton(x, y);
}

void DemineurView::showAll() {
    demineur->showAll();
    updateGrid();
}

void DemineurView::showWin() {
    showAll();
    QMessageBox::information(this, "Gagné", "Vous avez gagné !");
}

void DemineurView::showLoose() {
    showAll();
    QMessageBox::information(this, "Perdu", "Vous avez perdu !");
}
