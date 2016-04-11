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
vector<tableEntry> fwdTable;

string getNextHop(string);

int main() {
	std::string DestinationIP;
	std::string MyIP = getIP();
	std::string Message;
	std::thread routing(start, &fwdTable);
	std::thread test(tcpreceive ,6969, std::ref(q));

	std::cout << "Destination IP" << std::endl;
	std::cin >> DestinationIP;
	std::cout << "Say something: " << std::endl;
	while(1){

		std::getline(std::cin, Message);
		sendMessage(DestinationIP, getNextHop(DestinationIP), Message);

	}

}

string getNextHop(string dest){
	string output = "";
	for(auto& items: fwdTable){
		if(items.dest == dest)output=items.via;
	}
	return output;
}

