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

using namespace std;

struct tableEntry{
		int dest;
		int via;
	};

//void lolololo(vector<tableEntry>);

vector<tableEntry> stringToVector(string receivedString);
string vectorToString(vector<tableEntry> myTable);
int main() {
	int myadress = 4;
	int myname = 3045; // random
	tableEntry self;
	self.dest = myadress;
	self.via = myname;

	vector<tableEntry> myTable;
	myTable.push_back(self);
	vector<tableEntry> receivedTable;

	for(auto& itema: receivedTable){
		bool add = true;

		for(auto& itemb: myTable){
			if(itema.dest == itemb.dest) add = false;
		}

		if(add)myTable.push_back(itema);
	}

//	lolololo(myTable);
//	cout<<vectorToString(myTable)<<endl;
//	lolololo(stringToVector(vectorToString(myTable)));

	return 0;
}

string vectorToString(vector<tableEntry> myTable) {
	string myString;
	for(auto& items : myTable){
		string Dest = "";
		ostringstream convert1;
		convert1 << items.dest;
		Dest = convert1.str();

		ostringstream convert2;
		string Via = "";
		convert2 << items.via;
		Via = convert2.str();

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
	    	temp.dest = stoi(tempDest);
	    	temp.via = stoi(tempVia);
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
