# The Target File Name
TARGET = app

# Compile Tool
CXX = g++

# Objects Files
INCLUDES = $(wildcard ../include/*.h)
SOURCES = $(wildcard ../src/*.cpp) $(wildcard ../src/*.c)
OBJECTS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
DEPS = $(OBJECTS:%.o=%.d) 

# CLAGS
CFLAGS = -Wall
CFLAGS += -O
CFLAGS += -g
CFLAGS += -DGLUT_DISABLE_ATEXIT_HACK
CFLAGS += -DGLUT_NO_WARNING_DISABLE

CFLAGS += -DBUILD_DEBUG

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

# Libraries dir
LIBS_DIRS = -L../lib/

# Libraries
LDFLAGS =
ifeq ($(shell uname), Linux)
LDFLAGS += -lGL
LDFLAGS += -lGLU
LDFLAGS += -lglut
else
LDFLAGS += -lopengl32
LDFLAGS += -lglu32
LDFLAGS += -lglut32
endif

# Include dir
INCLUDE_DIRS = -I../include/

$(TARGET) : $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS_DIRS) $(LDFLAGS)
%.o : %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
%.o : %.c
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
	
define DEP_BUILD
@set -e; rm -f $@; \
$(CXX) -MM $(CFLAGS) $< $(INCLUDE_DIRS) > $@.$$$$; \
sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
rm -f $@.$$$$
endef

%.d : %.cpp
	$(DEP_BUILD)
%.d: %.c
	$(DEP_BUILD)

-include $(DEPS)
.PHONY : clean
clean :
	rm -rf $(TARGET) $(OBJECTS) $(DEPS)
