#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>

#include "Buffer_Manager.h"

using namespace std;

int main(){

    Buffer_Manager p(3);
    p.llamarABloque("Bloques/BLOQUE_01.txt");
    p.imprimirEstado();
    p.llamarABloque("Bloques/BLOQUE_04.txt");
    p.imprimirEstado();
    p.llamarABloque("Bloques/BLOQUE_06.txt");
    p.imprimirEstado();
    p.llamarABloque("Bloques/BLOQUE_06.txt");
    p.imprimirEstado();
    p.llamarABloque("Bloques/BLOQUE_02.txt");
    p.imprimirEstado();
    p.llamarABloque("Bloques/BLOQUE_04.txt");
    p.imprimirEstado();
    p.llamarABloque("Bloques/BLOQUE_05.txt");
    p.imprimirEstado();
    p.llamarABloque("Bloques/BLOQUE_03.txt");
    p.imprimirEstado();
    p.llamarABloque("Bloques/BLOQUE_02.txt");
    p.imprimirEstado();
    return 0;
}

