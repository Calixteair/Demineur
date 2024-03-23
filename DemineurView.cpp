#include <QMessageBox>
#include <QIcon>
#include <QScrollArea>
#include <QPushButton>
#include <QMouseEvent> // Ajout de l'inclusion pour utiliser QMouseEvent
#include "DemineurView.h"

DemineurView::DemineurView(int rows, int cols, int mines, QWidget *parent) :
    QWidget(parent), demineur(new Demineur(rows, cols, mines))
{
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget;
    gridLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(gridLayout);

    scrollArea->setWidget(scrollWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    createGrid(rows, cols);
}

void DemineurView::createGrid(int nbLigne, int nbColonne) {
    for(int i = 0; i < nbLigne; i++) {
        for(int j = 0; j < nbColonne; j++) {
            QPushButton *button = new QPushButton;
            button->setFixedSize(50, 50);
            button->setStyleSheet("QPushButton {"
                                   "background-color: #858585;"
                                   "border-style: outset;"
                                   "border-width: 2px;"
                                   "border-radius: 10px;"
                                   "border-color: beige;"
                                   "font: bold 14px;"
                                   "padding: 6px;"
                                   "}"
                                   "QPushButton:hover {"
                                   "background-color: #969595;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "background-color: #807e7e;"
                                   "}");

            gridLayout->addWidget(button, i, j);
            buttons.push_back(button);
            connect(button, &QPushButton::clicked, this, [this, i, j] {
                play(i, j); // Jouer lorsque le clic gauche est détecté
            });
        }
    }
}

void DemineurView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QPushButton *clickedButton = qobject_cast<QPushButton*>(childAt(event->pos()));
        if (clickedButton && buttons.contains(clickedButton)) {
            int index = buttons.indexOf(clickedButton);
            int row = index / demineur->getNbColonnes();
            int col = index % demineur->getNbColonnes();
            marquerCase(row, col);
        }
    }
    QWidget::mousePressEvent(event);
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
    int cellState = demineur->getCellState(x, y);
    int cellValue = demineur->getCellValue(x, y);
    if(cellState == 0) {
        button->setText("");
        button->setIcon(QIcon()); // Efface l'icône
    } else if(cellState == 1 && cellValue != -1) {
        button->setStyleSheet("QPushButton {"
                                   "background-color: #c0c0c0;"
                                   "border-style: outset;"
                                   "border-width: 2px;"
                                   "border-radius: 10px;"
                                   "border-color: beige;"
                                   "font: bold 14px;"
                                   "padding: 6px;"
                                   "}"
                                   "QPushButton:hover {"
                                   "background-color: #dcdcdc;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "background-color: #b0b0b0;"
                                   "}");
        int cellValue = demineur->getCellValue(x, y);
        button->setText(QString::number(cellValue));
        button->setIcon(QIcon()); // Efface l'icône
    } else if ( cellState == 1 && cellValue == -1) {
        QIcon icon("img/mine2.png");
        QSize buttonSize = button->size(); // Taille du bouton
        QSize iconSize(buttonSize.width() * 0.8, buttonSize.height() * 0.8); // Taille de l'icône (80% de la taille du bouton)
        button->setIconSize(iconSize); // Définition de la taille de l'icône
        button->setIcon(icon); // Utilisation d'une icône pour la bombe

    }
    else if(cellState == 2) {
        QIcon icon("img/marker.png");
        QSize buttonSize = button->size(); // Taille du bouton
        QSize iconSize(buttonSize.width() * 0.8, buttonSize.height() * 0.8); // Taille de l'icône (80% de la taille du bouton)
        button->setIconSize(iconSize); // Définition de la taille de l'icône
        button->setIcon(icon); // Utilisation d'une icône pour le drapeau
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
