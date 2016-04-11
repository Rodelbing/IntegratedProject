#include "getIP.h"
#include "sendMessage.h"
#include <iostream>
#include <vector>
#include <string>
#include "../lib/Includes.h"

int analyzeTCP(std::string Packet, std::vector <tableEntry> inputTable){
	std::string SplitMessage[4];
	std::string Delimiter = "+";
	size_t Pos = 0;
	int Counter = 0;

	while ((Pos = Packet.find(Delimiter)) != std::string::npos) {
	    SplitMessage[Counter] = Packet.substr(0, Pos);
	    //std::cout << SplitMessage[Counter] << std::endl;
	    Packet.erase(0, Pos + Delimiter.length());
	    Counter++;
	}
	SplitMessage[Counter] = Packet;
	//std::cout << SplitMessage[Counter] << std::endl;

if(SplitMessage[1] == getIP()){		// If this message is directed to me:
	if(SplitMessage[2] == "MSG"){
		std::cout << SplitMessage[1] << ": " << SplitMessage[3] << std::endl;
	}
}else{								// Elsewise forward it
	sendMessage(SplitMessage[0], getNextHop(SplitMessage[0], inputTable), SplitMessage[3]);
}

	return 0;
}


