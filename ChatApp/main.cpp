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

BlockingQueue<std::string> q;

int main() {

	std::string MyIP = getIP();

	multisend(14000, "228.1.2.3", MyIP, "HALLO");
	std::thread receiver(multirecieve, 14000, "228.1.2.3", MyIP,std::ref(q));
	tcpsend(55056, MyIP, "192,168.5.2", "Holabola");
	while (1) {
		std::string message = q.pop();
		std::cout << "main thread sees something! It sees:" << std::endl;
		std::cout << message << std::endl;
	}

}
