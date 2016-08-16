#include "Address.h"
#include <string>
#include <iostream>

using namespace std;

Address::Address(const int& processId, const int& pageNumber, const bool& dirty) {
	this->processId = processId;
	this->pageNumber = pageNumber;
	this->dirty = dirty;
}

bool Address::equals(const Address& address) const {
	return pageNumber == address.pageNumber && processId == address.processId;
}

bool Address::operator == (const Address& address) const {
	return this->equals(address);
}

string Address::toString() const {
	return to_string(processId)+" "+to_string(pageNumber)+" "+to_string(dirty);
}

void Address::print() const {
	cout << "Requesting page " << pageNumber << " from process " << processId << " for "
		 << (dirty ? "WRITE." : "READ.") << endl;
}
