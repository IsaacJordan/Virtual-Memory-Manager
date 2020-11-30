#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include "Process.h"
using namespace std;
map<int, vector<int> > AUX;

//Esta funcion es para realizar debbuging en el codigo
void saludar() {
    cout << "FUNCIONA PRRO!\n";
}

//Esta funcion recibe la informacion del proceso qe se quiere agregar a la memoria real y el contador de memoria
void cargarproceso(vector<int> info, int& count) {
    carga(info[0], info[1], count);
}

// Esta funcion es llamada cuando
void swap(vector<int> info, int& count) {
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



void liberar2(vector<int> info, int& count) {

    int proceso = info[0];
    int contador = 0;
    //
    for (int i = 0; i < RAM.size(); i++) {
        vector <int> valores = RAM.at(i);
        int valor = valores[1];
        if (proceso != valor) {
            cout << "entre" << endl;
            AUX.emplace(contador, RAM.at(i));
            contador++;
        }
    }

    //Imprimimos la memoria real
    cout << "\nEl contenido en AUX es : \n";
    cout << "\tPAGE\tPROCESS\tPAGEPROCESS\n";
    for (auto ii = AUX.begin(); ii != AUX.end(); ++ii) {
        cout << '\t' << (*ii).first << '\t';
        vector <int> myVector = (*ii).second;
        for (unsigned j = 0; j < myVector.size(); j++) {
            cout << myVector[j] << '\t' << '\t';
        }
        cout << endl;
    }


    //BORRAS
    RAM.clear();
    contador = 0;
    for (int i = 0; i < AUX.size(); i++) {
        RAM.insert(pair<int, vector<int> >(i, AUX.at(i)));
    }
    //BORRAS
    AUX.clear();

    //Imprimimos la memoria real
    cout << "\nEl contenido en Memoria Real es : \n";
    cout << "\tPAGE\tPROCESS\tPageProcess\n";
    for (auto ia = RAM.begin(); ia != RAM.end(); ++ia) {
        cout << '\t' << (*ia).first << '\t';
        vector <int> myVector = (*ia).second;
        for (unsigned j = 0; j < myVector.size(); j++) {
            cout << myVector[j] << '\t' << '\t';
        }

        cout << endl;
    }

    for (int i = 0; i < SWAP.size(); i++) {
        vector <int> valores = SWAP.at(i);
        int valor = valores[1];
        if (proceso != valor) {
            cout << "entre" << endl;
            AUX.emplace(contador, SWAP.at(i));
            contador++;
        }
    }
    //BORRAS
    SWAP.clear();
    
    for (int i = 0; i < AUX.size(); i++) {
        SWAP.insert(pair<int, vector<int> >(i, AUX.at(i)));
    }
    //BORRAS
    AUX.clear();

    cout << "\nEl contenido en SWAP es : \n";
    cout << "\tPAGE\tPROCESS\tPAGEPROCESS\n";
    for (auto ii = SWAP.begin(); ii != SWAP.end(); ++ii) {
        cout << '\t' << (*ii).first << '\t';
        vector <int> myVector = (*ii).second;
        for (unsigned j = 0; j < myVector.size(); j++) {
            cout << myVector[j] << '\t' << '\t';
        }
        cout << endl;
    }





    count = RAM.size();

}

