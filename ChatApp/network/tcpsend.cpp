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

int tcpsend(int PORT, std::string group, std::string ip, std::string buf){
	int pack;

	if ((pack = socket(AF_INET, SOCK_STREAM,0)) == -1){
		perror("cannot create socket!");
		return 0;
	}
	else{
		std::cout << "created socket: descriptor = " << pack << std::endl;
	}

	struct sockaddr_in myaddr;
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

	if (bind(pack, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0){
			perror ("bind failed");
			return 0;
		}
	else{
		std::cout << "succesfull, port = " << ntohs(myaddr.sin_port) << std::endl;
	}

	char loop = 0;
	 if(setsockopt(pack, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loop, sizeof(loop)) < 0){
		 perror("Loopback set error!");
	 }

	 struct in_addr local = {0};
	 local.s_addr = inet_addr(ip.c_str());
	 if(setsockopt(pack, IPPROTO_IP, IP_MULTICAST_IF, (char *)&local, sizeof(local)) < 0){
		 perror("Local interface failed");
	 }


	struct sockaddr_in remmulti;
	memset((char *) &remmulti, 0, sizeof(remmulti));
	remmulti.sin_family = AF_INET;
	remmulti.sin_port = htons(PORT);
	remmulti.sin_addr.s_addr = inet_addr(group.c_str());

	int slen = sizeof(remmulti);

	std::cout << "trying to send message" << std::endl;


	if ((sendto(pack, buf.c_str(), buf.size(), 0, (struct sockaddr *)&remmulti, slen)) < 0){
		perror("sendto");
	}

	close(pack);
	return 0;
}




