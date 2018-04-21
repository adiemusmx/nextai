#ifndef _TRINITY_UTIL_LOG_H_
#define _TRINITY_UTIL_LOG_H_

#include "base/mapbar_basic_define.h"
#include "base/mapbar_basic_types.h"

namespace MapBarDL
{

// LOG output dest
enum E_LOG_OUTPUT
{
	E_LOG_OUTPUT_FILE,			// File
	E_LOG_OUTPUT_CONSOLE,		// Console
	E_LOG_OUTPUT_MAX
};

// LOG output level
enum E_LOG_LEVEL
{
	E_LOG_LEVEL_OFF,			// Off
	E_LOG_LEVEL_VERBOSE,		// detail
	E_LOG_LEVEL_TRACE,			// trace
	E_LOG_LEVEL_INFO,			// infomation
	E_LOG_LEVEL_WARNING,		// warning
	E_LOG_LEVEL_ERROR,			// error
	E_LOG_LEVEL_MAX
};

// Log object
class Logger
{
public:
	// Single instance
	static Logger* getInstance();

	// Output log text
	void print(const CHAR* fileName, const CHAR* funcName, int32 lineNum, E_LOG_LEVEL level, const CHAR* content);

	// TODO
	void openFile(CHAR* filePath);
	void closeFile();

	void setLevel(E_LOG_OUTPUT output, E_LOG_LEVEL level);

private:
	Logger();

	// Disable copy constructor
	DISABLE_CLASS_COPY(Logger);

	const CHAR* trimFileName(const CHAR* fileName);

	BOOL m_logLevel[E_LOG_OUTPUT_MAX];
};
}

#define TRI_VERBOSE_LOG(format,...) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_VERBOSE, _temp_log_buffer); }

#define TRI_TRACE_LOG_START() { \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, "[START]");}

#define TRI_TRACE_LOG_END() { \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, "[END]"); }

#define TRI_TRACE_LOG() {	\
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, ""); }

#define TRI_TRACE_LOG_FLAG(flag) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, "%s", flag); \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, _temp_log_buffer); }

#define TRI_TRACE_LOG_FLAG_END(flag) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, "[END] %s", flag); \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, _temp_log_buffer); }

#define TRI_INFO_LOG(format,...) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_INFO, _temp_log_buffer); }

#define TRI_INFO_W_LOG(format,...) { \
		WCHAR _temp_log_buffer[512]; \
		swprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_INFO, _temp_log_buffer); }

#define TRI_WARNING_LOG(format,...) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_WARNING, _temp_log_buffer); }

#define TRI_WARNING_W_LOG(format,...) { \
		WCHAR _temp_log_buffer[512]; \
		swprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_WARNING, _temp_log_buffer); }

#define TRI_ERROR_LOG(format,...) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_ERROR, _temp_log_buffer); }

#define TRI_ERROR_W_LOG(format,...) { \
		WCHAR _temp_log_buffer[512]; \
		swprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FILE__, __FUNCTION__, __LINE__, E_LOG_LEVEL_ERROR, _temp_log_buffer); }

#endif // !_TRINITY_UTIL_LOG_H_