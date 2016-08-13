#include "LRU.h"
#include <iostream>

using namespace std;

LRU::LRU() {
	// TODO Auto-generated constructor stub

}

LRU::~LRU() {
	// TODO Auto-generated destructor stub
}

void LRU::prioritize(Address *address) {
	recentList.remove(address);
	recentList.push_front(address);
}

void LRU::print() {
	cout << "=== Recent List === " << endl;
	for (forward_list<Address *>::iterator it = recentList.begin() ; it != recentList.end() ; it++) {
		cout << (*it)->toString() << endl;
	}
}
