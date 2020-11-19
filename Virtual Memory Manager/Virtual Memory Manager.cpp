// Virtual Memory Manager.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
/*
   ------------------------------------
    Memoria Real - M = 2048 bytes
    0   - physical addres 0
    1
    2
    .
    .
    2047    -pyshical address 2047 = 128 paginas
    ------------------------------------
    Swapping - S = 4096 bytes = 256 paginas
    ------------------------------------
    Pagina = 16 bytes = 1 pagina
    ------------------------------------
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

    int count = 0;

    do {
        
        string input;
        getline(cin, input);
        //Enviamos el input a devolver solo los valores numericos
        vector<int> instruccion = removeDupWord(input);
      
        //Mostramos el contenido de nuestro nuevo vector
        //for (int i = 0; i < instruccion.size(); i++)
        //    cout << instruccion[i] << " ";

    switch (input[0]) {
        case 'P':
            cargarproceso(instruccion, count);
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
            return 0;

        default:
            invalido();
            break;
        }
    } while (true);
    
    

    return 0;
}

