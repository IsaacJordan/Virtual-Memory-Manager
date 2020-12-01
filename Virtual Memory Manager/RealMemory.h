#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib>
#include <stdio.h> 
#include "Process.h"
#include <ctime>
#include <map> 
#include <algorithm>    // std::swap_ranges
using namespace std;

//Mapa para la memoria real
map<int, vector<int> > RAM;

// Mapa para el registro de SWAP
map<int, vector<int> > SWAP;

//Mapa para llevar las estadisticas de cada proceso
map<int, vector <double> > STATS;




// Contador para llevar el registro de los swaps
int contador = 0;
// apuntador del mapa de la memoria real
int apuntador = 0;
// contador global de cuantos swap out se han hecho
int swapout = 0;
// contador global de cuantos swap in se han hecho
int swapinn = 0;

// Esta funcion hace primero el swap out, copia el proceso de la memoria real al registro de swap y borra lo que tiene en esa pagina
// despues agrega el nuevo proceso, lo que quiere decir que el nuevo proceso recibido se agrega en la pagina de donde se hizo el swap out
//La diferencia con el swap, es que este es un auxiliar para cuando la memoria se llene mientras inserta nuevos procesos en la RAM
void swaplleno(int bt, int pss, int pagina) {
	apuntador = 0;
	cout << "Swap Out" << endl;
	// Verificamos que el registro de SWAP no este lleno para poder realizar cambios
	if (contador >= 256) {
		cout << "El registro de SWAP esta lleno, no se pueden realizar mas movimientos" << endl;

	}
	else {

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
			vector<int> procesodeswap = RAM.at(apuntador);
			int pswap = procesodeswap[1];
			vector<double> val = STATS.at(pswap);
			double timestamps = val[0];
			

			SWAP.insert(pair<int, vector<int> >(contador, RAM.at(apuntador)));
			//BORRAS LO QUE HAY EN LA RAM EN ESA POSICION
			RAM.erase(apuntador);

			//MODIFICAS
			cout << "Swap Out en la pagina: " << apuntador << " de la memoria real." << endl;
			//Agregas los nuevos valores a la RAM
			RAM.insert(pair<int, vector<int> >(apuntador, { pagina,pss }));
			//incremento la variable del timestamp
			timestamps++;
			STATS.erase(pswap);
			STATS.insert(pair<int, vector<double> >(pswap, { timestamps, 0, val[2] }));
			//incrementas la pagina
			pagina++;
			//incrementas el apuntador del RAM
			apuntador++;
			//incrementas el apuntador del SWAP
			contador++;
			swapout++;
		}

		//Imprimimos el swap register
		cout << "\nEl contenido en SWAP REGISTER es : \n";
		cout << "\tPAGE\tPAGE PROCESS\tPROCESS\n";
		// Extraemos la informacion del mapa con auntadores
		for (auto ii = SWAP.begin(); ii != SWAP.end(); ++ii) {
			cout << '\t' << (*ii).first << '\t';
			// El segundo valor se lo asignamos a un vector, ya que el segundo dato es un vector.
			vector <int> inVect = (*ii).second;
			//imprimimos 2 valores del vector. (process page y process)
			for (unsigned j = 0; j < inVect.size(); j++) {
				cout << inVect[j] << '\t' << '\t';
			}
			cout << endl;
		}
	}

	//Imprimimos la memoria real
	cout << "\nEl contenido NUEVO en Memoria Real es : \n";
	cout << "\tPAGE\tPAGE PROCESS\tPROCESS\n";
	for (auto ii = RAM.begin(); ii != RAM.end(); ++ii) {
		cout << '\t' << (*ii).first << '\t';
		vector <int> inVect = (*ii).second;
		for (unsigned j = 0; j < inVect.size(); j++) {
			cout << inVect[j] << '\t' << '\t';
		}
		cout << endl;
	}
}

