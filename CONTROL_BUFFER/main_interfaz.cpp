#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <conio.h> // Para getch() en Windows
#include "bplusFinal.h"


#include "Buffer_Manager.h"
#include "Busqueda_Registro.h"

using namespace std;

void limpiarPantalla() {
    system("cls");
}

void esperarTecla() {
    getch();
}

void mostrarMenuInicial(){
    cout << "== MENU INICIAL ==" << endl;
    cout << "1. Llamar a Bloque" << endl;
    cout << "2. Flush Frame" << endl;
    cout << "3. Unpin Frame" << endl;
    cout << "4. Busqueda por PostID" << endl;
    cout << "5. Insertar nuevo registro" << endl;
    cout << "6. Eliminar registro" << endl;
    cout << "7. Buscar por rango" << endl;
    cout << "0. Salir" << endl;
    cout << "==================" << endl;
}

void mostrarMenuFlush() {
    cout << "== FLUSH FRAMES ==" << endl;
    cout << "1. Frame_1" << endl;
    cout << "2. Frame_2" << endl;
    cout << "3. Frame_3" << endl;
    cout << "4. Frame_4" << endl;
    cout << "5. Frame_5" << endl;
    cout << "0. Salir" << endl;
    cout << "==================" << endl;
}

void mostrarMenuUnpin() {
    cout << "== UNPIN FRAMES ==" << endl;
    cout << "1. Frame_1" << endl;
    cout << "2. Frame_2" << endl;
    cout << "3. Frame_3" << endl;
    cout << "4. Frame_4" << endl;
    cout << "5. Frame_5" << endl;
    cout << "0. Salir" << endl;
    cout << "==================" << endl;
}


void mostrarMenuLW(){
    cout << "== LECTURA O ESCRITURA ==" << endl;
    cout << "L. Lectura" << endl;
    cout << "W. Escritura" << endl;
    cout << "0. Salir" << endl;
    cout << "=========================" << endl;
}

void mostrarMenuBloques() {
    cout << "======== BLOQUE ========" << endl;
    cout << "1. Bloque_1" << endl;
    cout << "2. Bloque_2" << endl;
    cout << "3. Bloque_3" << endl;
    cout << "4. Bloque_4" << endl;
    cout << "5. Bloque_5" << endl;
    cout << "6. Bloque_6" << endl;
    cout << "0. Salir" << endl;
    cout << "========================" << endl;
}


void appendToFile(const string& filename, const string& text) {
    // Abrir el archivo en modo append
    ofstream file;
    file.open(filename, ios::app);

    if (file.is_open()) {
        file << text << endl; // Añadir el texto al final del archivo
        file.close(); // Cerrar el archivo después de escribir
        cout << "Texto añadido correctamente." << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
    }
}

// Función para eliminar registros según la columna y el valor
void removeLine(const string &filePath, int lineNum) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string tempFilePath = filePath + ".tmp";
    ofstream tempFile(tempFilePath);
    if (!tempFile.is_open()) {
        cerr << "Error al crear el archivo temporal." << endl;
        return;
    }

    string line;
    int currentLineNum = 1; // Contador de líneas
    
    // Leer el archivo original y escribir en el archivo temporal
    while (getline(file, line)) {
        if (currentLineNum != lineNum) {
            // Escribir la línea en el archivo temporal si no es la línea a eliminar
            tempFile << line << endl;
        }
        currentLineNum++;
    }

    file.close();
    tempFile.close();

    // Remplazar el archivo original con el archivo temporal
    if (remove(filePath.c_str()) != 0) {
        cerr << "Error al eliminar el archivo original." << endl;
    } else if (rename(tempFilePath.c_str(), filePath.c_str()) != 0) {
        cerr << "Error al renombrar el archivo temporal." << endl;
    }
}

vector<vector<string>> searchAndPrintRecordsRango(const string &filePath, const string &key, const string &inicioRango, const string &finRango) {
    ifstream file(filePath);
    vector<vector<string>> resultados;
    string linea;

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << filePath << endl;
        return resultados;
    }

    while (getline(file, linea)) {
        vector<string> elementos = split(linea, ','); // Asumiendo que los elementos están separados por comas

        if (elementos.size() > 0 && elementos[0] >= inicioRango && elementos[0] <= finRango) {
            resultados.push_back(elementos);
        }
    }

    file.close();
    return resultados;
}

