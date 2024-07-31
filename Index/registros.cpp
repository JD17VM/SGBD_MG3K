#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdexcept>

#include <locale>
#include <string>
#include <windows.h>
#define CP_UTF8 65001 
#define CP_UTF32 12000 
#include <codecvt>
using namespace std;


#include "bplus.h"
BPTree<int> arbol(4);
string dir = "Bloque.txt";

struct Atributo {
    string nombre;
    string tipo;
    size_t longitud;
};

std::wstring utf8_to_ws(std::string const& utf8) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cnv;
    std::wstring s = cnv.from_bytes(utf8);
    if (cnv.converted() < utf8.size())
        throw std::runtime_error("incomplete conversion");
    return s;
}

// Función para leer el esquema desde un archivo
vector<Atributo> leerArchivoMetadata(const string& archivoEsquema) {
    vector<Atributo> esquema;
    ifstream inFile(archivoEsquema);
    if (!inFile) {
        throw runtime_error("No se pudo abrir el archivo de esquema.");
    }
    string linea;

    while (getline(inFile, linea)) {
        istringstream ss(linea);
        Atributo atributo;
        getline(ss, atributo.nombre, '#');
        getline(ss, atributo.tipo, '#');
        ss >> atributo.longitud;
        esquema.push_back(atributo);
    }

    return esquema;
}



bool esCaracterEspecial(wchar_t c) {
    // Lista de caracteres especiales en wide characters
    wstring caracteresEspeciales = L"¡¿áéíóúÁÉÍÓÚñÑ";
    return caracteresEspeciales.find(c) != wstring::npos;
}

string formatearRegistro(const vector<string>& registro, const vector<Atributo>& esquema) {
    ostringstream registroFormateado;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

    for (size_t i = 0; i < registro.size(); ++i) {
        const auto& atributo = esquema[i];
        string valor = registro[i];
        wstring wvalor = converter.from_bytes(valor);

        // Calcular la longitud adicional debido a caracteres especiales
        size_t longitudAdicional = 0;
        for (wchar_t wc : wvalor) {
            if (esCaracterEspecial(wc)) {
                longitudAdicional++;
            }
        }

        if (atributo.tipo == "int") {
            registroFormateado << setw(atributo.longitud + longitudAdicional) << right << valor;
        } else if (atributo.tipo == "char") {
            registroFormateado << setw(atributo.longitud + longitudAdicional) << left << valor;
        } else if (atributo.tipo == "float") {
            float valorFloat = stof(valor);
            registroFormateado << setw(atributo.longitud + longitudAdicional) << left << valorFloat;
        } else if (atributo.tipo == "bool") {
            registroFormateado << setw(atributo.longitud + longitudAdicional) << left << valor;
        } 
    }

    return registroFormateado.str();
}

// Función para dividir una línea en atributos usando una coma como delimitador
vector<string> dividir(const string& linea, char delimitador) {
    vector<string> atributos;
    string atributo;
    istringstream ss(linea);
    bool dentroDeComillas = false;

    char c;
    while (ss.get(c)) {
        if (c == '\"') {
            dentroDeComillas = !dentroDeComillas;
        } else if (c == delimitador && !dentroDeComillas) {
            atributos.push_back(atributo);
            atributo.clear();
        } else {
            if (dentroDeComillas && c == ',') {
                // Si está dentro de comillas y es una coma, la omitimos
                continue;
            }
            atributo += c;
        }
    }
    atributos.push_back(atributo); // Añadir el último atributo

    return atributos;
}

