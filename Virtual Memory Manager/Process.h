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
	//int PA_LOW;
	//int PA_HIGH;
	//int VA_LOW;
	//int VA_HIGH;
	//bool inmemory;

public:
	Process();
	Process(int,int);
	void getData(int, int);
	void showData();

};

Process::Process() {
	bytes = 0;
	id = 0;
}

Process::Process(int bytes, int id) {
	this->bytes = bytes;
	this->id = id;
	
}

void Process::getData(int num, int num1) {
	bytes = num;
	id = num1;
	
}

void Process::showData() {
	cout << "EL proceso: " << id << " es de: " << bytes << " bytes." << endl;
}

#endif