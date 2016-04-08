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

#include "../lib/BlockingQueue.h"

#define BUFSIZE 2048															// define buffersize

int makesocket(int PORT, std::string group, std::string ip){					// function to create socket for multicast receiving
	int pack;																	// int to store socket in

	if ((pack = socket(AF_INET, SOCK_DGRAM,0)) < 0){							// create actual socket, AF_INET = ipv4, SOCK_DGRAM = UDP, 0 = standard setting
		throw std::runtime_error("Cannot create socket!");						// returns error when socket cannot be created
	}

	struct sockaddr_in myaddr;													// create structure set parameters of our address etc
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;												// listen on ipv4
	myaddr.sin_addr.s_addr = htonl(0);											// listen on every interface
	myaddr.sin_port = htons(PORT);												// listen to the specified port

	if (::bind(pack, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0){			// binds to socket
		throw std::runtime_error("Bind failed! multicast receiver");								// throws error if binding is not possible, e.g.:port already in use
	}

	struct ip_mreq group_req; 													//struct for multicast group requests
	group_req.imr_multiaddr.s_addr = inet_addr(group.c_str()); 					//the multicast address to join
	group_req.imr_interface.s_addr = inet_addr(ip.c_str()); 					//the address of the interface to perform the join on (our IP address)
	if(setsockopt(pack, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group_req, sizeof(group_req)) < 0){
	     throw std::runtime_error("Failed to join multicast group");
	}
 return pack;																	// returns the newly created socket

}

int multireceive(int PORT, std::string group, std::string ip,  BlockingQueue<std::string> &q){

	int pack = makesocket(PORT, group, ip);										// call function above to make socket
	int recvlen;
	char buf[BUFSIZE];
	std::string foreignIP;														// string to store IP of sender

	recvlen = 0;

	struct sockaddr_in peer_address;											// makes structure for peer_address
	socklen_t peer_address_len;
	peer_address_len = sizeof(struct sockaddr_storage);

	while(true){																// while loop to keep receiving
			std::cout << "waiting on port " << PORT << std::endl;
			recvlen = recvfrom(pack, buf, BUFSIZE, 0, (struct sockaddr *)&peer_address, &peer_address_len);	//actual receiving mechanism, returns amount of bytes received
			std::cout << "received bytes: " << recvlen << std::endl;
			if (recvlen > 0) {													// if bytes available push them to the BlockingQueue
				q.push(std::string(buf, recvlen));
			}
			foreignIP = inet_ntoa(peer_address.sin_addr);						// stores IP of sender
		}

		exit(0);
}

