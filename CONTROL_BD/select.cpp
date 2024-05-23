#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Campo{
    string nombre;
    string tipo;
    int numero_columna;
};


struct SELECT{
    string nombre_tabla;
};

vector<Campo> leer_cabecera(string texto_cabecera){
    vector<Campo> vec;
    int cont = 0;
    string linea;
    stringstream ss(texto_cabecera);
    getline(ss, linea, '#');
    Campo c;
    int cont_numero_columna = 0;
    while (getline(ss, linea, '#')){
        if(cont == 0){
            cont_numero_columna++;
            c.nombre = linea;
            c.numero_columna = cont_numero_columna;
            cont = 1;
        }else if(cont == 1){
            c.tipo = linea;
            vec.push_back(c);
            cont = 0;
        }
    }
    return vec;
}


string filtrar_registro_por_numero(string texto_registro,int numero){
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

string filtrar_registro_por_numero(string texto_registro,vector<int> numeros){
    string elemento;
    stringstream ss(texto_registro);
    int cont = 0;
    string texto = "";
    while (getline(ss, elemento, '#')){
        cont++;
        for (const int& numero: numeros){
            if(numero == cont){
                texto = texto + elemento + '\t';
                //texto = texto + elemento + "***";
                break;
            }
        }
    }
    return texto;
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
            cout << "Nombre: " << campo.nombre << ", Tipo: " << campo.tipo << ", Numero: " << campo.numero_columna << endl;
        }

        vector<int> numeros= {2,3,4};
        while (getline(archivo, linea)) { 
            cout<<filtrar_registro_por_numero(linea,3)<<endl;
        }
    archivo.close();
    }
}


int main() {
    
    leer_bloque_con_cabecera("metadata2.txt");
    //string texto = "HP01AP01A01#HDD/PLATO_01_A/PISTA_01/BLOQUE_01.txt#100#0";
    //vector<int> numeros= {1,2,3,4};
    //cout<<filtrar_registro_por_numero(texto,numeros);

    return 0;
}
