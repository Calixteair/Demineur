// MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QSlider>
#include <QWidgetAction>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class QStackedWidget;
class DifficultyWindow;
class ProfileManager;
class ProfileList;
class MainMenu;
class QMediaPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openDifficultyWindow();
    void openProfileWindow();
    void openLeaderboardWindow();
    void openMainWindow();
    private slots:
    void toggleMute();
    void setVolume(int volume);
    void openDemineurPageWithDifficulty(int rows, int cols, int mines);


private:
    QStackedWidget *stackedWidget;
    DifficultyWindow *difficultyWindow;
    ProfileManager *profileManager;
    ProfileList *profileList;
    MainMenu *mainMenu; 
    QMenu *settingsMenu;
    QAction *muteAction;
    QAction *prevSong;
    QAction *nextSong;
    QSlider *volumeSlider;

    QMediaPlaylist *playlist;
    QMediaPlayer *music;
    QWidget *navbar;
};

#endif // MAINWINDOW_H