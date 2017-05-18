#include "Log.h"
#include <stdarg.h>
#include <stdio.h>

#define BUF_SIZE (256)

time_t LogManager::m_startTime = 0;

bool LogManager::m_LogLevelPermission[E_LOG_LEVEL_MAX] = {0};

void LogManager::print(const char *funcName, INT32 lineNum, E_LOG_LEVEL level,
                       const char *format, ...) {

    if (0 > level && E_LOG_LEVEL_MAX <= level)
        return;
    if (m_LogLevelPermission[level] == false)
        return;

    time_t nowTime;
    time(&nowTime);

    INT32 milliSecond = nowTime - m_startTime;
    printf("[%02d:%02d:%03d][%s:%d]", (milliSecond / 1000 / 60), ((milliSecond / 1000) % 60), (milliSecond % 1000), funcName, lineNum);

    char message[BUF_SIZE] = {0};

    va_list pArgList;
    va_start(pArgList, format);
    vsnprintf(message, BUF_SIZE, format, pArgList);
    va_end(pArgList);

    printf("%s\n", message);
}

void LogManager::setLevelPermission(E_LOG_LEVEL level, bool permission) {
    if (0 > level && E_LOG_LEVEL_MAX <= level)
        return;

    m_LogLevelPermission[level] = permission;
}

void LogManager::init() {
    time_t now;
    time(&now);
    m_startTime = now;
}