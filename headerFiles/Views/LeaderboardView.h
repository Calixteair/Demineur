#ifndef LEADERBOARDVIEW_H
#define LEADERBOARDVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
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
    void updateDisplay();

private:
    QVBoxLayout *m_layout;
    QHBoxLayout *m_button_layout;
    QVBoxLayout *m_leaderboard_view;
    Leaderboard m_leaderboard;
    ProfileManager* profileManager;
};

#endif // LEADERBOARDVIEW_H
