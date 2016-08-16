#ifndef LRU_H_
#define LRU_H_

#include <list>
#include "Address.h"

/* Keep most recent page requests at the front of the list.
 * Last element is the least recently used. */
class LRU {

private:
	std::list<Address *> recentList;

public:
	LRU() {}
	~LRU() {}
	std::list<Address *>& getRecentList() {return recentList;}
	void prioritize(Address *address);
	Address *getVictim();
	void print() const;
};

#endif /* LRU_H_ */