// Esta funcion hace primero el swap out, copia el proceso de la memoria real al registro de swap y borra lo que tiene en esa pagina
// despues agrega el proceso, lo que quiere decir que el nuevo proceso recibido se agrega en la pagina de donde se hizo el swap out
void swap(int bt, int pss, int& count) {
	cout << "Swap Out" << endl;
	bool imprimir = true;
	double pagefault = 0;

	//Reiniciamos el apuntador de la memoria real si ya se registro toda la memoria real FIFO
	if (apuntador >= 128) {
		apuntador = 0;
	}
	// Verificamos que el registro de SWAP no este lleno para poder realizar cambios
	if (contador >= 256) {
		cout << "El registro de SWAP esta lleno, no se pueden realizar mas movimientos" << endl;

	}
	else {
		//Llevaremos un contador para saber el orden de la modificacion de la memoria real
		//revisar la catidad de marcos necesarios para agregar a la memoria real 
		int marcos = bt;
		if (marcos % 16 != 0) {
			marcos = (marcos / 16) + 1;
		}
		else {
			marcos = bt / 16;
		}

		STATS.insert(pair<int, vector<double> >(pss, { double(marcos), 0 ,pagefault }));

		//Agregamos el proceso al mapa de swap
		for (int i = 0; i < marcos; i++) {


			//Almacenamos en una variable tipo vector la informacion que hay en la RAM de la pagina que se le hara SWAP OUT
			vector<int> procesodeswap = RAM.at(apuntador);
			//Del vector anterior, extraemos el ID del proceso
			int pswap = procesodeswap[1];
			//Almacenamos en un vector las estadisticas del proceso al que le haremos SWAP
			vector<double> val = STATS.at(pswap);
			//Del vector, extraemos el timestamp
			double timestamps = val[0];

			//Insertamos en el SWAP la pagina a la que se le hizo SWAP OUT
			SWAP.insert(pair<int, vector<int> >(contador, RAM.at(apuntador)));
			//BORRAS ESA 
			RAM.erase(apuntador);
			//MODIFICAS
			cout << "Swap Out en la pagina: " << apuntador << " de la memoria real." << endl;
			RAM.insert(pair<int, vector<int> >(apuntador, { i,pss }));

			//incremento la variable del timestamp
			timestamps++;
			STATS.erase(pswap);
			STATS.insert(pair<int, vector<double> >(pswap, { timestamps, 0, val[2] }));
			
			contador++;
			apuntador++;
			swapout++;
			if ((apuntador == 128) and (i < marcos)) {
				int faltantes = (marcos - (i + 1)) * 16;
				count = 127;
				swaplleno(faltantes, pss, (i + 1));
				i = marcos;
				imprimir = false;
			}
		}

		if (imprimir) {
			//Imprimimos el registro SWAP
			cout << "\nEl contenido en SWAP REGISTER es : \n";
			cout << "\tPAGE\tPAGE PROCESS\tPROCESS\n";
			for (auto ii = SWAP.begin(); ii != SWAP.end(); ++ii) {
				cout << '\t' << (*ii).first << '\t';
				vector <int> inVect = (*ii).second;
				for (unsigned j = 0; j < inVect.size(); j++) {
					cout << inVect[j] << '\t' << '\t';
				}
				cout << endl;
			}

		}
	}

	if (imprimir) {
		//Imprimimos la memoria real
		cout << "\nEl contenido NUEVO en Memoria Real es : \n";
		cout << "\tPAGE\tPAGE PROCESS\tPROCESS\n";
		for (auto ii = RAM.begin(); ii != RAM.end(); ++ii) {
			cout << '\t' << (*ii).first << '\t';
			vector <int> inVect = (*ii).second;
			for (unsigned j = 0; j < inVect.size(); j++) {
				cout << inVect[j] << '\t' << '\t';
			}
			cout << endl;
		}
	}
}




//Esta funcion recibe los bytes y el nombre del proceso ha agregar, junto con el contador de los espacios de memoria
void carga(int bt, int pss, int& count) {
	cout << "Se recibio el proceso: " << pss << " de: " << bt << " bytes." << endl;
	//declaramos un booleano para saber si la memoria se imprimio el alguna funcion llamada, o la debemo imprimir en esta funcion
	bool imprimir = true;
	double pagefault = 0;
	
	

	//revisar la catidad de marcos necesarios para agregar a la memoria real
	int marcos = bt;
	if (marcos % 16 != 0) {
		marcos = (marcos / 16) + 1;
	}
	else {
		marcos = bt / 16;
	}

	STATS.insert(pair<int, vector<double> >(pss, { double(marcos), 0 ,pagefault }));

	cout << "Se requieren: " << marcos << " marcos." << endl;

	//Agregamos el proceso a la memoria real
	for (int i = 0; i < marcos; i++) {
		RAM.insert(pair<int, vector<int> >(count, { i,pss }));
		cout << "Se agrego contenido a la pagina: " << count << endl;
		count = count + 1;
		apuntador++;
		// checamos si la memoria se llena mientras cargamos procesos en la RAM
		if ((count == 128) and ((i + 1) < marcos)) {
			int faltantes = (marcos - (i + 1)) * 16;
			count = 127;
			// Llamamos una funcion que hara swap a las paginas necesarias del principio de la RAM, para almacenar el proceso restante
			swaplleno(faltantes, pss, (i + 1));
			// actualizamos i para salir del for
			i = marcos;
			imprimir = false;
		}
		//Process* pss = new Process();
		//itoa(pss)->getData(bt,pss,true);
	}

	if (imprimir) {
		//Imprimimos la memoria real 
		cout << "\nEl contenido en Memoria Real es : \n";
		cout << "\tPAGE\tPAGE PROCESS\tPROCESS\n";
		//navegamos por el mapa usando apuntadores
		for (auto ii = RAM.begin(); ii != RAM.end(); ++ii) {
			cout << '\t' << (*ii).first << '\t';
			vector <int> inVect = (*ii).second;
			for (unsigned j = 0; j < inVect.size(); j++) {
				cout << inVect[j] << '\t' << '\t';
			}
			cout << endl;
		}

	}
}

