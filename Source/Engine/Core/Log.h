#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Platform/Define.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <vector>


/// <summary>
/// The log message types.
/// </summary>
enum class LogType
{
    /// <summary>
    /// The information log message.
    /// </summary>
    Info = 1,

    /// <summary>
    /// The warning message.
    /// </summary>
    Warning = 2,

    /// <summary>
    /// The error message.
    /// </summary>
    Error = 4,

    /// <summary>
    /// The fatal error.
    /// </summary>
    Fatal = 8,
};


#define LOG_INFO(format, ...) Log::Logger::Write(LogType::Info, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) Log::Logger::Write(LogType::Warning, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) Log::Logger::Write(LogType::Error, format, ##__VA_ARGS__)

namespace Log
{
	class Logger
	{
	public:
        template<typename... Args>
        static void Write(LogType type, const char* format, const Args& ... args)
        {
            std::string str;
            va_list args;
            va_start(args, format);
            {
                int nLength = _vscprintf(format, args);
                nLength += 1;  //上面返回的长度是包含\0，这里加上
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