//GUI? zie SFML

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
	std::thread test(tcpreceive ,6969, std::ref(q));

	std::cout << "Destination IP" << std::endl;
	std::cin >> DestinationIP;
	std::cout << "Say something: " << std::endl;
	while(1){

		std::getline(std::cin, Message);
		sendMessage(DestinationIP, DestinationIP, Message);

	}

}