vector<vector<string>> searchAndPrintRecordsRango2(const string &filePath, const string &key, const string &inicioRango, const string &finRango) {
    ifstream file(filePath);
    vector<vector<string>> resultados;
    string linea;
    
    int inicio = stoi(inicioRango);
    int fin = stoi(finRango);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << filePath << endl;
        return resultados;
    }

    while (getline(file, linea)) {
        vector<string> elementos = split(linea, ','); // Asumiendo que los elementos están separados por comas

        if (elementos.size() > 0) {
            int postId = stoi(elementos[0]);
            if (postId >= inicio && postId <= fin) {
                resultados.push_back(elementos);
            }
        }
    }

    file.close();
    return resultados;
}


int main(){
    Buffer_Manager p(5);
    bool salir = false;

    while(!salir) {
        limpiarPantalla();
        p.imprimirEstado();
        mostrarMenuInicial();

        int opcionInicial;
        cout << "Selecciona una opcion: ";
        cin >> opcionInicial;

        switch(opcionInicial) {
            case 1: {
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();
                    mostrarMenuLW();

                    char opcionLW;
                    cout << "Lectura o escritura: ";
                    cin >> opcionLW;

                    limpiarPantalla();
                    p.imprimirEstado();
                    mostrarMenuBloques();

                    cout<<"La letra que se envia es: "<<opcionLW<<endl;
                    int opcionBloque;
                    cout << "Selecciona un bloque: ";
                    cin >> opcionBloque;

                    if (opcionBloque == 0) {
                        subMenuSalir = true;
                        continue;
                    }

                    
                    string direccionBloque;
                    switch(opcionBloque) {
                        case 1: direccionBloque = "Bloques/BLOQUE_01.txt"; break;
                        case 2: direccionBloque = "Bloques/BLOQUE_02.txt"; break;
                        case 3: direccionBloque = "Bloques/BLOQUE_03.txt"; break;
                        case 4: direccionBloque = "Bloques/BLOQUE_04.txt"; break;
                        case 5: direccionBloque = "Bloques/BLOQUE_05.txt"; break;
                        case 6: direccionBloque = "Bloques/BLOQUE_06.txt"; break;
                        default: cout << "Opcion invalida. Intenta de nuevo." << endl; esperarTecla(); continue;
                    }

                    limpiarPantalla();
                    p.llamarABloque(direccionBloque, opcionLW);
                    //p.imprimirEstado();
                    //esperarTecla();
                }
                break;
            }
            case 2: {
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();
                    mostrarMenuFlush();

                    int opcionFlush;
                    cout << "Selecciona un frame para hacer flush: ";
                    cin >> opcionFlush;

                    if (opcionFlush == 0) {
                        subMenuSalir = true;
                        continue;
                    }

                    if (opcionFlush >= 1 && opcionFlush <= 4) {
                        p.flushFrame(opcionFlush - 1);
                        cout << "Flush realizado en Frame_" << opcionFlush << "." << endl;
                    } else {
                        cout << "Opcion inválida. Intenta de nuevo." << endl;
                    }
                    esperarTecla();
                }
                break;
            }

            case 3:{
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();
                    mostrarMenuUnpin();

                    int opcionUnpin;
                    cout << "Selecciona un frame para hacer despinnear: ";
                    cin >> opcionUnpin;

                    if (opcionUnpin == 0) {
                        subMenuSalir = true;
                        continue;
                    }

                    if (opcionUnpin >= 1 && opcionUnpin <= 4) {
                        p.unPinFrame(opcionUnpin - 1);
                        cout << "Unpin realizado en Frame_" << opcionUnpin << "." << endl;
                    } else {
                        cout << "Opcion inválida. Intenta de nuevo." << endl;
                    }
                    esperarTecla();
                }
                break;
            }

            case 4:{
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();

                    string opcionLW;
                    cout << "Escribrir PostID: ";
                    cin >> opcionLW;

                    if (opcionLW == "x") {
                        subMenuSalir = true;
                        continue;
                    }


                    limpiarPantalla();
                    p.imprimirEstado();

                    vector<vector<string>> resultados = searchAndPrintRecords("Bloques/BLOQUE_08.txt","Postid",opcionLW);

                    for (const auto &linea : resultados) {
                        if (linea.size() >= 3) { // Verificar que hay suficientes elementos
                            /*cout << "Se llamara al bloque: " << linea[1] << endl;
                            cout << "En la linea: " << linea[2] << endl << endl;*/
                            p.llamarABloque("Bloques/"+linea[1], 'L');
                            mostrarRegistro("Bloques/"+linea[1],stoi(linea[2]));
                        } else {
                            cerr << "Error: Registro incompleto" << endl;
                        }
                    }
                    
                    esperarTecla();
                    limpiarPantalla();
                    mostrarMenuBloques();
                }
                break;
            }


            case 5:{
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();

                    string opcionLW;
                    cout << "Escribrir Registro: "; //38,13419,31072025,Este es un nuevo tema de discusi�n n�mero 38.,1
                    cin >> opcionLW;


                    if (opcionLW == "x") {
                        subMenuSalir = true;
                        continue;
                    }

                    limpiarPantalla();
                    p.imprimirEstado();

                    
                    p.llamarABloque("Bloques/BLOQUE_06.txt", 'W');
                    int posicion = p.posicionFramePorDireccionBloque("Bloques/BLOQUE_06.txt");
                    string direccion_frame = p.Buffer_Pool[posicion].direccion_frame;
                    appendToFile(direccion_frame,opcionLW);
                    appendToFile("updated_posts.csv",opcionLW);
                    BPTree<int> tree(4);
                    cargarCSVenBTree("updated_posts.csv","Postid",tree);
                    guardarArbolEnDOT(tree, "arbol.txt");
                    
                    esperarTecla();
                    limpiarPantalla();
                    mostrarMenuBloques();
                }
                break;
            }

            case 6:{
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();

                    string opcionLW;
                    cout << "Post Id de registro a eliminar: "; //38,13419,31072025,Este es un nuevo tema de discusi�n n�mero 38.,1
                    cin >> opcionLW;


                    if (opcionLW == "x") {
                        subMenuSalir = true;
                        continue;
                    }

                    limpiarPantalla();
                    p.imprimirEstado();


                    vector<vector<string>> resultados = searchAndPrintRecords("Bloques/BLOQUE_08.txt","Postid",opcionLW);

                    for (const auto &linea : resultados) {
                        if (linea.size() >= 3) { // Verificar que hay suficientes elementos
                            /*cout << "Se llamara al bloque: " << linea[1] << endl;
                            cout << "En la linea: " << linea[2] << endl << endl;*/
                            string dir_bloque = "Bloques/"+linea[1];
                            p.llamarABloque(dir_bloque, 'W');
                            mostrarRegistro(dir_bloque,stoi(linea[2]));
                            int posicion = p.posicionFramePorDireccionBloque(dir_bloque);
                            string direccion_frame = p.Buffer_Pool[posicion].direccion_frame;
                            removeLine(direccion_frame,stoi(linea[2]));
                        } else {
                            cerr << "Error: Registro incompleto" << endl;
                        }
                    }

                    esperarTecla();
                    limpiarPantalla();
                    mostrarMenuBloques();
                }
                break;
            }

            case 7: {
                bool subMenuSalir = false;
                while(!subMenuSalir) {
                    limpiarPantalla();
                    p.imprimirEstado();

                    string inicioRango, finRango;
                    cout << "Escribrir PostID de inicio: ";
                    cin >> inicioRango;
                    
                    cout << "Escribrir PostID de fin: ";
                    cin >> finRango;

                    if (inicioRango == "x" || finRango == "x") {
                        subMenuSalir = true;
                        continue;
                    }

                    limpiarPantalla();
                    p.imprimirEstado();

                    // Supongamos que searchAndPrintRecords puede aceptar un rango
                    vector<vector<string>> resultados = searchAndPrintRecordsRango("Bloques/BLOQUE_08.txt", "Postid", inicioRango, finRango);

                    for (const auto &linea : resultados) {
                        if (linea.size() >= 3) { // Verificar que hay suficientes elementos
                            /*cout << "Se llamara al bloque: " << linea[1] << endl;
                            cout << "En la linea: " << linea[2] << endl << endl;*/
                            p.llamarABloque("Bloques/"+linea[1], 'L');
                            mostrarRegistro("Bloques/"+linea[1], stoi(linea[2]));
                        } else {
                            cerr << "Error: Registro incompleto" << endl;
                        }
                    }

                    esperarTecla();
                    limpiarPantalla();
                    mostrarMenuBloques();
                }
                break;
            }
  

            case 0:
                salir = true;
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo." << endl;
                esperarTecla();
                break;
        }
    }

    return 0;
}
