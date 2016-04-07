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
#define BUFSIZE 2048


int makeTCPsocket(int PORT, std::string ip){
	int pack;

	if ((pack = socket(AF_INET, SOCK_STREAM,0)) < 0){
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


 return pack;

}

int tcpreceive(int PORT, std::string ip,  BlockingQueue<std::string> &q){

	int pack = makeTCPsocket(PORT, ip);
	ssize_t recvlen;
	char buf[BUFSIZE];

	recvlen = 0;
	struct sockaddr_in peer_address;
	socklen_t peer_address_len = sizeof(struct sockaddr_storage);
	while(true){
			if((listen(pack, 3)) < 0){
				perror("I won't receive!");
			}

			int readsocket = accept(pack, (struct sockaddr *) &peer_address, &peer_address_len);

			if (readsocket < 0) {
				perror("cannot accept!");
			}

			recvlen = read(readsocket,buf, BUFSIZE);
			if (recvlen < 0){
				perror("reading error!");
			}

			std::cout << recvlen << std::endl;

			q.push(std::string(buf, static_cast<int>(recvlen)));
			std::cout << buf << std::endl;
			}


		exit(0);
}

