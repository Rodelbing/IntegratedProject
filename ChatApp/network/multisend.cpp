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

#define BUFSIZE 2048

int multisend(int PORT, std::string group, std::string ip, std::string buf){			// function to send multicast
	int pack;																			// int to store created socket

	if ((pack = socket(AF_INET, SOCK_DGRAM,0)) < 0){									// creates socket, AF_INET = ipv4, SOCK_DGRAM = UDP, 0 = default
		throw std::runtime_error("Cannot create socket!");
	}

	struct sockaddr_in myaddr;															// structure to store our sockaddr information
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;														// set to ipv4
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);											// set interface to all interfaces
	myaddr.sin_port = htons(0);															// 0 = select random port

	if (bind(pack, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0){					// bind to socket
		throw std::runtime_error("Bind failed! multicast sender");
		}

	char loop = 0;																		// setting to incluse loopback interface in multicast, 0=no, 1=yes
	 if(setsockopt(pack, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loop, sizeof(loop)) < 0){
		 throw std::runtime_error("Loopback set error!");
	 }

	 struct in_addr local = {0};														// set interface to send multicast packets on, our own ip is used
	 local.s_addr = inet_addr(ip.c_str());
	 if(setsockopt(pack, IPPROTO_IP, IP_MULTICAST_IF, (char *)&local, sizeof(local)) < 0){
		 throw std::runtime_error("Local interface failed");
	 }


	struct sockaddr_in remmulti;														// structure to set desination of multicast packet, in this case group and port
	memset((char *) &remmulti, 0, sizeof(remmulti));
	remmulti.sin_family = AF_INET;														// set to ipv4
	remmulti.sin_port = htons(PORT);													// set the specified port
	remmulti.sin_addr.s_addr = inet_addr(group.c_str());								// set to the selected group

	int slen = sizeof(remmulti);

	if ((sendto(pack, buf.c_str(), buf.size(), 0, (struct sockaddr *)&remmulti, slen)) < 0){	// sends the packet
		throw std::runtime_error("sendto");
	}

	//std::cout << "ping!" << std::endl;

	close(pack);																		// closes the socket
	return 0;
}




