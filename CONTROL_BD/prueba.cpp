#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Campo{
    string nombre;
    string tipo;
};

vector<Campo> leer_cabecera(string texto_cabecera){
    vector<Campo> vec;
    int cont = 0;
    string linea;
    stringstream ss(texto_cabecera);
    getline(ss, linea, '#');
    Campo c;
    while (getline(ss, linea, '#')){
        if(cont == 0){
            c.nombre = linea;
            cont = 1;
        }else if(cont == 1){
            c.tipo = linea;
            vec.push_back(c);
            cont = 0;
        }
    }
    return vec;
}


string filtrar_registro(string texto_registro,int numero){
    string elemento;
    stringstream ss(texto_registro);
    int cont = 0;
    while (getline(ss, elemento, '#')){
        cont++;
        if(numero == cont){
            return elemento;
        }
    }
    return "";
}


void leer_bloque_con_cabecera(string nombre_archivo){
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
    }else{

        string linea;
        getline(archivo,linea);
        const vector<Campo> vec = leer_cabecera(linea);
        for (const auto& campo : vec) {
            cout << "Nombre: " << campo.nombre << ", Tipo: " << campo.tipo << endl;
        }


        //while (getline(archivo, linea)) {
        //    cout<<linea<<endl;
        //}
    archivo.close();
    }
}


int main() {
    
    //leer_bloque_con_cabecera("metadata2.txt");
    string texto = "HP01AP01A01#HDD/PLATO_01_A/PISTA_01/BLOQUE_01.txt#100#0";
    cout<<filtrar_registro(texto,6);

    return 0;
}
