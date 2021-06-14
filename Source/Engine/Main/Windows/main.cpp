

#if PLATFORM_WINDOWS

#include "Engine/Engine/Engine.h"
#include "Engine/Platform/Platform.h"
#include "Engine/Platform/Windows/IncludeWindowsHeader.h"
#include <conio.h>
#include <stdio.h>


//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPTSTR cmdLine, int showCmd)
//{
//    //AllocConsole();
//    //AttachConsole(ATTACH_PARENT_PROCESS);
//    //freopen("CONIN$", "r+t", stdin); // 重定向 STDIN
//    //freopen("CONOUT$", "w+t", stdout); // 重定向STDOUT
//    Platform::PreInit(hInstance);
//    __try
//    {
//        return Engine::Main();
//    }
//    __except (EXCEPTION_EXECUTE_HANDLER)
//    {
//        return -1;
//    }
//}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    Platform::PreInit(hInstance);
    __try
    {
        return Engine::Main();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return -1;
    }
    return 0;
}



#endif