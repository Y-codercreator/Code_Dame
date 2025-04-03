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

Jeu::Jeu(t_grille grid)
{
    for(int y = 0; y < MAX; y++)
    {
        for(int x = 0; x < MAX; x++)
        {
            grille[y][x] = grid[y][x];
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

t_retour Jeu::deplacement(int x_select, int y_select, int x_dpl, int y_dpl)
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

    std::cout << x_select << ' ' << y_select << ' ' <<
                 x_dpl << ' ' << y_dpl << ' ' << std::endl;

    t_retour ret = depl_valide();

    std::cout << "TR3" << std::endl;

    switch(ret)
    {

        case MANGER:
            if(depl_direct.direct == HAUT_DROIT)
             {
                 grille[depl_direct.y][depl_direct.x] = VIDE;
             }
             else if(depl_direct.direct == HAUT_GAUCHE )
             {
                 grille[case_select.y][depl_direct.x] = VIDE;
             }
             else if(depl_direct.direct == BAS_DROIT )
             {
                 grille[depl_direct.y][depl_direct.x] = VIDE;
             }
             else
             {
                 grille[case_select.y][case_select.x] = VIDE;
             }

             grille[case_depl.y][case_depl.x] = adv_pion;
             grille[case_select.y][case_select.x] = VIDE;
             return ret;
         case SIMPLE:
             grille[case_depl.y][case_depl.x] = adv_pion;
             grille[case_select.y][case_select.x] = VIDE;
             return ret;
         default:
             return ret;
     }

    return ret;
}

bool Jeu::i_grille()
{


    if((case_depl.x < MAX || case_depl.x > -1) && (case_depl.y < MAX || case_depl.y > -1) && (case_depl.x != case_select.x && case_depl.y != case_select.y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Jeu::i_pion()
{


    if(grille[case_select.y][case_select.x] == NOIR || grille[case_select.y][case_select.x] == BLANC)
    {
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
    std::cout << case_select.y << " - " << case_select.x << std::endl;
    std::cout << NOIR << ' ' << BLANC << ' ' << grille[case_select.y][case_select.x] << std::endl;

    if(i_grille()) // Il faut que le deplacement se fasse dans les limites valides de la grille
    {
        if(i_pion())  // On cherche a savoir s'il s'agit de pions
        {
            /*if((x_dpl + 1 == x_s || x_dpl - 1 == x_s ) &&  (y_dpl + 1 == y_s || y_dpl - 1 == y_s ))
            {
                bool ret = detect_mangeable_pion();

                if(ret)
                {
                    return MANGER;
                }
                else
                {
                    return SIMPLE;
                }
            }
            else
            {

            }*/

            return SIMPLE;
        }
        else
        {
            return NON_PION;
        }
    }
    else
    {
        return HORS_LIMITE;
    }

    return INVALIDE;
}

bool Jeu::detect_mangeable_pion()
{
    bool a_manger = false;
    t_case adv_pion;

    if(j_mod == E_NOIR)
    {
        adv_pion = BLANC;
    }
    else
    {
        adv_pion = NOIR;
    }

    if(depl_direct.direct == HAUT_DROIT && grille[case_select.y - 1][case_select.x + 1] == adv_pion)
    {
        a_manger = true;
    }
    else if(depl_direct.direct == HAUT_GAUCHE && grille[case_select.y - 1][case_select.x - 1] == adv_pion)
    {
        a_manger = true;
    }
    else if(depl_direct.direct == BAS_DROIT && grille[case_select.y + 1][case_select.x + 1] == adv_pion)
    {
        a_manger = true;
    }
    else if(depl_direct.direct == BAS_GAUCHE && grille[case_select.y + 1][case_select.x - 1] == adv_pion)
    {
        a_manger = true;
    }
    else
    {
        return false;
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
    case_select.x = x;
    case_select.y = y;
}

void Jeu::set_case_depl(int x, int y)
{
    case_depl.x = x;
    case_depl.y = y;
}

void Jeu::set_case(int x, int y, t_case c)
{
    grille[y][x] = c;
}
