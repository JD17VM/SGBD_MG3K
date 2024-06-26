#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <conio.h> // Para getch() en Windows


#include "Buffer_Manager.h"

using namespace std;

void limpiarPantalla() {
    system("cls");
}

void esperarTecla() {
    getch();
}

void mostrarMenuInicial(){
    cout << "== MENU INICIAL ==" << endl;
    cout << "1. Llamar a Bloque" << endl;
    cout << "2. Flush Frame" << endl;
    cout << "3. Unpin Frame" << endl;
    cout << "0. Salir" << endl;
    cout << "==================" << endl;
}

void mostrarMenuFlush() {
    cout << "== FLUSH FRAMES ==" << endl;
    cout << "1. Frame_1" << endl;
    cout << "2. Frame_2" << endl;
    cout << "3. Frame_3" << endl;
    cout << "4. Frame_4" << endl;
    cout << "5. Frame_5" << endl;
    cout << "0. Salir" << endl;
    cout << "==================" << endl;
}

void mostrarMenuUnpin() {
    cout << "== UNPIN FRAMES ==" << endl;
    cout << "1. Frame_1" << endl;
    cout << "2. Frame_2" << endl;
    cout << "3. Frame_3" << endl;
    cout << "4. Frame_4" << endl;
    cout << "5. Frame_5" << endl;
    cout << "0. Salir" << endl;
    cout << "==================" << endl;
}


void mostrarMenuLW(){
    cout << "== LECTURA O ESCRITURA ==" << endl;
    cout << "L. Lectura" << endl;
    cout << "W. Escritura" << endl;
    cout << "0. Salir" << endl;
    cout << "=========================" << endl;
}

void mostrarMenuBloques() {
    cout << "======== BLOQUE ========" << endl;
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
    Buffer_Manager p(5);
    bool salir = false;

    while(!salir) {
        limpiarPantalla();
        p.imprimirEstado();
        mostrarMenuInicial();

        int opcionInicial;
        cout << "Selecciona una opcion: ";
        cin >> opcionInicial;

        switch(opcionInicial) {
            case 1: {
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();
                    mostrarMenuLW();

                    char opcionLW;
                    cout << "Lectura o escritura: ";
                    cin >> opcionLW;

                    limpiarPantalla();
                    p.imprimirEstado();
                    mostrarMenuBloques();

                    cout<<"La letra que se envia es: "<<opcionLW<<endl;
                    int opcionBloque;
                    cout << "Selecciona un bloque: ";
                    cin >> opcionBloque;

                    if (opcionBloque == 0) {
                        subMenuSalir = true;
                        continue;
                    }

                    
                    string direccionBloque;
                    switch(opcionBloque) {
                        case 1: direccionBloque = "Bloques/BLOQUE_01.txt"; break;
                        case 2: direccionBloque = "Bloques/BLOQUE_02.txt"; break;
                        case 3: direccionBloque = "Bloques/BLOQUE_03.txt"; break;
                        case 4: direccionBloque = "Bloques/BLOQUE_04.txt"; break;
                        case 5: direccionBloque = "Bloques/BLOQUE_05.txt"; break;
                        case 6: direccionBloque = "Bloques/BLOQUE_06.txt"; break;
                        default: cout << "Opcion invalida. Intenta de nuevo." << endl; esperarTecla(); continue;
                    }

                    limpiarPantalla();
                    p.llamarABloque(direccionBloque, opcionLW);
                    //p.imprimirEstado();
                    //esperarTecla();
                }
                break;
            }
            case 2: {
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();
                    mostrarMenuFlush();

                    int opcionFlush;
                    cout << "Selecciona un frame para hacer flush: ";
                    cin >> opcionFlush;

                    if (opcionFlush == 0) {
                        subMenuSalir = true;
                        continue;
                    }

                    if (opcionFlush >= 1 && opcionFlush <= 4) {
                        p.flushFrame(opcionFlush - 1);
                        cout << "Flush realizado en Frame_" << opcionFlush << "." << endl;
                    } else {
                        cout << "Opcion inválida. Intenta de nuevo." << endl;
                    }
                    esperarTecla();
                }
                break;
            }

            case 3:{
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();
                    mostrarMenuUnpin();

                    int opcionUnpin;
                    cout << "Selecciona un frame para hacer despinnear: ";
                    cin >> opcionUnpin;

                    if (opcionUnpin == 0) {
                        subMenuSalir = true;
                        continue;
                    }

                    if (opcionUnpin >= 1 && opcionUnpin <= 4) {
                        p.unPinFrame(opcionUnpin - 1);
                        cout << "Unpin realizado en Frame_" << opcionUnpin << "." << endl;
                    } else {
                        cout << "Opcion inválida. Intenta de nuevo." << endl;
                    }
                    esperarTecla();
                }
                break;
            }

            case 0:
                salir = true;
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo." << endl;
                esperarTecla();
                break;
        }
    }

    return 0;
}
