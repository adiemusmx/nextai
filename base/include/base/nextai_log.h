#ifndef _NEXTAI_LOG_H_
#define _NEXTAI_LOG_H_

#include "base/nextai_basic_define.h"

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
		void log(Logger::Level level, std::wstring format, const char* tag, const char* file, const char* function, size_t line, const Args &... args)
		{
			char log_buffer[LOGGER_BUFFER_MAX_LENGTH] = { 0 };
			wchar_t wlog_buffer[LOGGER_BUFFER_MAX_LENGTH] = { 0 };
			sprintf_s(log_buffer, LOGGER_BUFFER_MAX_LENGTH, "[%s][%s|%s:%d]", tag, file, function, line);
			mbstowcs(wlog_buffer, log_buffer, LOGGER_BUFFER_MAX_LENGTH);

			format = wlog_buffer + format;

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

		template<typename... Args>
		void log(Logger::Level level, const char* format, const char* tag, const char* file, const char* function, size_t line, const Args &... args)
		{
			wchar_t wformat[LOGGER_BUFFER_MAX_LENGTH] = { 0 };
			mbstowcs(wformat, format, LOGGER_BUFFER_MAX_LENGTH);
			log(level, wformat, tag, file, function, line, args...);
		}

	private:
		std::shared_ptr<spdlog::logger> m_logger;
	};

	extern std::shared_ptr<NextAI::Logger> globalLogger;
}

#define NEXTAI_TRACE_LOG(tag, format, ...)		{ globalLogger->log(NextAI::Logger::Level::Trace, format, tag, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_INFO_LOG(tag, format, ...)		{ globalLogger->log(NextAI::Logger::Level::Info,  format, tag, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_WARN_LOG(tag, format, ...)		{ globalLogger->log(NextAI::Logger::Level::Warn,  format, tag, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_ERROR_LOG(tag, format, ...)		{ globalLogger->log(NextAI::Logger::Level::Error, format, tag, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_TRACE_FUNC(tag)					{ globalLogger->log(NextAI::Logger::Level::Trace, "", tag, __FILE__, __FUNCTION__, __LINE__); }

#endif // !_NEXTAI_LOG_H_
