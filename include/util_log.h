#pragma once

#include "common_define.h"
#include "common_types.h"

namespace Trinity
{

// LOG输出的位置
enum E_LOG_OUTPUT
{
	E_LOG_OUTPUT_FILE,			// 输出到文件
	E_LOG_OUTPUT_CONSOLE,		// 输出到控制台
	E_LOG_OUTPUT_MAX
};

// LOG输出的级别
enum E_LOG_LEVEL
{
	E_LOG_LEVEL_OFF,			// 关闭
	E_LOG_LEVEL_VERBOSE,		// 最详细
	E_LOG_LEVEL_TRACE,			// 跟踪函数调用
	E_LOG_LEVEL_INFO,			// 输出信息
	E_LOG_LEVEL_WARNING,		// 发生警告，可能不会影响功能
	E_LOG_LEVEL_ERROR,			// 发生错误，会影响功能
	E_LOG_LEVEL_MAX
};

// 输出log的对象
class Logger
{
public:
	// 初始化LogManager
	static Logger* getInstance();

	// 输出LOG
	void print(const char* funcName, int32 lineNum, E_LOG_LEVEL level, const char* content);

	// #未实现# 设定文件输出路径，最大D_TEXT_MAX_LENGTH
	void openFile(char* filePath);
	void closeFile();

	void setLevel(E_LOG_OUTPUT output, E_LOG_LEVEL level);

private:
	Logger();

	D_CLASS_DISABLE_COPY(Logger);

	BOOL m_logLevel[E_LOG_OUTPUT_MAX];
};
}

#define TRI_VERBOSE_LOG(format,...) { \
		cqCHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_VERBOSE, _temp_log_buffer); }

#define TRI_TRACE_LOG_START() { \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, "[START]");}

#define TRI_TRACE_LOG_END() { \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, "[END]"); }

#define TRI_TRACE_LOG() {	\
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, ""); }

#define TRI_TRACE_LOG_FLAG(flag) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, "%s", flag); \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, _temp_log_buffer); }

#define TRI_TRACE_LOG_FLAG_END(flag) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, "[END] %s", flag); \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, _temp_log_buffer); }

#define TRI_INFO_LOG(format,...) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_INFO, _temp_log_buffer); }

#define TRI_INFO_W_LOG(format,...) { \
		WCHAR _temp_log_buffer[512]; \
		swprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_INFO, _temp_log_buffer); }

#define TRI_WARNING_LOG(format,...) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_WARNING, _temp_log_buffer); }

#define TRI_WARNING_W_LOG(format,...) { \
		WCHAR _temp_log_buffer[512]; \
		swprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_WARNING, _temp_log_buffer); }

#define TRI_ERROR_LOG(format,...) { \
		CHAR _temp_log_buffer[512]; \
		sprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_ERROR, _temp_log_buffer); }

#define TRI_ERROR_W_LOG(format,...) { \
		WCHAR _temp_log_buffer[512]; \
		swprintf(_temp_log_buffer, format, ##__VA_ARGS__); \
		Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_ERROR, _temp_log_buffer); }
