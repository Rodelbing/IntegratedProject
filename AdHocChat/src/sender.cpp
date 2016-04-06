#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdexcept>
#include <iostream>

using namespace std;

int sendPacket(string ip, uint port, string group){

	int sock = -1;

	try
	{
		/**
		 * Create a new datagram socket 
		 */
		if( (sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
			throw std::runtime_error("Socket creation failed");

		/**
		 * Enable/Disable loopback. (loop = 0 is disabled, loop =1 is enabled)
		 * This allows you to receive multicast packets you yourself have send.
		 * Obviously enabling this is not really useful for anything but testing
		 */
		char loop = 0;
		if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loop, sizeof(loop)) < 0)
			throw std::runtime_error("Failed to disable loopback");

		/**
		 * Set the interface to send multicast packets on.
		 * This should be our own IP address
		 */
		struct in_addr local = {0};
		local.s_addr = inet_addr(ip.c_str());
		if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char *)&local, sizeof(local)) < 0)
			throw std::runtime_error("Local interface failed");

		/**
		 * Fill in the sockaddr_in to specify the destination of datagrams
		 * In this case this is simply a port and multicast group address
		 */
		struct sockaddr_in multicastSender = {0};
		multicastSender.sin_family = AF_INET;
		multicastSender.sin_addr.s_addr = inet_addr(group.c_str());
		multicastSender.sin_port = htons(port);

		//send a packet every 5 seconds
		while(1){
			std::string bla = "Blablabla";

			if (sendto(sock, bla.c_str(), bla.size(), 0, (struct sockaddr*)&multicastSender,sizeof(struct sockaddr_in)) < 0) //sent a UDP packet containing our example data
				    perror("Sendto failed");
			printf("Packet of size %d sent!\n", (int)bla.size());
			sleep(5);
		}
	} catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	if(sock != -1)
		close(sock);

	return 0;
}
