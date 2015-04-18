OBJECTS = main.o
CXX = g++
CFLAGS = -Wall -O -g

VPATH = ../src

game : $(OBJECTS)
	$(CXX) $(OBJECTS) -o game -lglut -lGL -lGLU

main.o : main.cpp
	$(CXX) $(CFLAGS) -c main.cpp -o main.o

.PHONY : clean
clean :
	-rm game $(objects)
