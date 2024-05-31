#include "Bloque.h"

using namespace std;

struct Frame{
    shared_ptr<Bloque> bloque;

    string direccion_frame;
    int pin_count;
    bool dirty;
    int lastUsedCount;

    Frame(string direccion_frame){
        this->direccion_frame = direccion_frame;
        this->pin_count = 0;
        this->dirty = false;
        this->bloque = nullptr;
        this->lastUsedCount = 0;
    }

    void setDirty(bool dirty){
        this->dirty = dirty;
    }

    void pinPage(){
        this->pin_count++;
    }

    void unPinPage(){
        if(this->pin_count){
            this->pin_count--;
        }
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
            //copiar texto de Frame sobre Bloque
        }
    }

    void resetearFrame(){
        this->pin_count = 0;
        this->dirty = false;
        this->bloque = nullptr;
        this->lastUsedCount = 0;
    }

};


