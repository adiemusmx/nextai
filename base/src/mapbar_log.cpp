#include "base/mapbar_log.h"
#include <cstdio>
#include <cstring>
#include "base/mapbar_time.h"

namespace MapBarDL {

Logger::Logger()
{
	m_logLevel[E_LOG_OUTPUT_FILE] = E_LOG_LEVEL_TRACE;
	m_logLevel[E_LOG_OUTPUT_CONSOLE] = E_LOG_LEVEL_VERBOSE;
}

Logger* Logger::getInstance()
{
	static Logger instance;
	return &instance;
}

const CHAR* Logger::trimFileName(const CHAR* fileName)
{
	int32 loopIdx;
	for (loopIdx = (int32)strlen(fileName) - 2; loopIdx >= 0; --loopIdx)
	{
		if (fileName[loopIdx] == '/' || fileName[loopIdx] == '\\')
		{
			break;
		}
	}
	return fileName + loopIdx + 1;
}

void Logger::print(const CHAR* fileName, const CHAR* funcName, int32 lineNum, E_LOG_LEVEL level, const CHAR* content)
{
	const CHAR* LogLevelTable[] = {"OFF", "VERBOSE", "TRACE", "INFO", "WARN", "ERROR", "MAX"};

	if (E_LOG_LEVEL_OFF > level && E_LOG_LEVEL_MAX <= level)
		return;

	DateTime currentTime = DateTime::now();

	if (m_logLevel[E_LOG_OUTPUT_CONSOLE] <= level)
	{
		printf("[%02u:%02u:%02u.%03u][%s][%s:%d|%s]%s\n",
		       currentTime.getHour(), currentTime.getMinute(), currentTime.getSecond(),
		       currentTime.getMillisecond(), LogLevelTable[level], trimFileName(fileName), lineNum, funcName, content);
	}
}

void Logger::setLevel(E_LOG_OUTPUT output, E_LOG_LEVEL level)
{
	if (output < E_LOG_OUTPUT_FILE || output >= E_LOG_OUTPUT_MAX)
		return;

	if (level < E_LOG_LEVEL_OFF && level >= E_LOG_LEVEL_MAX)
		return;

	m_logLevel[output] = level;
}

}