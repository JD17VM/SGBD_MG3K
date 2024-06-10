#include "Frame.h"

using namespace std;

struct Buffer_Manager
{
    vector<Frame> Buffer_Pool;
    vector<shared_ptr<Bloque>> vector_Bloques; //Alamacenar punteros en Memoria
    int useCounter;

    Frame* ptr_clock; 

    Buffer_Manager(int cantidad_frames)
    {
        useCounter = 0;
        for (int i = 1; i <= cantidad_frames; i++)
        {
            const string nombre_frame = "Frame_" + to_string(i) + ".txt";
            string direccion_frame = "Buffer_Pool/" + nombre_frame;
            Buffer_Pool.emplace_back(direccion_frame);
            ofstream archivo_frame(direccion_frame);
        }
        Frame* ptr_clock = &Buffer_Pool[0];
    }

    void imprimirEstado()
    {
        for (const auto &frame : Buffer_Pool)
        {
            cout << frame.direccion_frame << " : "
                 << " pin count: " << frame.pin_count << " bloque: "
                 << (frame.bloque ? frame.bloque->direccion_bloque : "N/A") << " lastUsedCount: " << frame.lastUsedCount 
                 << " dirty: ";
                 if(frame.dirty == true){
                    cout<<"SI";
                 }else if(frame.dirty == false){
                    cout<<"NO";
                 }
                 cout<<" - BIT: ";
                 if(frame.bit_de_uso_CLOCK == true){
                    cout<<"1";
                 }else if(frame.bit_de_uso_CLOCK == false){
                    cout<<"0";
                 }
                 cout<<endl;
        }
        cout << endl;
    }

    bool poolSaturated()
    {
        for (const auto &frame : Buffer_Pool)
        {
            if (!(frame.bloque))
            {
                return false;
            }
        }
        return true;
    }

    int posicionFramePorDireccionBloque(string direccion_bloque)
    {
        int i = 0;
        for (const auto &frame : Buffer_Pool)
        {
            if (frame.bloque != nullptr)
            {
                cout << "Direccion bloque comprobar: " << frame.bloque->direccion_bloque << endl;
                cout << "Pagina bloque comprobar: " << direccion_bloque << endl
                     << endl;
                if (frame.bloque->direccion_bloque == direccion_bloque)
                {
                    return i;
                }
            }
            i++;
        }
        return -1;
    }

    int posicionPrimerFrameVacio()
    {
        int i = 0;
        for (const auto &frame : Buffer_Pool)
        {
            if ((frame.bloque == nullptr))
            {
                return i;
            }
            i++;
        }
        return -1;
    }

    int posicionRecientementeMenosUsadoLRU() {
        int pos = -1;
        int minLastUsedCount = INT_MAX;
        for (int i = 0; i < Buffer_Pool.size(); i++) {
            if (Buffer_Pool[i].pin_count == 0 && Buffer_Pool[i].lastUsedCount < minLastUsedCount) {
                minLastUsedCount = Buffer_Pool[i].lastUsedCount;
                pos = i;
            }
        }
        return pos;
    }

    //CHEQUEAR
    int posicionRecientementeMasUsadoMRU() {
        int pos = -1;
        int maxLastUsedCount = -1;
        for (int i = 0; i < Buffer_Pool.size(); i++) {
            if (Buffer_Pool[i].pin_count == 0 && Buffer_Pool[i].lastUsedCount > maxLastUsedCount) {
                maxLastUsedCount = Buffer_Pool[i].lastUsedCount;
                pos = i;
            }
        }
        return pos;
    }

    int posicionPrimerFrameNoPinneadoCLOCK(){
        int size = Buffer_Pool.size();
        for(int i=0; i<size; i++){
            if(!ptr_clock->bit_de_uso_CLOCK){
                ptr_clock->setbitDeUsoCLOCK(true);
                int pos = ptr_clock - &Buffer_Pool[0];
                ptr_clock++;
                if (ptr_clock == &Buffer_Pool[0] + size){
                    ptr_clock = &Buffer_Pool[0];
                } 
                return pos;
            }
            ptr_clock->setbitDeUsoCLOCK(false);
            ptr_clock++;
            if (ptr_clock == &Buffer_Pool[0] + size){
                ptr_clock = &Buffer_Pool[0];
            } 
        }
        return -1;
    }


    void actualizarPinCounts(int exceptIndex) {
        for (int i = 0; i < Buffer_Pool.size(); i++) {
            if (i != exceptIndex && Buffer_Pool[i].pin_count > 0) {
                Buffer_Pool[i].unPinPage();
            }
        }
    }

    void flushFrame(int posicion){
        Buffer_Pool[posicion].flushing();
    }

    void llamarABloque(string direccion_bloque,char indicadorLW) {
        int pos = posicionFramePorDireccionBloque(direccion_bloque);
        if (pos != -1) {
            // El bloque ya existe en el buffer, incrementar pin_count y actualizar lastUsedCount
            Buffer_Pool[pos].setLastUsedCount(++useCounter); // Actualizar el contador de uso
            Buffer_Pool[pos].pinPage();
            Buffer_Pool[pos].setbitDeUsoCLOCK(true);
            if(indicadorLW == 'W'){
                Buffer_Pool[pos].setDirty(true);
            }
            actualizarPinCounts(pos); // Actualizar pin counts de otros frames
            cout << "Bloque ya existe en el buffer: " << direccion_bloque << endl;
            
        } else {
            // El bloque no existe en el buffer
            if (!poolSaturated()) {
                int pos = posicionPrimerFrameVacio();
                if (pos != -1) {
                    shared_ptr<Bloque> newBloque = make_shared<Bloque>(direccion_bloque);
                    Buffer_Pool[pos].setBloque(newBloque);
                    Buffer_Pool[pos].setLastUsedCount(++useCounter); // Actualizar el contador de uso
                    Buffer_Pool[pos].pinPage();
                    Buffer_Pool[pos].setbitDeUsoCLOCK(true);
                    if(indicadorLW == 'W'){
                        Buffer_Pool[pos].setDirty(true);
                    }
                    actualizarPinCounts(pos); // Actualizar pin counts de otros frames
                    vector_Bloques.push_back(newBloque);
                    
                }
            } else {
                int pos = posicionPrimerFrameNoPinneadoCLOCK(); // Encontrar el frame menos recientemente usado con pin_count 0
                if (pos != -1) {
                    Buffer_Pool[pos].resetearFrame();
                    shared_ptr<Bloque> newBloque = make_shared<Bloque>(direccion_bloque);
                    Buffer_Pool[pos].setBloque(newBloque);
                    Buffer_Pool[pos].setLastUsedCount(++useCounter); // Actualizar el contador de uso
                    Buffer_Pool[pos].pinPage();
                    Buffer_Pool[pos].setbitDeUsoCLOCK(true);
                    if(indicadorLW == 'W'){
                        Buffer_Pool[pos].setDirty(true);
                    }
                    actualizarPinCounts(pos); // Actualizar pin counts de otros frames
                    vector_Bloques.push_back(newBloque);
                    
                } else {
                    cout << "No hay frames disponibles para reemplazar." << endl;
                }
            }
        }
    }
};
