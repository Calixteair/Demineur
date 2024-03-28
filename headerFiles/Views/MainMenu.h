#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);

signals:
    void playClicked();
    void profileClicked();
    void leaderboardClicked();

private slots:
    void onPlayButtonClicked();
    void onProfileButtonClicked();
    void onLeaderboardButtonClicked();

private:
    QVBoxLayout *layout;
    QPushButton *playButton;
    QPushButton *profileButton;
    QPushButton *leaderboardButton;
};

#endif // MAINMENU_H
