#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip> // Para std::setw
#include <string>


using namespace std;

string completarStringConCeros(int numero, int longitud){
    string texto = to_string(numero);
    if(longitud > texto.length()){
        texto = string(longitud - texto.length(), '0') + texto;
    }

    return texto;
}

void crear_carpetas_enumeradas_secuencialmente(string directorio,string nombre_inicial, int cantidad){
    string direccion = "";
    for(int i = 1; i <= cantidad; i++){
        direccion = directorio + nombre_inicial + completarStringConCeros(i,2);
        if (CreateDirectory(direccion.c_str(), NULL) != 0) {
            cout << "Carpeta " + direccion + " creada correctamente.\n";
        } else {
            cerr << "Error al crear la carpeta.\n";
        }
        cout<<endl;
    }
}


void crear_carpetas_enumeradas_secuencialmente_s(string directorio,string nombre_inicial_platos, int cantidad_platos, int cantidad_pistas, int cantidad_bloques){
    string direccion = "";
    for(int i = 1; i <= cantidad_platos; i++){
        direccion = directorio + nombre_inicial_platos + completarStringConCeros(i,2);
        if (CreateDirectory(direccion.c_str(), NULL) != 0) {
            cout << "Carpeta " + direccion + " creada correctamente.\n";
            string direccion_cara_A = direccion + "/" + "CARA_A";
            string direccion_cara_B = direccion + "/" + "CARA_B";
            CreateDirectory(direccion_cara_A.c_str(), NULL);
            CreateDirectory(direccion_cara_B.c_str(), NULL);
            for(int j = 1; j <= cantidad_pistas; j++){
                string direccion_platos_base_A = direccion_cara_A + "/" + "PISTA_" + completarStringConCeros(j,2);
                string direccion_platos_base_B = direccion_cara_B + "/" + "PISTA_" + completarStringConCeros(j,2);
                CreateDirectory(direccion_platos_base_A.c_str(), NULL);
                CreateDirectory(direccion_platos_base_B.c_str(), NULL);
                for(int k = 1; k <= cantidad_bloques; k++){
                    string nombre_bloque_txt_direccion_A = direccion_platos_base_A + "/" + "BLOQUE_" + completarStringConCeros(k,2) + ".txt";
                    string nombre_bloque_txt_direccion_B = direccion_platos_base_B + "/" + "BLOQUE_" + completarStringConCeros(k,2) + ".txt";
                    ofstream archivo_A(nombre_bloque_txt_direccion_A.c_str()); 
                    ofstream archivo_B(nombre_bloque_txt_direccion_A.c_str()); 

                }
            }
            


        } else {
            cerr << "Error al crear la carpeta.\n";
        }
        cout<<endl;
    }
}



int main() {
    crear_carpetas_enumeradas_secuencialmente_s("HDD/","PLATOS_",4,5,3);
    

    return 0;
}
