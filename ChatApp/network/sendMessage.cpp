#include "tcpsend.h"
#include "getIP.h"
#include <iostream>

int sendMessage(std::string Source, std::string DestinationIP, std::string NextHop, std::string Message){
	std::string FullMessage = Source + "+" + DestinationIP + "+MSG+" + Message;
	//std::cout << FullMessage << std::endl;
	tcpsend(6969, NextHop, FullMessage);


	return 0;
}
