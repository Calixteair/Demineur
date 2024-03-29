// ModifyProfileDialog.cpp
#include "headerFiles/Views/ModifyProfileDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QDir>

ModifyProfileDialog::ModifyProfileDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Modifier le profil");

    QVBoxLayout *layout = new QVBoxLayout(this);

    nameLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Nouveau nom :", this));
    layout->addWidget(nameLineEdit);

    QHBoxLayout *avatarLayout = new QHBoxLayout;
    avatarLabel = new QLabel("Sélectionner un nouvel avatar :", this);
    avatarLayout->addWidget(avatarLabel);
    avatarButton = new QPushButton("Parcourir", this);
    connect(avatarButton, &QPushButton::clicked, this, &ModifyProfileDialog::handleAvatarButtonClicked);
    avatarLayout->addWidget(avatarButton);
    layout->addLayout(avatarLayout);
    
    // path to the avatar


    saveButton = new QPushButton("Enregistrer", this);
    connect(saveButton, &QPushButton::clicked, this, [this]() {
        emit profileModified(nameLineEdit->text(), avatarLabel->text());
        close();
    });
    layout->addWidget(saveButton);

    cancelButton = new QPushButton("Annuler", this);
    connect(cancelButton, &QPushButton::clicked, this, &ModifyProfileDialog::close);
    layout->addWidget(cancelButton);
}

void ModifyProfileDialog::handleAvatarButtonClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Sélectionner un avatar", QString(), "Images (*.png *.jpg *.jpeg)");
    if (!filePath.isEmpty()) {
        avatarLabel->setText(filePath);
    }
    else {
        avatarLabel->clear();
    }
}
