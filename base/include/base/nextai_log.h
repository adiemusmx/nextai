#ifndef _NEXTAI_LOG_H_
#define _NEXTAI_LOG_H_

#if 1

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
			if (m_logger == NULL) return;

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
				//m_logger->info(wlog_buffer, args...);
				break;
			case Level::Warn:
				//m_logger->warn(wlog_buffer, args...);
				break;
			case Level::Error:
				//m_logger->error(wlog_buffer, args...);
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

#if 1
#define NEXTAI_TRACE_LOG(tag, format, ...)		{ if (globalLogger == NULL)	globalLogger->log(NextAI::Logger::Level::Trace, format, tag, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_INFO_LOG(tag, format, ...)		{ if (globalLogger == NULL)	globalLogger->log(NextAI::Logger::Level::Info,  format, tag, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_WARN_LOG(tag, format, ...)		{ if (globalLogger == NULL)	globalLogger->log(NextAI::Logger::Level::Warn,  format, tag, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_ERROR_LOG(tag, format, ...)		{ if (globalLogger == NULL)	globalLogger->log(NextAI::Logger::Level::Error, format, tag, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); }
#define NEXTAI_TRACE_FUNC(tag)					{ if (globalLogger == NULL)	globalLogger->log(NextAI::Logger::Level::Trace, "", tag, __FILE__, __FUNCTION__, __LINE__); }
#else
#define NEXTAI_TRACE_LOG(tag, format, ...)	
#define NEXTAI_INFO_LOG(tag, format, ...)	
#define NEXTAI_WARN_LOG(tag, format, ...)
#define NEXTAI_ERROR_LOG(tag, format, ...)	
#define NEXTAI_TRACE_FUNC(tag)				
#endif
}

#else
#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"
#include "base/nextai_file_system.h"

namespace NextAI
{
	/* 日志 */
	class Logger
	{
	public:

		/* 输出平台 */
		enum class Platform
		{
			File = 0,	/* 文件（未实现） */
			Console,	/* 控制台 */
			Max
		};

		/* 输出级别 */
		enum class Level
		{
			Off,			/* 关闭 */
			Verbose,		/* 最详细 */
			Trace,			/* 跟踪函数调用 */
			Info,			/* 重要信息 */
			Warning,		/* 重要警告 */
			Error,			/* 致命错误 */
			Max
		};

	public:
		/* 单例模式 */
		static Logger* instance();

		/* 向控制台输入 */
		void print(const CHAR* fileName, const CHAR* funcName, int32 lineNum, Level level, const CHAR* content);
		void print(const CHAR* fileName, const CHAR* funcName, int32 lineNum, Level level, const WCHAR* content);

		/* 向文件输入 */
		void enableFile(const WCHAR* filePath);
		void disableFile();

		void setLevel(Platform output, Level level);

	private:
		Logger();

		/* 禁用拷贝构造函数 */
		DISABLE_CLASS_COPY(Logger);

		/* 裁剪文件名，不显示文件路径 */
		const CHAR* trimFileName(const CHAR* fileName);

		/* 日志输出级别 */
		Level m_logLevel[(int32)Platform::Max];

		/* 文件日志 */
		File m_file;
	};
}

#define SPRINTF(x,c,...) sprintf(x,##__VA_ARGS__)
#ifdef SYSTEM_LINUX
#define SWPRINTF(x,c,...) swprintf(x,c,##__VA_ARGS__)
#else
#define SWPRINTF(x,c,...) swprintf_s(x,##__VA_ARGS__) 
#endif

#define NEXTAI_VERBOSE_LOG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	SPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), format, ##__VA_ARGS__); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Verbose, _temp_log_buffer); }

#define NEXTAI_TRACE_LOG() { \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, "[START]"); }

#define NEXTAI_TRACE_LOG_END() { \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, "[END]"); }

#define NEXTAI_TRACE_LOG() {	\
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, ""); }

#define NEXTAI_TRACE_LOG_FLAG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	SPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), format, ##__VA_ARGS__); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, _temp_log_buffer); }

#define NEXTAI_TRACE_LOG_FLAG_END(flag) { \
	CHAR _temp_log_buffer[512]; \
	SPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), "[END] %s", flag); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, _temp_log_buffer); }

#define NEXTAI_INFO_LOG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	SPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), format, ##__VA_ARGS__); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Info, _temp_log_buffer); }

#define NEXTAI_INFO_LOG(format,...) { \
	WCHAR _temp_log_buffer[512]; \
	SWPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), format, ##__VA_ARGS__); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Info, _temp_log_buffer); }

#define NEXTAI_WARNING_LOG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	SPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), format, ##__VA_ARGS__); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Warning, _temp_log_buffer); }

#define NEXTAI_WARNING_W_LOG(format,...) { \
	WCHAR _temp_log_buffer[512]; \
	SWPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), format, ##__VA_ARGS__); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Warning, _temp_log_buffer); }

#define NEXTAI_ERROR_LOG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	SPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), format, ##__VA_ARGS__); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Error, _temp_log_buffer); }

#define NEXTAI_ERROR_W_LOG(format,...) { \
	WCHAR _temp_log_buffer[512]; \
	SWPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), format, ##__VA_ARGS__); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Error, _temp_log_buffer); }

#endif

#endif // !_NEXTAI_LOG_H_
