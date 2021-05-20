

#if PLATFORM_WINDOWS

#include "Engine/Engine/Engine.h"
#include "Engine/Platform/Platform.h"
#include "Engine/Platform/Windows/IncludeWindowsHeader.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPTSTR cmdLine, int showCmd)
{

    Platform::PreInit(hInstance);
    __try
    {
        return Engine::Main(cmdLine);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return -1;
    }
}



#endif