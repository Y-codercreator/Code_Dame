#include "debug.h"
#include "iostream"

Debug::Debug(t_mod mod)
{
    if(mod == CONFIG_1)
    {
        t_grille grid;

        for(int y = 0; y < MAX; y++)
        {
            for(int x = 0; x < MAX; x++)
            {
                grid[y][x] = VIDE;
            }
        }

        grid[4][8] = BLANC;

        Jeu game (grid);
        this->mod = mod;
    }

    grid_print(space);
}

Debug::Debug(t_mod mod, int g_space)
{
    if(mod == CONFIG_1)
    {
        t_grille grid;

        for(int y = 0; y < MAX; y++)
        {
            for(int x = 0; x < MAX; x++)
            {
                grid[y][x] = VIDE;
            }
        }

        grid[4][8] = BLANC;

        Jeu game (grid);
        this->mod = mod;
        this->space = g_space;
    }

    grid_print(space);
}

t_retour Debug::move(t_direct direct, t_coord empl)
{
    std::cout << "TR1" << std::endl;
    switch(direct)
    {
        case HAUT_DROIT:
        std::cout << "TR2" << std::endl;
            return game.deplacement(empl.x, empl.y, empl.x + 1, empl.y + 1);
        case HAUT_GAUCHE:
            return game.deplacement(empl.x, empl.y, empl.x - 1, empl.y + 1);
        case BAS_DROIT:
            return game.deplacement(empl.x, empl.y, empl.x + 1, empl.y - 1);
        case BAS_GAUCHE:
            return game.deplacement(empl.x, empl.y, empl.x - 1, empl.y - 1);
        default:
            return INVALIDE;
    }

    grid_print(space);
}

void Debug::grid_print(int space)
{

    for(int tab = 0; tab < 5; tab++)
    {
       std::cout << std::endl ;
    }

    for(int y = 0; y < MAX; y++)
    {
        for(int x = 0; x < MAX; x++)
        {
            for(int a = 0; a < space; a++)
            {
               std::cout << ' ' ;
            }

           std::cout << ' ' << game.get_case_grille(x, y) << ' ' ;

           for(int b = 0; b < space; b++)
           {
              std::cout << ' ' ;
           }
        }

        for(int c = 0; c < space + 1; c++)
        {

           std::cout << std::endl;
        }
    }
}

void Debug::return_print(t_retour primo)
{
    switch(primo)
    {
        case SIMPLE:
            std::cout << "Deplacement simple effectue" << std::endl;
            break;
        case MANGER:
            std::cout << "Deplacement en mangeant effectue" << std::endl;
            break;
        case INVALIDE:
            std::cout << "ERREUR : source de l'erreur inconnue" << std::endl;
            break;
        case NON_PION:
            std::cout << "ERREUR : la case selectionnee ne contient pas de pion" << std::endl;
            break;
        case HORS_LIMITE:
            std::cout << "ERREUR : tentative de deplacement hors des limites de la grille de jeu" << std::endl;
            break;
        default:
            break;
    }
}

void Debug::script()
{
    switch(mod)
    {
        case CONFIG_1:
            t_coord select;
            select.x = 4;
            select.y = 8;
            return_print(move(HAUT_DROIT, select));
            break;
    }
}
