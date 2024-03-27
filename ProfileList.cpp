#include "ProfileList.h"
#include "ProfileManager.h" // Assurez-vous d'inclure le ProfileManager
#include <QListWidgetItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QList>
#include <QDebug>
#include <QHBoxLayout>

#include <QVBoxLayout>


ProfileList::ProfileList(ProfileManager* profileManager, QWidget *parent) : QWidget(parent), profileManager(profileManager)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    profileListView = new QListWidget(this);
    connect(profileListView, &QListWidget::itemClicked, this, &ProfileList::handleProfileItemClicked);
    layout->addWidget(profileListView);

    addButton = new QPushButton("Add Profile", this);
    connect(addButton, &QPushButton::clicked, this, &ProfileList::handleAddProfileClicked);
    layout->addWidget(addButton);

    deleteButton = new QPushButton("Delete Profile", this);
    connect(deleteButton, &QPushButton::clicked, this, &ProfileList::handleDeleteProfileClicked);
    layout->addWidget(deleteButton);
    profiles = profileManager->getProfiles();
    loadProfiles(); // Charge les profils existants
}

void ProfileList::loadProfiles()
{
    QList<Profile*> loadedProfiles = profileManager->getProfiles();
    qDebug() << "Loaded profiles: " << loadedProfiles.size();
    for (Profile* profile : loadedProfiles) {
        addProfile(profile);
    }
}

void ProfileList::addProfile(Profile *profile)
{
    profiles.append(profile);

    qDebug() << profile->getName();
    qDebug() << profile->getAvatarPath();
    qDebug() << profile->getEasyRecord();

    // Créer une nouvelle QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(profileListView);

    // Créer un widget personnalisé pour contenir l'avatar, le nom et le record
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(widget);

    // Charger l'image de l'avatar
    QPixmap avatarPixmap(profile->getAvatarPath());
    avatarPixmap = avatarPixmap.scaled(64, 64, Qt::KeepAspectRatio); // Redimensionner l'avatar si nécessaire

    // Créer un QLabel pour afficher l'avatar
    QLabel *avatarLabel = new QLabel();
    avatarLabel->setPixmap(avatarPixmap);

    // Ajouter l'avatar au layout
    layout->addWidget(avatarLabel);

    // Créer un QLabel pour afficher le nom du profil
    QLabel *nameLabel = new QLabel(profile->getName());
    layout->addWidget(nameLabel);

    // Créer un QLabel pour afficher le record
    int recordEasy = profile->getEasyRecord();
    QLabel *recordLabel = new QLabel(QString("Record: %1").arg(recordEasy));
    layout->addWidget(recordLabel);

    // Définir le layout comme widget de l'item
    item->setSizeHint(QSize(100, 100)); // Définir la taille de l'élément
    profileListView->setItemWidget(item, widget);

    // Ajouter l'élément à la QListWidget
    profileListView->addItem(item);
}
void ProfileList::deleteSelectedProfile()
{
    int selectedIndex = profileListView->currentRow();
    if (selectedIndex >= 0 && selectedIndex < profiles.size()) {
        Profile *profile = profiles.takeAt(selectedIndex);
        delete profileListView->takeItem(selectedIndex);
        delete profile;
    } else {
        QMessageBox::warning(this, "Error", "No profile selected.");
    }
}

Profile* ProfileList::getSelectedProfile() const
{
    int selectedIndex = profileListView->currentRow();
    if (selectedIndex >= 0 && selectedIndex < profiles.size()) {
        return profiles.at(selectedIndex);
    }
    return nullptr;
}

void ProfileList::handleProfileItemClicked()
{
    Profile *selectedProfile = getSelectedProfile();
    if (selectedProfile) {
        emit profileSelected(selectedProfile);
    }
}

void ProfileList::handleAddProfileClicked()
{
    QString name = QInputDialog::getText(this, "Enter Profile Name", "Name:");
    if (name.isEmpty()) {
        return;
    }

    QString avatarPath = QFileDialog::getOpenFileName(this, "Select Avatar Image", QString(), "Images (*.png *.jpg *.jpeg)");
    if (avatarPath.isEmpty()) {
        return;
    }
    qDebug() << "Avatar path: " << avatarPath;

    QPixmap avatar(avatarPath);
    if (avatar.isNull()) {
        QMessageBox::warning(this, "Error", "Failed to load avatar image.");
        return;
    }

    Profile *newProfile = new Profile(name, avatarPath);
    profileManager->addProfile(newProfile); // Ajoute le nouveau profil au ProfileManager
    profileManager->saveProfiles(newProfile); // Sauvegarde les profils
    addProfile(newProfile);
}

void ProfileList::handleDeleteProfileClicked()
{
    
    profileManager->removeProfile(getSelectedProfile()); // Supprime le profil du ProfileManager
    deleteSelectedProfile();
}
