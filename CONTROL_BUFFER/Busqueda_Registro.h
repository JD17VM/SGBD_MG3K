#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../megatron.h"


using namespace std;


// Función para buscar y devolver registros por una columna y valor específico
vector<vector<string>> searchAndPrintRecords(const string &filePath, const string &column, const string &value) {
    ifstream file(filePath);
    string line;
    vector<vector<string>> registro;

    // Verificar si el archivo se abrió correctamente
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return registro; // Retornar un vector vacío en caso de error
    }

    // Leer la primera línea (encabezados)
    getline(file, line);
    stringstream ss(line);
    string token;
    vector<string> headers;
    int columnIndex = -1;
    int currentIndex = 0;

    // Determinar el índice de la columna para buscar
    while (getline(ss, token, ',')) {
        headers.push_back(token);
        if (token == column) {
            columnIndex = currentIndex;
        }
        currentIndex++;
    }

    if (columnIndex == -1) {
        cerr << "Columna no encontrada: " << column << endl;
        return registro; // Retornar un vector vacío en caso de error
    }

    // Leer y buscar en cada línea del archivo
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        currentIndex = 0;

        while (getline(ss, token, ',')) {
            row.push_back(token);
            currentIndex++;
        }

        // Comparar el valor en la columna especificada
        if (row.size() > columnIndex && row[columnIndex] == value) {
            registro.push_back(split(line, ','));
            //cout << line << endl; // Imprimir la línea completa si hay coincidencia
        }
    }

    return registro;
}

vector<string> mostrarRegistro(const string &filePath, int lineNum) {
    ifstream file(filePath);
    string line;
    vector<string> registro;

    // Verificar si el archivo se abrió correctamente
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return registro; // Retornar un vector vacío en caso de error
    }

    // Leer el archivo línea por línea hasta encontrar la línea deseada
    int currentLineNum = 1; // Contador de líneas
    while (getline(file, line)) {
        if (currentLineNum == lineNum) {
            registro = split(line, ',');
            cout << line << endl; // Imprimir la línea completa
            return registro;
        }
        currentLineNum++;
    }

    cerr << "Línea no encontrada: " << lineNum << endl;
    return registro; // Retornar un vector vacío si la línea no se encuentra
}


void llamar_registro_bloques(const vector<vector<string>> &matriz_indices) {
    for (const auto &linea : matriz_indices) {
        if (linea.size() >= 3) { // Verificar que hay suficientes elementos
            cout << "Se llamara al bloque: " << linea[1] << endl;
            cout << "En la linea: " << linea[2] << endl << endl;
        } else {
            cerr << "Error: Registro incompleto" << endl;
        }
    }
}
/*
int main() {
    string filePath = "Bloques/BLOQUE_08.txt"; // Reemplaza con la ruta real al archivo
    string column, value;

    cout << "Ingrese la columna para buscar: ";
    cin >> column;
    cout << "Ingrese el valor para buscar: ";
    cin >> value;

    cout << "Registros encontrados:" << endl;
    vector<vector<string>> resultados = searchAndPrintRecords(filePath, column, value);
    llamar_registro_bloques(resultados);

    return 0;
}
*/
