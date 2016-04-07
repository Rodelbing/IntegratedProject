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

#define BUFSIZE 2048

int makesocket(int PORT, std::string group, std::string ip){
	struct sockaddr_in remaddr;
	int pack;
	unsigned char buf[BUFSIZE];

	if ((pack = socket(AF_INET, SOCK_DGRAM,0)) < 0){
		perror("cannot create socket!");
		return 0;
	}
	else{
		std::cout << "created socket: descriptor = " << pack << std::endl;
	}

	struct sockaddr_in myaddr;
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(0);
	myaddr.sin_port = htons(PORT);

	if (bind(pack, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0){
		perror ("bind failed");
		return 0;
	}
	else{
		std::cout << "succesfull, port = " << ntohs(myaddr.sin_port) << std::endl;
	}

	struct ip_mreq group_req; //struct for multicast group requests
	group_req.imr_multiaddr.s_addr = inet_addr(group.c_str()); //the multicast address to join
	group_req.imr_interface.s_addr = inet_addr(ip.c_str()); //the address of the interface to perform the join on (our IP address)
	if(setsockopt(pack, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group_req, sizeof(group_req)) < 0){
	     perror("Failed to join multicast group");
	     exit(1);
	}
 return pack;

}

int multirecieve(int PORT, std::string group, std::string ip){

	int pack = makesocket(PORT, group, ip);
	int recvlen;
	unsigned char buf[BUFSIZE];

	struct sockaddr_in peer_address;
	socklen_t peer_address_len;
	peer_address_len = sizeof(struct sockaddr_storage);

	while(true){
			std::cout << "waiting on port " << PORT << std::endl;
			recvlen = recvfrom(pack, buf, BUFSIZE, 0, (struct sockaddr *)&peer_address, &peer_address_len);
			std::cout << "received bytes: " << recvlen << std::endl;
			if (recvlen > 0) {
				buf[recvlen] = 0;
				std::cout << buf << std::endl;
			}
		}

		exit(0);
}

