#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include "Process.h"
using namespace std;

void invalido() {
	cout << "La instruccion no es valida\n";
}

void saludar() {
	cout << "FUNCIONA PRRO!\n";
}

void cargarproceso(vector<int> info, int &count) {
    /*Process P = *new Process();
    P.getData(info[0], info[1], count);
    P.showData();
    P.Upload();*/
    carga(info[0], info[1], count);
}

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