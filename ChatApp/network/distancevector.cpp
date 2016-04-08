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
BlockingQueue<std::string> q;

void init(){
	tableEntry self;
	self.dest = "192.168.5.4";
	self.via = "192.168.5.4";
	myTablePtr->push_back(self);
}

void start(vector<tableEntry> *inputTable){
	myTablePtr = inputTable;
	init();
	std::thread receiver(multireceive, 14000, "228.1.2.3", getIP(),std::ref(q));
	while(true){
		std::string message;
		while(message==q.pop()){
			routing(message);
		}
		//send
		string sendStr = vectorToString(*myTablePtr);
		multisend(14000, "228.1.2.3", getIP(), sendStr);
		sleep(1);
	}
}

void routing(string recStr) {
	vector<tableEntry> receivedTable = stringToVector(recStr);
	for(auto& itema: receivedTable){
		bool add = true;
		for(auto& itemb: *myTablePtr){
			if(itema.dest == itemb.dest) add = false;
			if(itema.dest == itemb.dest && itemb.dest != itemb.via && itema.dest == itema.via)itemb.via = itema.via;
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
		myString += "/";
	};
	return myString;
}

vector<tableEntry> stringToVector(string receivedString) {
	vector<tableEntry> tempTable;
	string tempDest;
	string tempVia;

	for(unsigned int i = 0; i<receivedString.length(); i++) {
	    if(receivedString[i]=='_'){
	    	for(unsigned int j = i+1; j<receivedString.length(); j++) {
	    		if(receivedString[j]=='-'){
	    			for(unsigned int k = i+1; k<j; k++){
	    				tempDest += receivedString[k];
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
	    }
	}
	return tempTable;
}


void printTable(vector<tableEntry> dus){
 for(auto& items: dus){
	 cout<<items.dest<<" voor fuck sake thom "<<items.via<<endl;
 	 }


}

