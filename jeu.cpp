#include "jeu.h"

Jeu::Jeu()
{
    for(int y = 0; y < MAX; y++)
    {
        for(int x = 0; x < MAX; x++)
        {
            grille[y][x] = VIDE;
        }
    }
}

void Jeu::init()
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < MAX; x+= 2)
        {
            if(y % 2 != 0 && x == 0)
            {
                x++;
            }

            grille[y][x] = NOIR;
        }
    }

    for(int y = 6; y < MAX; y++)
    {
        for(int x = 0; x < MAX; x+= 2)
        {
            if(y % 2 != 0 && x == 0)
            {
                x++;
            }

            grille[y][x] = BLANC;
        }
    }
}

void Jeu::detect_dame()
{
    if(j_mod == E_NOIR)
    {
        for(int x = 0 ; x < MAX; x += 2)
        {
            if(grille[9][x] == NOIR)
            {
                grille[9][x] = D_NOIRE;
            }
        }
    }
    else
    {
        for(int x = 1 ; x < MAX; x += 2)
        {
            if(grille[0][x] == BLANC)
            {
                grille[0][x] = D_BLANC;
            }
        }
    }
}

bool Jeu::depl_valide()
{
    int x_dpl = case_depl.x;
    int y_dpl = case_depl.y;

    int x_s = case_select.x;
    int y_s = case_select.y;

    // Raccourcissement des noms de variables

    if((x_dpl < MAX || x_dpl > -1) && (y_dpl < MAX || y_dpl > -1) && (x_dpl != x_s && y_dpl != y_s)) // Il faut que le deplacement se fasse dans les limites valides de la grille
    {
        if(grille[y_s][x_s] == NOIR || grille[y_s][x_s] == BLANC)  // On cherche a savoir s'il s'agit de pions
        {
            if((x_dpl + 1 == x_s || x_dpl - 1 == x_s ) &&  (y_dpl + 1 == y_s || y_dpl - 1 == y_s ))
            {
                if(grille[y_s][x_s] == VIDE)
                {
                    return true;
                }
            }
        }
        else if(grille[y_s][x_s] == D_NOIRE || grille[y_s][x_s] == D_BLANC) // Ici le cas pour un dame s'agit de pions
        {
            if(grille[y_s][x_s] == VIDE)
            {
                return true;
            }
        }
    }

    return false;
}

bool Jeu::detect_mangeable_pion()
{
    bool a_manger = false;
    int incr_x = case_select.x;
    int incr_y = case_select.y;
    t_case adv_pion = VIDE;
    t_case adv_dame = VIDE;

    if(j_mod == E_NOIR)
    {
        adv_pion = BLANC;
        adv_dame = D_BLANC;
    }
    else
    {
        adv_pion = NOIR;
        adv_dame = D_NOIRE;
    }

    if(grille[incr_y + 1][incr_x - 1] == adv_dame || grille[incr_y + 1][incr_x - 1] == adv_pion)
    {
        a_manger = true;
    }
    else if(grille[incr_y + 1][incr_x + 1] == adv_dame || grille[incr_y + 1][incr_x + 1] == adv_pion)
    {
        a_manger = true;
    }
    else if(grille[incr_y - 1][incr_x - 1] == adv_dame || grille[incr_y - 1][incr_x - 1] == adv_pion)
    {
        a_manger = true;
    }
    else if(grille[incr_y - 1][incr_x + 1] == adv_dame || grille[incr_y - 1][incr_x + 1] == adv_pion)
    {
        a_manger = true;
    }

    return a_manger;
}

bool Jeu::detect_mangeable_dame()
{
    bool a_manger = false;
    int incr_x = case_select.x;
    int incr_y = case_select.y;
    t_case adv_pion = VIDE;
    t_case adv_dame = VIDE;

    if(j_mod == E_NOIR)
    {
        adv_pion = BLANC;
        adv_dame = D_BLANC;
    }
    else
    {
        adv_pion = NOIR;
        adv_dame = D_NOIRE;
    }

    for(incr_x = case_select.x; incr_x < MAX; incr_x++)
    {
        for(incr_y = case_select.y; incr_y > 0; incr_y--)
        {
            if(grille[incr_y][incr_x] == adv_dame || grille[incr_y][incr_x] == adv_pion)
            {
                a_manger = true;
            }
        }
    }
    for(incr_x = case_select.x; incr_x < MAX; incr_x++)
    {
        for(incr_y = case_select.y; incr_y < MAX; incr_y++)
        {
            if(grille[incr_y][incr_x] == adv_dame || grille[incr_y][incr_x] == adv_pion)
            {
                a_manger = true;
            }
        }
    }
    for(incr_x = case_select.x; incr_x > 0; incr_x--)
    {
        for(incr_y = case_select.y; incr_y > 0; incr_y--)
        {
            if(grille[incr_y][incr_x] == adv_dame || grille[incr_y][incr_x] == adv_pion)
            {
                a_manger = true;
            }
        }
    }
    for(incr_x = case_select.x; incr_x > 0; incr_x--)
    {
        for(incr_y = case_select.y; incr_y < MAX; incr_y++)
        {
            if(grille[incr_y][incr_x] == adv_dame || grille[incr_y][incr_x] == adv_pion)
            {
                a_manger = true;
            }
        }
    }

    return a_manger;
}

void Jeu::detect_direct()
{
    int vect_x = case_depl.x - case_select.x;
    int vect_y = case_depl.y - case_select.y;

    if(vect_x < 0 && vect_y > 0 )
    {
        depl_direct = HAUT_GAUCHE;
    }
    else if(vect_x > 0 && vect_y > 0 )
    {
        depl_direct = HAUT_DROIT;
    }
    else if(vect_x > 0 && vect_y < 0 )
    {
        depl_direct = BAS_GAUCHE;
    }
    else if(vect_x < 0 && vect_y < 0 )
    {
        depl_direct = BAS_DROIT;
    }
}

void Jeu::select_case(int x, int y)
{
    case_select = coo_to_matrice(x, y);
}

void Jeu::select_depl(int x, int y)
{
    case_depl = coo_to_matrice(x, y);
}

t_coord Jeu::coo_to_matrice(int x, int y)
{
    t_coord x_y;

    x_y.x = x / ECART_CASE;
    x_y.y = y / ECART_CASE;

    return x_y;
}
