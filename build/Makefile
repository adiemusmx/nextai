# The Target File Name
TARGET = app.exe

# Compile Tool
CXX = g++

# Objects Files
INCLUDES = $(wildcard ../include/*.h)
SOURCES = $(wildcard ../src/*.cpp) $(wildcard ../src/*.c)
OBJECTS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
DEPENDENCE = $(OBJECTS:.o=.d) 

# CLAGS
CFLAGS := -Wall
CFLAGS += -O
CFLAGS += -g
CFLAGS += -DGLUT_DISABLE_ATEXIT_HACK
CFLAGS += -DGLUT_NO_WARNING_DISABLE

# Libraries dir
LIBS_DIRS = -L../lib/

# Libraries
LDFLAGS = -lopengl32
LDFLAGS += -lglu32
LDFLAGS += -lglut32

# Include dir
INCLUDE_DIRS = -I../include/

	
$(TARGET) : $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS_DIRS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
	
%.o : %.c
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)

include $(DEPENDENCE)

define gen_dep   
set -e; rm -f $@; \
$(CXX) -MM $(CFLAGS) $< > $@.$$$$; \
sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
rm -f $@.$$$$
endef

%.d: %.c  
	$(gen_dep)
	
%.d: %.cpp  
	$(gen_dep)

.PHONY : clean
clean :
	rm -rf $(TARGET) $(OBJECTS) $(DEPENDENCE)
