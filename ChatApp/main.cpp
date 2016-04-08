#include <thread>
#include <cstring>
#include <unistd.h>
#include <vector>
//#include <SDL.h>
#include <stdio.h>

#include "network/getIP.h"
#include "network/multisend.h"
#include "network/multisend.h"
#include "network/tcpsend.h"
#include "network/tcpreceive.h"
#include "lib/BlockingQueue.h"
#include "network/multireceive.h"
#include "network/sendMessage.h"


BlockingQueue<std::string> q;

struct tableEntry{
		string dest;
		string via;
	};

int main() {
	std::string DestinationIP;
	std::string MyIP = getIP();
	std::string Message;
	vector<tableEntry> fwdTable;
	//multisend(14000, "228.1.2.3", MyIP, "HALLO");
	//tcpsend(55056, "192.168.5.2", "Holabola");
	std::thread receiver(tcpreceive, 14000, std::ref(q));
	std::cout << "With who will you chat this session?" << std::endl;
	std::cin >> DestinationIP;
	std::cout << "Say something! (or I'm giving up on you.)" << std::endl;
	while (1) {

		std::getline(std::cin, Message);
		std::cout << "You: " << Message << std::endl;
		sendMessage(DestinationIP, DestinationIP, Message);
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//std::string message = q.pop();
		//std::cout << message << std::endl;
	}

}
