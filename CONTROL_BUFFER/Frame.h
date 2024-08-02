#include "Bloque.h"

using namespace std;

struct Frame{
    shared_ptr<Bloque> bloque;

    string direccion_frame;
    int pin_count;
    bool dirty;
    int lastUsedCount;

    bool bit_de_uso_CLOCK;

    char estado_requerimiento_actual;
    vector<char> cola_de_requerimientos;

    Frame(string direccion_frame){
        this->direccion_frame = direccion_frame;
        this->pin_count = 0;
        this->dirty = false;
        this->bloque = nullptr;
        this->lastUsedCount = 0;
        this->bit_de_uso_CLOCK = false;
    }

    void setDirty(bool dirty){
        this->dirty = dirty;
    }

    void actualizarEstadoRequerimientoActual(){
        if(this->cola_de_requerimientos.size() > 0){
            this->estado_requerimiento_actual = this->cola_de_requerimientos[0];
            int contador_pin = 0;
            for(char solicitud: this->cola_de_requerimientos){
                if(solicitud == 'L'){
                    contador_pin++;
                }else{
                    break;
                }
            }
            pin_count = contador_pin;
        }
    }

    void llamarRequerimiento(char indicadorLW){
        this->cola_de_requerimientos.push_back(indicadorLW);

        if(this->cola_de_requerimientos[0] == 'W'){
            setDirty(true);
        }else if(this->cola_de_requerimientos[0] == 'L'){
            setDirty(false);
        }

        establecerPinCountEnBaseARequerimientos();
    }

    void liberarRequerimiento(){
        if(this->cola_de_requerimientos[0]){
            this->cola_de_requerimientos.erase(cola_de_requerimientos.begin());

            if(this->cola_de_requerimientos[0] == 'W'){
                setDirty(true);
            }else if(this->cola_de_requerimientos[0] == 'L'){
                setDirty(false);
            }
        }
        else{
            this->pin_count = 0;
        }

        establecerPinCountEnBaseARequerimientos();
    }

    void establecerPinCountEnBaseARequerimientos(){
        if(this->cola_de_requerimientos[0]){
            if(this->cola_de_requerimientos[0] == 'L'){
            int contador_requerimientos_lectura = 0;
            for(char requerimiento : this->cola_de_requerimientos){
                if (requerimiento == 'L') contador_requerimientos_lectura++;
                else break;
            }
            this->pin_count = contador_requerimientos_lectura;
            }else if(this->cola_de_requerimientos[0] == 'W'){
                this->pin_count = 1;
            } 
        }else{
            this->pin_count = 0;
        }

    }

    /*void pinPage(){
        this->pin_count++;
    }

    void unPinPage(){
        if(this->pin_count){
            this->pin_count--;
        }
    }*/


    void reemplazarContenidoDeArchivoTXTEnOtro(const string& sourceFileName, const string& destinationFileName) {
        // Nombre temporal para la copia del archivo
        string tempFileName = "temp.txt";

        // Copiar el contenido de sourceFileName a tempFileName
        ifstream sourceFile(sourceFileName, ios::binary);
        ofstream tempFile(tempFileName, ios::binary);
        if (!sourceFile) {
            cerr << "No se pudo abrir el archivo de entrada: " << sourceFileName << endl;
            return;
        }
        if (!tempFile) {
            cerr << "No se pudo crear el archivo temporal: " << tempFileName << endl;
            return;
        }
        tempFile << sourceFile.rdbuf();
        sourceFile.close();
        tempFile.close();

        // Eliminar el archivo destino original
        if (remove(destinationFileName.c_str()) != 0) {
            cerr << "Error al eliminar el archivo: " << destinationFileName << endl;
            return;
        }

        // Renombrar el archivo temporal al nombre del archivo destino
        if (rename(tempFileName.c_str(), destinationFileName.c_str()) != 0) {
            cerr << "Error al renombrar el archivo: " << tempFileName << " a " << destinationFileName << endl;
            return;
        }

        cout << "El contenido del archivo " << sourceFileName << " ha reemplazado a " << destinationFileName << endl;
    }

    void setBloque(shared_ptr<Bloque> bloque){
        this->bloque = bloque;
        cout<<"Frame: "<<this->direccion_frame<<endl;
        cout<<"Bloque: "<<this->bloque->direccion_bloque<<endl<<endl;
        ifstream archivo_origen(this->bloque->direccion_bloque); 
        ofstream archivo_destino(this->direccion_frame);

        if (!archivo_origen || !archivo_destino) { 
            cerr << "Error al abrir los archivos." << endl;
        }

        string linea;

        while (getline(archivo_origen, linea)) { 
            archivo_destino << linea << endl;
        }

        archivo_origen.close();
        archivo_destino.close();
    }

    void setLastUsedCount(int n){
        this->lastUsedCount = n;
    }
    


    void flushing(){
        if(this->dirty){
            setDirty(false);
            reemplazarContenidoDeArchivoTXTEnOtro(this->direccion_frame,this->bloque->direccion_bloque);
        }
    }

    void resetearFrame(){
        this->pin_count = 0;
        this->dirty = false;
        this->bloque = nullptr;
        this->lastUsedCount = 0;
    }


    void setbitDeUsoCLOCK(bool n){
        this->bit_de_uso_CLOCK = n;
    }



    void imprimirColaDeRequerimientos() const {
        if (this->cola_de_requerimientos.size() > 0) {
            if (this->cola_de_requerimientos[0] == 'L') {
                int indice_de_vector = -1;
                cout << "En ejecucion: ";
                for (int i = 0; i < this->cola_de_requerimientos.size(); i++) {
                    if (this->cola_de_requerimientos[i] == 'L') {
                        if (i > 0) cout << " - ";
                        cout << this->cola_de_requerimientos[i];
                    } else {
                        indice_de_vector = i;
                        break;
                    }
                }
                cout << ", En cola: ";
                for (int j = indice_de_vector; j < this->cola_de_requerimientos.size(); j++) {
                    if (j > indice_de_vector) cout << " - ";
                    cout << this->cola_de_requerimientos[j];
                }
            } else if (this->cola_de_requerimientos[0] == 'W') {
                cout << "En ejecucion: " << this->cola_de_requerimientos[0];
                cout << ", En cola: ";
                for (int i = 1; i < this->cola_de_requerimientos.size(); i++) {
                    if (i > 1) cout << " - ";
                    cout << this->cola_de_requerimientos[i];
                }
            }
        }
    }

};


