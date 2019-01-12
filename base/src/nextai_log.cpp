#include "stdafx.h"
#include "base/nextai_time.h"

#if 1
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace NextAI
{
	Logger::Logger(const char* logName, const char* fileName)
	{
		m_logger = NULL;

		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::warn);

		char pattern[256] = { 0 };
		sprintf(pattern, "[%%^%%l%%$] %%v[%s]", logName);
		console_sink->set_pattern(pattern);

		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fileName, true);
		file_sink->set_level(spdlog::level::trace);

		spdlog::logger* logger = new spdlog::logger(logName, { console_sink, file_sink });
		m_logger = std::shared_ptr<spdlog::logger>(logger);
	}

	Logger::~Logger()
	{
	}

#if 0
	template<typename... Args>
	void Logger::log(Logger::Level level, const char* format, const char* tag, const char* file, const char* function, size_t line, const Args &... args)
	{
		if (m_logger == NULL) return;

		char log_buffer[LOGGER_BUFFER_MAX_LENGTH] = { 0 };
		sprintf(log_buffer, "[{}][{}|{}:{}]%s", format);

		switch (level)
		{
		case Level::Trace:
			m_logger->trace(_temp_log_buffer, tag, file, function, line, args...);
			break;
		case Level::Info:
			m_logger->info(_temp_log_buffer, tag, file, function, line, args...);
			break;
		case Level::Warn:
			m_logger->warn(_temp_log_buffer, tag, file, function, line, args...);
			break;
		case Level::Error:
			m_logger->error(_temp_log_buffer, tag, file, function, line, args...);
			break;
		default:
			break;
		}
	}
#endif
	std::shared_ptr<Logger> globalLogger;

	class SpdLogRegister
	{
	public:
		SpdLogRegister()
		{
			globalLogger = std::make_shared<Logger>("global", "logs/default.txt");
		}
	};

	static SpdLogRegister g_spdLogRegister;
}

#else

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

#endif