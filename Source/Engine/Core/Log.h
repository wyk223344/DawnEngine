#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Platform/Define.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <vector>


#define LOG_INFO(format, ...) DawnEngine::Log::Logger::Write(DawnEngine::Log::LogType::Info, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) DawnEngine::Log::Logger::Write(DawnEngine::Log::LogType::Warning, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) DawnEngine::Log::Logger::Write(DawnEngine::Log::LogType::Error, format, ##__VA_ARGS__)


namespace DawnEngine::Log
{
    // The log message types.
    enum class LogType
    {
        Info = 1,

        Warning = 2,

        Error = 4,

        Fatal = 8,
    };

    class Logger
    {
    public:

        static void Write(LogType type, const char* format, ...)
        {
            std::string str;
            va_list args;
            va_start(args, format);
            {
                int nLength = _vscprintf(format, args);
                nLength += 1;  //上面返回的长度是包含\0，这里加上r
                std::vector<char> vectorChars(nLength);
                _vsnprintf(vectorChars.data(), nLength, format, args);
                str.assign(vectorChars.data());
            }
            va_end(args);
            str = str + "\n";
            switch (type)
            {
            case LogType::Info:
                printf(str.c_str());
                break;
            case LogType::Warning:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//设置红色和绿色相加
                printf(str.c_str());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                break;
            case LogType::Error:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//设置红色
                printf(str.c_str());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
                break;
            default:
                printf(str.c_str());
                break;
            }
        }
    };

}