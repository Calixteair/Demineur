#ifndef PROFILELIST_H
#define PROFILELIST_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QList>
#include <QLabel>

#include "headerFiles/Views/ModifyProfileDialog.h"

#include "headerFiles/Models/Profile.h"
#include "headerFiles/Controllers/ProfileManager.h"

class ProfileList : public QWidget
{
    Q_OBJECT
public:
    explicit ProfileList(ProfileManager* profileManager, QWidget *parent = nullptr); 

    void loadProfiles();

signals:
    void profileSelected(Profile *profile);
    void playClicked();


private slots:
    void handleProfileItemClicked();
    void handleAddProfileClicked();
    void handleDeleteProfileClicked();
    void addProfile(Profile *profile);
    void handlePlayButtonClicked();
    void deleteSelectedProfile();
    void updatePlayButtonState();
    void handleModifyProfileButtonClicked();
    void modifyProfile(const QString &name, const QString &avatarPath);
    Profile* getSelectedProfile();

private:

    QListWidget *profileListView;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *playButton;
    QPushButton *modifyProfileButton;
    QLabel *avatarLabel;
    ProfileManager* profileManager;
    QList<Profile*> profiles;
    ModifyProfileDialog *dialog;
};

#endif // PROFILELIST_H
