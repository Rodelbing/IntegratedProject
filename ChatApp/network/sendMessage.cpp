#include "tcpsend.h"
#include "getIP.h"
#include <iostream>
int sendMessage(std::string DestinationIP, std::string Message){
	std::string FullMessage = getIP() + "+" + DestinationIP + "+" + Message;
	//std::cout << FullMessage << std::endl;
	tcpsend(55056, DestinationIP, FullMessage);


	return 0;
}
