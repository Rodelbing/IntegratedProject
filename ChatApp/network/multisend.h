/*
 * Multicast_send.h
 *
 *  Created on: Apr 7, 2016
 *      Author: gino
 */
#include <string.h>

int multisend(int PORT, std::string group, std::string ip, std::string buf); // (Input port, 228.2.1.3, OWN IP, message to be sent)
