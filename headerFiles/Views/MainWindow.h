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
#include <QTime>

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
    void endGame(int rows , int cols, int mines, QTime time, bool wind);
    private slots:
    void toggleMute();
    void setVolume(int volume);
    void openDemineurPageWithDifficulty(int rows, int cols, int mines);
    void openDemineurPageWithFilePATH(QString filePath);
    void BackToMainPage();



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
    QAction *randomSong;
    QSlider *volumeSlider;
    QString *currentProfile;

    QMediaPlaylist *playlist;
    QMediaPlayer *music;
    QWidget *navbar;
};

#endif // MAINWINDOW_H