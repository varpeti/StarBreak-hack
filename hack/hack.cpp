#include "hack.h"

bool Hack::init()
{
    //*/// root

    if (getuid() != 0)
    {
        endit("Cannot start as NON ROOT user.");
    }

    //*/// pid

    while (true)
    {
        if (remote::FindProcessByName(PROCESSNAME, &handle)) break;
        usleep(1000);
    }

    printab("Discovered with PID: ",handle.GetPid());

    //*/// find by pattern

    memaddr = 0;

    while (memaddr==0) 
    {
        if (!handle.IsRunning())
        {
            endit("regions");
        }

        handle.ParseMaps();

        for (auto region : handle.regions)
        {
            memaddr = (long)region.find(handle,patternPlayerClass);

            printf("%lx - %lx\n",region.start, memaddr);
            if (memaddr>0) {memaddr; break;}
        }

        usleep(500); 
    }

    printf("Found memaddr address: %lx\n",memaddr);

    //*/// read memory

    if( handle.Read( (void*)(memaddr+0), &player.rw_Health, sizeof(player.rw_Health) ) ) printf("Health: %d \n",player.rw_Health);
    
    if( handle.Read( (void*)(memaddr+0x4), &player.r_MaxHealth, sizeof(player.r_MaxHealth) ) ) printf("MaxHealth: %d \n",player.r_MaxHealth);
    player.r_last_MaxHealth = player.r_MaxHealth;

    if( handle.Read( (void*)(memaddr+0x28c), &player.rw_Ammo, sizeof(player.rw_Ammo) ) ) printf("Ammo: %d \n",player.rw_Ammo);

    if( handle.Read( (void*)(memaddr+0x28c-0x08), &player.r_MaxAmmo, sizeof(player.r_MaxAmmo) ) ) printf("MaxAmmo: %d \n",player.r_MaxAmmo);
    player.r_last_MaxAmmo = player.r_MaxAmmo;

    /*/// debug

    remote::MapModuleMemoryRegion *region = NULL;
    
    handle.ParseMaps();

    region = handle.GetRegionOfAddress((void*)memaddr);
    region->print(handle,(void*)memaddr);

    //*/// end

    return true;
}

bool Hack::isOK()
{
    return handle.IsRunning();
}


bool Hack::run()
{

    if( !handle.Read( (void*)(memaddr+0x4), &player.r_MaxHealth, sizeof(player.r_MaxHealth) ) ) return false;
    if (player.r_last_MaxHealth != player.r_MaxHealth) return false;

    if( !handle.Read( (void*)(memaddr+0x28c-0x08), &player.r_MaxAmmo, sizeof(player.r_MaxAmmo) ) ) return false;
    if (player.r_last_MaxAmmo != player.r_MaxAmmo) return false;

    //The server tracks the player stats, and u die and run out of ammo anyway. So basicly u are alive in client side, but dead in server side, and those fooes whom killed by ur ammo are dead in clientside and alive serverside, (and kill u)

    //player.rw_Health=player.r_MaxHealth;
    //handle.Write( (void*)(memaddr+0), &player.rw_Health, sizeof(player.rw_Health) );

    //player.rw_Ammo=player.r_MaxAmmo;
    //handle.Write( (void*)(memaddr+0x28c), &player.rw_Ammo, sizeof(player.rw_Ammo) );

    return true;
}