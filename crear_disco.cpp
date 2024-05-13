#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <iomanip> // Para std::setw

using namespace std;

string completarStringConCeros(int numero, int longitud)
{
    string texto = to_string(numero);
    if (longitud > texto.length())
    {
        texto = string(longitud - texto.length(), '0') + texto;
    }

    return texto;
}

vector<string> generar_texto(string nombre_disco, string nombre_platos, int cant_platos_por_disco, char caras_a, char caras_b, string nombre_pistas, int cant_pistas_por_cara, string nombre_bloques, int cant_bloques_por_pista)
{
    vector<string> direcciones;
    direcciones.push_back(nombre_disco);
    for (int i = 1; i <= cant_platos_por_disco; i++)
    {
        const string plato_a = nombre_disco + "/" + nombre_platos + "_" + completarStringConCeros(i, 2) + "_" + caras_a;
        const string plato_b = nombre_disco + "/" + nombre_platos + "_" + completarStringConCeros(i, 2) + "_" + caras_b;
        direcciones.push_back(plato_a);
        direcciones.push_back(plato_b);
        for (int j = 1; j <= cant_pistas_por_cara; j++)
        {
            const string pista_a = plato_a + "/" + nombre_pistas + "_" + completarStringConCeros(j, 2);
            const string pista_b = plato_b + "/" + nombre_pistas + "_" + completarStringConCeros(j, 2);
            direcciones.push_back(pista_a);
            direcciones.push_back(pista_b);
            for (int k = 1; k <= cant_bloques_por_pista; k++)
            {
                const string bloque_a = pista_a + "/" + nombre_bloques + "_" + completarStringConCeros(k, 2) + ".txt";
                const string bloque_b = pista_b + "/" + nombre_bloques + "_" + completarStringConCeros(k, 2) + ".txt";
                direcciones.push_back(bloque_a);
                direcciones.push_back(bloque_b);
            }
        }
    }

    return direcciones;
}

void crear_carpetas_o_archivos(vector<string> &vector_direcciones,int bytes_por_bloque)
{
    for (const string direccion : vector_direcciones)
    {
        if (direccion[direccion.length() - 4] == '.')
        {
            ofstream archivo(direccion.c_str());
            if (archivo.is_open()){
                const string espacios_vacios(bytes_por_bloque,'*');
                archivo<<espacios_vacios;
                archivo.close();
            }
        }
        else
        {
            CreateDirectory(direccion.c_str(), NULL);
        }
    }
}

void crear_archivo_metadatos(string direccion,vector<string> &vector){
    ofstream archivo_m(direccion.c_str());
    if (archivo_m.is_open()){
        const string texto;
        for (const string &vec: vector)
        archivo_m<<vec<<endl;
        archivo_m.close();
    }
}


int main()
{


    int cantidad_platos = 5;
    int cantidad_pistas = 6;
    int cantidad_bloques = 3;
    int bytes_por_bloque = 10;

    vector<string> vec_dic = generar_texto("HDD", "PLATO", cantidad_platos, 'A', 'B', "PISTA", cantidad_pistas, "BLOQUE", cantidad_bloques);

    crear_carpetas_o_archivos(vec_dic,bytes_por_bloque);
    crear_archivo_metadatos("HDD/metadata.txt", vec_dic);

    return 0;
}