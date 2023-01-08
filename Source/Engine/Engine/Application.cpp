#include "Engine.h"
#include "Application.h"

using namespace DawnEngine;

int32 Application::Main()
{
    Engine::Init();
    
    if (!Init())
    {
        LOG_ERROR("Init Application Error!!");
        return 0;
    }

    return Engine::Main();

}
