/*
 * main.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: gino
 */

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>

std::string getIP () {																//function to get ipv4 address of the local machine
	std::string IP;																	// makes a linked list of interfaces and their addresses
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

            if (strncmp(addressBuffer, "192.168.0.0", 7) == 0){						// check to see if the address is a internal IP address of
            	IP = addressBuffer;													// the 192.168.0.0/16 range, returns error if not since user is otherwise
            	return IP;															// not properly connected
            }
            else {
            	//return "ERROR!";
            }
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return "ERROR!";
}


