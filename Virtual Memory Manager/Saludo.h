#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
using namespace std;
//Mapa auxiliar para realizar los swapings
map<int, vector<int> > AUX;


//Esta funcion recibe la informacion del proceso qe se quiere agregar a la memoria real y el contador de memoria
//Esta funcion recibe los datos del proceso y un contador global que lleva registro del tamaño de la memoria real
void cargarproceso(vector<int> info, int& count) {
    carga(info[0], info[1], count);
}

// Esta funcion es llamada cuando se busca realizar un swap por diferentes razones
//Esta funcion recibe los datos del proceso y un contador global que lleva registro del tamaño de la memoria real
void swap(vector<int> info, int& count) {
    //La funcion es llamada mediante datos especificos a RealMemory.h para realizar el cambio definitivo.
    swap(info[0], info[1], count);
}


//Esta funcion se llama para remover los espacios del string input y guardar en un vector la informacion de tamano de proceso y su id
//Recibe el string de la linea del archivo de texto para eliminar los espacios entre palabras y numeros
//Despues, regresa la informacion en un string para poder acceder a esa informacion/datos mas facilmente
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
        //De una libreria especial, stoi convierte un string a un entero para poderlo
        //introducir a nuestro nuevo vector
        int num = stoi(word);
        vector.push_back(num);
    }

    vector.erase(vector.begin());
    //Regresa el vector con la informacion deseada
    return vector;

}


//Esta funcion es llamada para liberar el espacio que ocupa un cierto proceso
//Recibe la informacion del proceso en forma de vector y contador global que lleva la cuenta del
//tamaño de la memoria real para saber si esta llena
void liberar2(vector<int> info, int& count) {

    //Nombre del proceso que se desea liberar
    int proceso = info[0];
    int contador = 0;
    //LOOP que copia los procesos que son diferentas al buscado. De esta manera obtenemos un nuevo mapa
    //sin el proceso que queremos borrar, pero ahora ordenado
    for (int i = 0; i < RAM.size(); i++) {
        vector <int> valores = RAM.at(i);
        int valor = valores[1];
        if (proceso != valor) {
            AUX.emplace(contador, RAM.at(i));
            contador++;
        }
    }

    //Imprimimos la memoria real
    cout << "\nEl contenido en AUX es : \n";
    cout << "\tPAGE\tPAGE PROCESS\tPROCESS\n";
    for (auto ii = AUX.begin(); ii != AUX.end(); ++ii) {
        cout << '\t' << (*ii).first << '\t';
        vector <int> myVector = (*ii).second;
        for (unsigned j = 0; j < myVector.size(); j++) {
            cout << myVector[j] << '\t' << '\t';
        }
        cout << endl;
    }

    //Se declara un vector que nos ayuda a mantener la informacion de estadisticas del proceso
    vector<double> val = STATS.at(proceso);
    //Aumentamos por 0.1 segundos al eliminar cada marco del proceso
    double borradas = (RAM.size() - AUX.size()) * .1;
    double segundoliberar = val[0] + borradas;
    STATS.erase(proceso);
    STATS.insert(pair<int, vector<double> >(proceso, { segundoliberar, 1 , val[2] }));

    //Borramos el contenido de la memoria real
    RAM.clear();
    
    //Ingresamos los datos ordenados con el proceso eliminado y con todos los procesos restantes sin guecos
    contador = 0;
    for (int i = 0; i < AUX.size(); i++) {
        RAM.insert(pair<int, vector<int> >(i, AUX.at(i)));
    }
    //Borramos el contenido mapa auxiliar
    AUX.clear();

    //Imprimimos la memoria real
    cout << "\nEl contenido en Memoria Real es : \n";
    cout << "\tPAGE\tPAGE PROCESS\tPROCESS\n";
    for (auto ia = RAM.begin(); ia != RAM.end(); ++ia) {
        cout << '\t' << (*ia).first << '\t';
        vector <int> myVector = (*ia).second;
        for (unsigned j = 0; j < myVector.size(); j++) {
            cout << myVector[j] << '\t' << '\t';
        }

        cout << endl;
    }

    //Ingresamos los datos del registro swap a nuestro mapa auxiliar
    for (int i = 0; i < SWAP.size(); i++) {
        vector <int> valores = SWAP.at(i);
        int valor = valores[1];
        if (proceso != valor) {
            AUX.emplace(contador, SWAP.at(i));
            contador++;
        }
    }
    
    //Aumentamos por 0.1 segundos al eliminar cada marco del proceso
    val = STATS.at(proceso);
    borradas = (SWAP.size() - AUX.size()) * .1;
    segundoliberar = val[0] + borradas;
    STATS.erase(proceso);
    STATS.insert(pair<int, vector<double> >(proceso, { segundoliberar, 1 , val[2] }));

    //Borramos el contenido del mapa del registro de swap
    SWAP.clear();
    
    //Actualizamos nuestro registro de swap desde el mapa auxiliar con los procesos sin guecos
    for (int i = 0; i < AUX.size(); i++) {
        SWAP.insert(pair<int, vector<int> >(i, AUX.at(i)));
    }
    //BORRAS
    AUX.clear();

    //Mostramos el contenido del registro de SWAP
    cout << "\nEl contenido en SWAP es : \n";
    cout << "\tPAGE\tPAGE PROCESS\tPROCESS\n";
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

