#include <iostream>
#include <string>
#include <vector>


#include "Frame.h"

using namespace std;

struct Buffer_Manager{
    vector<Frame> Buffer_Pool;


    Buffer_Manager(int cantidad_frames){
        for(int i = 1; i <= cantidad_frames;i++){
            const string nombre_frame = "Frame_" + to_string(i) + ".txt";
            string direccion_frame = "Buffer_Pool/" + nombre_frame;
            Frame f(direccion_frame);
            Buffer_Pool.push_back(f);
            ofstream archivo_frame(direccion_frame);
        }
    }

    void imprimirEstado(){
        for (const auto &frame : Buffer_Pool) {
            cout << frame.direccion_frame << " : "
                 << " pin count: " << frame.pin_count << " bloque: "
                 << (frame.bloque ? frame.bloque->direccion_bloque : "N/A") << endl;
        }
    }

    
    void agregarBloque(Bloque& nuevo_bloque){
        //cout<<"Entro el bloque";
        if(this->poolSaturated()){
            cout<<"Saturado";
            Frame& f = Buffer_Pool[this->posFrameProximoAVaciarLRU()];
            f.resetearFrame();
            f.setBloque(nuevo_bloque);
        }else{
            //cout<<"libre";
            cout<<this->posPrimerFrameDisponible();
            //Buffer_Pool[this->posPrimerFrameDisponible()].bloque = &nuevo_bloque;
            Buffer_Pool[this->posPrimerFrameDisponible()].setBloque(nuevo_bloque);
        }
    }

    bool poolSaturated(){
        for(const auto &frame : Buffer_Pool){
            if(!(frame.bloque)){
                return false;
            }
        }
        return true;
    }

    
    int comprobarPaginaPos(string pagina){
        int i = 0;
        //cout<<Buffer_Pool.size();
        for(auto &frame : Buffer_Pool){
            if(frame.bloque){
                if(frame.bloque->direccion_bloque == pagina){
                    return i;
                }
            }
            i++;
        }
        return -1;
    }
    

   int posPrimerFrameDisponible(){
        int i = 0;
        for(const auto &frame : Buffer_Pool){
            if (!(frame.bloque)){
                return i;
            }
            i++;
        }
        return -1;
   }

    int posFrameProximoAVaciarLRU() {
        int max = -1; // Inicializar con un valor menor que cualquier lastUsedCount posible
        int pos = -1; // Posición del elemento con el mayor lastUsedCount y pin_count igual a 0

        for (int i = 0; i < Buffer_Pool.size(); ++i) {
            const auto& frame = Buffer_Pool[i];
            if (frame.lastUsedCount > max && frame.pin_count == 0) {
                max = frame.lastUsedCount;
                pos = i;
            }
        }

        return pos;
    }

    void llamarABloque(string direccion_bloque){
        int pos = comprobarPaginaPos(direccion_bloque);
        if(pos ==  -1){
            Bloque b(direccion_bloque);
            this->agregarBloque(b);
        }else{
            for(auto &frame : Buffer_Pool){
                frame.unPinPage();
            }
            this->Buffer_Pool[pos].pinPage();
            this->Buffer_Pool[pos].pinPage();
        }
    }

};
