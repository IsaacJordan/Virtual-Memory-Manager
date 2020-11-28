#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include "Process.h"
using namespace std;
map<int, int> AUX;
map<int, int>::iterator itr;

//Esta funcion es para realizar debbuging en el codigo
void saludar() {
	cout << "FUNCIONA PRRO!\n";
}

//Esta funcion recibe la informacion del proceso qe se quiere agregar a la memoria real y el contador de memoria
void cargarproceso(vector<int> info, int &count) {
    carga(info[0], info[1], count);
}

// Esta funcion es llamada cuando
void swap(vector<int> info,int &count) {
    swap(info[0], info[1], count);
}

//Esta funcion se llama para remover los espacios del string input y guardar en un vector la informacion de tamano de proceso y su id
vector<int> removeDupWord(string str)
{
    // Used to split string around spaces.
    str[0] = '1';
    istringstream ss(str);
    vector<int> vector;
    string word; // for storing each word

    // Traverse through all words
    // while loop till we get 
    // strings to store in string word
    while (ss >> word)
    {
        // print the read word
        //cout << word << "\n";
        int num = stoi(word);
        vector.push_back(num);
    }

    vector.erase(vector.begin());
    return vector;
  
}

void accesso(vector<int> info, int &count) {

    //A 17 5 0 ejemplo
    bool memory = false;
    int cuentas = -1;
    int cuentar = -1;
    int memoria = info[0];
    int proceso = info[1];
    int modificar = info[2];

    cout << "Se busca la memoria: " << memoria<< endl;
    cout << "Del proceso: " << proceso << endl;
    cout << "Modificar: " << modificar << endl;

    int va = memoria / 16;
    cout << "va es: " << va << endl;

    cout << "Pagina de la direccion virtual: " << va << endl;

    for (int i = 0; i < SWAP.size(); i++) {
        if (proceso == SWAP.at(i)) {
            memory = true;
            cuentas++;
            
            if (cuentas == va) {
                cout << "El proceso se encuentra en la pagina: " << i << " del Registrp SWAP" << endl;
            }
        }
    }
    for (int i = 0; i < RAM.size(); i++) {
        if (proceso == RAM.at(i)) {
            memory = true;
            cuentar++;
            
            if (cuentar == va) {
                cout << "El proceso se encuentra en la pagina: " << i << " de la memoria real" << endl;
            }
        }
    }
  
    if (!memory) {
        cout << "No se encontro direccion real del proceso..." << endl;
        swap(info[0], info[1], count);
    }

    /*
    cout << "Esta es la instruccion: " << endl;

    for (int i = 0; i < info.size(); i++)
        cout << info[i] << " ";
        */
}


void liberar2(vector<int> info, int& count) {
    
    int proceso = info[0];
    int contador = 0;
    int pos;
    //
    for (int i = 0; i < RAM.size(); i++) {

        if(proceso != RAM.at(i)) {
            cout << "entre" << endl;
            AUX.emplace(contador, RAM.at(i));
            contador++;
        }
    }

    //Imprimimos la memoria real
    cout << "\nEl contenido en AUX es : \n";
    cout << "\tPAGE\tPROCESS\n";
    for (itr = AUX.begin(); itr != AUX.end(); ++itr) {
        cout << '\t' << itr->first
            << '\t' << itr->second << '\n';
    }
    cout << endl;
    
     //BORRAS
    RAM.clear();

    for (int i = 0; i < AUX.size(); i++) {
        RAM.insert(pair<int, int>(i, AUX.at(i)));
    }
    //BORRAS
    AUX.clear();

    //Imprimimos la memoria real
    cout << "\nEl contenido en Memoria Real es : \n";
    cout << "\tPAGE\tPROCESS\n";
    for (itr = RAM.begin(); itr != RAM.end(); ++itr) {
        cout << '\t' << itr->first
            << '\t' << itr->second << '\n';
    }
    cout << endl;
 
}

