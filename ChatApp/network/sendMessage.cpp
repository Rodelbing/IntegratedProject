#include "tcpsend.h"
#include "getIP.h"
#include <iostream>
int sendMessage(std::string ClientIP, std::string Message){
	std::string FullMessage = getIP() + ClientIP + Message;
	std::cout << FullMessage << std::endl;
	tcpsend(55056, ClientIP, FullMessage);


	return 0;
}
