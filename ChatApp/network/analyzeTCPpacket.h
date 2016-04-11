/*
 * analyzeTCPpacket.h
 *
 *  Created on: Apr 8, 2016
 *      Author: nahuel
 */
#include <vector>
#include <string>
#include "../lib/Includes.h"
#ifndef NETWORK_ANALYZETCPPACKET_H_
#define NETWORK_ANALYZETCPPACKET_H_

int analyzeTCP(std::string Packet, std::vector<tableEntry>);

#endif /* NETWORK_ANALYZETCPPACKET_H_ */
