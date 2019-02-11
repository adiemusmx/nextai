#include "stdafx.h"
#include "base/nextai_time.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#define SPDLOG_PATTERN "[%H:%M:%S][%^%L%$][%t]%v"

namespace NextAI
{
	Logger::Logger(const char* logName, const char* fileName)
	{
		m_logger = NULL;
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::warn);
		char pattern[256] = { 0 };
		console_sink->set_pattern(SPDLOG_PATTERN);
		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fileName, false);
		file_sink->set_level(spdlog::level::trace);
		file_sink->set_pattern(SPDLOG_PATTERN);
		spdlog::logger* logger = new spdlog::logger(logName, { console_sink, file_sink });
		m_logger = std::shared_ptr<spdlog::logger>(logger);
		spdlog::flush_every(std::chrono::seconds(3));
	}
	
	Logger::~Logger()
	{
	}
	
	const char* Logger::trimFilePath(const char* path)
	{
		const char* ret = path + strlen(path) - 1;
		
		while (ret != path && *(ret - 1) != '\\' && *(ret - 1) != '/')
		{
			--ret;
		}
		
		return ret;
	}
	
	std::shared_ptr<Logger> globalLogger;
	
	void SpdLogInitial()
	{
		globalLogger = std::make_shared<Logger>("global", "logs/default.txt");
	}
}
