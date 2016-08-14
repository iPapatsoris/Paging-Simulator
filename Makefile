OBJS =  Launcher.o Simulator.o Address.o InvertedPageTable.o LRU.o WorkingSet.o Statistics.o
HEADER = Simulator.h Address.h InvertedPageTable.h LRU.h WorkingSet.h Statistics.h

all: psim

CC 	= g++ -g
FLAGS	= -c 

psim: $(OBJS) $(HEADER)
	$(CC) -o psim $(OBJS)

Launcher.o: Launcher.cpp
	$(CC) $(FLAGS) Launcher.cpp -std=c++11

Simulator.o: Simulator.cpp
	$(CC) $(FLAGS) Simulator.cpp -std=c++11

Address.o: Address.cpp
	$(CC) $(FLAGS) Address.cpp -std=c++11

InvertedPageTable.o: InvertedPageTable.cpp
	$(CC) $(FLAGS) InvertedPageTable.cpp

LRU.o: LRU.cpp
	$(CC) $(FLAGS) LRU.cpp 

WorkingSet.o: WorkingSet.cpp
	$(CC) $(FLAGS) WorkingSet.cpp -std=c++11

Statistics.o: Statistics.cpp
	$(CC) $(FLAGS) Statistics.cpp -std=c++11
	
clean:
	rm -f psim $(OBJS)
	
	