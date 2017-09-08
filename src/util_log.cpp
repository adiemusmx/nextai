#include "util_log.h"
#include <cstdio>
#include "util_time.h"

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

void Logger::print(const char* funcName, int32 lineNum, E_LOG_LEVEL level, const char* content)
{

	if (E_LOG_LEVEL_OFF > level && E_LOG_LEVEL_MAX <= level)
		return;

	DateTime currentTime;
	Util_getCurrentSystemTime(currentTime);

	if (m_logLevel[E_LOG_OUTPUT_CONSOLE] <= level)
		printf("[%02d:%02d:%02d.%03d][%s:%d]%s\n", currentTime.hour, currentTime.minute, currentTime.second, currentTime.millisecond, funcName, lineNum, content);
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