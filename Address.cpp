#include "Address.h"
#include <string>

using namespace std;

Address::Address(const int& processId, const int& pageNumber, const int& offset) {
	this->processId = processId;
	this->pageNumber = pageNumber;
	this->offset = offset;
}

Address::~Address() {
	// TODO Auto-generated destructor stub
}

string Address::toString() {
	return to_string(processId)+" "+to_string(pageNumber)+" "+to_string(offset);
}
