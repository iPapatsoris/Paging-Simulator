#ifndef INVERTEDPAGETABLE_H_
#define INVERTEDPAGETABLE_H_

#include "Address.h"

class InvertedPageTable {

private:
	Address **invertedPageTable;
	int invertedPageTableSize;

public:
	InvertedPageTable(const int& frames);
	~InvertedPageTable();
	Address **getFrameByAddress(const Address& address);
	Address **getFreeFrame();
	void occupyFrame(Address **frame, Address *content);
	void print();
};

#endif /* INVERTEDPAGETABLE_H_ */
