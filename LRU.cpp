#include "LRU.h"
#include <iostream>

using namespace std;

/* Remove specific Address and put at the front */
void LRU::prioritize(Address *address) {
	recentList.remove(address);
	recentList.push_front(address);
}

/* Remove and return victim Address found in the back */
Address *LRU::getVictim() {
	Address *victim = recentList.back();
	recentList.pop_back();
	return victim;
}

void LRU::print() {
	cout << "=== Recent List === " << endl;
	for (list<Address *>::iterator it = recentList.begin() ; it != recentList.end() ; it++) {
		cout << (*it)->toString() << endl;
	}
}
