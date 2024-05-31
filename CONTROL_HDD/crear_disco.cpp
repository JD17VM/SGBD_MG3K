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

    /*Estructura_HDD E(
        "HDD2", 
        "PLATO", cantidad_platos, 'A', 'B', 
        "PISTA", cantidad_pistas, 
        "BLOQUE", cantidad_bloques,
        bytes_por_bloque
    );

    E.crearCarpetasArchivos();
    E.crearArchivoMetadatos("metadata");*/

    Estructura_HDD E("HDD2","HDD2/metadata.txt",cantidad_platos,cantidad_pistas,cantidad_bloques,bytes_por_bloque);
    for(string texto: E.HDD.listadoDeDireccionesHijos()){
        cout<<texto<<endl;
    }
    
    E.HDD.setNodosEspacio();
    cout<<E.HDD.nodos_espacio.size();
    for(const auto &elemento : E.HDD.nodos_espacio){
        const string texto = elemento->direccion;
        cout<<texto<<endl;
    }

    //cin.get();

    return 0;
}