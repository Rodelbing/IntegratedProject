/*
 * Multicast_send.h
 *
 *  Created on: Apr 7, 2016
 *      Author: gino
 */
#include <string.h>

int tcpsend(int PORT, std::string receiver, std::string ip, std::string buf); // (Input port, 228.2.1.3, OWN IP, message to be sent)
