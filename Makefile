OBJS =  Launcher.o Simulator.o Address.o InvertedPageTable.o LRU.o WorkingSet.o Statistics.o
HEADER = Simulator.h Address.h InvertedPageTable.h LRU.h WorkingSet.h Statistics.h

all: psim

CC 	= g++
FLAGS	= -c -std=c++11

psim: $(OBJS) $(HEADER)
	$(CC) -o psim $(OBJS)

Launcher.o: Launcher.cpp
	$(CC) $(FLAGS) Launcher.cpp 

Simulator.o: Simulator.cpp
	$(CC) $(FLAGS) Simulator.cpp

Address.o: Address.cpp
	$(CC) $(FLAGS) Address.cpp

InvertedPageTable.o: InvertedPageTable.cpp
	$(CC) $(FLAGS) InvertedPageTable.cpp

LRU.o: LRU.cpp
	$(CC) $(FLAGS) LRU.cpp 

WorkingSet.o: WorkingSet.cpp
	$(CC) $(FLAGS) WorkingSet.cpp

Statistics.o: Statistics.cpp
	$(CC) $(FLAGS) Statistics.cpp 
	
clean:
	rm -f psim $(OBJS)
	
	