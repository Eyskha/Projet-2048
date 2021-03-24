#include "grille.h"
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

Grille::Grille(int l, int c, int i, QObject *parent) : QObject(parent){
    L = l;
    C = c;
    paletteCouleurs = {
        QColor::fromRgb(255,201,86),
        QColor::fromRgb(255,155,81),
        QColor::fromRgb(241,110,89),
        QColor::fromRgb(212,70,101),
        QColor::fromRgb(170,41,111),
        QColor::fromRgb(140,79,166),
        QColor::fromRgb(69,111,199),
        QColor::fromRgb(0,135,203),
        QColor::fromRgb(0,152,184),
        QColor::fromRgb(0,164,152)
    };
    initiatedTiles = i;
    contenu = new int*[L];
    for(int i=0; i<L; i++){
        contenu[i] = new int[C];
    }
    initGrid();
    majListeCases();
    majListeCouleurs();
    emit sizeChanged();
}

void Grille::mouvUp(){
    // Parcours du bas vers le haut, pas première ligne
    test = false;
    for(int i=L-1; i>0; i--){
        for(int j=0; j<C; j++){
            // Cas 1 : case vide au-dessus
            if(contenu[i-1][j] == 0 and contenu[i][j] != 0){
                contenu[i-1][j] = contenu[i][j];
                contenu[i][j] = 0;
                test = true;

                // Décalage des tuiles en-dessous
                if(i==L-1){
                    contenu[i][j] = 0;
                }
                else{
                    for(int d=i; d<L-1;d++){
                       contenu[d][j] = contenu[d+1][j];
                    }
                    contenu[L-1][j] = 0;
                }
            }

            // Cas 2 : case de la même valeur au-dessus
            if(contenu[i-1][j] == contenu[i][j] and contenu[i][j] != 0){
                contenu[i-1][j] = 2*contenu[i][j];
                Score += contenu[i-1][j];
                test = true;

                // Décalage des tuiles en-dessous
                if(i==L-1){
                    contenu[i][j] = 0;
                }
                else{
                    for(int d=i; d<L-1;d++){
                       contenu[d][j] = contenu[d+1][j];
                    }
                    contenu[L-1][j] = 0;
                }
            }
        }
    }

    if(test == true){
    newTile();
    majListeCases();
    majListeCouleurs();
    }
    if(testfinpartie()){
        Fingame = "partie finie";
        partietermine();
    }
    else
        Fingame = "haut, continuez";
    emit caseChanged();
}

void Grille::mouvDown(){
    // Parcours du haut vers le bas, pas dernière ligne
    test = false;
    for(int i=0; i<L-1; i++){
        for(int j=0; j<C; j++){
            // Cas 1 : case vide en-dessous
            if(contenu[i+1][j] == 0 and contenu[i][j] != 0){
                contenu[i+1][j] = contenu[i][j];
                contenu[i][j] = 0;
                test = true;

                // Décalage des tuiles au-dessus
                if(i==0){
                    contenu[i][j] = 0;
                }
                else{
                    for(int d=i; d>0;d--){
                       contenu[d][j] = contenu[d-1][j];
                    }
                    contenu[0][j] = 0;
                }
            }

            // Cas 2 : case de la même valeur en-dessous
            if(contenu[i+1][j] == contenu[i][j] and contenu[i][j] != 0){
                contenu[i+1][j] = 2*contenu[i][j];                
                Score += contenu[i+1][j];
                test = true;

                // Décalage des tuiles au-dessus
                if(i==0){
                    contenu[i][j] = 0;
                }
                else{
                    for(int d=i; d>0;d--){
                       contenu[d][j] = contenu[d-1][j];
                    }
                    contenu[0][j] = 0;
                }
            }
        }
    }

    if(test == true){
    newTile();
    majListeCases();
    majListeCouleurs();
    }
    if(testfinpartie()){
        Fingame = "partie finie";
        partietermine();
    }
    else
        Fingame = "bas, continuez";
    emit caseChanged();
}

void Grille::mouvRight(){
    // Parcours de la gauche vers la droite, pas dernière colonne
    test = false;
    for(int j=0; j<C-1; j++){
        for(int i=0; i<L; i++){
            // Cas 1 : case vide à droite
            if(contenu[i][j+1] == 0 and contenu[i][j] != 0){
                contenu[i][j+1] = contenu[i][j];
                contenu[i][j] = 0;
                test = true;

                // Décalage des tuiles à gauche
                if(j==0){
                    contenu[i][j] = 0;
                }
                else{
                    for(int d=j; d>0;d--){
                       contenu[i][d] = contenu[i][d-1];
                    }
                    contenu[i][0] = 0;
                }
            }

            // Cas 2 : case de la même valeur à droite
            if(contenu[i][j+1] == contenu[i][j] and contenu[i][j] != 0){
                contenu[i][j+1] = 2*contenu[i][j];                
                Score += contenu[i][j+1];
                test = true;

                // Décalage des tuiles à gauche
                if(j==0){
                    contenu[i][j] = 0;
                }
                else{
                    for(int d=j; d>0;d--){
                       contenu[i][d] = contenu[i][d-1];
                    }
                    contenu[i][0] = 0;
                }
            }
        }
    }

    if(test == true){
    newTile();
    majListeCases();
    majListeCouleurs();
    }
    if(testfinpartie()){
        Fingame = "partie finie";
        partietermine();
    }
    else
        Fingame = "droite, continuez";
    emit caseChanged();
}

