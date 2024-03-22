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

private:
    QStackedWidget *stackedWidget;
    DifficultyWindow *difficultyWindow;
    MainMenu *mainMenu; 
    QMenu *settingsMenu;
    QAction *muteAction;
    QSlider *volumeSlider;
    QMediaPlayer *music;
    QMediaPlaylist *playlist;
};

#endif // MAINWINDOW_H