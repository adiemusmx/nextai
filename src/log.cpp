#include "log.h"
#include <cstdio>
#include "util.h"

namespace Trinity {

	Logger::Logger() {
		m_logLevel[E_LOG_OUTPUT_FILE] = E_LOG_LEVEL_TRACE;
		m_logLevel[E_LOG_OUTPUT_CONSOLE] = E_LOG_LEVEL_WARNING;
	}

	Logger* Logger::getInstance() {
		static Logger instance;
		return &instance;
	}

	void Logger::print(const char *funcName, int32 lineNum, E_LOG_LEVEL level, const char *format, ...) {

		if (E_LOG_LEVEL_OFF > level && E_LOG_LEVEL_MAX <= level)
			return;

		Time currentTime;
		Util_getCurrentSystemTime(currentTime);

		char message[D_TEXT_MAX_LENGTH + 50] = { 0 };

		va_list pArgList;
		va_start(pArgList, format);
		vsnprintf(message, D_TEXT_MAX_LENGTH + 50, format, pArgList);
		va_end(pArgList);

		if (m_logLevel[E_LOG_OUTPUT_CONSOLE] <= level)
			printf("[%02d:%02d:%02d.%03d][%s:%d]%s\n", currentTime.hour, currentTime.minute, currentTime.second, currentTime.millisecond, funcName, lineNum, message);

		// 文件log未实现
	}

	void Logger::setLevel(E_LOG_OUTPUT output, E_LOG_LEVEL level) {
		if (output < E_LOG_OUTPUT_FILE || output >= E_LOG_OUTPUT_MAX)
			return;

		if (level < E_LOG_LEVEL_OFF && level >= E_LOG_LEVEL_MAX)
			return;

		m_logLevel[output] = level;
	}

}