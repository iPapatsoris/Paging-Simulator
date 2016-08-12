#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>

class Address {

private:
	int processId;
	int pageNumber;
	int offset;

public:
	Address(const int& processId, const int& pageNumber, const int& offset);
	~Address();
	std::string toString();
};

#endif /* ADDRESS_H_ */
