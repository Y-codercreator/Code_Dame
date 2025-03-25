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

typedef enum
{
    HAUT_GAUCHE,
    HAUT_DROIT,
    BAS_GAUCHE,
    BAS_DROIT
}t_direct;

typedef struct //Type conteneur de coordonnées
{
    int x;
    int y;
}t_coord;

typedef t_case t_grille[MAX][MAX];

class Jeu
{
    private:
        t_grille grille;    //Grille de jeu
        t_joueur j_mod;     //Si je joueur jou blanc ou noir

        t_coord case_select;  //Case pour laquel on veut effectuer un deplacement pour un tour
        t_coord case_depl;  //Case sur laquel on veut aller (en cours de traitement)
        t_direct depl_direct; //Direction du deplacement

    public:
        Jeu();

        //INITIALISATION DE LA GRILLE
        void init(bool aff);

        //EXECUTION PRINCIPALE
        void trigger_jeu();

        //DETECTION ET MODIFICATIONS
        void detect_dame();     //Detecte et modifie le pion en dame si valide
        bool depl_valide();     //Detecte la validité d'un mouvement
        bool detect_manger();   //Detecte la possibilité de manger un pion/dame à coté
        bool detect_mangeable_pion();//Detecte si un pion/dame peut être mangé par un pion
        bool detect_mangeable_dame();//Detecte si un pion/dame peut être mangé par une dame

        void detect_direct();            //Defini la direction que va prendre le pion sélectionné lors du déplacement
        void select_case(int x, int y);  //Defini quelle case vient d'être sélectionnée
        void select_depl(int x, int y);  //Defini sur quelle case on veut aller

        //CONVERSION
        t_coord coo_to_matrice(int x, int y); // Adapte les coordonnées de pixel en coordonnées de la matrice

        //GET
        t_case get_case_grille(int x, int y) {return grille[y][x];}
        t_joueur get_j_mod() {return j_mod;}
        t_coord get_case_select() {return case_select;}
        t_coord get_case_depl() {return case_depl;}
        t_direct get_depl_direct(){return depl_direct;}

        //SET
        void set_depl_direct();            //Defini la direction que va prendre le pion sélectionné lors du déplacement
        void set_case_select(int x, int y);  //Defini quelle case vient d'être sélectionnée
        void set_case_depl(int x, int y);  //Defini sur quelle case on veut aller
};

#endif // JEU_H
