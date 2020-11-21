#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include "Process.h"
#include <map> 
#include <algorithm>    // std::swap_ranges
using namespace std;
//Mapa para la memoria real
map<int, int> RAM;
// Mapa para el registro de SWAP
map<int, int> SWAP;
// Contador para llevar el registro de los swaps
int contador = 0;

//Esta funcion recibe los bytes y el nombre del proceso ha agregar, junto con el contador de los espacios de memoria
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
		cout << "Se agrego contenido a la pagina: " << count << endl;
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

// Esta funcion hace primero el swap out, copia el proceso de la memoria real al registro de swap y borra lo que tiene en esa pagina
// despues hace un swap in, lo que quiere decir que el nuevo proceso recibido se agrega en la pagina de donde se hizo el swap out
void swap(int bt, int pss, int &count) {
	cout << "Swap Out" << endl;
	//Reiniciamos el contador del swap si ya se registro toda la memoria real FIFO
	if (contador == 128) {
		contador = 0;
	}
	// Verificamos que el registro de SWAP no este lleno para poder realizar cambios
	if (count >= 256) {
		cout << "El registro de SWAP esta lleno, no se pueden realizar mas movimientos" << endl;
		
	}
	else {
		map<int, int>::iterator itr;
		//Llevaremos un contador para saber el orden de la modificacion de la memoria real
		//revisar la catidad de marcos necesarios para agregar a la memoria real
		int marcos = bt;
		if (marcos % 16 != 0) {
			marcos = (marcos / 16) + 1;
		}
		else {
			marcos = bt / 16;
		}
		//Agregamos el proceso al mapa de swap
		for (int i = 0; i < marcos; i++) {
			
			SWAP.insert(pair<int, int>(contador, RAM.at(contador)));
			//BORRAS
			RAM.erase(contador);
			//MODIFICAS
			cout << "Swap In en la pagina: "<< contador << " de la memoria real." << endl;
			RAM.insert(pair<int, int>(contador, pss));
			contador++;
		}

		//Imprimimos la memoria real
		cout << "\nEl contenido en SWAP REGISTER es : \n";
		cout << "\tPAGE\tPROCESS\n";
		for (itr = SWAP.begin(); itr != SWAP.end(); ++itr) {
			cout << '\t' << itr->first
				<< '\t' << itr->second << '\n';
		}
		cout << endl;
	}

	map<int, int>::iterator itr;
	//Imprimimos la memoria real
	cout << "\nEl contenido NUEVO en Memoria Real es : \n";
	cout << "\tPAGE\tPROCESS\n";
	for (itr = RAM.begin(); itr != RAM.end(); ++itr) {
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
	cout << endl;
	
}