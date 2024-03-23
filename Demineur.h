

#include <list>

class Demineur {
   

public:

    int nbLignes;
    int nbColonnes;
    int nbMines;
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

    Demineur(int lignes, int colonnes, int mines);

    Demineur(const char* filename);

    Demineur();

    int importeGame(const char *filename);
    
    void sauvegarderGame(const char *filename);

    void initialiserGrille();

    bool play(int x, int y);

    void afficherGrille();

    void marquerCase(int x, int y);

    Etat getState();
    






    ~Demineur();
};

 