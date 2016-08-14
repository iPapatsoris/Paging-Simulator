#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>

class Address {

private:
	int processId;
	int pageNumber;
	bool dirty;

public:
	Address(const int& processId, const int& pageNumber, const bool& dirty);
	~Address() {}
	bool getDirty() {return dirty;}
	int getProcessId() {return processId;}
	int getPageNumber() {return pageNumber;}
	void setDirty(const bool& dirty) {this->dirty = dirty;}
	bool equals(const Address& address);
	bool operator == (const Address& address) const;
	std::string toString();
};

#endif /* ADDRESS_H_ */
