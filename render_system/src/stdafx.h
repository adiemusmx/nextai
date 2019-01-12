#ifndef _STDAFX_H_
#define _STDAFX_H_

#include "base/nextai_basic_define.h"
#include "base/nextai_file_system.h"
#include "base/nextai_log.h"

#include <GL/glut.h>
#include <GL/glu.h>

#define RENDER_SYSTEM_TRACE_LOG(format, ...) NEXTAI_TRACE_LOG("RENDER_SYSTEM", format, ##__VA_ARGS__)
#define RENDER_SYSTEM_INFO_LOG(format, ...) NEXTAI_INFO_LOG("RENDER_SYSTEM", format, ##__VA_ARGS__)
#define RENDER_SYSTEM_WARN_LOG(format, ...) NEXTAI_WARN_LOG("RENDER_SYSTEM", format, ##__VA_ARGS__)
#define RENDER_SYSTEM_ERROR_LOG(format, ...) NEXTAI_ERROR_LOG("RENDER_SYSTEM", format, ##__VA_ARGS__)
#define RENDER_SYSTEM_TRACE_FUNC() NEXTAI_TRACE_FUNC("RENDER_SYSTEM")

#endif // !_STDAFX_H_