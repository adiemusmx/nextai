#ifndef _NEXTAI_LOG_H_
#define _NEXTAI_LOG_H_

#include "base/nextai_basic_types.h"

#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bundled/ostream.h"

#define LOGGER_BUFFER_MAX_LENGTH 512

#define SPRINTF(x,c,...) sprintf(x,##__VA_ARGS__)
#ifdef SYSTEM_LINUX
#define SWPRINTF(x,c,...) swprintf(x,c,##__VA_ARGS__)
#else
#define SWPRINTF(x,c,...) swprintf_s(x,c,##__VA_ARGS__)
#endif

namespace NextAI
{
	class Logger
	{
	public:
		/* 输出级别 */
		enum class Level
		{
			Trace,
			Info,
			Warn,
			Error
		};
		
	public:
		Logger(const char* logName, const char* fileName = "DefaultFileName");
		virtual ~Logger();
		
		template<typename... Args>
		void log(Logger::Level level, const std::wstring& format, const char* tag, const char* file, const char* function, size_t line, const Args &... args)
		{
			char log_buffer[LOGGER_BUFFER_MAX_LENGTH] = { 0 };
			wchar_t wlog_buffer[LOGGER_BUFFER_MAX_LENGTH] = { 0 };
			sprintf_s(log_buffer, LOGGER_BUFFER_MAX_LENGTH, "[%s][%s|%s:%d]", tag, trimFilePath(file), function, line);
			mbstowcs(wlog_buffer, log_buffer, LOGGER_BUFFER_MAX_LENGTH);
			wcscat(wlog_buffer, format.c_str());
			
			switch (level)
			{
			case Level::Trace:
				m_logger->trace(wlog_buffer, args...);
				break;
				
			case Level::Info:
				m_logger->info(wlog_buffer, args...);
				break;
				
			case Level::Warn:
				m_logger->warn(wlog_buffer, args...);
				break;
				
			case Level::Error:
				m_logger->error(wlog_buffer, args...);
				break;
				
			default:
				break;
			}
		}
		
	private:
		const char* trimFilePath(const char* path);
		
		std::shared_ptr<spdlog::logger> m_logger;
	};
	
	extern std::shared_ptr<NextAI::Logger> globalLogger;
}

#define NEXTAI_TRACE_LOG(format, ...)		{ globalLogger->log(NextAI::Logger::Level::Trace,	format,	MODULE_NAME, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_INFO_LOG(format, ...)		{ globalLogger->log(NextAI::Logger::Level::Info,	format, MODULE_NAME, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_WARN_LOG(format, ...)		{ globalLogger->log(NextAI::Logger::Level::Warn,	format, MODULE_NAME, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_ERROR_LOG(format, ...)		{ globalLogger->log(NextAI::Logger::Level::Error,	format, MODULE_NAME, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_TRACE_FUNC()					{ globalLogger->log(NextAI::Logger::Level::Trace,	L"",	MODULE_NAME, __FILE__, __FUNCTION__, __LINE__); }

#endif // !_NEXTAI_LOG_H_