void convertir_registros_long_fija(string archivoEsquema, string archivoRegistros, string archivoSalida) {
    try {
        // Leer el esquema
        auto esquema = leerArchivoMetadata(archivoEsquema);

        // Leer los registros y convertirlos a formato de longitud fija
        ifstream inFile(archivoRegistros);
        if (!inFile) {
            throw runtime_error("No se pudo abrir el archivo de registros.");
        }
        vector<string> registros; // Almacenar registros en un vector
        string linea;

        while (getline(inFile, linea)) {
            auto a = utf8_to_ws(linea);
            string reg = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(a);
            registros.push_back(reg);
        }

        inFile.close(); // Cerrar el archivo de entrada

        ofstream outFile(archivoSalida); // Abrir el archivo para escribir
        if (!outFile) {
            throw runtime_error("No se pudo abrir el archivo de salida.");
        }

        for (const auto& registro : registros) {
            auto atributos = dividir(registro, ',');
            if (atributos.size() != esquema.size()) {
                //cout<<"======>"<<atributos.size() <<"  =========> "<<esquema.size()<<endl;
                throw runtime_error("Discrepancia entre el número de atributos en el archivo de esquema y en el registro.");
            }
            string registroFormateado = formatearRegistro(atributos, esquema);
            auto R = utf8_to_ws(registroFormateado);
            outFile << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(R) << "\n";
        }

        //cout << "Conversión completada en el archivo " << archivoSalida << endl;
    } catch (const exception& e) {
        cerr << "Nota: " << e.what() << endl;
    }
}



void agregarRegistro(string archivoEsquema,  string archivoRegistros, string registro, int columna) {
    try {
        auto esquema = leerArchivoMetadata(archivoEsquema);
        auto atributos = dividir(registro, ',');

        if (columna < atributos.size()) {
            
            cout << atributos[columna] << endl;
            try {
                int valor = std::stoi(atributos[columna]);
                cout << valor << endl;
                arbol.set(valor, valor, dir, 100);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
            } catch (const std::invalid_argument& e) {
                cerr << "Error: el valor en la columna " << columna << " no es un número entero." << endl;
            } catch (const std::out_of_range& e) {
                cerr << "Error: el valor en la columna " << columna << " está fuera del rango de los enteros." << endl;
            }
            
        }

        if (atributos.size() != esquema.size()) {
            cout<<atributos.size() <<"==========>"<<esquema.size();
            throw runtime_error("Discrepancia entre el número de atributos en el archivo de esquema y en el registro.");
        }

        string registroFormateado = formatearRegistro(atributos, esquema);


        ofstream outFile(archivoRegistros, ios::app); // Abrir el archivo para añadir

        if (!outFile) {
            throw runtime_error("No se pudo abrir el archivo de registros para añadir.");
        }

        outFile << registroFormateado << "\n";
        cout<<"Registro Agregado en "<<archivoRegistros<<endl;
    } catch (const exception& e) {
        cerr << "Nota: " << e.what() << endl;
    }
}
/*
void agregarRegistro(string archivoEsquema,  string archivoRegistros, string registro) {
    try {
        auto esquema = leerArchivoMetadata(archivoEsquema);
        auto atributos = dividir(registro, ',');

        if (atributos.size() != esquema.size()) {
            cout << atributos.size() << "==========>" << esquema.size();
            throw runtime_error("Discrepancia entre el número de atributos en el archivo de esquema y en el registro.");
        }

        string registroFormateado = formatearRegistro(atributos, esquema);

        ofstream outFile(archivoRegistros, ios::app);
        if (!outFile) {
            throw runtime_error("No se pudo abrir el archivo de registros para añadir.");
        }

        outFile << registroFormateado << "\n";
        cout << "Registro Agregado\n";
    } catch (const exception& e) {
        cerr << "Nota: " << e.what() << endl;
    }
}*/


int longitudDeRegistroFijo_leyendoMetadata(string archivo) {
    ifstream file(archivo); // Nombre del archivo con los datos
    string line;
    int tamTotal1Registro = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string field;

        // Vamos a leer hasta llegar a la tercera columna 
        for (int i = 0; i < 2; ++i) {
            getline(ss, field, '#'); // Descartamos las primeras dos columnas
        }

        // Ahora leemos la tercera columna 
        getline(ss, field, '#');
        int tamAtributo = stoi(field);
        tamTotal1Registro += tamAtributo;
    }

    return tamTotal1Registro;
}



void leyendoUnSoloRegistro(string archivo, int recordNumber) {
    // Desplazarse al inicio del registro deseado
    
    ifstream inFile(archivo);
    string linea;
    int cont =0;
    cout<<"|";
    while (getline(inFile, linea)) {
        
        if (cont==recordNumber)
        {
            cout << linea<< "|";
            break;
        }      
        cont++;  
    }

}

