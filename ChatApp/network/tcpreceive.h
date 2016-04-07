/*
 * multireceive.h
 *
 *  Created on: Apr 7, 2016
 *      Author: gino
 */

#include "../lib/BlockingQueue.h"

int tcpreceive(int PORT, std::string ip,  BlockingQueue<std::string> &q);
