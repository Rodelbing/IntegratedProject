#include "tcpsend.h"
#include "getIP.h"
#include <iostream>
int sendMessage(std::string DestinationIP, std::string NextHop, std::string Message){
	std::string FullMessage = getIP() + "+" + DestinationIP + "+MSG+" + Message;
	//std::cout << FullMessage << std::endl;
	tcpsend(6968, NextHop, FullMessage);


	return 0;
}
