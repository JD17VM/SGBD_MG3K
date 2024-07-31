#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Estructura para almacenar los datos
struct Registro {
    int numero;
    std::vector<std::pair<std::string, int>> archivos_lineas; // Par de archivo y línea
};

// Función para cargar datos desde el archivo de registros
std::vector<Registro> cargarDatos(const std::string &nombreArchivo) {
    std::vector<Registro> datos;
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string parteNumero;
        std::getline(ss, parteNumero, ' ');
        int numero = std::stoi(parteNumero);

        std::vector<std::pair<std::string, int>> archivos_lineas;
        std::string segmento;
        while (std::getline(ss, segmento, '|')) {
            std::stringstream ss_segmento(segmento);
            std::string parteArchivo, parteLinea;
            std::getline(ss_segmento, parteArchivo, ',');
            std::getline(ss_segmento, parteLinea);

            archivos_lineas.push_back({parteArchivo, std::stoi(parteLinea)});
        }

        datos.push_back({numero, archivos_lineas});
    }

    archivo.close();
    return datos;
}

// Función de búsqueda binaria
int busquedaBinaria(const std::vector<Registro> &datos, int objetivo) {
    int izquierda = 0, derecha = datos.size() - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (datos[medio].numero == objetivo) {
            return medio;
        } else if (datos[medio].numero < objetivo) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return -1; // No encontrado
}

// Función para leer una línea específica de un archivo
std::string leerLineaArchivo(const std::string &nombreArchivo, int numeroLinea) {
    std::ifstream archivo(nombreArchivo);
    std::string linea;
    int contador = 0;

    while (std::getline(archivo, linea)) {
        if (contador == numeroLinea) {
            return linea;
        }
        contador++;
    }

    return ""; // Línea no encontrada
}

int main() {
    std::string nombreArchivo = "index.txt";
    std::vector<Registro> datos = cargarDatos(nombreArchivo);

    // Ordenar los datos para la búsqueda binaria (asegurar que estén ordenados)
    std::sort(datos.begin(), datos.end(), [](const Registro &a, const Registro &b) {
        return a.numero < b.numero;
    });

    int objetivo = 10150; // Cambia esto al número que quieres buscar
    int resultado = busquedaBinaria(datos, objetivo);

    if (resultado != -1) {
        Registro registro = datos[resultado];
        std::cout << "Encontrado: " << registro.numero << std::endl;
        for (const auto &archivo_linea : registro.archivos_lineas) {
            std::string lineaArchivo = leerLineaArchivo(archivo_linea.first, archivo_linea.second);
            std::cout << "Archivo: " << archivo_linea.first << " | Registro: " << archivo_linea.second << std::endl;
            std::cout << "Contenido de la linea: " << lineaArchivo << std::endl;
        }
    } else {
        std::cout << "No encontrado" << std::endl;
    }

    return 0;
}
