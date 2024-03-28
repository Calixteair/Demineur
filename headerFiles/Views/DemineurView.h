#ifndef DEMINEURVIEW_H
#define DEMINEURVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QPushButton>
#include "../Models/Demineur.h"
#include <QMouseEvent> // Ajout de l'inclusion pour utiliser QMouseEvent


class DemineurView : public QWidget
{
    Q_OBJECT
    
public:
    DemineurView(int rows, int cols, int mines, QWidget *parent);
    DemineurView(QString filePath, QWidget *parent);

private:
    QGridLayout *gridLayout;
    Demineur *demineur;
    QTimer *timer;
    QLabel *timeLabel;
    QLabel *counterFlag;
    QTime timeElapsed;
    QVector<QPushButton*> buttons;
    void mousePressEvent(QMouseEvent *event);
    void updateTime();
    void InitialiserView(int rows , int cols);

    void createGrid(int nbLigne, int nbColonne);
    void updateGrid();
    void updateButton(int x, int y);
    void play(int x, int y);
    void marquerCase(int x, int y);
    void showAll();
    void showWin();
    void showLoose(); 
    void ResetGame();


signals:
    void BackToMain();
    void endGameRequest(int rows , int cols, int mines, QTime time, bool wind);
};

#endif // DEMINEURVIEW_H
