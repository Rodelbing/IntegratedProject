#include <thread>
#include <cstring>
#include <unistd.h>

#include "network/multisend.h"
#include "network/multirecieve.h"
#include "network/multisend.h"
#include "network/tcpsend.h"
#include "lib/BlockingQueue.h"

BlockingQueue<std::string> q;

int main() {

	//std::thread receiver(multirecieve, 14000, "228.1.2.3", "192.168.5.2",std::ref(q));
	tcpsend(4242, "192.168.5.2", "192,168.5.1", "Holabola TCP!");
	//multisend(55056, "228.1.2.3", "192,168.5.2", "Holabola");
	//while (1) {

		//std::string message = q.pop();
		//std::cout << "main thread sees something! It sees:" << std::endl;
		//std::cout << message << std::endl;

		//}

	}
