#ifndef DEBUG_H
#define DEBUG_H

#include "jeu.h"

typedef enum
{
    CONFIG_1
}t_mod;

class Debug
{
    public:
        Debug ();
        Debug(t_mod mod);
        Debug(t_mod mod, int g_space);

        t_retour move(t_direct direct, t_coord empl);
        void grid_print(int space);
        void return_print(t_retour);

        void script();

    private:
        Jeu game;
        t_mod mod;
        int space;
};

#endif // DEBUG_H
