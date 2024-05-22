#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <iomanip> // Para std::setw
#include "../megatron.h"

using namespace std;

struct Espacio_HDD
{
    string tipo; // HDD, PLATO_CARA, PISTA, BLOQUE
    string direccion;
    int capacidad_total;
    int capacidad_usada;
    vector<Espacio_HDD> vector_espacios_hdd;

    vector<string> listado_de_direcciones_hijos()
    {
        vector<string> direcciones;
        direcciones.push_back(direccion);
        for (const auto &espacio : vector_espacios_hdd)
        {
            direcciones.push_back(espacio.direccion);
            for (const auto &espacio_2 : espacio.vector_espacios_hdd)
            {
                direcciones.push_back(espacio_2.direccion);
                for (const auto &espacio_3 : espacio_2.vector_espacios_hdd)
                {
                    direcciones.push_back(espacio_3.direccion);
                }
            }
        }
        return direcciones;
    };

    int calcularCapacidadTotal() const
    {
        int capacidadTotal = capacidad_total;
        for (const auto &espacio : vector_espacios_hdd)
        {
            capacidadTotal += espacio.calcularCapacidadTotal();
        }
        return capacidadTotal;
    }

    int calcularEspacioUsado() const
    {
        int capacidadUsada = capacidad_usada;
        for (const auto &espacio : vector_espacios_hdd)
        {
            capacidadUsada += espacio.calcularEspacioUsado();
        }
        return capacidadUsada;
    }

    vector<int> listado_de_tamanio_direcciones_hijos()
    {
        vector<int> tamanios;
        tamanios.push_back(calcularEspacioUsado());
        for (const auto &espacio : vector_espacios_hdd)
        {
            tamanios.push_back(espacio.calcularEspacioUsado());
            for (const auto &espacio_2 : espacio.vector_espacios_hdd)
            {
                tamanios.push_back(espacio_2.calcularEspacioUsado());
                for (const auto &espacio_3 : espacio_2.vector_espacios_hdd)
                {
                    tamanios.push_back(espacio_3.calcularEspacioUsado());
                }
            }
        }
        return tamanios;
    };
};

struct Estructura_HDD
{
    Espacio_HDD ESPACIO_HDD;

    string nombre_disco;
    string nombre_platos;
    int cant_platos_por_disco;
    char caras_a; 
    char caras_b;
    string nombre_pistas;
    int cant_pistas_por_cara;
    string nombre_bloques;
    int cant_bloques_por_pista;
    int bytes_por_bloque;

    Estructura_HDD(string _nombre_disco, string _nombre_platos, int _cant_platos_por_disco, char _caras_a, char _caras_b, string _nombre_pistas, int _cant_pistas_por_cara, string _nombre_bloques, int _cant_bloques_por_pista, int _bytes_por_bloque){
        nombre_disco = _nombre_disco;
        nombre_platos = _nombre_platos;
        cant_platos_por_disco = _cant_platos_por_disco;
        caras_a = _caras_a;
        caras_b = _caras_b;
        nombre_pistas = _nombre_pistas;
        cant_pistas_por_cara = _cant_pistas_por_cara;
        nombre_bloques = _nombre_bloques;
        cant_bloques_por_pista = _cant_bloques_por_pista;
        bytes_por_bloque = _bytes_por_bloque;

        ESPACIO_HDD.tipo = "HDD";
        ESPACIO_HDD.direccion = "HDD";
        ESPACIO_HDD.capacidad_total = 0;
        ESPACIO_HDD.capacidad_usada = 0;

        for (int i = 1; i <= cant_platos_por_disco; i++)
        {
            const string plato_a = nombre_disco + "/" + nombre_platos + "_" + completarNumeroConCeros(i, 2) + "_" + caras_a;
            const string plato_b = nombre_disco + "/" + nombre_platos + "_" + completarNumeroConCeros(i, 2) + "_" + caras_b;
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
            for (int j = 1; j <= cant_pistas_por_cara; j++)
            {
                const string pista_a = plato_a + "/" + nombre_pistas + "_" + completarNumeroConCeros(j, 2);
                const string pista_b = plato_b + "/" + nombre_pistas + "_" + completarNumeroConCeros(j, 2);
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
                for (int k = 1; k <= cant_bloques_por_pista; k++)
                {
                    const string bloque_a = pista_a + "/" + nombre_bloques + "_" + completarNumeroConCeros(k, 2) + ".txt";
                    const string bloque_b = pista_b + "/" + nombre_bloques + "_" + completarNumeroConCeros(k, 2) + ".txt";
                    Espacio_HDD BLOQUE_A;
                    Espacio_HDD BLOQUE_B;
                    BLOQUE_A.tipo = "BLOQUE";
                    BLOQUE_B.tipo = "BLOQUE";
                    BLOQUE_A.direccion = bloque_a;
                    BLOQUE_B.direccion = bloque_b;
                    BLOQUE_A.capacidad_total = bytes_por_bloque;
                    BLOQUE_B.capacidad_total = bytes_por_bloque;
                    BLOQUE_A.capacidad_usada = bytes_por_bloque;
                    BLOQUE_B.capacidad_usada = bytes_por_bloque;
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


    void crearCarpetasArchivos()
    {
        for (const string direccion : ESPACIO_HDD.listado_de_direcciones_hijos())
        {
            if (direccion[direccion.length() - 4] == '.')
            {
                ofstream archivo(direccion.c_str());
                if (archivo.is_open())
                {
                    const string espacios_vacios(bytes_por_bloque, '*');
                    archivo << espacios_vacios;
                    archivo.close();
                }
            }
            else
            {
                CreateDirectory(direccion.c_str(), NULL);
            }
        }
    }

    void crearArchivoMetadatos(string direccion)
    {
        ofstream archivo_m(direccion.c_str());
        if (archivo_m.is_open())
        {
            const string texto;
            for (int i = 0; i < ESPACIO_HDD.listado_de_direcciones_hijos().size(); i++)
            {
                const string texto_direccion_hijo = ESPACIO_HDD.listado_de_direcciones_hijos()[i];
                const string texto_tamanio_hijo = to_string(ESPACIO_HDD.listado_de_tamanio_direcciones_hijos()[i]);
                archivo_m << textoCompletadoCon(texto_direccion_hijo,' ',45,"derecha") << "      " << textoCompletadoCon(texto_tamanio_hijo,' ',8,"izquierda") << endl;
            }
            archivo_m.close();
        }
    }
};

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
    E.crearArchivoMetadatos("HDD/metadata.txt");

    return 0;
}