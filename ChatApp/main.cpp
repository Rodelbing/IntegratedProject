#include <thread>
#include <cstring>
#include <unistd.h>
#include <vector>

#include "network/getIP.h"
#include "network/multisend.h"
#include "network/multisend.h"
#include "network/tcpsend.h"
#include "network/tcpreceive.h"
#include "lib/BlockingQueue.h"
#include "network/multireceive.h"
#include "network/sendMessage.h"
#include "network/distancevector.h"

static BlockingQueue<std::string> q;

int main() {
	std::string DestinationIP;
	std::string MyIP = getIP();
	std::string Message;
	vector<tableEntry> fwdTable;
	std::thread routing(start, &fwdTable);
	//std::thread test(multireceive ,14000, "228.1.2.3", MyIP, std::ref(q));

	while(1){

	}

}
