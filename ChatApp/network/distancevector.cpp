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

using namespace std;

struct tableEntry{
		string dest;
		string via;
	};

void lolololo(vector<tableEntry>);
vector<tableEntry> stringToVector(string receivedString);
string vectorToString(vector<tableEntry> myTablePtr);
vector<tableEntry> *myTablePtr;

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
	std::thread receiver(multirecieve, 14000, "228.1.2.3", "192.168.5.4",std::ref(q));
	while(true){
		while(q.pop)
		std::string message = q.pop();
		routing(message);
		sleep(1);
	}
}

void routing(string recStr) {
	vector<tableEntry> receivedTable = stringToVector(recStr);
	for(auto& itema: receivedTable){		//ostringstream convert1;
		//convert1 << items.dest;
		//Dest = convert1.str();
		bool add = true;

		for(auto& itemb: myTablePtr){
			if(itema.dest == itemb.dest) add = false;
		}

		if(add)myTablePtr->push_back(itema);
	}
	string sendStr = vectorToString(myTablePtr);
	//send string;

}

string vectorToString(vector<tableEntry> myTablePtr) {
	string myString;
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


void lolololo(vector<tableEntry> dus){
 for(auto& items: dus){
	 cout<<items.dest<<" voor fuck sake thom "<<items.via<<endl;
 	 }


}