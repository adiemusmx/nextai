#include "trinity_util_log.h"
#include <cstdio>
#include <cstring>
#include "trinity_util_time.h"

namespace Trinity
{

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
	for (loopIdx = strlen(fileName) - 2; loopIdx >= 0; --loopIdx)
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
	if (E_LOG_LEVEL_OFF > level && E_LOG_LEVEL_MAX <= level)
		return;

	DateTime currentTime;
	Util_getCurrentSystemTime(currentTime);

	if (m_logLevel[E_LOG_OUTPUT_CONSOLE] <= level)
		printf("[%02d:%02d:%02d.%03d][%s:%d|%s]%s\n", currentTime.hour, currentTime.minute, currentTime.second, currentTime.millisecond, trimFileName(fileName), lineNum, funcName, content);
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