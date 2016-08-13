#ifndef LRU_H_
#define LRU_H_

#include <forward_list>
#include "Address.h"

class LRU {

private:
	std::forward_list<Address *> recentList;

public:
	LRU();
	~LRU();
	std::forward_list<Address *>& getRecentList() {return recentList;}
	void prioritize(Address *address);
	void print();
};

#endif /* LRU_H_ */
