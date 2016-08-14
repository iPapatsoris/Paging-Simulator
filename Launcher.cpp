#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Simulator.h"
using namespace std;

#define FRAME_SIZE 4096

int main(int argc, char **argv) {
	if (argc < 7) {
		cout << "Failure: usage: -a <algorithm> -f <frames> -q <quantum>" << endl;
		exit(EXIT_FAILURE);
	}

	string replacementAlgorithm = "";
	int frames = 0;
	int quantum = 0;
	int workingSetSize = 0;
	int maxReferences = -1;
	int frameSize = FRAME_SIZE;

	/* Argument parse */
	for (int i=1 ; i < argc ; i++) {
		if (!strcmp(argv[i],"-a")) {
			replacementAlgorithm = argv[++i];
			if (replacementAlgorithm.compare("lru") && replacementAlgorithm.compare("ws")) {
				cout << "Failure: algorithm should be either lru or ws" << endl;
				exit(EXIT_FAILURE);
			}
		}
		else if (!strcmp(argv[i], "-f")) {
			frames = atoi(argv[++i]);
		}
		else if (!strcmp(argv[i], "-q")) {
			quantum = atoi(argv[++i]);
		}
		else if (!strcmp(argv[i], "-w")) {
			workingSetSize = atoi(argv[++i]);
		}
		else if (!strcmp(argv[i], "-m")) {
			maxReferences = atoi(argv[++i]);
		}
	}

	if (! replacementAlgorithm.compare("") || !frames || !quantum) {
		cout << "Failure: usage: -a <algorithm> -f <frames> -q <quantum>" << endl;
		exit(EXIT_FAILURE);
	}
	if (!replacementAlgorithm.compare("ws") && !workingSetSize) {
		cout << "Failure: did not provide working set size with -w <window>" << endl;
		exit(EXIT_FAILURE);
	}
	if (!replacementAlgorithm.compare("ws") && workingSetSize > frames) {
			cout << "Failure: working set size should be less or equal to the number of frames" << endl;
			exit(EXIT_FAILURE);
		}
	cout << replacementAlgorithm << " " << frames << " " << quantum  << endl;
	cout << workingSetSize << maxReferences << endl;

	Simulator sim(replacementAlgorithm, frames, frameSize, quantum, workingSetSize, maxReferences);
	sim.run();
}
