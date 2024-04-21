#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Estructura para representar una tupla en una relación
struct Tupla
{
    vector<string> valores;
};

// Estructura para representar una relación
struct Relacion
{
    string nombre;
    vector<string> atributos;
    vector<Tupla> tuplas;
};

vector<string> split(const string &str, const char delimiter)
{
    vector<string> tokens;
    int start = 0;
    int end = 0;
    while (end < str.length())
    {
        if (str[end] == delimiter)
        {
            tokens.push_back(str.substr(start, end - start));
            start = end + 1;
        }
        end++;
    }
    tokens.push_back(str.substr(start, end - start));
    return tokens;
}

// Función para leer el esquema de la base de datos desde un archivo
vector<Relacion> leerEsquema(string archivoEsquema)
{
    vector<Relacion> relaciones;
    ifstream archivo(archivoEsquema);

    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            cout << "Leyendo línea del esquema: " << linea << endl; // Impresión de depuración
            // Resto del código para leer el esquema...

            // Extraer información de la línea del esquema
            vector<string> partes = split(linea, '#');
            string nombreRelacion = partes[0];
            vector<string> atributosRelacion;
            vector<string> tiposAtributos;

            for (int i = 1; i < partes.size(); i += 2)
            {
                atributosRelacion.push_back(partes[i]);
                tiposAtributos.push_back(partes[i + 1]);
            }

            // Crear una nueva relación y agregarla al vector
            Relacion relacion;
            relacion.nombre = nombreRelacion;
            relacion.atributos = atributosRelacion;
            relaciones.push_back(relacion);
        }

        archivo.close();
    }
    else
    {
        cerr << "Error al abrir el archivo de esquema: " << archivoEsquema << endl;
    }

    return relaciones;
}

// Función para leer los datos de una relación desde un archivo
void leerDatosRelacion(Relacion &relacion, string archivoDatos)
{
    ifstream archivo(archivoDatos);

    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            cout << "Leyendo línea de datos: " << linea << endl;

            // Extraer valores de la línea de datos
            vector<string> valores = split(linea, '#');

            // Crear una nueva tupla y agregarla a la relación
            Tupla tupla;
            for (int i = 0; i < valores.size(); i++)
            {
                tupla.valores.push_back(valores[i]);
            }

            relacion.tuplas.push_back(tupla);
        }

        archivo.close();
    }
    else
    {
        cerr << "Error al abrir el archivo de datos: " << archivoDatos << endl;
    }
}


// Función para mostrar una relación en la consola
void mostrarRelacion(const Relacion &relacion)
{
    cout << "Relación: " << relacion.nombre << endl;
    cout << "|";

    for (int i = 0; i < relacion.atributos.size(); i++)
    {
        cout << " " << relacion.atributos[i] << " |";
    }

    cout << endl;

    for (const Tupla &tupla : relacion.tuplas)
    {
        cout << "|";

        for (const string &valor : tupla.valores)
        {
            cout << " " << valor << " |";
        }

        cout << endl;
    }
}

int main()
{
    // Leer el esquema de la base de datos
    vector<Relacion> relaciones = leerEsquema("esquema.txt");

    // Leer los datos de las relaciones
    for (Relacion &relacion : relaciones)
    {
        string archivoDatos = relacion.nombre + ".txt"; // Modificación en la ruta del archivo de datos
        cout << "Ruta del archivo de datos: " << archivoDatos << endl; // Impresión de depuración
        leerDatosRelacion(relacion, archivoDatos);
    }

    // Mostrar las relaciones en la consola
    for (const Relacion &relacion : relaciones)
    {
        mostrarRelacion(relacion);
    }

    return 0;
}
