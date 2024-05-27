#include <iostream>
#include <string>

using namespace std;

struct Bloque{
    string direccion_bloque;
    int capacidad_disponible;
    int capacidad_total;

    Bloque* siguiente;
    Bloque* anterior;

    Bloque(string direccion_bloque){
        this->direccion_bloque = direccion_bloque;
        this->siguiente = nullptr;
        this->anterior = nullptr;
    }
};