#include <thread>
#include <cstring>
#include <unistd.h>

#include "network/getIP.h"
#include "network/multisend.h"
#include "network/multirecieve.h"
#include "network/multisend.h"
#include "network/tcpsend.h"
#include "network/tcpreceive.h"
#include "lib/BlockingQueue.h"
#include "network/sendMessage.h"

BlockingQueue<std::string> q;

int main() {
	std::string DestinationIP;
	std::string MyIP = getIP();
	std::string Message;
	//multisend(14000, "228.1.2.3", MyIP, "HALLO");
	//std::thread receiver(multirecieve, 14000, "228.1.2.3", MyIP,std::ref(q));
	//tcpsend(55056, "192.168.5.2", "Holabola");
	std::thread receiver(tcpreceive, 55056, )
	std::cout << "With who will you chat this session?" << std::endl;
	std::cin >> DestinationIP;
	while (1) {
		std::cin >> Message;
		std::cout << "You: " << Message << std::endl;
		sendMessage("192.168.5.1", Message);
		//std::string message = q.pop();
		//std::cout << message << std::endl;
	}

}
