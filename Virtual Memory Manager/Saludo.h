#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include "Process.h"
using namespace std;

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

void accesso(vector<int> info) {

    //A 17 5 0 ejemplo
    int count = 0;
    int memoria = info[0];
    int proceso = info[1];
    int modificar = info[2];

    cout << "Se busca la memoria: " << memoria<< endl;
    cout << "Del proceso: " << proceso << endl;
    cout << "Modificar: " << modificar << endl;

    int va = memoria / 16;

    //cout << "Esta en la direccion virtual: " << va << endl;

    for (int i = 0; i < RAM.size(); i++) {
        if (proceso == RAM.at(i)) {
            cout << "Se encontro el proceso" << endl;
            count = i;
        }

        if (va == count) {
            
            cout << "La memoria real esta en la pagina: " << count << endl;
        }

    }

    /*
    cout << "Esta es la instruccion: " << endl;

    for (int i = 0; i < info.size(); i++)
        cout << info[i] << " ";
        */
}