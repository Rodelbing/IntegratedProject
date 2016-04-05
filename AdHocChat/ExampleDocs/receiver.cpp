#include "BlockingQueue.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

using namespace std;
/**
 * Opens the socket, attach it to an interface and join the multicast group
 */
int get_receive_socket( string ip, uint16_t port, string group ) {
	/**
	 * Create a new datagram socket
	 */
	int retsock;
	if ((retsock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) //Get a IPv4 (AF_INET) socket for UDP packets (SOCK_DGRAM)
		throw std::runtime_error("Failed to create socket!");

	/**
	 * Setting the reuse var to 1 so multiple programs can read from this port
	 * This is only useful if you want multiple clients to be able to listen on this port, for example when testing your application locally
	 * It only really makes sense to use it this way with multicast traffic
	 */
	int reuse = 0;
	if(setsockopt(retsock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0) 
		throw std::runtime_error("Failed to set SO_REUSEADDR!");

	/**
	 * Bind the socket to all addresses on our system and a specific port
	 */
	struct sockaddr_in local = {0};
	memset((char *) &local, 0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = INADDR_ANY;
	if(bind(retsock, (struct sockaddr*)&local, sizeof(local)))
		throw std::runtime_error("Failed to bind socket!");

	/**
	 * Join a multicast group
	 * If we do not do this we wont receive or accept any multicast packets on this socket
	 */
	struct ip_mreq group_req; //struct for multicast group requests
	group_req.imr_multiaddr.s_addr = inet_addr(group.c_str()); //the multicast address to join
	group_req.imr_interface.s_addr = inet_addr(ip.c_str()); //the address of the interface to perform the join on (our IP address)
	if(setsockopt(retsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group_req, sizeof(group_req)) < 0)
		throw std::runtime_error("Failed to join multicast group!");

	return retsock;
}

int receivePacket(string ip, uint port, string group, BlockingQueue<std::string> &q) 
{
	try
	{
		int rsock;

		rsock = get_receive_socket(ip, port, group);

		// prepare a structure to put peer data into
		struct sockaddr_in peer_address;
		socklen_t peer_address_len;
		peer_address_len = sizeof(struct sockaddr_storage);
		
		// allocate memory to put the received data into
		char data[1500];
		int len;
		len = 0;

		while (1) {
			// Receive packet and put its contents in data, recvfrom will block until a packet for this socket has been received
			len = recvfrom(rsock, data, sizeof(data), 0, (struct sockaddr *) &peer_address, &peer_address_len);
			if(len > 0){
				q.push(std::string(data, len));
			}
		}
	} catch(std::exception &e)	
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}

	return 0;
}
