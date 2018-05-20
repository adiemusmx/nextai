# The Target File Name
TARGET = app.exe

# Common makefile
include ../build/configuration.mk

SOURCES := $(wildcard src/*.cpp) $(wildcard src/*.c)
OBJECTS := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$(TARGET) : $(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBS_DIRS) $(LDFLAGS) -o $(TARGET)
%.o : %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
%.o : %.c
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
	
#define DEP_BUILD
#@set -e; rm -f $@; \
$(CXX) -MM $(CFLAGS) $< $(INCLUDE_DIRS) > $@.$$$$; \
sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
rm -f $@.$$$$
#endef

#%.d : %.cpp
#	$(DEP_BUILD)
#%.d: %.c
#	$(DEP_BUILD)

#-include $(DEPS)
.PHONY : clean
clean :
#	rm -rf $(TARGET) $(OBJECTS) $(DEPS) ../src/*.d.* ../src/*.d
	rm -rf $(TARGET) ./src/*.o
