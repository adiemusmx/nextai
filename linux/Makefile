# The Target File Name
TARGET = snake

# Compile Tool
CXX = g++

# Objects Files
OBJECTS = main.o

# CLAGS
CFLAGS := -Wall
CFLAGS += -O
CFLAGS += -g
CFLAGS += -MM

# Libraries
LIBS  = -lglut
LIBS += -lGL
LIBS += -lGLU

# VPATH
VPATH = ../src

$(TARGET) : $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS) 

.PHONY : clean
clean :
	-rm $(TARGET) $(OBJECTS)
