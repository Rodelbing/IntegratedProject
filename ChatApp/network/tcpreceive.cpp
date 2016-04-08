/*
 * main.cpp
 *
 *  Created on: Apr 7, 2016
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
#include "getIP.h"
#include "analyzeTCPpacket.h"
#include "../lib/BlockingQueue.h"
#define BUFSIZE 8192


int makeTCPsocket(int PORT, std::string ip){									// function to make tcp socket
	int pack;																	// int to store socket

	if ((pack = socket(AF_INET, SOCK_STREAM,0)) < 0){							// create socket, AF_INET = ipv4, SOCK_STREAM = TCP, 0 = default
		throw std::runtime_error("Cannot create socket!");
	}

	struct sockaddr_in myaddr;													// create structure set parameters of our address etc
		memset((char *)&myaddr, 0, sizeof(myaddr));
		myaddr.sin_family = AF_INET;											// listen on ipv4
		myaddr.sin_addr.s_addr = htonl(0);										// listen on every interface
		myaddr.sin_port = htons(PORT);											// listen to the specified port

		if (::bind(pack, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0){
			throw std::runtime_error("Bind failed! tcp receiver");							// throws error if binding is not possible, e.g.:port already in use
		}


 return pack;																	// return socket

}

int tcpreceive(int PORT, BlockingQueue<std::string> &q){						// function to receive, set port and blocking queue to store message

	std::string foreignIP;														// string to save IP of client that sent the message
	int pack = makeTCPsocket(PORT, getIP());									// call function to create socket and store it
	ssize_t recvlen;
	char buf[BUFSIZE];

	recvlen = 0;
	struct sockaddr_in peer_address;											// structure for peer_address
	socklen_t peer_address_len = sizeof(struct sockaddr_storage);

	while(true){																// while loop to keep running and look for incoming packets
			if((listen(pack, 3)) < 0){
				throw std::runtime_error("Error while listening");
			}

			int readsocket = accept(pack, (struct sockaddr *) &peer_address, &peer_address_len);	// accept connection and store it in readsocket
			foreignIP = inet_ntoa(peer_address.sin_addr);

			if (readsocket < 0) {
				throw std::runtime_error("Cannot read!");
			}

			recvlen = read(readsocket,buf, BUFSIZE);							// saves received information to buffer
			if (recvlen < 0){
				perror("reading error!");
			}

			q.push(std::string(buf, static_cast<int>(recvlen)));				// pushed message onto the blockingqueue
			//std::cout <<  foreignIP << ": " << buf << std::endl;					// prints sender and message
			analyzeTCP(buf);
			}


		exit(0);
}

