#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Bloque.h"

using namespace std;

struct Frame{
    Bloque* bloque;

    string direccion_frame;
    int pin_count;
    bool dirty;

    int lastUsedCount;

    Frame(string direccion_frame){
        this->direccion_frame = direccion_frame;
        this->pin_count = 0;
        this->dirty = false;
        this->bloque = nullptr;
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

    void setBloque(Bloque &bloque){
        this->bloque = &bloque;
        cout<<"Frame: "<<this->direccion_frame<<endl;
        cout<<"Bloque: "<<this->bloque->direccion_bloque<<endl;
        ifstream archivo_origen(this->bloque->direccion_bloque); 
        ofstream archivo_destino(this->direccion_frame);

        if (!archivo_origen || !archivo_destino) { 
            std::cerr << "Error al abrir los archivos." << std::endl;
        }

        std::string linea;

        while (std::getline(archivo_origen, linea)) { 
            archivo_destino << linea << std::endl;
        }

        archivo_origen.close();
        archivo_destino.close();
    }

    void setLastUsedCount(int n){
        this->lastUsedCount = n;
    }
    /*
    void flushing(){
        if(this->dirty){
            //copiar texto de Frame sobre Bloque
        }
    }*/

    void resetearFrame(){
        this->pin_count = 0;
        this->dirty = false;
        this->bloque = nullptr;
    }

};


