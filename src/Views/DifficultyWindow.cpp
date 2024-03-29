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
#include <QLineEdit>
#include <QIntValidator>
#include <QDialogButtonBox>


DifficultyWindow::DifficultyWindow(QWidget *parent) : QWidget(parent)
{
    // Layout principal
    QHBoxLayout *layout = new QHBoxLayout;

     QString buttonStyleEasy = "QPushButton {"
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

    QString buttonStyleMedium = "QPushButton {"
                            "background-color: #FFA500;"
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
                            "background-color: #FF8C00;"
                            "color: white;"
                            "}";

    QString buttonStyleHard = "QPushButton {"
                            "background-color: #f44336;"
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
                            "background-color: #d32f2f;"
                            "color: white;"
                            "}";

    QString buttonStyleCustom = "QPushButton {"
                            "background-color: #008CBA;"
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
                            "background-color: #0077A3;"
                            "color: white;"
                            "}";

    QString buttonStyle = "QPushButton {"

                            "background-color: #ba00b1;"
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
                            "background-color: #8f1389;"
                            "color: white;"
                            "}";

            

    // Boutons de sélection de difficulté
    QPushButton *beginnerButton = new QPushButton("8x8, 10 mines");
    beginnerButton->setStyleSheet(buttonStyleEasy);
    QPushButton *intermediateButton = new QPushButton("16x16, 40 mines");
    intermediateButton->setStyleSheet(buttonStyleMedium);
    QPushButton *expertButton = new QPushButton("30x16, 99 mines");
    expertButton->setStyleSheet(buttonStyleHard);
    QPushButton *customButton = new QPushButton("Personnalisé");
    customButton->setStyleSheet(buttonStyleCustom);
    QPushButton *loadGameButton = new QPushButton("Charger une partie");
    loadGameButton->setStyleSheet(buttonStyle);

    // centrer les boutons verticalement et horizontalement et leur taille minimale et maximale

    beginnerButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    intermediateButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    expertButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    customButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    loadGameButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    beginnerButton->setMinimumSize(200, 50);
    intermediateButton->setMinimumSize(200, 50);
    expertButton->setMinimumSize(200, 50);
    customButton->setMinimumSize(200, 50);
    loadGameButton->setMinimumSize(200, 50);
    
    beginnerButton->setMaximumSize(200, 50);
    intermediateButton->setMaximumSize(200, 50);
    expertButton->setMaximumSize(200, 50);
    customButton->setMaximumSize(200, 50);
    loadGameButton->setMaximumSize(200, 50);
    
    QVBoxLayout *buttonLayout = new QVBoxLayout;

    buttonLayout->addWidget(beginnerButton);
    buttonLayout->addWidget(intermediateButton);
    buttonLayout->addWidget(expertButton);
    buttonLayout->addWidget(customButton);
    buttonLayout->addWidget(loadGameButton);

    buttonLayout->setAlignment(Qt::AlignCenter);





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
    
    layout->addLayout(buttonLayout);


  
    setLayout(layout);
}

void DifficultyWindow::launchDemineurView(int rows, int cols, int mines)
{
    // Émettre le signal pour demander l'affichage de la vue du démineur
    
    emit demineurViewRequested(rows, cols, mines);    
}

void DifficultyWindow::loadGame(QString filePath)
{
    // Implémentez la logique pour charger une partie sauvegardée

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




