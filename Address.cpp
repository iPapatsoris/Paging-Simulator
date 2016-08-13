#include "Address.h"
#include <string>

using namespace std;

Address::Address(const int& processId, const int& pageNumber, const bool& dirty, const int& offset) {
	this->processId = processId;
	this->pageNumber = pageNumber;
	this->dirty = dirty;
	this->offset = offset;
}

bool Address::equals(Address address) {
	return pageNumber == address.pageNumber && processId == address.processId;
}

string Address::toString() {
	return to_string(processId)+" "+to_string(pageNumber)+" "+to_string(dirty);
}
