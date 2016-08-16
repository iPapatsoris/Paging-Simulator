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
	bool getDirty() const {return dirty;}
	int getProcessId() const {return processId;}
	int getPageNumber() const {return pageNumber;}
	void setDirty(const bool& dirty) {this->dirty = dirty;}
	bool equals(const Address& address) const;
	bool operator == (const Address& address) const;
	std::string toString() const;
	void print() const;
};

#endif /* ADDRESS_H_ */
