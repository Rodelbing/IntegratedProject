#include "getIP.h"
#include <iostream>
int analyzeTCP(std::string Packet){

	std::string SplitMessage[4];
	std::string Delimiter = "+";
	size_t Pos = 0;
	int Counter = 0;

	while ((Pos = Packet.find(Delimiter)) != std::string::npos) {
	    SplitMessage[Counter] = Packet.substr(0, Pos);
	    std::cout << SplitMessage[Counter] << std::endl;
	    Packet.erase(0, Pos + Delimiter.length());
	    Counter++;
	}
	SplitMessage[Counter] = Packet;
	std::cout << Packet << std::endl;

if(SplitMessage[0] == getIP()){		// If this message is directed to me:
	std::cout << SplitMessage[1] << ": " << SplitMessage[3] << std::endl;
}else{								// Elsewise forward it

}

	return 0;
}
