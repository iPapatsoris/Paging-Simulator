#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>

class Address {

private:
	int processId;
	int pageNumber;
	int offset;
	bool dirty;

public:
	Address(const int& processId, const int& pageNumber, const bool& dirty, const int& offset);
	~Address();
	bool getDirty() {return dirty;}
	int getProcessId() {return processId;}
	int getPageNmuber() {return pageNumber;}
	void setDirty(const bool& dirty) {this->dirty = dirty;}
	bool equals(Address address);
	std::string toString();
};

#endif /* ADDRESS_H_ */
