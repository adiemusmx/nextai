#include "base/nextai_log.h"
#include <cstdio>
#include <cstring>
#include "base/nextai_time.h"

#define NEXT_AI_LOG_FORMAT_STRING   "[%02u:%02u:%02u.%03u][%s][%s:%d|%s]%s\n"
#define NEXT_AI_LOG_FORMAT_STRING_W "[%02u:%02u:%02u.%03u][%s][%s:%d|%s]%S\n"

namespace NextAI {

	Logger::Logger()
	{
		m_logLevel[(int32)Platform::File] = Level::Warning;
		m_logLevel[(int32)Platform::Console] = Level::Verbose;
	}

	Logger* Logger::instance()
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

	static const CHAR* _g_logLevelNameTable[] = { "OFF", "VERBOSE", "TRACE", "INFO", "WARN", "ERROR", "MAX" };

	void Logger::print(const CHAR* fileName, const CHAR* funcName, int32 lineNum, Level level, const CHAR* content)
	{
		if (Level::Off > level && Level::Max <= level)
			return;

		DateTime currentTime = DateTime::now();

		if (m_logLevel[(int32)Platform::Console] <= level)
		{
			printf(NEXT_AI_LOG_FORMAT_STRING,
				   currentTime.getHour(), currentTime.getMinute(), currentTime.getSecond(),
				   currentTime.getMillisecond(), _g_logLevelNameTable[(int32)level], trimFileName(fileName), lineNum, funcName, content);
		}
	}

	void Logger::print(const CHAR* fileName, const CHAR* funcName, int32 lineNum, Level level, const WCHAR* content)
	{
		if (Level::Off > level && Level::Max <= level)
			return;

		DateTime currentTime = DateTime::now();

		if (m_logLevel[(int32)Platform::Console] <= level)
		{
			printf(NEXT_AI_LOG_FORMAT_STRING_W,
				currentTime.getHour(), currentTime.getMinute(), currentTime.getSecond(),
				currentTime.getMillisecond(), _g_logLevelNameTable[(int32)level], trimFileName(fileName), lineNum, funcName, content);
		}
	}

	void Logger::enableFile(const WCHAR* filePath)
	{
		m_file.open(filePath, FileAccessMode::Append);
	}

	void Logger::disableFile()
	{
		if (m_file.isOpen()) m_file.close();
	}

	void Logger::setLevel(Platform output, Level level)
	{
		if (output < Platform::File || output >= Platform::Max)
			return;

		if (level < Level::Off && level >= Level::Max)
			return;

		m_logLevel[(int32)output] = level;
	}

}