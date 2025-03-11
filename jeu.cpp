#include "jeu.h"

jeu::jeu()
{
    for(int y = 0; y < MAX; y++)
    {
        for(int x = 0; x < MAX; x++)
        {
            grille[y][x] = VIDE;
        }
    }
}

void jeu::init()
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

void jeu::detect_dame()
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
