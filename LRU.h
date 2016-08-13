#ifndef LRU_H_
#define LRU_H_

#include <list>
#include "Address.h"

class LRU {

private:
	std::list<Address *> recentList;

public:
	LRU() {}
	~LRU() {}
	std::list<Address *>& getRecentList() {return recentList;}
	void prioritize(Address *address);
	Address *getVictim();
	void print();
};

#endif /* LRU_H_ */
