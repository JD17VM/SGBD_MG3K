#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


string crearEsquema(vector<string> &fila, string nombre_archivo){
    string texto = "";
    texto += nombre_archivo + "#";
        for (int i=0;i<fila.size();i++){
            texto += fila[i];
            if(!(i==(fila.size()-1))){
                texto += "#";
            }
        }
        return texto;
}

int main() {
    // Abre el archivo CSV
    ifstream archivo("datos.csv");

    // Verifica si se pudo abrir el archivo
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    // Define un vector para almacenar los datos
    vector<vector<string>> datos;

    // Lee el archivo línea por línea
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        vector<string> fila;
        string campo;

        // Divide la línea en campos usando la coma como delimitador
        while (getline(ss, campo, ',')) {
            fila.push_back(campo);
        }

        // Agrega la fila al vector de datos
        datos.push_back(fila);
    }

    // Cierra el archivo
    archivo.close();


    const vector<string> fila = datos[0];
    //for (const string& campo : fila) {
    //        cout << campo << "#";
    //}


    

    cout<<crearEsquema(datos[0],"titanic");
    // Imprime los datos
    //for (const auto& fila : datos) {
    //    for (const auto& campo : fila) {
    //        cout << campo << " ";
    //    }
    //    cout << endl;
    //}

    return 0;
}
