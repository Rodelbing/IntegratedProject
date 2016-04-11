/*
 * Includes.h
 *
 *  Created on: Apr 11, 2016
 *      Author: nahuel
 */
#include <vector>
#ifndef LIB_INCLUDES_H_
#define LIB_INCLUDES_H_

struct tableEntry{
		std::string dest;
		std::string via;
	};

std::string getNextHop(std::string destn,std::vector<tableEntry> newfwdTable);


#endif /* LIB_INCLUDES_H_ */
