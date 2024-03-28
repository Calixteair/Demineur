#include "headerFiles/Views/ProfileList.h"
#include "headerFiles/Controllers/ProfileManager.h" // Assurez-vous d'inclure le ProfileManager
#include "headerFiles/Models/Profile.h"
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
#include <QCheckBox>
#include <QDialog>

#include <QVBoxLayout>


ProfileList::ProfileList(ProfileManager* profileManager, QWidget *parent) : QWidget(parent), profileManager(profileManager)
{
    QString buttonStylePlay = "QPushButton {"
                        "background-color: #2ECC71;" // vert
                        "border: 1px solid #2ECC71;"
                        "border-radius: 5px;"
                        "color: white;" // Couleur du texte blanc
                        "padding: 5px 10px;"
                        "}"
                        "QPushButton:hover {"
                        "background-color: #27AE60;" 
                        "}"
                        "QPushButton:disabled {" 
                        "background-color: #dcdcdc;" // Gris clair
                        "border-color: #dcdcdc;" // Gris clair
                        "color: #a0a0a0;" // Couleur du texte grise
                        "}";

    QString buttonStyle = "QPushButton {"
                        "background-color: #f0f0f0;"
                        "border-style: solid;"
                        "border-width: 2px;" 
                        "border-color: #c0c0c0;" 
                        "border-radius: 5px;" 
                        "padding: 5px 10px;"
                        "}"
                        //hover
                        "QPushButton:hover {"
                        "background-color: #e0e0e0;" 
                        "border-color: #a0a0a0;" 
                        "}"
                        "QPushButton:disabled {" 
                        "background-color: #dcdcdc;" // Gris clair
                        "border-color: #dcdcdc;" // Gris clair
                        "color: #a0a0a0;" 
                        "}"; 

    QVBoxLayout *layout = new QVBoxLayout(this);
    dialog = new ModifyProfileDialog(this);

    profileListView = new QListWidget(this);
    connect(profileListView, &QListWidget::itemClicked, this, &ProfileList::handleProfileItemClicked);
    layout->addWidget(profileListView);

    QHBoxLayout *bottomLeftLayout = new QHBoxLayout;
    addButton = new QPushButton("Add Profile", this);
    deleteButton = new QPushButton("Delete Profile", this);
    
    QHBoxLayout *bottomRightLayout = new QHBoxLayout;
    playButton = new QPushButton("Jouer", this);
    modifyProfileButton = new QPushButton("Modifier le profil", this);
 
    playButton->setStyleSheet(buttonStylePlay);
    deleteButton->setStyleSheet(buttonStyle);
    addButton->setStyleSheet(buttonStyle);
    modifyProfileButton->setStyleSheet(buttonStyle);

    bottomLeftLayout->addWidget(addButton);
    bottomLeftLayout->addWidget(deleteButton);
    bottomRightLayout->addWidget(modifyProfileButton);
    bottomRightLayout->addWidget(playButton);

    layout->addLayout(bottomLeftLayout);
    layout->addLayout(bottomRightLayout);

    connect(deleteButton, &QPushButton::clicked, this, &ProfileList::handleDeleteProfileClicked);
    connect(addButton, &QPushButton::clicked, this, &ProfileList::handleAddProfileClicked);
    QObject::connect(playButton, &QPushButton::clicked, this, &ProfileList::handlePlayButtonClicked);
    QObject::connect(modifyProfileButton, &QPushButton::clicked, this, &ProfileList::handleModifyProfileButtonClicked);
    QObject::connect(dialog, &ModifyProfileDialog::profileModified, this, &ProfileList::modifyProfile);

    profiles = profileManager->getProfiles();    
    updatePlayButtonState();
    loadProfiles(); // Charge les profils existants

}

void ProfileList::loadProfiles()
{
    QList<Profile*> loadedProfiles = profileManager->getProfiles();
    profiles.clear();

    // Effacer les éléments de la QListWidget
    profileListView->clear();

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
    QTime recordEasy = profile->getRecord(1);
    QLabel *recordLabel = new QLabel(QString("Record: %1").arg(recordEasy.toString("hh:mm:ss")));
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

Profile* ProfileList::getSelectedProfile()
{
    int selectedIndex = profileListView->currentRow();
    if (selectedIndex >= 0 && selectedIndex < profiles.size()) {
        profileManager->profileSelected = true;
        updatePlayButtonState();
        return profiles.at(selectedIndex);
    }
    profileManager->profileSelected = false;
    updatePlayButtonState();
    return nullptr;
}

void ProfileList::handleProfileItemClicked()
{
    qDebug() << "Profile item clicked";
    Profile *selectedProfile = getSelectedProfile();
    if (selectedProfile) {
        emit profileSelected(selectedProfile);
        profileManager->curentProfile = selectedProfile;
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
    
    profileManager->removeProfile(getSelectedProfile());
    deleteSelectedProfile();
}

void ProfileList::handlePlayButtonClicked()
{
    qDebug() << "Play button clicked";
    if (profileManager->profileSelected)
    {
        // Lancer le jeu avec le profil sélectionné
        
        qDebug() << "Selected profile: " << profileManager->curentProfile->getName();
        emit playClicked();
    }
    else
    {
        QMessageBox::warning(this, "Error", "No profile selected.");
    }
}


void ProfileList::updatePlayButtonState()
{
    if (profileManager->profileSelected) {
        playButton->setEnabled(true);
        modifyProfileButton->setEnabled(true);
    } else {
        playButton->setEnabled(false);
        modifyProfileButton->setEnabled(false);
    }
}

void ProfileList::handleModifyProfileButtonClicked(){

        // Créer une instance du dialogue de modification du profil
    


    // Afficher le dialogue de modification du profil
    dialog->exec();
}


void ProfileList::modifyProfile(const QString &name, const QString &avatarPath)
{
    // Mettre à jour le profil sélectionné avec les nouvelles données
    qDebug() << "Modifying profile";
    qDebug() << "Name: " << name;
    qDebug() << "Avatar path: " << avatarPath;

        if (!name.isEmpty()) {
        
            qDebug() << "Name: " << name;
            qDebug() << profileManager->curentProfile->getName();
            

            
            if(profileManager->curentProfile->getName() != name){
                profileManager->changeName(profileManager->curentProfile, name);
                profileManager->curentProfile->setName(name);
            }
        }

        if(!avatarPath.isEmpty()){
            qDebug() << "Avatar path: " << avatarPath;
            profileManager->changeAvatar(profileManager->curentProfile, avatarPath);

        }

        profileManager->profileSelected = false;
        updatePlayButtonState();
        loadProfiles(); 
}