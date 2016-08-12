OBJS =  Launcher.o Simulator.o

all: psim

CC 	= g++
FLAGS	= -c

psim: $(OBJS) 
	$(CC) -o psim $(OBJS)

Launcher.o: Launcher.cpp
	$(CC) $(FLAGS) Launcher.cpp

Simulator.o: Simulator.cpp
	$(CC) $(FLAGS) Simulator.cpp

clean:
	rm -f psim $(OBJS)
	
	