// DifficultyWindow.cpp

#include "../headerFiles/Views/DifficultyWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QLineEdit>
#include <QIntValidator>
#include <QDialogButtonBox>


DifficultyWindow::DifficultyWindow(QWidget *parent) : QWidget(parent)
{
    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout;

     QString buttonStyle = "QPushButton {"
                          "background-color: #4CAF50;"
                          "border: none;"
                          "color: white;"
                          "padding: 10px 24px;"
                          "text-align: center;"
                          "text-decoration: none;"
                          "font-size: 16px;"
                          "margin: 4px 2px;"
                          "border-radius: 8px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #45a049;"
                          "color: white;"
                          "}";

    // Boutons de sélection de difficulté
    QPushButton *beginnerButton = new QPushButton("8x8, 10 mines");
    beginnerButton->setStyleSheet(buttonStyle);
    QPushButton *intermediateButton = new QPushButton("16x16, 40 mines");
    intermediateButton->setStyleSheet(buttonStyle);
    QPushButton *expertButton = new QPushButton("30x16, 99 mines");
    expertButton->setStyleSheet(buttonStyle);
    QPushButton *customButton = new QPushButton("Personnalisé");
    customButton->setStyleSheet(buttonStyle);
    QPushButton *loadGameButton = new QPushButton("Charger une partie");
    loadGameButton->setStyleSheet(buttonStyle);


    connect(beginnerButton, &QPushButton::clicked, this, [=]() {
        launchDemineurView(8, 8, 10);
    });
    connect(intermediateButton, &QPushButton::clicked, this, [=]() {
        launchDemineurView(16, 16, 40);
    });
    connect(expertButton, &QPushButton::clicked, this, [=]() {
        launchDemineurView(16, 30, 99);
    });
    connect(customButton, &QPushButton::clicked, this, &DifficultyWindow::showCustomDialog);




    connect (loadGameButton, &QPushButton::clicked, this, [=]() {
        // Demande un fichier en utilisant QFileDialog pour charger une partie sauvegardée

        QString fileName = QFileDialog::getOpenFileName(this, "Charger une partie", QDir::homePath(), "Fichiers de sauvegarde (*.sav)");

        if (!fileName.isEmpty()) {
            loadGame(fileName);

        }

    });
    layout->addWidget(beginnerButton);
    layout->addWidget(intermediateButton);
    layout->addWidget(expertButton);
    layout->addWidget(customButton);
    layout->addWidget(loadGameButton);
  
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



void DifficultyWindow::showCustomDialog()
{
    QDialog customDialog(this);
    customDialog.setWindowTitle("Configuration personnalisée");

    QVBoxLayout *layout = new QVBoxLayout(&customDialog);

    QLabel *rowsLabel = new QLabel("Lignes:");
    QLineEdit *rowsLineEdit = new QLineEdit(&customDialog);
    QLabel *colsLabel = new QLabel("Colonnes:");
    QLineEdit *colsLineEdit = new QLineEdit(&customDialog);
    QLabel *minesLabel = new QLabel("Mines:");
    QLineEdit *minesLineEdit = new QLineEdit(&customDialog);

    layout->addWidget(rowsLabel);
    layout->addWidget(rowsLineEdit);
    layout->addWidget(colsLabel);
    layout->addWidget(colsLineEdit);
    layout->addWidget(minesLabel);
    layout->addWidget(minesLineEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                                       Qt::Horizontal, &customDialog);
    layout->addWidget(buttonBox);

    // Connexion personnalisée pour activer/désactiver le bouton OK en fonction de la validité des valeurs
    QObject::connect(rowsLineEdit, &QLineEdit::textChanged, [&]() {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(validateInput(rowsLineEdit, colsLineEdit, minesLineEdit));
    });
    QObject::connect(colsLineEdit, &QLineEdit::textChanged, [&]() {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(validateInput(rowsLineEdit, colsLineEdit, minesLineEdit));
    });
    QObject::connect(minesLineEdit, &QLineEdit::textChanged, [&]() {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(validateInput(rowsLineEdit, colsLineEdit, minesLineEdit));
    });

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &customDialog, [&]() {
        if (validateInput(rowsLineEdit, colsLineEdit, minesLineEdit)) {
            customDialog.accept();
        }
    });
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &customDialog, &QDialog::reject);

    if (customDialog.exec() == QDialog::Accepted) {
        int rows = rowsLineEdit->text().toInt();
        int cols = colsLineEdit->text().toInt();
        int mines = minesLineEdit->text().toInt();
        launchDemineurView(rows, cols, mines);
    }
}

bool DifficultyWindow::validateInput(QLineEdit *rowsLineEdit, QLineEdit *colsLineEdit, QLineEdit *minesLineEdit)
{
    bool ok;
    int rows = rowsLineEdit->text().toInt(&ok);
    if (!ok || rows < 4 || rows > 100) {
        return false;
    }

    int cols = colsLineEdit->text().toInt(&ok);
    if (!ok || cols < 4 || cols > 100) {
        return false;
    }

    int maxMines = rows * cols - 9;
    int mines = minesLineEdit->text().toInt(&ok);
    if (!ok || mines < 1 || mines > maxMines) {
        return false;
    }

    return true;
}




