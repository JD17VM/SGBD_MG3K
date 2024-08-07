#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Estructura para representar una tupla en una relación
struct Registro{
    vector<string> valores;
};

// Estructura para representar una relación
struct Tabla{
    string nombre;
    vector<string> atributos;
    vector<Registro> registros;
};

//Recibe un texto y un caracter delimitador ("texto1#texto2#texto3", '#')
//Retorna un vector de strings divididos por un delimitador 
vector<string> split(const string &str, const char delimiter){
    vector<string> tokens;
    int start = 0;
    int end = 0;
    while (end < str.length()){
        if (str[end] == delimiter){
            tokens.push_back(str.substr(start, end - start));
            start = end + 1;
        }
        end++;
    }
    tokens.push_back(str.substr(start, end - start));
    return tokens;
}

//Recibe un texto que es el nombre del archivo txt "esquema.txt"
//Retorna el vector de todas las Tablas del esquema (Relacion) sólo con los nombres de las tablas y los nombres de columnas
vector<Tabla> leerEsquema(string archivoEsquema){
    vector<Tabla> relaciones;
    ifstream archivo("db/" + archivoEsquema);

    if (archivo.is_open()){
        string linea;
        while (getline(archivo, linea)){
            //cout << "Leyendo linea del esquema: " << linea << endl; // Impresión de depuración
            // Resto del código para leer el esquema...

            // Extraer información de la línea del esquema
            vector<string> partes = split(linea, '#');
            string nombreRelacion = partes[0];
            vector<string> atributosRelacion;
            vector<string> tiposAtributos;

            for (int i = 1; i < partes.size(); i += 2){
                atributosRelacion.push_back(partes[i]);
                tiposAtributos.push_back(partes[i + 1]);
            }

            // Crear una nueva relación y agregarla al vector
            Tabla relacion;
            relacion.nombre = nombreRelacion;
            relacion.atributos = atributosRelacion;
            relaciones.push_back(relacion);
        }

        archivo.close();
    }
    else{
        cerr << "Error al abrir el archivo de esquema: " << archivoEsquema << endl;
    }

    return relaciones;
}

//Recibe una Tabla (Relacion) y con su nombre y atributos (nombres de columnas) y el nombre del archivo txt de los registros
//Llena la Tabla (Relacion) con los registros correspondientes de el mismo archivo
void leerDatosRelacion(Tabla &relacion, string archivoDatos){
    ifstream archivo("db/"+ archivoDatos);

    if (archivo.is_open()){
        string linea;
        while (getline(archivo, linea)){
            //cout << "Leyendo linea de datos: " << linea << endl;

            // Extraer valores de la línea de datos
            vector<string> valores = split(linea, '#');

            // Crear una nueva tupla y agregarla a la relación
            Registro registro;
            for (int i = 0; i < valores.size(); i++){
                registro.valores.push_back(valores[i]);
            }

            relacion.registros.push_back(registro);
        }

        archivo.close();
    }
    else{
        cerr << "Error al abrir el archivo de datos: " << archivoDatos << endl;
    }
}

//Recibe una Tabla completa (relacion) con sus registros
//Función para mostrar una relación en la consola
void mostrarRelacion(const Tabla &relacion){
    cout << "Relacion: " << relacion.nombre << endl;
    cout << "|";

    for (int i = 0; i < relacion.atributos.size(); i++){
        cout << " " << relacion.atributos[i] << " |";
    }

    cout << endl;

    for (const Registro &registro : relacion.registros){
        cout << "|";

        for (const string &valor : registro.valores){
            cout << " " << valor << " |";
        }

        cout << endl;
    }
}


int buscarPosicionTablaPorNombre(vector<Tabla> &relaciones,string nombre_tabla){
    for (int i = 0; i < relaciones.size(); i++){
        if (relaciones[i].nombre == nombre_tabla){
            return i;
        }
    }
    return -1;
}


void SELECT_ALL_FROM(vector<Tabla> &relaciones,string nombre_tabla){
    Tabla &relacion_encontrada = relaciones[buscarPosicionTablaPorNombre(relaciones,nombre_tabla)];
    string archivoDatos = relacion_encontrada.nombre + ".txt";
    leerDatosRelacion(relacion_encontrada, archivoDatos);
    mostrarRelacion(relacion_encontrada);
}

int main(){

    vector<Tabla> relaciones = leerEsquema("esquema.txt");
    SELECT_ALL_FROM(relaciones, "depts");
    SELECT_ALL_FROM(relaciones, "estudiantes");

    return 0;
}