//Funcion que hace swap in a la pagina que queremos accesar y que se encuentra en el registro SWAP
void swapin(int page) {
	//declaramos un vector que reciba la informacion del vector en la pagina deseada
	vector <int> valores = SWAP.at(page);
	//Borramos lo que hay en el SWAP en esa pagina
	SWAP.erase(page);
	//Insertamos lo que hay en la pagina del RAM que vamos a hacer swap out
	SWAP.insert(pair<int, vector<int> >(page, RAM.at(apuntador)));

	vector<int> procesodeswap = RAM.at(apuntador);
	int pswap = procesodeswap[1];
	vector<double> val = STATS.at(pswap);
	double timestamps = val[0];

	//BORRAS lo que hay en la RAM
	RAM.erase(apuntador);

	//incremento la variable del timestamp
	timestamps++;
	STATS.erase(pswap);
	STATS.insert(pair<int, vector<double> >(pswap, { timestamps, 0, val[2] }));

	cout << "Swap IN de la pagina: " << page << " de la memoria swap." << endl;
	//Insertamos lo que almacenamos del SWAP en el hueco que hay en la RAM
	RAM.insert(pair<int, vector<int> >(apuntador, valores));
	apuntador++;
	swapinn++;
	swapout++;
}

void estadisticas() {

	cout << "numero de Swap In's " << swapinn << endl;
	cout << "numero de Swap Out's " << swapout << endl;
	//Imprimimos las estadisticas de todos los procesos liberados 
	cout << "\nLas estadisticas son: \n";
	cout << "\tPROCESS\tTURNAROUND\tPAGE FAULTS\n";
	//navegamos por el mapa usando apuntadores
	for (auto ii = STATS.begin(); ii != STATS.end(); ++ii) {

			vector<double> myVector = (*ii).second;
			double timestamp = myVector[0];
			double check = myVector[1];
			double pagefault = myVector[2];
			if (check == 1) {

				cout << '\t' << (*ii).first << '\t' << timestamp << "s" << '\t' << '\t' << pagefault;
			}			


			cout << endl;

	}


}


void accesso(vector<int> info, int& count) {

	//A 17 5 0 ejemplo
	bool mem = false;
	int memoria = info[0];
	int proceso = info[1];
	int modificar = info[2];

	cout << "Se busca la memoria: " << memoria << endl;
	cout << "Del proceso: " << proceso << endl;
	cout << "Modificar: " << modificar << endl;

	int va = memoria / 16;
	cout << "va es: " << va << endl;

	cout << "Pagina de la direccion virtual: " << va << endl;

	vector<double> val = STATS.at(proceso);
	double read = val[0];
	

	for (int i = 0; i < SWAP.size(); i++) {
		vector<double> val = STATS.at(proceso);
		double pagefault = val[2];
		vector <int> valores = SWAP.at(i);
		int valor = valores[1];
		int valorn = valores[0];
		if (proceso == valor) {
			if (valorn == va) {
				cout << "El proceso se encuentra en la pagina: " << i << " del Registro SWAP" << endl;
				cout << "Swap in" << endl;
				pagefault++;
				read = val[0] + .1;
				STATS.erase(proceso);
				STATS.insert(pair<int, vector<double> >(proceso, { read, 0 ,pagefault}));
				swapin(i);
			}
		}
	}

	val = STATS.at(proceso);

	for (int i = 0; i < RAM.size(); i++) {
		vector <int> valores = RAM.at(i);
		int valor = valores[1];
		int valorn = valores[0];
		if (proceso == valor) {
			if (valorn == va) {
				read = val[0] + .1;
				STATS.erase(proceso);
				STATS.insert(pair<int, vector<double> >(proceso, { read, 0 , val[2]}));
				cout << "El proceso se encuentra en la pagina: " << i << " de la memoria real" << endl;
				int memoriareal;
				memoriareal = (i * 16) + (memoria - (va * 16));
				mem = true;
				cout << "La direccion real es " << memoriareal << endl;
			}
		}
	}

	if (!mem) {
		cout << "No se encontro ese proceso en la memoria..." << endl;
	}

	/*
	cout << "Esta es la instruccion: " << endl;
	for (int i = 0; i < info.size(); i++)
		cout << info[i] << " ";
		*/
}
