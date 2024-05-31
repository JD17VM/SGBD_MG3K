#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../megatron.h"

using namespace std;

struct Campo{
    string nombre;
    string tipo;
    int numero_columna;
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

vector<int> numeros_de_campos(vector<string> &campos_solicitados,vector<Campo> &campos_todo){
    vector<int> v;
    for(const auto& campo_t : campos_todo){
        for(const string& campo_s : campos_solicitados){
            if(campo_t.nombre == campo_s){
                v.push_back(campo_t.numero_columna);
            }
        }
    }
    return v;
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
                texto = texto + textoCompletadoCon(elemento,' ',15,"derecha") + " | ";
                //texto = texto + elemento + "***";
                
                break;
            }
        }
    }
    return texto;
}


struct SELECT{
    string nombre_tabla;
    vector<Campo> lista_de_campos;

    void SELECT_ALL(string direccion_archivo,string nombre_tabla, string cabecera = ""){
        ifstream archivo(direccion_archivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo." << endl;
        }else{

            string linea;
            if(cabecera == ""){
                getline(archivo,linea);
                lista_de_campos = leer_cabecera(linea);
            }else{
                lista_de_campos = leer_cabecera(cabecera);
            }

            for (const auto& campo : lista_de_campos) {
                cout << textoCompletadoCon(campo.nombre,' ',15,"derecha") << " | ";
            }cout<<endl;

            string elemento;
            while (getline(archivo, linea)) { 
                stringstream ss(linea);
                while (getline(ss, elemento, '#')){
                    cout << textoCompletadoCon(elemento,' ',15,"derecha") << " | ";
                }
                cout<<endl;
            }
        archivo.close();
        }
    }

    void SELECT_N(string direccion_archivo,string nombre_tabla,vector<string> campos){
        ifstream archivo(direccion_archivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo." << endl;
        }else{

            string linea;
            getline(archivo,linea);
            lista_de_campos = leer_cabecera(linea);
            const vector<int> n= numeros_de_campos(campos,lista_de_campos);

            for (const auto& campo : campos) {
                cout << textoCompletadoCon(campo,' ',15,"derecha") << " | ";
            }cout<<endl;

            string elemento;
            while (getline(archivo, linea)) { 
                const string elemento = filtrar_registro_por_numero(linea,n);
                cout << elemento;
                cout<<endl;
            }
        archivo.close();
        }
    }


};

int main() {
    

    SELECT n;
    //vector<string> campos = {"direccion","espacio_disponible","espacio_usado"};
    //n.SELECT_ALL("metadata2.txt","metadata2");
    n.SELECT_ALL("metadata2.txt","metadata2","metadata2#id#str#direccion#str#espacio_disponible#int#espacio_usado#int");
    //n.SELECT_ALL("metadata.txt","metadata","metadata#id#str#direccion#str#espacio_disponible#int#espacio_usado#int");

    return 0;
}
