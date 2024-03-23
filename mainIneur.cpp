#include <iostream>
#include "Demineur.h"



int main() {
    // Demander Paramètres du jeu 
    int lignes, colonnes, mines;
    std::cout << "Entrez le nombre de lignes : ";
    std::cin >> lignes;
    std::cout << "Entrez le nombre de colonnes : ";
    std::cin >> colonnes;
    std::cout << "Entrez le nombre de mines : ";
    std::cin >> mines;

    
    Demineur demineur(lignes, colonnes, mines);



    while (demineur.getState() == Demineur::EN_COURS || demineur.getState() == Demineur::INIT) {
        demineur.afficherGrille();
        std::cout<< "Decouvrire une case ou marquer une mine ? (d/m) : ";
        char choix;
        std::cin >> choix;
        if (choix == 'm') {
            int x, y;
            std::cout << "Entrez les coordonnées de la case à marquer (x y) : ";
            std::cin >> x >> y;
            demineur.marquerCase(x, y);
            continue;
        }else if (choix != 'd') {
            std::cout << "Choix invalide" << std::endl;
            continue;
        }

        int x, y;
        std::cout << "Entrez les coordonnées de la case à découvrir (x y) : ";
        std::cin >> x >> y;
        if (!demineur.play(x, y)) {
            if(demineur.getState() == Demineur::GAGNE){
                demineur.afficherGrille();
                std::cout << "Vous avez gagné !" << std::endl;
            }else{
                demineur.afficherGrille();
                std::cout << "Vous avez perdu !" << std::endl;
            }

            break;
        }
    }


    return 0;
}

// compiler g++ mainIneur.cpp Demineur.cpp -o demineur