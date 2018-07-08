#include <thread>
#include <iostream>

#include "hack.h"

#define endit(s) {std::cout << s << "\n";  return false;}

Hack hack;

void hackr()
{
    while(hack.isOK())
    {
        if (!hack.run())
        {
            if (!hack.init()) break;
        }

        usleep(1000);
    }
}

int main()
{
    
    if (!hack.init()) endit("FAIL init");

    std::thread thackr(hackr);

    thackr.join();

    std::cout << "END" << "\n";

    return 0;
}
