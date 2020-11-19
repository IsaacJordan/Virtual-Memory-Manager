#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include "Process.h"
#include <map> 
using namespace std;

map<int, int> RAM;

void carga(int bt, int pss, int &count) {
	map<int, int>::iterator itr;
	cout << "Se recibio el proceso: " << pss << " de: " << bt << " bytes." << endl;
	
	//revisar la catidad de marcos necesarios para agregar a la memoria real
	int marcos = bt;
	if (marcos % 16 != 0) {
		marcos = (marcos/16)+1;
	}
	else {
		marcos = bt / 16;
	}
	cout << "Se requieren: " << marcos << " marcos." << endl;

	//Agregamos el proceso a la memoria real
	for (int i = 0; i < marcos; i++) {
		RAM.insert(pair<int, int>(count, pss));
		cout << "Cuenta de la pagina: " << count << endl;
		count = count +1;
	}

	//Imprimimos la memoria real
	cout << "\nEl contenido en Memoria Real es : \n";
	cout << "\tPAGE\tPROCESS\n";
	for (itr = RAM.begin(); itr != RAM.end(); ++itr) {
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
	cout << endl;

}