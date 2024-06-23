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

    int cantidad_platos = 3;
    int cantidad_pistas = 3;
    int cantidad_bloques = 5;
    int bytes_por_bloque = 320;
    string nombre_archivo_metadata = "metadata";
    
    /*
    Estructura_HDD E(
        "HDD", 
        "PLATO", cantidad_platos, 'A', 'B', 
        "PISTA", cantidad_pistas, 
        "BLOQUE", cantidad_bloques,
        bytes_por_bloque,
        nombre_archivo_metadata
    );
    */

    Estructura_HDD E(
        "HDD","metadata.txt",
        cantidad_platos,
        cantidad_pistas,
        cantidad_bloques,
        bytes_por_bloque
    );
    for(string texto: E.HDD.listadoDeDireccionesHijos()){
        cout<<texto<<endl;
    }
    /*E.llenarBloque("HP01AP01A02",20);
    E.crearArchivoMetadatos("metadata");
    E.llenarBloque("HP01AP01A01",34);
    E.crearArchivoMetadatos("metadata");
    E.llenarBloque("HP01AP01A03",20);
    E.crearArchivoMetadatos("metadata");
    E.llenarBloque("HP02AP02A02",21);
    E.crearArchivoMetadatos("metadata");*/
    //E.llenarBloque("HP01AP02A01",20);

    //E.insertarTextoABloquePorID("Este se un texto que tiene más de 100 caracteres, es importante considerar que en este caso debería a saltar de linea. A continuacion pongo el ejemplo de un nuevo texto que tiene problemas para solucionar, espero que funque","HP01AP01A01");
    //E.crearArchivoMetadatos("metadata");
    

    /*cout << "Espacio usado: " << disco.getEspacioUsado() << endl;
    cout << "Espacio disponible: " << disco.getEspacioDisponible() << endl;*/
    /*E.HDD.setNodosEspacio();
    cout<<E.HDD.nodos_espacio.size();
    for(const auto &elemento : E.HDD.nodos_espacio){
        const string texto = elemento->direccion;
        cout<<texto<<endl;
    }*/

    //cin.get();

    return 0;
}