void Grille::mouvLeft(){
    // Parcours de la droite vers la gauche, pas première colonne
    test = false;
    for(int j=C-1; j>0; j--){
        for(int i=0; i<L; i++){
            // Cas 1 : case vide à gauche
            if(contenu[i][j-1] == 0 and contenu[i][j] != 0){
                contenu[i][j-1] = contenu[i][j];
                contenu[i][j] = 0;
                test = true;

                // Décalage des tuiles à droite
                if(j==C-1){
                    contenu[i][j] = 0;
                }
                else{
                    for(int d=j; d<C-1;d++){
                       contenu[i][d] = contenu[i][d+1];
                    }
                    contenu[i][C-1] = 0;
                }
            }

            // Cas 2 : case de la même valeur à gauche
            if(contenu[i][j-1] == contenu[i][j] and contenu[i][j] != 0){
                contenu[i][j-1] = 2*contenu[i][j];                
                Score += contenu[i][j-1];
                test = true;

                // Décalage des tuiles à droite
                if(j==C-1){
                    contenu[i][j] = 0;
                }
                else{
                    for(int d=j; d<C-1;d++){
                       contenu[i][d] = contenu[i][d+1];
                    }
                    contenu[i][C-1] = 0;
                }
            }
        }
    }

    if(test == true){
    newTile();
    majListeCases();
    majListeCouleurs();
    }
    if(testfinpartie()){
        Fingame = "partie finie";
        partietermine();
    }
    else
        Fingame = "gauche, continuez";
    emit caseChanged();
}

void Grille::initGrid(){
    for(int i=0; i<L; i++){
        for(int j=0; j<C; j++){
            contenu[i][j] = 0;
        }
    }

    // Set first tiles
    srand((unsigned int)time(NULL)); // To get real random numbers (get rid of the seed)
    for(int i=0; i<initiatedTiles; i++){
        newTile();
    }
}

void Grille::newTile(){
    bool test = 0;
    while(!test){
        int randIndex = rand() % 16;
        int * tile = &contenu[(int) floor(randIndex/4)][randIndex%4];
        if(*tile == 0){
            int randNum = rand() % 100;
            if(randNum<94){
                *tile = 2;
            }
            else
                *tile = 4;

            test = 1;
        }
    }
}

void Grille::majListeCases(){
    listeCases.clear();
    for(int i=0; i<L; i++){
        for(int j=0; j<C; j++){
            listeCases.push_back(QString::number(contenu[i][j]));
        }
    }
}

void Grille::majListeCouleurs(){
    listeCouleurs.clear();
    for(int i=0; i<L; i++){
        for(int j=0; j<C; j++){
            if(contenu[i][j]==0)
                listeCouleurs.push_back(QColor::fromRgb(157,150,143));
            else
                listeCouleurs.push_back(paletteCouleurs[log(contenu[i][j])/log(2)]);
        }
    }
}

bool Grille::testfinpartie(){
    findepartie = true;
    for (int i=0; i<L; i++){
        for (int j=0; j<C; j++){
            if (contenu[i][j]==0){
                findepartie = false;
            }
            else if (i==0){
                if (j==0){
                    if (contenu[i+1][j]==contenu[i][j] || contenu[i][j+1]==contenu[i][j]){
                        findepartie = false;
                    }
                }
                else if (j==C-1){
                    if (contenu[i+1][j]==contenu[i][j] || contenu[i][j-1]==contenu[i][j]){
                        findepartie = false;
                    }
                }
                else{
                    if (contenu[i+1][j]==contenu[i][j] || contenu[i][j-1]==contenu[i][j] || contenu[i][j+1]==contenu[i][j]){
                        findepartie = false;
                    }
                }
            }
            else if (i==L-1){
                if (j==0){
                    if (contenu[i-1][j]==contenu[i][j] || contenu[i][j+1]==contenu[i][j]){
                        findepartie = false;
                    }
                }
                else if (j==C-1){
                    if (contenu[i-1][j]==contenu[i][j] || contenu[i][j-1]==contenu[i][j]){
                        findepartie = false;
                    }
                }
                else{
                    if (contenu[i-1][j]==contenu[i][j] || contenu[i][j-1]==contenu[i][j] || contenu[i][j+1]==contenu[i][j]){
                        findepartie = false;
                    }
                }
            }
            else{
                if (j==0){
                    if (contenu[i+1][j]==contenu[i][j] || contenu[i][j+1]==contenu[i][j] || contenu[i-1][j]==contenu[i][j]){
                        findepartie = false;
                    }
                }
                else if (j==C-1){
                    if (contenu[i+1][j]==contenu[i][j] || contenu[i][j-1]==contenu[i][j] || contenu[i-1][j]==contenu[i][j]){
                        findepartie = false;
                    }
                }
                else{
                    if (contenu[i+1][j]==contenu[i][j] || contenu[i][j-1]==contenu[i][j] || contenu[i][j+1]==contenu[i][j] || contenu[i-1][j]==contenu[i][j]){
                        findepartie = false;
                    }
                }
            }
        }
    }
    return findepartie;
}

void Grille::partietermine(){
    opacite = 1;
    emit caseChanged();
}

void Grille::newgame(){
    if (opacite == 1){
    opacite = 0;
    Score = 0;
    initGrid();
    majListeCases();
    majListeCouleurs();
    emit caseChanged();
    }
}
