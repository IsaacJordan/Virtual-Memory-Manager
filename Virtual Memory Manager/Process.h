#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include <vector>
#include "RealMemory.h"
using namespace std;

class Process {
	int bytes;
	int id;
	int PA;
	int VA;
	bool inmemory;

public:
	Process();
	Process(int,int, int, int,bool);
	void getData(int, int,bool);
	void showData();
	void access(vector<int>,bool);

};

Process::Process() {
	bytes = 0;
	id = 0;
	PA = 0;
	VA = 0;
	inmemory = false;
}

Process::Process(int bytes, int id, int PA, int VA, bool inmemory) {
	this->bytes = bytes;
	this->id = id;
	this->PA = PA;
	this->VA = VA;
	this->inmemory = inmemory;
}

void Process::getData(int num, int num1, bool memory) {
	bytes = num;
	id = num1;
	inmemory = memory;
	
}

void Process::showData() {
	cout << "EL proceso: " << id << " es de: " << bytes << " bytes." << endl;
}

void Process::access(vector<int> info ,bool memory) {
	
}

#endif