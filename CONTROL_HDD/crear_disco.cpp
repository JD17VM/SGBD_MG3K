#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <iomanip> // Para std::setw
#include "../megatron.h"
#include "Espacio_HDD.h"
#include "Estructura_HDD.h"

using namespace std;

int main()
{

    int cantidad_platos = 4;
    int cantidad_pistas = 3;
    int cantidad_bloques = 6;
    int bytes_por_bloque = 100;

    Estructura_HDD E(
        "HDD", 
        "PLATO", cantidad_platos, 'A', 'B', 
        "PISTA", cantidad_pistas, 
        "BLOQUE", cantidad_bloques,
        bytes_por_bloque
    );

    E.crearCarpetasArchivos();
    E.crearArchivoMetadatos("metadata");

    return 0;
}