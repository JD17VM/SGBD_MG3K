#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>

#include <cstdlib>
#include <conio.h>

#include "Buffer_Manager.h"

using namespace std;

void mostrarMenu() {
    cout << "========= MENÚ =========" << endl;
    cout << "1. Bloque_1" << endl;
    cout << "2. Bloque_2" << endl;
    cout << "3. Bloque_3" << endl;
    cout << "4. Bloque_4" << endl;
    cout << "5. Bloque_5" << endl;
    cout << "6. Bloque_6" << endl;
    cout << "0. Salir" << endl;
    cout << "========================" << endl;
}


int main(){

    Buffer_Manager p(3);
    /*p.llamarABloque("Bloques/BLOQUE_01.txt");
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
    p.imprimirEstado();*/

    int opcion = 0;
    char opcion2 = 0;
    bool salir = false;
    system("cls");
    p.imprimirEstado();
    while(!salir){

        mostrarMenu();
        cout << "Lectura o escritura: ";
        cin >> opcion2;
        cout << "Selecciona una opción: ";
        cin >> opcion;


        switch(opcion){
            case 1:
                p.llamarABloque("Bloques/BLOQUE_01.txt");
                break;
            case 2:
                p.llamarABloque("Bloques/BLOQUE_02.txt");
                break;
            case 3:
                p.llamarABloque("Bloques/BLOQUE_03.txt");
                break;
            case 4:
                p.llamarABloque("Bloques/BLOQUE_04.txt");
                break;
            case 5:
                p.llamarABloque("Bloques/BLOQUE_05.txt");
                break;
            case 6:
                p.llamarABloque("Bloques/BLOQUE_06.txt");
                break;
            case 0:
                salir = true;
                break;
        }
        system("cls");
        p.imprimirEstado();
        
    }


    return 0;
}

