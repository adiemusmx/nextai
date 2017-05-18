# The Target File Name
TARGET = app.exe
.PHONY : clean

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

ifeq ($(shell uname), Linux) 
CFLAGS += -D_LINUX
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
	
%.d : %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CFLAGS) $< $(INCLUDE_DIRS) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.d: %.c
	set -e; rm -f $@; \
	$(CXX) -MM $(CFLAGS) $< $(INCLUDE_DIRS) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(DEPS)

clean :
	rm -rf $(TARGET) $(OBJECTS) $(DEPS)
