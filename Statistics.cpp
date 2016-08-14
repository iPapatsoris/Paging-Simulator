#include "Statistics.h"

using namespace std;

string Statistics::toString() {
	return "\nPage requests: "+to_string(pageRequests)+"\nPage faults: "+to_string(pageFaults)
					 +"\nDisk writes: "+to_string(diskWrites);
}


