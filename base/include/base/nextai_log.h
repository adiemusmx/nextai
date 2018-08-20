#ifndef _NEXTAI_LOG_H_
#define _NEXTAI_LOG_H_

#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"

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
		// Single instance
		static Logger* getInstance();

		// Output log text
		void print(const CHAR* fileName, const CHAR* funcName, int32 lineNum, Level level, const CHAR* content);
		void print(const CHAR* fileName, const CHAR* funcName, int32 lineNum, Level level, const WCHAR* content);

		// TODO
		void openFile(CHAR* filePath);
		void closeFile();

		void setLevel(Platform output, Level level);

	private:
		Logger();

		/* 禁用拷贝构造函数 */
		DISABLE_CLASS_COPY(Logger);

		const CHAR* trimFileName(const CHAR* fileName);

		Level m_logLevel[(int32)Platform::Max];
	};
}

#define NEXTAI_VERBOSE_LOG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Verbose, _temp_log_buffer); }

#define NEXTAI_TRACE_LOG_START() { \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, "[START]"); }

#define NEXTAI_TRACE_LOG_END() { \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, "[END]"); }

#define NEXTAI_TRACE_LOG() {	\
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, ""); }

#define NEXTAI_TRACE_LOG_FLAG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, _temp_log_buffer); }

#define NEXTAI_TRACE_LOG_FLAG_END(flag) { \
	CHAR _temp_log_buffer[512]; \
	sprintf(_temp_log_buffer, "[END] %s", flag); \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Trace, _temp_log_buffer); }

#define NEXTAI_INFO_LOG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Info, _temp_log_buffer); }

#define NEXTAI_INFO_W_LOG(format,...) { \
	WCHAR _temp_log_buffer[512]; \
	swprintf_s(_temp_log_buffer, format, ##__VA_ARGS__); \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Info, _temp_log_buffer); }

#define NEXTAI_WARNING_LOG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Warning, _temp_log_buffer); }

#define NEXTAI_WARNING_W_LOG(format,...) { \
	WCHAR _temp_log_buffer[512]; \
	swprintf_s(_temp_log_buffer, format, ##__VA_ARGS__); \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Warning, _temp_log_buffer); }

#define NEXTAI_ERROR_LOG(format,...) { \
	CHAR _temp_log_buffer[512]; \
	sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Error, _temp_log_buffer); }

#define NEXTAI_ERROR_W_LOG(format,...) { \
	WCHAR _temp_log_buffer[512]; \
	swprintf_s(_temp_log_buffer, format, ##__VA_ARGS__); \
	NextAI::Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, NextAI::Logger::Level::Error, _temp_log_buffer); }

#endif // !_NEXTAI_LOG_H_
