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

void Jeu::init(bool aff)
{
    bool pair = false;

    for(int y = 0; y < 4; y++)
    {
        for(int x = 1; x < MAX; x+= 2)
        {
            if(pair && x == 1)
            {
                x = 0;
            }

            grille[y][x] = NOIR;
        }

        pair = !pair;
    }


    for(int y = 6; y < MAX; y++)
    {
        for(int x = 1; x < MAX; x+= 2)
        {
            if(pair && x == 1)
            {
                x = 0;
            }

            grille[y][x] = BLANC;
        }

        pair = !pair;
    }

    if(aff)
    {
        for(int y = 0; y < MAX; y++)
        {
            for(int x = 0; x < MAX; x++)
            {
               std::cout << ' ' << grille[y][x] << ' ' ;
            }

            std::cout << std::endl;
        }
    }
}

bool Jeu::deplacement(int x_select, int y_select, int x_dpl, int y_dpl)
{
    set_case_select(x_select, y_select);
    set_case_depl(x_dpl, y_dpl);
    set_depl_direct();
    t_case adv_pion;

    if(j_mod == E_NOIR)
    {
        adv_pion = NOIR;
    }
    else
    {
        adv_pion = BLANC;
    }

    if()
    {
        switch(depl_valide())
        {
            case MANGER:
                if(depl_direct == HAUT_DROIT)
                {
                    grille[depl_direct.y][depl_direct.x] = VIDE;
                }
                else if(depl_direct == HAUT_GAUCHE )
                {
                    grille[case_select.y][depl_direct.x] = VIDE;
                }
                else if(depl_direct == BAS_DROIT )
                {
                    grille[depl_direct.y][depl_direct.x] = VIDE;
                }
                else
                {
                    grille[case_select.y][case_select.x] = VIDE;
                }

                grille[case_depl.x][case_depl.y] = adv_pion;
                grille[case_select.x][case_select.y] = VIDE;
                break;
            case SIMPLE:
                grille[case_depl.x][case_depl.y] = adv_pion;
                grille[case_select.x][case_select.y] = VIDE;
                break;
            default:
                break;
        }

        return true;
    }
    else
    {
        return false;
    }


}
/*
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
}*/

t_retour Jeu::depl_valide()
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
                if(detect_mangeable_pion())
                {
                    return MANGER;
                }
                else
                {
                    return SIMPLE;
                }
            }
        }
        /*
        else if(grille[y_s][x_s] == D_NOIRE || grille[y_s][x_s] == D_BLANC) // Ici le cas pour un dame s'agit de pions
        {
            if(grille[y_s][x_s] == VIDE)
            {
                return true;
            }
        }
        */
    }

    return INVALIDE;
}

bool Jeu::detect_mangeable_pion()
{
    bool a_manger = false;

    if(j_mod == E_NOIR)
    {
        adv_pion = BLANC;
    }
    else
    {
        adv_pion = NOIR;
    }

    if(depl_direct.direct == HAUT_DROIT && grille[case_select.y - 1][case_select.x - 1] == adv_pion)
    {
        a_manger = true;
    }
    else if(depl_direct.direct == HAUT_GAUCHE && grille[case_select.y - 1][case_select.x + 1] == adv_pion)
    {
        a_manger = true;
    }
    else if(depl_direct.direct == BAS_DROIT && grille[case_select.y + 1][case_select.x - 1] == adv_pion)
    {
        a_manger = true;
    }
    else if(depl_direct.direct == BAS_GAUCHE && grille[case_select.y + 1][case_select.x + 1] == adv_pion)
    {
        a_manger = true;
    }

    return a_manger;
}

/*
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
*/

void Jeu::set_depl_direct()
{
    int vect_x = case_depl.x - case_select.x;
    int vect_y = case_depl.y - case_select.y;

    if(vect_x < 0 && vect_y > 0 )
    {
        depl_direct.direct = HAUT_GAUCHE;
        int vect_x = case_select.x - 1;
        int vect_y = case_select.y + 1;
    }
    else if(vect_x > 0 && vect_y > 0 )
    {
        depl_direct.direct = HAUT_DROIT;
        int vect_x = case_select.x + 1;
        int vect_y = case_select.y + 1;
    }
    else if(vect_x > 0 && vect_y < 0 )
    {
        depl_direct.direct = BAS_GAUCHE;
        int vect_x = case_select.x - 1;
        int vect_y = case_select.y - 1;
    }
    else if(vect_x < 0 && vect_y < 0 )
    {
        depl_direct.direct = BAS_DROIT;
        int vect_x = case_select.x + 1;
        int vect_y = case_select.y - 1;
    }
}

void Jeu::set_case_select(int x, int y)
{
    case_depl.x = x;
    case_depl.y = y;
}

void Jeu::set_case_depl(int x, int y)
{
    case_depl.x = x;
    case_depl.y = y;
}
