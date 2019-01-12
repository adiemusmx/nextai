#ifndef _NEXTAI_STDAFX_H_
#define _NEXTAI_STDAFX_H_

#ifdef SYSTEM_LINUX

#include <algorithm>
#include <sys/io.h>
#include <unistd.h>
#include "time.h"
#include "sys/time.h"

#else

#include <io.h>

#endif

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

#include "base/nextai_log.h"

#define BASE_TRACE_LOG(format, ...) NEXTAI_TRACE_LOG("BASE", format, ##__VA_ARGS__)
#define BASE_INFO_LOG(format, ...) NEXTAI_INFO_LOG("BASE", format, ##__VA_ARGS__)
#define BASE_WARN_LOG(format, ...) NEXTAI_WARN_LOG("BASE", format, ##__VA_ARGS__)
#define BASE_ERROR_LOG(format, ...) NEXTAI_ERROR_LOG("BASE", format, ##__VA_ARGS__)
#define BASE_TRACE_FUNC() NEXTAI_TRACE_FUNC("BASE")

#endif // !_NEXTAI_STDAFX_H_