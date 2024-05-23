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
    
    leer_bloque_con_cabecera("metadata2.txt");

    return 0;
}
