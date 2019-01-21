#include "stdafx.h"
#include "base/nextai_time.h"

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

	void SpdLogInitial()
	{
		globalLogger = std::make_shared<Logger>("global", "logs/default.txt");
	}
}
