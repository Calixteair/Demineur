// MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStackedWidget;
class DifficultyWindow;
class MainMenu;

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

private:
    QStackedWidget *stackedWidget;
    DifficultyWindow *difficultyWindow;
    MainMenu *mainMenu; 
};

#endif // MAINWINDOW_H