#ifndef LEADERBOARDVIEW_H
#define LEADERBOARDVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include "headerFiles/Models/Leaderboard.h"
#include "headerFiles/Controllers/ProfileManager.h"

class LeaderboardView : public QWidget
{
    Q_OBJECT
public:
    LeaderboardView(ProfileManager* profileManager, QWidget *parent = nullptr);

private slots:
    void sortByParameter();
    void updateLeaderboard();
    void updateDisplay(int mode, QString parameterName);
    void updateListe();

private:
    QVBoxLayout *m_layout;
    QHBoxLayout *m_button_layout;
    QLabel *indexHeader;
    QHBoxLayout *headerLayout;
    QLabel *avatarHeader;
    QLabel *nameHeader;
    QLabel *parameterHeader;
    Leaderboard m_leaderboard;
    ProfileManager* profileManager;
    QList<Profile*> profilesSorted;
};

#endif // LEADERBOARDVIEW_H
