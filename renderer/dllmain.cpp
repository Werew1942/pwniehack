#include "engine.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        engine::ignite();
    case DLL_PROCESS_DETACH:
            return TRUE;
    }

    return FALSE;
}

