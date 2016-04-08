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
//dikke vette yolo
struct tableEntry{
		string dest;
		string via;
	};

void printTable(vector<tableEntry>);
vector<tableEntry> stringToVector(string receivedString);
string vectorToString(vector<tableEntry> myTablePtr);
vector<tableEntry> *myTablePtr;
void routing(string);
BlockingQueue<std::string> x;

void init(){
	tableEntry self;
	self.dest = getIP();
	self.via = getIP();
	myTablePtr->push_back(self);
}

void start(vector<tableEntry> *inputTable){
	myTablePtr = inputTable;
	init();
	std::thread receiver(multireceive, 14000, "228.1.2.3", getIP(),std::ref(x));
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
	vector<tableEntry> receivedTable = stringToVector(recStr);
	for(auto& itema: receivedTable){
		bool add = true;
		for(auto& itemb: *myTablePtr){
			if(itema.dest == itemb.dest) add = false;
			if(itema.dest == itemb.dest && itemb.dest != itemb.via && itema.dest == itema.via) itemb.via = itema.via;
		}

		if(add)myTablePtr->push_back(itema);
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
		std::cout << myString << std::endl;
	};
	return myString;
}

vector<tableEntry> stringToVector(string receivedString) {
	vector<tableEntry> tempTable;
	size_t Pos;
	size_t finePos;
	vector<std::string> routes;
	string tempVia;
	int Counter=0;

	Pos = receivedString.find("_");
	receivedString.erase(0, Pos);
	while(Pos = receivedString.find("_") != std::string::npos){
		routes[Counter] = receivedString.substr(0, Pos);
			finePos = routes[Counter].find("-");
			tableEntry temp;
			temp.dest = routes[Counter].substr(0,finePos);
			temp.via = routes[Counter].substr(finePos,routes[Counter].size()-finePos);
			tempTable.push_back(temp);
		receivedString.erase(0, Pos);
		Counter++;
	}
	/*for(unsigned int i = 0; i<receivedString.length(); i++) {
	    if(receivedString[i]=='_'){
	    	for(unsigned int j = i+1; j<receivedString.length(); j++) {
	    		if(receivedString[j]=='-'){
	    			for(unsigned int k = i+1; k<j; k++){
	    				tempDest += receivedString[k];
	    				//std::cout << tempDest << std::endl;
	    			}
	    			for(unsigned int l = j+1; l<receivedString.length(); l++){
	    				if(receivedString[l]=='/'){
	    	    			for(unsigned int m = j+1; m<l; m++){
	    	    				tempVia += receivedString[m];
	    	    			}
	    				}
	    			}
	    		}
	    	}
	    	tableEntry temp;
	    	temp.dest = tempDest;
	    	temp.via = tempVia;
	    	tempTable.push_back(temp);
	    	tempDest="";
	    	tempVia="";
	    }
	}*/


	return tempTable;
}


void printTable(vector<tableEntry> dus){
 for(auto& items: dus){
	 cout<<items.dest<<" VIA "<<items.via<<endl;
 	 }
 	 cout<<"<-End table->"<<endl;

}

