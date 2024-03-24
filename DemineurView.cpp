#include <QMessageBox>
#include <QIcon>
#include <QSize>
#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QString> // Add this line if not included
#include <QScrollArea>
#include <QPushButton>
#include <QMouseEvent> // Ajout de l'inclusion pour utiliser QMouseEvent
#include "DemineurView.h"



DemineurView::DemineurView(QString filePath, QWidget *parent) :
    QWidget(parent), demineur(new Demineur(filePath.toStdString().c_str()))
{  


    int rows = demineur->getNbLignes();
    int cols = demineur->getNbColonnes();    

    //bouton pour sauvegarder la partie

    QPushButton *saveButton = new QPushButton("Sauvegarder la partie", this);

    connect(saveButton, &QPushButton::clicked, this, [=]() {

        QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder la partie", "~", "Fichiers de sauvegarde (*.sav)");
        if (!fileName.isEmpty()) {
            demineur->sauvegarderGame(fileName.toStdString().c_str());
        }
    });

      QVBoxLayout *layout = new QVBoxLayout(this);

      layout->addWidget(saveButton);   

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    


    QWidget *scrollWidget = new QWidget;
    gridLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(gridLayout);

    scrollArea->setWidget(scrollWidget);

    
    layout->addWidget(scrollArea);



    //Verifier si la grille est plus grande que la taille de la fenêtre
    if (rows * 50 > 1080 || cols * 50 > 1920) {
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
   


    // Définir une taille fixe pour la grille en fonction du nombre de lignes et de colonnes
    int gridSizeX = cols * 50; // 50 pixels par bouton
    int gridSizeY = rows * 50; // 50 pixels par bouton
    scrollWidget->setFixedSize(gridSizeX, gridSizeY);



    // Désactiver le redimensionnement automatique de la fenêtre principale

    createGrid(rows, cols);
    updateGrid();
    

}




DemineurView::DemineurView(int rows, int cols, int mines, QWidget *parent) :
    QWidget(parent), demineur(new Demineur(rows, cols, mines))
{
    
   
    QPushButton *saveButton = new QPushButton("Sauvegarder la partie", this);

    connect(saveButton, &QPushButton::clicked, this, [=]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder la partie", QDir::homePath(), "Fichiers de sauvegarde (*.sav)");
        if (!fileName.isEmpty()) {
            demineur->sauvegarderGame(fileName.toStdString().c_str());
        }
    });

      QVBoxLayout *layout = new QVBoxLayout(this);

      layout->addWidget(saveButton);   

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    


    QWidget *scrollWidget = new QWidget;
    gridLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(gridLayout);

    scrollArea->setWidget(scrollWidget);

    
    layout->addWidget(scrollArea);



    //Verifier si la grille est plus grande que la taille de la fenêtre
    if (rows * 50 > 1080 || cols * 50 > 1920) {
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
   


    // Définir une taille fixe pour la grille en fonction du nombre de lignes et de colonnes
    int gridSizeX = cols * 50; // 50 pixels par bouton
    int gridSizeY = rows * 50; // 50 pixels par bouton
    scrollWidget->setFixedSize(gridSizeX, gridSizeY);



    // Désactiver le redimensionnement automatique de la fenêtre principale

    createGrid(rows, cols);


}

void DemineurView::createGrid(int nbLigne, int nbColonne) {
    for(int i = 0; i < nbLigne; i++) {
        for(int j = 0; j < nbColonne; j++) {
            QPushButton *button = new QPushButton;
            button->setFixedSize(50, 50);
            button->setStyleSheet("QPushButton {"
                                   "background-color: #bdbdbd;"
                                   "border-style: outset;"
                                   "border-width: 1px;"
                                   "border-radius: 0px;"
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
                    button->setText( QString::number(j) + "," + QString::number(i));

            buttons.push_back(button);
            connect(button, &QPushButton::clicked, this, [this, j, i] {

                play(j, i); // Jouer lorsque le clic gauche est détecté
            });
        }
    }
}

void DemineurView::mousePressEvent(QMouseEvent *event) {
        QPushButton *clickedButton = qobject_cast<QPushButton*>(childAt(event->pos()));
    if (clickedButton && buttons.contains(clickedButton)) {
        int index = buttons.indexOf(clickedButton);
        int row = index / demineur->getNbColonnes();
        int col = index % demineur->getNbColonnes();

        // Utilisez le paramètre event pour obtenir le bouton de la souris
        if (event->button() == Qt::RightButton) {
            marquerCase(col, row);
        } 
    }

    // Vous n'avez pas besoin d'appeler la méthode event() ici.
    // La gestion de l'événement sera effectuée automatiquement par le système.
    // Appelez simplement la méthode de la classe de base pour traiter l'événement.
    QWidget::mousePressEvent(event);
}



void DemineurView::updateGrid() {
    for(int i = 0; i < demineur->getNbLignes(); i++) {
        for(int j = 0; j < demineur->getNbColonnes(); j++) {
            updateButton(j, i);
        }
    }
}

void DemineurView::ResetGame() {
    demineur->resetGame();
     for(int i = 0; i < demineur->getNbLignes() ; i++) {
        for(int j = 0; j < demineur->getNbColonnes(); j++) {
            QPushButton *button = buttons[i * demineur->getNbColonnes() + j];
            button->setFixedSize(50, 50);
            button->setStyleSheet("QPushButton {"
                                   "background-color: #bdbdbd;"
                                   "border-style: outset;"
                                   "border-width: 1px;"
                                   "border-radius: 0px;"
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
        button->setText("");
        button->setIcon(QIcon());

        

        }
        }
    
}

void DemineurView::updateButton(int x, int y) {
    QPushButton *button = buttons[y * demineur->getNbColonnes() + x];
    int cellState = demineur->getCellState(x, y);
    int cellValue = demineur->getCellValue(x, y);

    if(cellState == 0) {
        button->setText("");
        button->setIcon(QIcon()); // Efface l'icône
    } else if(cellState == 1 && cellValue != -1) {
         QString backgroundColor;
        switch (cellValue) {
            case 1:
                backgroundColor = "#ADD8E6"; // Blue
                break;
            case 2:
                backgroundColor = "#90EE90"; // Green
                break;
            case 3:
                backgroundColor = "#FFA07A"; // Light Coral
                break;
            case 4:
                backgroundColor = "#FFB6C1"; // Light Pink
                break;
            case 5:
                backgroundColor = "#FFD700"; // Gold
                break;
            case 6:
                backgroundColor = "#20B2AA"; // Light Sea Green
                break;
            case 7:
                backgroundColor = "#87CEEB"; // Sky Blue
                break;
            case 8:
                backgroundColor = "#C0C0C0"; // Silver
                break;
            default:
                backgroundColor = "#FFFFFF"; // White
        }
        button->setStyleSheet(QString("QPushButton {"
                                       "background-color: %1;" // Couleur différente pour chaque chiffre
                                       "border-style: outset;"
                                       "border-width: 1px;"
                                       "border-radius: 0px;"
                                       "border-color: beige;"
                                       "font: bold 14px;"
                                       "padding: 6px;"
                                       "}").arg(backgroundColor));
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
    // Show all cells to reveal the full grid
    showAll();
    
    // Display a message box indicating the win
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Gagné", "Vous avez gagné ! Voulez-vous rejouer ?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ResetGame();
    } else {
        // If the user chooses not to replay, go back to the main menu
        // Implement the functionality to go back to the main menu here

        emit BackToMain();
    }
}

void DemineurView::showLoose() {
    // Show all cells to reveal the full grid
    showAll();
    
    // Display a message box indicating the loss
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Perdu", "Vous avez perdu ! Voulez-vous rejouer ?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
                ResetGame();
    } else {
        // If the user chooses not to replay, go back to the main menu
        // Implement the functionality to go back to the main menu here
                emit BackToMain();

    }
}

