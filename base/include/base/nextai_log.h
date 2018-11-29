#ifndef _NEXTAI_LOG_H_
#define _NEXTAI_LOG_H_

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
#define SWPRINTF(x,c,...) swprintf(x,##__VA_ARGS__) 
#endif

#define NEXTAI_VERBOSE_LOG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	SPRINTF(_temp_log_buffer, element_of(_temp_log_buffer), format, ##__VA_ARGS__); \
	NextAI::Logger::instance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Verbose, _temp_log_buffer); }

#define NEXTAI_TRACE_LOG_START() { \
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

#define NEXTAI_INFO_W_LOG(format,...) { \
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

#endif // !_NEXTAI_LOG_H_
