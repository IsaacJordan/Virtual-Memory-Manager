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
	int count;
	//int PA_LOW;
	//int PA_HIGH;
	//int VA_LOW;
	//int VA_HIGH;
	//bool inmemory;

public:
	Process();
	Process(int,int,int);
	void getData(int, int,int);
	void showData();
	void Upload();

};

Process::Process() {
	bytes = 0;
	id = 0;
}

Process::Process(int bytes, int id,int count) {
	this->bytes = bytes;
	this->id = id;
	this->count = count;
}

void Process::getData(int num, int num1,int cuenta) {
	bytes = num;
	id = num1;
	count = cuenta;
}

void Process::showData() {
	cout << "EL proceso: " << id << " es de: " << bytes << " bytes." << endl;
}

void Process::Upload() {
	carga(bytes,id,count);
}


#endif