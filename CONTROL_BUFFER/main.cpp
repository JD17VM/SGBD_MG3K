#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

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
    p.llamarABloque("Bloques/BLOQUE_02.txt");
    p.imprimirEstado();
    p.llamarABloque("Bloques/BLOQUE_04.txt");
    p.imprimirEstado();
    

   //Frame p("NUEVO");
   //cout<<p.direccion_frame;

    return 0;
}

