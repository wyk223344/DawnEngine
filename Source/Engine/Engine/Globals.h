#pragma once

#include "Engine/Core/Types/BaseTypes.h"


class Globals
{
public:
    // True if engine need to be closed
    static bool IsRequestingExit;

    // Exit code
    static int32 ExitCode;
};