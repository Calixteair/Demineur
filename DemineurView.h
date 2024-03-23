#ifndef DEMINEURVIEW_H
#define DEMINEURVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "Demineur.h"
#include <QMouseEvent> // Ajout de l'inclusion pour utiliser QMouseEvent


class DemineurView : public QWidget
{
    Q_OBJECT
    
public:
    DemineurView(int rows, int cols, int mines, QWidget *parent);

private:
    QGridLayout *gridLayout;
    Demineur *demineur;
    QVector<QPushButton*> buttons;
    void mousePressEvent(QMouseEvent *event);

    void createGrid(int nbLigne, int nbColonne);
    void updateGrid();
    void updateButton(int x, int y);
    void play(int x, int y);
    void marquerCase(int x, int y);
    void showAll();
    void showWin();
    void showLoose(); 
};

#endif // DEMINEURVIEW_H
