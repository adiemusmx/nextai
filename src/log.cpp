#include "Log.h"
#include <stdarg.h>
#include <stdio.h>

bool Logger::m_LogLevelPermission[E_LOG_OUTPUT_MAX] = {
	E_LOG_LEVEL_TRACE , E_LOG_LEVEL_WARNING
};

void Logger::print(const CHAR *funcName, INT32 lineNum, E_LOG_LEVEL level, const CHAR *format, ...) {

	if (E_LOG_LEVEL_OFF > level && E_LOG_LEVEL_MAX <= level)
		return;

	time_t nowTime;
	time(&nowTime);

	CHAR message[D_TEXT_MAX_LENGTH + 20] = { 0 };

	va_list pArgList;
	va_start(pArgList, format);
	vsnprintf(message, D_TEXT_MAX_LENGTH + 20, format, pArgList);
	va_end(pArgList);

	if (m_LogLevelPermission[E_LOG_OUTPUT_CONSOLE] <= level)
		printf("[%02d:%02d:%03d][%s:%d]%s\n", (nowTime / 1000 / 60), ((nowTime / 1000) % 60), (nowTime % 1000), funcName, lineNum, message);

	// 文件log未实现
}

void Logger::setLevel(E_LOG_OUTPUT output, E_LOG_LEVEL level) {
	if (output < E_LOG_OUTPUT_FILE || output >= E_LOG_OUTPUT_MAX)
		return;

	if (level < E_LOG_LEVEL_OFF && level >= E_LOG_LEVEL_MAX)
		return;

	m_LogLevelPermission[level] = permission;
}