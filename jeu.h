#ifndef JEU_H
#define JEU_H

#include <iostream>
#include <string>

#include "defines.h"

typedef enum
{
    VIDE,       //Case vide
    NOIR,       //Case pion noir
    BLANC,      //Case pion blanc
    D_NOIRE,    //Case dame noir
    D_BLANC     //Case dame blanc
}t_case;

typedef enum
{
    E_BLANC,    //Joueur blanc
    E_NOIR      //Joueur noir
}t_joueur;

typedef t_case t_grille[MAX][MAX];

class jeu
{
    private:
        t_grille grille;
        t_joueur j_mod;

    public:
        jeu();

        //INITIALISATION DE LA GRILLE
        void init();

        //DETECTION ET MODIFICATIONS
        void detect_dame();

};

#endif // JEU_H
