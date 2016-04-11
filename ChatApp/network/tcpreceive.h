/*
 * multireceive.h
 *
 *  Created on: Apr 7, 2016
 *      Author: gino
 */

#include "../lib/BlockingQueue.h"
#include "../lib/Includes.h"
int tcpreceive(int PORT,  BlockingQueue<std::string> &q, vector<tableEntry> *inputTable);
