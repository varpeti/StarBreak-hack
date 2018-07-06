#ifndef __HACK_H_
#define __HACK_H_

#include <iostream>

#include "remote.h"
#include "StarBreak.h"

#define endit(s) {std::cout << s << "\n";  return false;}
#define printa(a) {std::cout << a << "\n";}
#define printab(a,b) {std::cout << a << b <<"\n";}
#define printhex(a,b) {std::cout << a << std::hex << b <<"\n";}

struct Player
{
    public:
        Player() :
            r_MaxHealth(0),
            rw_Health(0),
            r_MaxAmmo(0),
            rw_Ammo(0),
            r_last_MaxHealth(0),
            r_last_MaxAmmo(0)
        {}

        int r_MaxHealth;
        int rw_Health;
        int r_MaxAmmo;
        int rw_Ammo;

        int r_last_MaxHealth;
        int r_last_MaxAmmo;
};

class Hack
{
    public:
        
    private:
        remote::Handle handle;
        unsigned long memaddr;
        Player player;

    public:
        bool init();
        bool run();
        bool isOK();

    private:

    
};

#endif