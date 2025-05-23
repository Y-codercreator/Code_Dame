#ifndef JEU_H
#define JEU_H

#include <iostream>
#include <string>
#include <cstdlib>

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

typedef enum        //ENUMERATION DES DIRECTIONS POSSIBLES LORS DE DEPLACMENTS
{
    NONE,
    HAUT_GAUCHE,
    HAUT_DROIT,
    BAS_GAUCHE,
    BAS_DROIT
}t_direct;

typedef enum
{
    SIMPLE,     // deplacement simple
    MANGER,     // deplacement pour manger (en x2)
    INVALIDE,   //  deplacement impossible
    NON_PION,   // la case selectionnée ne contient pas de pion
    HORS_LIMITE, // le deplacement voulu se fait hors des limites
    EQUIPE_INVALIDE //le pion séléctionné n'appartient pas à la bonne équipe
}t_retour;

typedef struct //Type conteneur de coordonnées + direction
{
    int x;
    int y;
    t_direct direct = NONE;
}t_coord;

typedef t_case t_grille[MAX][MAX]; //Grille de jeu

class Jeu
{
    private:
        t_grille grille;    //Grille de jeu
        t_joueur j_mod;     //Si je joueur jou blanc ou noir

        t_coord case_select;  //Case pour laquel on veut effectuer un deplacement pour un tour
        t_coord case_depl;  //Case sur laquel on veut aller (en cours de traitement)
        t_coord depl_direct; //Direction du deplacement

    public:
        Jeu();
        Jeu(t_grille grid);

        //INITIALISATION DE LA GRILLE
        void init(bool aff = false);

        //DETECTION ET MODIFICATIONS
        t_retour deplacement(int x_select, int y_select, int x_dpl, int y_dpl);   // effectue un déplacement

        bool i_grille();
        bool i_pion();
        bool i_equipe();
        void detect_dame();         //Detecte et modifie le pion en dame si valide
        t_retour depl_valide();     //Detecte la validité d'un mouvement
        t_retour detect_manger();       //Detecte la possibilité de manger un pion/dame à coté
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
        t_coord get_depl_direct(){return depl_direct;}
        std::string get_string_grille();

        //SET
        void set_depl_direct();            //Defini la direction que va prendre le pion sélectionné lors du déplacement
        void set_case_select(int x, int y);  //Defini quelle case vient d'être sélectionnée
        void set_case_depl(int x, int y);  //Defini sur quelle case on veut aller
        void set_case(int x, int y, t_case c);
        void set_equipe(t_joueur j);
        void set_grille_string(std::string grille);

        //VERIFICATION
};

#endif // JEU_H
