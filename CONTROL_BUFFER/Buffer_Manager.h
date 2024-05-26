#include "Frame.h"

struct Buffer_Manager{
    vector<Frame> Buffer_Pool;

    Buffer_Manager(int cantidad_frames){
        for(int i = 1; i <= cantidad_frames;i++){
            const string direccion_frame = "Frame_" + to_string(i) + ".txt"
            Frame(direccion_frame);
            //crear_archivo(direccion_frame) - Dentro de una carpeta BUFFER_POOL
        }
    }

    void agregarBloque(Espacio_HDD& Bloque){
        //if poolSaturated
            //const Frame f = Buffer_Pool[this->posFrameProximoAVaciar()]
            //f.resetearFrame();
            //f.setBloque(Bloque);
        // else
            //Comprobar el primer Frame Disponible
            //Vincular el puntero del Frame con el bloque
    }

    bool poolSaturaded(){
        //Comprueba si todos los Frames del vector estan siendo usados, chequear si todos los punteros no son nullptr 
    }

    bool comprobarPagina(string pagina){
        //Comprueba si el Frame está usando algun bloque solicitado
    }

    int posFrameProximoAVaciarLRU(){
        //Revisa cual es el Frame que sería el proximo a reemplazar y devuelve su posicion en el buffer
    }


};
