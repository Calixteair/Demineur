// DifficultyWindow.h

#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

#include <QWidget>

// Ajoutez l'inclusion nécessaire pour DemineurView si elle n'est pas déjà incluse
#include "DemineurView.h"

class DifficultyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DifficultyWindow(QWidget *parent = nullptr);
    void launchDemineurView(int rows, int cols, int mines);
    void loadGame(QString filePath);



signals:
    void demineurViewRequested(int rows, int cols, int mines);
    void demineurViewRequestedWithFile(QString filePath);





private:
    // Déclarez la fonction de lancement dans la section privée pour qu'elle soit utilisable dans la classe

};

#endif // DIFFICULTYWINDOW_H