void imprimirPrimeraColumna(string archivoEsquema) {
    ifstream inFile(archivoEsquema);
    if (!inFile) {
        throw runtime_error("No se pudo abrir el archivo de esquema.");
    }

    string linea;
    cout << "ATRIBUTOS DE LA TABLA:\n";
    cout << "  |  ";
    while (getline(inFile, linea)) {
        istringstream ss(linea);
        string nombre;
        getline(ss, nombre, '#'); // Extraer la primera columna
        cout << nombre << "  |  ";
    }
}


void indexandoValores(string archivoRegistros, int columna) {
    ifstream inFile(archivoRegistros);
    string linea;

    while (getline(inFile, linea)) {
        auto atributos = dividir(linea, ',');
        if (columna < atributos.size()) {
            
            cout << atributos[columna] << endl;
            try {
                int valor = std::stoi(atributos[columna]);
                cout << valor << endl;
                arbol.set(valor, valor, dir, 100);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
            } catch (const std::invalid_argument& e) {
                cerr << "Error: el valor en la columna " << columna << " no es un número entero." << endl;
            } catch (const std::out_of_range& e) {
                cerr << "Error: el valor en la columna " << columna << " está fuera del rango de los enteros." << endl;
            }
            
        }
    }
}

void aR(const std::string& nombreArchivo, string nuevoRegistro) {
    

    // Abrir el archivo en modo de adición (append)
    std::ofstream archivo(nombreArchivo, std::ios::app);
    
    // Verificar si el archivo se abrió correctamente
    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    // Agregar el nuevo registro al archivo
    archivo << nuevoRegistro << std::endl;

    // Cerrar el archivo
    archivo.close();

    std::cout << "Registro añadido al archivo." << std::endl;
}


void eliminarArchivo(const std::string& nombreArchivo) {
    // Intentar eliminar el archivo
    if (std::remove(nombreArchivo.c_str()) != 0) {
        std::cerr << "Error al eliminar el archivo." << std::endl;
    } else {
        std::cout << "Archivo eliminado exitosamente." << std::endl;
    }
}


int main() {
    // Configurar la consola para UTF-8
    if (!SetConsoleOutputCP(CP_UTF8)) {
        cerr << "Error: no se pudo configurar la consola a UTF-8.\n";
        return 1;
    }

    string archivoEsquema = "metadataPOST.txt";
    string archivoRegistros = "registrosPOST.txt";
    string archivoSalida = "registrosFijosPOST.txt";

    // Convertir registros de un archivo a otro
    convertir_registros_long_fija(archivoEsquema, archivoRegistros, archivoSalida);

    // Calcular el tamaño de un solo registro fijo
    //cout << "Tamaño de 1 registro de longitud fija = " << longitudDeRegistroFijo_leyendoMetadata(archivoEsquema) << endl;

    // Imprimir registro en posición N
    int numRegistro;
    string file = "registrosFijosPOST.txt";
    cout << "Ingrese número de registro: ";
    cin >> numRegistro;
    cout<<"Imprimiendo Registro:\n";
    leyendoUnSoloRegistro(file, numRegistro);
    cout << "\n\n";


    


    
    // Añadir un solo registro
    /*
    cin.ignore(); // Limpiar el buffer de entrada
    string nuevoRegistro;
    imprimirPrimeraColumna(archivoEsquema);
    cout << "\n\nIngrese el nuevo registro (separado por comas):\n ";
    getline(cin, nuevoRegistro);
    
    agregarRegistro(archivoEsquema, archivoSalida, nuevoRegistro);*/

    


    int columna;
    cout << "Ingrese el número de columna para indexar ";
    cin >> columna;
    indexandoValores(archivoRegistros, columna);
    

    cin.ignore();
    string nuevoRegistro;
    cout << "\n\nIngrese el nuevo registro (separado por comas):\n ";
    getline(cin, nuevoRegistro);
    aR(archivoRegistros, nuevoRegistro);
    agregarRegistro(archivoEsquema, archivoSalida, nuevoRegistro,columna);
    
    
    



    arbol.imprimirArbol();
    arbol.guardarArbolEnArchivo("index.txt");

    /*
    eliminarArchivo("index.txt");
    arbol.guardarArbolEnArchivo("index.txt");
    indexandoValores(archivoRegistros, columna);
    */
    return 0;
}
