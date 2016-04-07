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

int tcpsend(int PORT, std::string receiver, std::string buf){
	int pack;

	if ((pack = socket(AF_INET, SOCK_STREAM,0)) == -1){
		perror("cannot create socket!");
		return 0;
	}
	else{
		//std::cout << "created socket: descriptor = " << pack << std::endl;
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
		//std::cout << "succesfull, port = " << ntohs(myaddr.sin_port) << std::endl;
	}

	struct sockaddr_in remmulti;
	memset((char *) &remmulti, 0, sizeof(remmulti));
	remmulti.sin_family = AF_INET;
	remmulti.sin_port = htons(PORT);
	remmulti.sin_addr.s_addr = inet_addr(receiver.c_str());

	int slen = sizeof(remmulti);

	//std::cout << "trying to send message" << std::endl;

	if ( connect(pack, (struct sockaddr *)&remmulti, sizeof(remmulti))<0 ){
		perror("cannot connect");
		exit(1);
	}

	if (send(pack, buf.c_str(), buf.size(), 0) < 0){
		perror("send");
	}

	close(pack);
	return 0;
}




