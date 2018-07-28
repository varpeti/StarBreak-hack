#include <dlfcn.h>
#include <stdio.h>

char almaspite[] = "Almaspite";

typedef char* (*to_SDL_GetClipboardText)();
to_SDL_GetClipboardText o_SDL_GetClipboardText = NULL;

extern "C" char* SDL_GetClipboardText(void)
{

    if (!o_SDL_GetClipboardText)
    {
        o_SDL_GetClipboardText = (to_SDL_GetClipboardText) dlsym(RTLD_NEXT, "SDL_GetClipboardText");
    }

    printf("%s\n", o_SDL_GetClipboardText());

    return almaspite;
}
