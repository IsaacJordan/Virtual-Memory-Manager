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
#include "Process.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include "Saludo.h"
#include <fstream>
using namespace std;


int main() {
    
    //Esta variable nos ayuda a llevar un conteo de las paginas de la memoria real, para saber si aun hay espacio disponible
    int count = 0;
    vector<int> instruccion;

    //string line;
    ifstream myfile("ArchivoTrabajo.txt");
    if (myfile.is_open())
    {
        while (myfile.good())
        {
            //getline(myfile, line);
            do {
                //Declaramos una variable de tipo string para leer el input del usuario
                string input;
                getline(myfile, input);


                if (input[0] != 'C')
                {
                    //Enviamos el input a devolver solo los valores numericos
                    instruccion = removeDupWord(input);
                }


                //Se utiliza un switch para leer la primer posicion del input y determinar que tipo de instruccion es
                switch (input[0]) {
                    //Para el caso P se carga un proceso
                case 'P':
                    cout << "Input: " << input << endl;
                    //Revisamos si el numero de bytes que se ingresaron son mayores al maximo permitido
                    if (instruccion[0] > 2048 || instruccion[0] < 16) {
                        cout << "El numero de bytes es muy grande o muy pequeño para ser almacenado, vuelva a intentar" << endl;
                        break;
                    }
                    else if (count >= 127) {
                        //Se necesita hacer un swap si la memoria real de 128 paginas esta llena (0 - 127 paginas)
                        cout << "Se necesita hacer un swap, memoria llena!" << endl;
                        swap(instruccion, count);
                    }
                    else {
                        //Llamamos la funcion cargaproceso para subir el proceso recibido a la memoria real si hay espacio
                        cargarproceso(instruccion, count);
                    }

                    break;

                case 'A':
                    cout << "Input: " << input << endl;
                    accesso(instruccion, count);
                    break;

                case 'L':
                    cout << "Input: " << input << endl;
                    liberar2(instruccion, count);
                    break;

                case 'C':
                    cout << input << endl;
                    break;

                case 'F':
                    cout << "Input: " << input << endl;
                    estadisticas();
                    break;

                case 'E':
                    // 'E' es una instruccion para terminar el programa
                    return 0;

                default:
                    //Desplegar cuando una instruccion no es valida
                    cout << "La instruccion no es valida\n";
                    break;
                }
            } while (true);
        }
        myfile.close();
    }

    else cout << "Unable to open file";

   

    return 0;
}





//Mostramos el contenido de nuestro nuevo vector
//for (int i = 0; i < instruccion.size(); i++)
//    cout << instruccion[i] << " ";
