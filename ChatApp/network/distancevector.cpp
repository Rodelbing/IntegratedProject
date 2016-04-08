/*
 * pseudodistancevector.cpp
 *
 *  Created on: 7 apr. 2016
 *      Author: thomleemans
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <thread>
#include <cstring>
#include <unistd.h>
#include "getIP.h"
#include "multisend.h"
#include "multireceive.h"
#include "multisend.h"
#include "tcpsend.h"
#include "tcpreceive.h"
#include "../lib/BlockingQueue.h"

using namespace std;
struct tableEntry{
		string dest;
		string via;
	};

void printTable(vector<tableEntry>);
vector<tableEntry> stringToVector(string receivedString);
string vectorToString(vector<tableEntry> myTablePtr);
vector<tableEntry> *myTablePtr;
void routing(string);
BlockingQueue<std::string> x, y;

void init(){
	tableEntry self;
	self.dest = getIP();
	self.via = getIP();
	myTablePtr->push_back(self);
}

void start(vector<tableEntry> *inputTable){
	myTablePtr = inputTable;
	init();
	std::thread receiver(multireceive, 14000, "228.1.2.3", getIP(),std::ref(x), std::ref(y));
	string sendStr = vectorToString(*myTablePtr);
	multisend(14000, "228.1.2.3", getIP(), sendStr);
	while(true){
		std::string message;
		while((message=x.pop()).size()>0){
			routing(message);
		}
		//send
		sendStr = vectorToString(*myTablePtr);
		multisend(14000, "228.1.2.3", getIP(), sendStr);
		printTable(*myTablePtr);
		sleep(1);
	}
}

void routing(string recStr) {
	string senderIP;
	vector<tableEntry> receivedTable = stringToVector(recStr);
	bool first = true;
	for(auto& itema: receivedTable){

		if(first){
			senderIP = itema.dest;
			first = false;
		}

		bool add = true;
		for(auto& itemb: *myTablePtr){
			if(itema.dest == itemb.dest){
				add = false;
				}
		}

		if(add){
			tableEntry tmp;
			tmp.dest = itema.dest;
			tmp.via = senderIP;
			myTablePtr->push_back(tmp);

		}
	}

}

string vectorToString(vector<tableEntry> myTablePtr) {
	string myString;
	myString += "Routing+";
	for(auto& items : myTablePtr){
		string Dest = items.dest;
		string Via = items.via;
		myString += "_";
		myString += Dest;
		myString += "-";
		myString += Via;
		//std::cout << myString << std::endl;
	};
	return myString;
}

vector<tableEntry> stringToVector(string receivedString) {
	vector<tableEntry> tempTable;
	size_t Pos;
	size_t finePos;
	vector<std::string> routes;
	string tempVia;
	for (int i =0; i< receivedString.length(); i++){
	  if(receivedString[i] == '_'){
	  tableEntry tmp;
	  tmp.dest = receivedString.substr(i+1, 11);
	  tmp.via = receivedString.substr(i+13, 11);
	  tempTable.push_back(tmp);
	  }
	}



	return tempTable;
}


void printTable(vector<tableEntry> dus){
 for(auto& items: dus){
	 cout<<items.dest<<" VIA "<<items.via<<endl;
 	 }
 	 cout<<"<-End table->"<<endl;

}

