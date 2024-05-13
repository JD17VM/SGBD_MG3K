#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <iomanip> // Para std::setw

using namespace std;

struct Espacio_HDD{
    string tipo; //HDD, PLATO_CARA, PISTA, BLOQUE
    string direccion;
    int capacidad_total;
    int capacidad_usada;
    vector<Espacio_HDD> vector_espacios_hdd;
};


// Se queda, no se modifica
string completarStringConCeros(int numero, int longitud){
    string texto = to_string(numero);
    if (longitud > texto.length()){
        texto = string(longitud - texto.length(), '0') + texto;
    }
    return texto;
}

// Modificar para que lea la estructura
vector<string> vectorDireccionesEstructuraHDD(string nombre_disco, string nombre_platos, int cant_platos_por_disco, char caras_a, char caras_b, string nombre_pistas, int cant_pistas_por_cara, string nombre_bloques, int cant_bloques_por_pista){
    vector<string> direcciones;
    direcciones.push_back(nombre_disco);
    for (int i = 1; i <= cant_platos_por_disco; i++){
        const string plato_a = nombre_disco + "/" + nombre_platos + "_" + completarStringConCeros(i, 2) + "_" + caras_a;
        const string plato_b = nombre_disco + "/" + nombre_platos + "_" + completarStringConCeros(i, 2) + "_" + caras_b;
        direcciones.push_back(plato_a);
        direcciones.push_back(plato_b);
        for (int j = 1; j <= cant_pistas_por_cara; j++){
            const string pista_a = plato_a + "/" + nombre_pistas + "_" + completarStringConCeros(j, 2);
            const string pista_b = plato_b + "/" + nombre_pistas + "_" + completarStringConCeros(j, 2);
            direcciones.push_back(pista_a);
            direcciones.push_back(pista_b);
            for (int k = 1; k <= cant_bloques_por_pista; k++){
                const string bloque_a = pista_a + "/" + nombre_bloques + "_" + completarStringConCeros(k, 2) + ".txt";
                const string bloque_b = pista_b + "/" + nombre_bloques + "_" + completarStringConCeros(k, 2) + ".txt";
                direcciones.push_back(bloque_a);
                direcciones.push_back(bloque_b);
            }
        }
    }

    return direcciones;
}

