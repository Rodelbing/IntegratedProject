#include <thread>
#include <cstring>
#include <unistd.h>

#include "receiver.h"
#include "sender.h"
#include "BlockingQueue.h"

#define PORT 14000 //The port you want to use
#define IP "192.168.5.1" //The IP address of this computer
#define GROUP "228.1.2.3" //The multicast group you want to use

using namespace std;

BlockingQueue<std::string> q;

int main() {
	thread sender(sendPacket, IP, PORT, GROUP); //start networking sending thread
	thread receiver(receivePacket, IP, PORT, GROUP, std::ref(q)); //start network receiving thread

	while(1)
	{
		std::string message = q.pop();
		printf("Packet of size %d received, message: %s\n", (int)message.size(), message.c_str());
	}
}
