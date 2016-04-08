/*
 * distancevector.h
 *
 *  Created on: Apr 8, 2016
 *      Author: gino
 */

#include <vector>
#include <string>

using namespace std;

struct tableEntry{
		string dest;
		string via;
	};

void start(vector<tableEntry> *inputTable);
