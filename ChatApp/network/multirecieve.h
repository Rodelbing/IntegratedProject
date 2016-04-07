/*
 * multireceive.h
 *
 *  Created on: Apr 7, 2016
 *      Author: gino
 */

#include "../lib/BlockingQueue.h"

int multirecieve(int PORT, std::string group, std::string ip,  BlockingQueue<std::string> &q);
