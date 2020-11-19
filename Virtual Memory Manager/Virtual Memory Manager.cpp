// Virtual Memory Manager.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
/*
/hola amiguitos :)
*   ------------------------------------
    Memoria Real - M = 2048 bytes
    0   - physical addres 0
    1
    2
    .
    .
    2047    -pyshical address 2047
    ------------------------------------
    Swapping - S = 4096 bytes
    ------------------------------------
    Pagina = 16 bytes
*/
#include "Saludo.h"
#include "Process.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
using namespace std;


int main() {
    
    string input;
    getline(cin, input);
    //Enviamos el input a devolver solo los valores numericos
    vector<int> vector = removeDupWord(input);
    //Mostramos el contenido de nuestro nuevo vector
    for (int i = 0; i < vector.size(); i++)
        cout << vector[i] << " ";

   switch (input[0]) {
    case 'P':
        saludar();
        break;

    case 'A':
        saludar();
        break;

    case 'L':
        saludar();
        break;

    case 'C':
        saludar();
        break;

    case 'F':
        saludar();
        break;

    case 'E':
        saludar();
        break;

    default:
        invalido();
        break;

        //holi


    }

    return 0;
}

