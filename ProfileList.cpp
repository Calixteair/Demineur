#include "ProfileList.h"
#include "ProfileManager.h" // Assurez-vous d'inclure le ProfileManager
#include <QListWidgetItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QPixmap>
#include <QListWidget>
#include <QPushButton>
#include <QList>
#include <QDebug>

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
    QListWidgetItem *item = new QListWidgetItem(profile->getName(), profileListView);
    item->setData(Qt::UserRole, QVariant::fromValue(profile));
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
    deleteSelectedProfile();
}
