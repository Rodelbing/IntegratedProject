/*
 * Includes.cpp
 *
 *  Created on: Apr 11, 2016
 *      Author: nahuel
 */
#include <string>
#include <vector>
struct tableEntry{
		std::string dest;
		std::string via;
	};
std::string getNextHop(std::string destn,std::vector<tableEntry> newfwdTable){
	std::string output = "";
	for(auto& items: newfwdTable){
		if(items.dest == destn)output=items.via;
	}
	return output;
}

