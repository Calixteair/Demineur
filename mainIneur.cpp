#include <iostream>
#include "Demineur.h"




int main() {
    std::cout << "Vous voulez charger une partie? (y/N) : ";
    char choix;
    std::cin >> choix;
    Demineur game;

    if (choix == 'y') {
        std::string filename;
        std::cout << "Entrez le nom du fichier : ";
        std::cin >> filename;
        game = Demineur(filename.c_str());
        if (game.getState() == Demineur::ERROR) {
            return 1;
        }
    }
    else {
        
        int lignes, colonnes, mines;
        std::cout << "Entrez le nombre de lignes : ";
        std::cin >> lignes;
        std::cout << "Entrez le nombre de colonnes : ";
        std::cin >> colonnes;
        std::cout << "Entrez le nombre de mines : ";
        std::cin >> mines;
        
         game = Demineur(lignes, colonnes, mines);
    }





    while (game.getState() == Demineur::EN_COURS || game.getState() == Demineur::INIT) {
        game.afficherGrille();
        std::cout<< "Decouvrire une case ou marquer une mine ou save ? (d/m/s) : ";
        char choix;
        std::cin >> choix;
        if (choix == 'm') {
            int x, y;
            std::cout << "Entrez les coordonnées de la case à marquer (x y) : ";
            std::cin >> x >> y;
            game.marquerCase(x, y);
            continue;
        }else if (choix == 's'){
            std::string filename;
            std::cout << "Entrez le nom du fichier : ";
            std::cin >> filename;
            game.sauvegarderGame(filename.c_str());
            continue;
        }else if (choix != 'd') {
            std::cout << "Choix invalide" << std::endl;
            continue;
        }

        int x, y;
        std::cout << "Entrez les coordonnées de la case à découvrir (x y) : ";
        std::cin >> x >> y;
        if (!game.play(x, y)) {
            if(game.getState() == Demineur::GAGNE){
                game.afficherGrille();
                std::cout << "Vous avez gagné !" << std::endl;
            }else{
                game.afficherGrille();
                std::cout << "Vous avez perdu !" << std::endl;
            }

            break;
        }
    }


    return 0;
}

// compiler g++ mainIneur.cpp emineur.cpp -o demineur