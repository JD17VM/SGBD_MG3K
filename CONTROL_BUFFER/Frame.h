#include "Bloque.h"

using namespace std;

struct Frame{
    shared_ptr<Bloque> bloque;

    string direccion_frame;
    int pin_count;
    bool dirty;
    int lastUsedCount;

    bool bit_de_uso_CLOCK;

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

    void pinPage(char indicadorLW){
        this->pin_count++;
        this->cola_de_requerimientos.push_back(indicadorLW);

        if(this->cola_de_requerimientos[0] == 'W'){
            setDirty(true);
        }else if(this->cola_de_requerimientos[0] == 'L'){
            setDirty(false);
        }
    }

    void unPinPage(){
        if(this->pin_count){
            this->pin_count--;
            this->cola_de_requerimientos.erase(cola_de_requerimientos.begin());

            if(this->cola_de_requerimientos[0] == 'W'){
                setDirty(true);
            }else if(this->cola_de_requerimientos[0] == 'L'){
                setDirty(false);
            }
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


    void setbitDeUsoCLOCK(bool n){
        this->bit_de_uso_CLOCK = n;
    }



    void imprimirColaDeRequerimientos() const{
        if(this->cola_de_requerimientos.size() > 0){
            for(char solicitud: this->cola_de_requerimientos){
                cout<<solicitud<<"-";
            }
        }
    }

};


