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
#include "../lib/Includes.h"
using namespace std;


void printTable(vector<tableEntry>);
vector<tableEntry> stringToVector(string receivedString);
string vectorToString(vector<tableEntry> myTablePtr);
vector<tableEntry> *myTablePtr;
void routing(string);
BlockingQueue<std::string> x, y;
void updateTimetable(vector<tableEntry>*);


void init(){
	tableEntry self;
	self.dest = getIP();
	self.via = getIP();
	self.time = 5;
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
			cout<<message<<endl;
			routing(message);
		}
		//send
		sendStr = vectorToString(*myTablePtr);
		multisend(14000, "228.1.2.3", getIP(), sendStr);
		updateTimetable(myTablePtr);
		printTable(*myTablePtr);

		sleep(1);
	}
}

void routing(string recStr) {

	string senderIP;
	vector<tableEntry> receivedTable = stringToVector(recStr);
	//printTable(receivedTable);
	int i =0;
	bool first = true;
	for(auto& recItem: receivedTable){
		cout<<"rec item "<<i++<<endl;
		if(first){
			senderIP = recItem.dest;
			first = false;
		}

		for(size_t it = 0; it < myTablePtr->size(); ++it){
			auto& myTableItem = (*myTablePtr)[it];

			bool add = true;
			bool update = false;
			cout<<recItem.dest<<"LOL"<<endl;
			cout<<myTableItem.dest<<"deze moet je hebben"<<endl;
			if(recItem.dest == myTableItem.dest || recItem.via == getIP()){
				cout<<"add = false nigga!"<<endl;
				add = false;
				update = (recItem.dest == recItem.via && recItem.via!=myTableItem.via);
				}

			if(add){
				tableEntry tmp;
				tmp.dest = recItem.dest;
				tmp.via = senderIP;
				tmp.time = 5;
				myTablePtr->push_back(tmp);
				cout<<"hij heeft ge-add"<<endl;
					}
			if(update){
				for(auto& items: *myTablePtr){
					if(recItem.dest == items.dest){
						items.via = recItem.via;
					}
					items.time = 5;
				}

			}
			bool deleteItem = true;
			if(myTableItem.via == senderIP){
				for(auto& items: receivedTable){
					if(recItem.dest == myTableItem.dest)deleteItem = false;
				}
				//items.time = 5;
			}

//
//			if(deleteItem)
//				myTablePtr->erase(myTablePtr->begin() + it);

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
	 cout<<items.dest<<" VIA "<<items.via << " FOR ANOTHER " << items.time << "sec" << endl;
 	 }
 	 cout<<"<-End table->"<<endl;

}

void updateTimetable(vector<tableEntry> *dus){
	for(vector<tableEntry>::iterator i = dus->begin(); i != dus->end();)
	{
		tableEntry &item = (*i);
		if(!(item.dest==getIP()))item.time -= 1;

		vector<tableEntry>::iterator next_i = i;
		++next_i;

		if(item.time < 1)
		{
			if (item.dest != getIP()){
				cout << "delete!" << endl;
				tableEntry *ptr = &item;
				next_i = dus->erase(i);

			}
		}

		i = next_i;
	}
};