void llenarEstructuraHDD(Espacio_HDD &ESPACIO_HDD, string nombre_disco, string nombre_platos, int cant_platos_por_disco, char caras_a, char caras_b, string nombre_pistas, int cant_pistas_por_cara, string nombre_bloques, int cant_bloques_por_pista){
    ESPACIO_HDD.tipo = "HDD";
    ESPACIO_HDD.direccion = "HDD";
    ESPACIO_HDD.capacidad_total = 0;
    ESPACIO_HDD.capacidad_usada = 0;

    for (int i = 1; i <= cant_platos_por_disco; i++){
        const string plato_a = nombre_disco + "/" + nombre_platos + "_" + completarStringConCeros(i, 2) + "_" + caras_a;
        const string plato_b = nombre_disco + "/" + nombre_platos + "_" + completarStringConCeros(i, 2) + "_" + caras_b;
        Espacio_HDD PLATO_A; 
        Espacio_HDD PLATO_B;
        PLATO_A.tipo = "PLATO_CARA"; 
        PLATO_B.tipo = "PLATO_CARA";
        PLATO_A.direccion = plato_a;
        PLATO_B.direccion = plato_b;
        PLATO_A.capacidad_total = 0;
        PLATO_B.capacidad_total = 0;
        PLATO_A.capacidad_usada = 0;
        PLATO_B.capacidad_usada = 0;
        for (int j = 1; j <= cant_pistas_por_cara; j++){
            const string pista_a = plato_a + "/" + nombre_pistas + "_" + completarStringConCeros(j, 2);
            const string pista_b = plato_b + "/" + nombre_pistas + "_" + completarStringConCeros(j, 2);
            Espacio_HDD PISTA_A;
            Espacio_HDD PISTA_B;
            PISTA_A.tipo = "PISTA"; 
            PISTA_B.tipo = "PISTA";
            PISTA_A.direccion = pista_a;
            PISTA_B.direccion = pista_b;
            PISTA_A.capacidad_total = 0;
            PISTA_B.capacidad_total = 0;
            PISTA_A.capacidad_usada = 0;
            PISTA_B.capacidad_usada = 0;
            for (int k = 1; k <= cant_bloques_por_pista; k++){
                const string bloque_a = pista_a + "/" + nombre_bloques + "_" + completarStringConCeros(k, 2) + ".txt";
                const string bloque_b = pista_b + "/" + nombre_bloques + "_" + completarStringConCeros(k, 2) + ".txt";
                Espacio_HDD BLOQUE_A;
                Espacio_HDD BLOQUE_B;
                BLOQUE_A.tipo = "BLOQUE"; 
                BLOQUE_B.tipo = "BLOQUE";
                BLOQUE_A.direccion = bloque_a;
                BLOQUE_B.direccion = bloque_b;
                BLOQUE_A.capacidad_total = 0;
                BLOQUE_B.capacidad_total = 0;
                BLOQUE_A.capacidad_usada = 0;
                BLOQUE_B.capacidad_usada = 0;
                PISTA_A.vector_espacios_hdd.push_back(BLOQUE_A);
                PISTA_B.vector_espacios_hdd.push_back(BLOQUE_B);
            }
            PLATO_A.vector_espacios_hdd.push_back(PISTA_A);
            PLATO_B.vector_espacios_hdd.push_back(PISTA_B);
        }
        ESPACIO_HDD.vector_espacios_hdd.push_back(PLATO_A);
        ESPACIO_HDD.vector_espacios_hdd.push_back(PLATO_B);
    }
}


// Modificar para que lea la estructura
void crearCarpetasArchivos(vector<string> &vector_direcciones,int bytes_por_bloque){
    for (const string direccion : vector_direcciones){
        if (direccion[direccion.length() - 4] == '.'){
            ofstream archivo(direccion.c_str());
            if (archivo.is_open()){
                const string espacios_vacios(bytes_por_bloque,'*');
                archivo<<espacios_vacios;
                archivo.close();
            }
        }
        else{
            CreateDirectory(direccion.c_str(), NULL);
        }
    }
}

void crearArchivoMetadatos(string direccion,vector<string> &vector_de_direccion_de_elementos_de_disco){
    ofstream archivo_m(direccion.c_str());
    if (archivo_m.is_open()){
        const string texto;
        for (const string &vec: vector_de_direccion_de_elementos_de_disco)
        archivo_m<<vec<<endl;
        archivo_m.close();
    }
}


int main()
{


    int cantidad_platos = 4;
    int cantidad_pistas = 3;
    int cantidad_bloques = 6;
    int bytes_por_bloque = 100;

    //vector<string> vec_dic = vectorDireccionesEstructuraHDD("HDD", "PLATO", cantidad_platos, 'A', 'B', "PISTA", cantidad_pistas, ///////"BLOQUE", cantidad_bloques);

    //crearCarpetasArchivos(vec_dic,bytes_por_bloque);
    //crearArchivoMetadatos("HDD/metadata.txt", vec_dic);



    Espacio_HDD ESPACIO_HDD;
    llenarEstructuraHDD(ESPACIO_HDD,"HDD", "PLATO", cantidad_platos, 'A', 'B', "PISTA", cantidad_pistas, "BLOQUE", cantidad_bloques);
    cout<<ESPACIO_HDD.vector_espacios_hdd.size();
    cout<<ESPACIO_HDD.vector_espacios_hdd[0].vector_espacios_hdd.size();
    cout<<ESPACIO_HDD.vector_espacios_hdd[0].vector_espacios_hdd[0].vector_espacios_hdd.size();

    return 0;
}