#include "Frame.h"

using namespace std;

struct Buffer_Manager
{
    vector<Frame> Buffer_Pool;
    vector<shared_ptr<Bloque>> vector_Bloques;
    int useCounter;

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
    }

    void imprimirEstado()
    {
        for (const auto &frame : Buffer_Pool)
        {
            cout << frame.direccion_frame << " : "
                 << " pin count: " << frame.pin_count << " bloque: "
                 << (frame.bloque ? frame.bloque->direccion_bloque : "N/A") << " lastUsedCount: " << frame.lastUsedCount << endl;
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

    int Pos(string pagina)
    {
        int i = 0;
        for (const auto &frame : Buffer_Pool)
        {
            if (frame.bloque != nullptr)
            {
                cout << "Direccion bloque comprobar: " << frame.bloque->direccion_bloque << endl;
                cout << "Pagina bloque comprobar: " << pagina << endl
                     << endl;
                if (frame.bloque->direccion_bloque == pagina)
                {
                    return i;
                }
            }
            i++;
        }
        return -1;
    }

    int posPrimerFrameDisponible()
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

    int posMenosUsado() {
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
    /*
    int posMenosUsado() {
        int pos = 0;
        int minLastUsedCount = Buffer_Pool[0].lastUsedCount;
        for (int i = 1; i < Buffer_Pool.size(); i++) {
            if (Buffer_Pool[i].lastUsedCount < minLastUsedCount) {
                minLastUsedCount = Buffer_Pool[i].lastUsedCount;
                pos = i;
            }
        }
        return pos;
    }*/

    void actualizarPinCounts(int exceptIndex) {
        for (int i = 0; i < Buffer_Pool.size(); i++) {
            if (i != exceptIndex && Buffer_Pool[i].pin_count > 0) {
                Buffer_Pool[i].unPinPage();
            }
        }
    }

    int posFrameProximoAVaciarLRU()
    {
        int max = -1; // Inicializar con un valor menor que cualquier lastUsedCount posible
        int pos = -1; // Posición del elemento con el mayor lastUsedCount y pin_count igual a 0

        for (int i = 0; i < Buffer_Pool.size(); ++i)
        {
            const auto &frame = Buffer_Pool[i];
            if (frame.lastUsedCount > max && frame.pin_count == 0)
            {
                max = frame.lastUsedCount;
                pos = i;
            }
        }

        return pos;
    }


    int comprobarExistenciaDePaginaEnBufferPoolPos(string pagina){
        int i = 0;
        //cout<<Buffer_Pool.size();
        cout<<"Tamanio Buffer Pool: "<<Buffer_Pool.size();
        for(const auto &frame : Buffer_Pool){
            if(frame.bloque != nullptr){
                //cout<<frame.bloque->direccion_bloque<<endl;
                if(frame.bloque->direccion_bloque == pagina){
                    return i;
                }
            }
            i++;
        }
        return -1;
    }

    /*void agregarBloque(shared_ptr<Bloque> nuevo_bloque)
    {
        if (this->poolSaturated())
        {
            cout << "BufferPool Saturado" << endl;
            cout << "Posicion del Frame Proximo a Vaciar: " << this->posFrameProximoAVaciarLRU() << endl;
            Frame &f = Buffer_Pool[this->posFrameProximoAVaciarLRU()];
            f.resetearFrame();
            f.setBloque(nuevo_bloque);
            //FrameOrderList.push_back(f);
        }
        else
        {
            cout << "Posicion Frame disponible " << this->posPrimerFrameDisponible() << endl;
            Buffer_Pool[this->posPrimerFrameDisponible()].setBloque(nuevo_bloque);
        }

    }

    void llamarABloque(const string &direccion_bloque)
    {
        cout << "Llamando a bloque: " << direccion_bloque << endl;
        int pos = comprobarExistenciaDePaginaEnBufferPoolPos(direccion_bloque);
        cout << "Posicion: " << pos << endl;
        if (pos == -1)
        {
            auto nuevo_bloque = make_shared<Bloque>(direccion_bloque);
            vector_Bloques.push_back(nuevo_bloque);
            this->agregarBloque(nuevo_bloque);
        }
        else
        {
            for (auto &frame : Buffer_Pool)
            {
                frame.unPinPage();
            }
            this->Buffer_Pool[pos].pinPage();
            this->Buffer_Pool[pos].pinPage();
        }
    }*/

    /*void llamarABloque(string direccion_bloque) {
        if (!poolSaturated()) {
            int pos = Pos(direccion_bloque);
            if (pos == -1) {
                shared_ptr<Bloque> newBloque = make_shared<Bloque>(direccion_bloque);
                int pos = posPrimerFrameDisponible();
                Buffer_Pool[pos].setBloque(newBloque);
                Buffer_Pool[pos].setLastUsedCount(++useCounter); // Actualizar el contador de uso
                vector_Bloques.push_back(newBloque);
            } else {
                Buffer_Pool[pos].setLastUsedCount(++useCounter); // Actualizar el contador de uso
                cout << "Bloque ya existe en el buffer: " << direccion_bloque << endl;
            }
        }
    }*/

    void llamarABloque(string direccion_bloque) {
        int pos = Pos(direccion_bloque);
        if (pos != -1) {
            // El bloque ya existe en el buffer, incrementar pin_count y actualizar lastUsedCount
            Buffer_Pool[pos].setLastUsedCount(++useCounter); // Actualizar el contador de uso
            Buffer_Pool[pos].pinPage();
            actualizarPinCounts(pos); // Actualizar pin counts de otros frames
            cout << "Bloque ya existe en el buffer: " << direccion_bloque << endl;
        } else {
            // El bloque no existe en el buffer
            if (!poolSaturated()) {
                int pos = posPrimerFrameDisponible();
                if (pos != -1) {
                    shared_ptr<Bloque> newBloque = make_shared<Bloque>(direccion_bloque);
                    Buffer_Pool[pos].setBloque(newBloque);
                    Buffer_Pool[pos].setLastUsedCount(++useCounter); // Actualizar el contador de uso
                    Buffer_Pool[pos].pinPage();
                    actualizarPinCounts(pos); // Actualizar pin counts de otros frames
                    vector_Bloques.push_back(newBloque);
                }
            } else {
                int pos = posMenosUsado(); // Encontrar el frame menos recientemente usado con pin_count 0
                if (pos != -1) {
                    Buffer_Pool[pos].resetearFrame();
                    shared_ptr<Bloque> newBloque = make_shared<Bloque>(direccion_bloque);
                    Buffer_Pool[pos].setBloque(newBloque);
                    Buffer_Pool[pos].setLastUsedCount(++useCounter); // Actualizar el contador de uso
                    Buffer_Pool[pos].pinPage();
                    actualizarPinCounts(pos); // Actualizar pin counts de otros frames
                    vector_Bloques.push_back(newBloque);
                } else {
                    cout << "No hay frames disponibles para reemplazar." << endl;
                }
            }
        }
    }

    void reordenarFrames() {
        sort(Buffer_Pool.begin(), Buffer_Pool.end(), [](const Frame &a, const Frame &b) {
            return a.lastUsedCount < b.lastUsedCount;
        });
    }
};
