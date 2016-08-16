#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <string>

class Statistics {

friend class Simulator;

private:
	int pageRequests;
	int pageFaults;
	int diskWrites;
	//int diskReads;

public:
	Statistics() : pageRequests(0), pageFaults(0), diskWrites(0) {}
	~Statistics() {}
	std::string toString() const;
};

#endif /* STATISTICS_H_ */
