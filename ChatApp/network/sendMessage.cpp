#include "tcpsend.h"
#include "getIP.h"
#include <iostream>
#include "../encryption/encryption.h"

int sendMessage(std::string DestinationIP, std::string NextHop, std::string Message){
	std::string FullMessage = getIP() + "+" + DestinationIP + "+MSG+" + Message;
	//std::cout << FullMessage << std::endl;
	tcpsend(6969, NextHop, encrypt(FullMessage,getPublicKey()));


	return 0;
}
