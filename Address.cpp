#include "Address.h"
#include <string>

using namespace std;

Address::Address(const int& processId, const int& pageNumber, const bool& dirty) {
	this->processId = processId;
	this->pageNumber = pageNumber;
	this->dirty = dirty;
}

bool Address::equals(const Address& address) {
	return pageNumber == address.pageNumber && processId == address.processId;
}

bool Address::operator == (const Address& address) const {
	return pageNumber == address.pageNumber && processId == address.processId;
}

string Address::toString() {
	return to_string(processId)+" "+to_string(pageNumber)+" "+to_string(dirty);
}
