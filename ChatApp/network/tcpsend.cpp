/*
 * main.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: gino
 */

/*
 * main.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: gino
 */

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFSIZE 8192

int tcpsend(int PORT, std::string receiver, std::string buf){
	int pack;

	if ((pack = socket(AF_INET, SOCK_STREAM,0)) == -1){
		perror("cannot create socket!");
		return 0;
	}
	else{
		//std::cout << "created socket: descriptor = " << pack << std::endl;
	}

	struct sockaddr_in myaddr;													// create structure set parameters of our address etc
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;												// listen on ipv4
	myaddr.sin_addr.s_addr = htonl(0);											// listen on every interface
	myaddr.sin_port = htons(0);													// listen to the specified port

	if (bind(pack, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0){			// binds to socket
		throw std::runtime_error("Bind failed! tcp sender");								// throws error if binding is not possible, e.g.:port already in use
	}

	struct sockaddr_in receiving;												// strcucture to set receiver address and port
	memset((char *) &receiving, 0, sizeof(receiving));
	receiving.sin_family = AF_INET;												// set to ipv4
	receiving.sin_port = htons(PORT);											// set to specified port
	receiving.sin_addr.s_addr = inet_addr(receiver.c_str());					// set to specified receiver

	if ( connect(pack, (struct sockaddr *)&receiving, sizeof(receiving))<0 ){	// attempts to connect to receiving client
		throw std::runtime_error("Cannot connect to receiving client");
	}

	if (send(pack, buf.c_str(), buf.size(), 0) < 0){							// send actual information after connection is established
		throw std::runtime_error("Sending failed!");
	}

	close(pack);																// closes socket
	return 0;
}




