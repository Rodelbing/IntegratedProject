//GUI? zie SFML

#include <thread>
#include <cstring>
#include <unistd.h>
#include <vector>
#include "lib/Includes.h"
#include "network/getIP.h"
#include "network/multisend.h"
#include "network/multisend.h"
#include "network/tcpsend.h"
#include "network/tcpreceive.h"
#include "lib/BlockingQueue.h"
#include "network/multireceive.h"
#include "network/sendMessage.h"
#include "network/distancevector.h"
#include "encryption/encryption.h"

static BlockingQueue<std::string> q;
vector<tableEntry> fwdTable;

int main() {
	std::string DestinationIP;
	std::string MyIP = getIP();
	std::string Message;
	std::thread routing(start, &fwdTable);
	std::thread test(tcpreceive ,6969, std::ref(q), &fwdTable);

	std::cout << "Destination IP" << std::endl;
	std::cin >> DestinationIP;
	std::cout << "Say something: " << std::endl;
	while(1){
		std::getline(std::cin, Message);
		if (Message.size()==0){
			Message = getIP() + " is connected to you.";
		}
		//sendMessage( DestinationIP, getNextHop(DestinationIP, fwdTable), encrypt(Message,getPublicKey()));
		string Hoi = encrypt(Message,getPublicKey());
		std:: cout << Hoi << ", " << decrypt(Hoi, getPublicKey()) << std::endl;
		//std::cout << getNextHop(DestinationIP) << std::endl;
	}

}


