# Compile Tool
CXX = g++
AR = ar

# CFLAGS
CFLAGS  = -Wall
CFLAGS += -std=c++14
CFLAGS += -O
CFLAGS += -g
CFLAGS += -DGLUT_DISABLE_ATEXIT_HACK
CFLAGS += -DGLUT_NO_WARNING_DISABLE
CFLAGS += -DGLUT_NO_LIB_PRAGMA
CFLAGS += -DBUILD_DEBUG
CFALGS += -DCOMPILER_MINGW

ifeq ($(shell uname), Linux)
CFLAGS += -DSYSTEM_LINUX
else
CFLAGS += -DSYSTEM_WINDOWS
endif

ifeq ($(shell getconf LONG_BIT), 32)
CFLAGS += -DARCH_X86
else
CFLAGS += -DARCH_X64
endif

# Include dir
INCLUDE_DIRS  = -I../base/include/
INCLUDE_DIRS += -I../render_system/include/
INCLUDE_DIRS += -I../third_party/include/
INCLUDE_DIRS += -I../trinity/include/

# Libraries
LDFLAGS =
ifeq ($(shell uname), Linux)
LDFLAGS += -lGL
LDFLAGS += -lGLU
LDFLAGS += -lglut
else
LDFLAGS += -lwinmm
LDFLAGS += -lopengl32
LDFLAGS += -lglu32
LDFLAGS += -lglut32
endif

LDFLAGS += -lbase
LDFLAGS += -lrender_system
LDFLAGS += -ltrinity
LDFLAGS += -lFreeImage_win32

# Libraries dir
LIBS_DIRS  = -L../base/lib/
LIBS_DIRS += -L../trinity/lib/
LIBS_DIRS += -L../third_party/lib/
LIBS_DIRS += -L../render_system/lib/
