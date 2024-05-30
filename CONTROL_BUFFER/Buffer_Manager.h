#include "Frame.h"

using namespace std;

struct Buffer_Manager{
    vector<Frame> Buffer_Pool;
    vector<shared_ptr<Bloque>> vector_Bloques; 

    Buffer_Manager(int cantidad_frames){
        for(int i = 1; i <= cantidad_frames;i++){
            const string nombre_frame = "Frame_" + to_string(i) + ".txt";
            string direccion_frame = "Buffer_Pool/" + nombre_frame;
            Buffer_Pool.emplace_back(direccion_frame);
            ofstream archivo_frame(direccion_frame);
        }
    }

    void imprimirEstado(){
        for (const auto &frame : Buffer_Pool) {
            cout << frame.direccion_frame << " : "
                 << " pin count: " << frame.pin_count << " bloque: "
                 << (frame.bloque ? frame.bloque->direccion_bloque : "N/A") << endl;
        }
        cout<<endl;
    }

    bool poolSaturated(){
        for(const auto &frame : Buffer_Pool){
            if(!(frame.bloque)){
                return false;
            }
        }
        return true;
    }
    
    int Pos(string pagina){
        int i = 0;
        for(const auto &frame : Buffer_Pool){
            if(frame.bloque != nullptr){
                cout<<"Direccion bloque comprobar: "<<frame.bloque->direccion_bloque<<endl;
                cout<<"Pagina bloque comprobar: "<<pagina<<endl<<endl;
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

    void agregarBloque(shared_ptr<Bloque> nuevo_bloque){
        //cout<<"Entro el bloque";
        if(this->poolSaturated()){
            cout<<"BufferPool Saturado"<<endl;
            cout<<"Posicion del Frame Proximo a Vaciar: "<<this->posFrameProximoAVaciarLRU()<<endl;
            Frame& f = Buffer_Pool[this->posFrameProximoAVaciarLRU()];
            f.resetearFrame();
            f.setBloque(nuevo_bloque);
        }else{
            cout<<"Posicion Frame disponible "<<this->posPrimerFrameDisponible()<<endl;
            Buffer_Pool[this->posPrimerFrameDisponible()].setBloque(nuevo_bloque);
        }
    }

    void llamarABloque(const string &direccion_bloque){
        cout<<"Llamando a bloque: "<<direccion_bloque<<endl;
        int pos = comprobarExistenciaDePaginaEnBufferPoolPos(direccion_bloque);
        cout<<"Posicion: "<<pos<<endl;
        if(pos ==  -1){
            auto nuevo_bloque = make_shared<Bloque>(direccion_bloque);
            vector_Bloques.push_back(nuevo_bloque);
            this->agregarBloque(nuevo_bloque);
        }else{
            for(auto &frame : Buffer_Pool){
                frame.unPinPage();
            }
            this->Buffer_Pool[pos].pinPage();
            this->Buffer_Pool[pos].pinPage();
        }
    }

};
