#include "RulesDialogue.h"

#include <QVBoxLayout>
#include <QTextBrowser>
#include <QPushButton>

RulesDialog::RulesDialog(QWidget *parent)
    : QDialog(parent)
{
    // Créer un QTextBrowser pour afficher les règles
    rulesTextBrowser = new QTextBrowser(this);
    rulesTextBrowser->setOpenExternalLinks(true);
    rulesTextBrowser->setSource(QUrl("qrc:/rules.html")); // Chemin vers votre fichier HTML contenant les règles

    // Créer un bouton "Fermer"
    QPushButton *closeButton = new QPushButton("Fermer", this);

    // Configuration du layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(rulesTextBrowser);
    layout->addWidget(closeButton);

    // Connexion du signal clicked() du bouton "Fermer" au slot accept() de la boîte de dialogue
    QObject::connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    // Définir le titre de la fenêtre
    setWindowTitle("Règles du démineur");
}