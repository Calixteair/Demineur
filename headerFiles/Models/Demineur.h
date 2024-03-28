

#include <list>

class Demineur {
   

public:

    int nbLignes;
    int nbColonnes;
    int nbMines;
    int drapeau = 0;
    int grille[100][100];
    int grilleCachee[100][100];
    enum Etat {
        INIT,
        EN_COURS,
        GAGNE,
        PERDU,
        ERROR
    };

    Etat gameState;

    Demineur(int lignes, int colonnes, int mines , int drapeau);
    
    Demineur(int lignes, int colonnes, int mines);


    Demineur(const char* filename);

    Demineur();

    int importeGame(const char *filename);
    
    void sauvegarderGame(const char *filename);

    void initialiserGrille();

    void initialiserGrilleXY(int x, int y);

    bool play(int x, int y);

    void afficherGrille();

    void resetGame();

    void marquerCase(int x, int y);

    Etat getState();

    int* getGrille();

    int* getGrilleCachee();

    int getNbLignes();

    int getNbColonnes();

    int getNbMines();

    int getNbFlag();

    int getCellValue(int x, int y);

    int getCellState(int x, int y);

    void showAll();


    






    ~Demineur();
};

 