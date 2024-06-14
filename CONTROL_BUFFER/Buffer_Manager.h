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

    //INNECESARIO
    string acomodarTexto(string texto,int posicion_inicial){
        int taman = texto.length();
        return texto.substr(posicion_inicial, taman - 4 - posicion_inicial);
    }

    void imprimirEstado()
    {
        for (const auto &frame : Buffer_Pool)
        {
            cout << acomodarTexto(frame.direccion_frame,12) << " : "
                 << (frame.bloque ? acomodarTexto(frame.bloque->direccion_bloque,8) : "N/A      ") 
                 << " - pin: " << frame.pin_count 
                 << " - LUCount: " << frame.lastUsedCount 
                 << " Dirty: ";
                 if(frame.dirty == true){
                    cout<<"si";
                 }else if(frame.dirty == false){
                    cout<<"no";
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
                    cout<<"QUE PASA: "<<i;
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




        int posicionUltimoFrameLlamado()
    {
        // Implementa la lógica para determinar la posición del último frame llamado
        int max_last_used_count = INT_MIN;
        int posicion = -1;
        for (int i = 0; i < Buffer_Pool.size(); ++i)
        {
            if (Buffer_Pool[i].lastUsedCount > max_last_used_count)
            {
                max_last_used_count = Buffer_Pool[i].lastUsedCount;
                posicion = i;
            }
        }
        return posicion;
    }

    string comprobarEstadoDeTodosLosFrames(){ // P: PINNED, PD: PINNED and DIRTY, PDR: PINNED DIRTY and RECENTLY, L: HAY DISPONIBLES
        bool pinned = true;
        bool pinned_dirty = true;
        bool pinned_dirty_recently = true;
        //bool hay_disponibles = false;

        for (int i = 0; i < Buffer_Pool.size(); i++) {
            if (Buffer_Pool[i].pin_count == 0) {
                pinned = false;
                break;
            }
        }

        if(pinned == true) {
            cout<<"TODO PINNEADO"<<endl; 
            return "P";
        }

        for (int i = 0; i < Buffer_Pool.size(); i++) {
            if (Buffer_Pool[i].pin_count == 0 || Buffer_Pool[i].dirty == false) {
                pinned_dirty = false;
                break;
            }
        }

        if(pinned_dirty == true){
            cout<<"TODO PINNEADO Y/O DIRTY"<<endl; 
            return "PD";
        } 

        int posicion_ultimo_frame_llamado = posicionUltimoFrameLlamado();
        for (int i = 0; i < Buffer_Pool.size(); i++) {
            if(i != posicion_ultimo_frame_llamado){
                if (Buffer_Pool[i].pin_count == 0 || Buffer_Pool[i].dirty == false) {
                    pinned_dirty_recently = false;
                    break;
                }
            }
        }

        if(pinned_dirty_recently == true){
            cout<<"TODO PINNEADO Y/O DIRTY y el ultimo esta atento"<<endl;
            return "PDR";
        } 

        cout<<"HAY ESPACIOS LIBRES"<<endl;
        return "L";

    }

    /*int posicionRecientementeMenosUsadoLRUMasOtrasEvaluaciones() {
        int pos = -1;
        int minLastUsedCount = INT_MAX;
        const string estado_frames = comprobarEstadoDeTodosLosFrames();

        if(estado_frames != "P"){
            if(estado_frames == "PD" || estado_frames == "PDR"){
                for (int i = 0; i < Buffer_Pool.size(); i++) {
                    if (Buffer_Pool[i].lastUsedCount < minLastUsedCount && Buffer_Pool[i].dirty && Buffer_Pool[i].pin_count == 0) 
                    {
                        minLastUsedCount = Buffer_Pool[i].lastUsedCount;
                        cout<<"Frame Flusheado"<<endl;
                        pos = i;
                    }
                }
            }else if(estado_frames == "L"){
                for (int i = 0; i < Buffer_Pool.size(); i++) {
                    if (Buffer_Pool[i].pin_count == 0 && Buffer_Pool[i].dirty == false && Buffer_Pool[i].lastUsedCount < minLastUsedCount) 
                    {
                        minLastUsedCount = Buffer_Pool[i].lastUsedCount;
                        pos = i;
                    }
                }
            }
        }
        
        return pos;
    }*/


    int posicionRecientementeMenosUsadoLRUMasOtrasEvaluaciones()
    {
        int min_last_used_count = INT_MAX;
        int posicion = -1;

        // Step 1: Identify pinned frames and exclude them
        for (int i = 0; i < Buffer_Pool.size(); ++i)
        {
            if (Buffer_Pool[i].pin_count == 0)
            {
                // Step 2: Identify dirty frames and exclude them temporarily
                if (!Buffer_Pool[i].dirty)
                {
                    // Step 3-A: Apply LRU among remaining frames
                    if (Buffer_Pool[i].lastUsedCount < min_last_used_count)
                    {
                        min_last_used_count = Buffer_Pool[i].lastUsedCount;
                        posicion = i;
                    }
                }
            }
        }

        // Special Case: All frames are pinned
        if (posicion == -1 && poolSaturated())
        {
            cout << "All frames are pinned. Blocking request until a frame is unpinned." << endl;
            return -1; // Indicate blocking situation
        }

        // Special Case: All frames are either pinned or dirty
        if (posicion == -1)
        {
            cout << "All frames are either pinned or dirty. Applying LRU among dirty frames." << endl;
            min_last_used_count = INT_MAX;
            for (int i = 0; i < Buffer_Pool.size(); ++i)
            {
                if (Buffer_Pool[i].pin_count == 0)
                {
                    if (Buffer_Pool[i].lastUsedCount < min_last_used_count)
                    {
                        min_last_used_count = Buffer_Pool[i].lastUsedCount;
                        posicion = i;
                    }
                }
            }

            if (posicion != -1)
            {
                // Perform flushing of the dirty frame
                cout << "Flushing the dirty frame at position " << posicion << endl;
                // Add flushing logic here
                Buffer_Pool[posicion].dirty = false; // Assuming flushing is done successfully
            }
        }

        // Special Case: LRU when all frames are pinned or dirty except the most recent
        if (posicion == -1)
        {
            int posicion_ultimo_frame_llamado = posicionUltimoFrameLlamado();
            for (int i = 0; i < Buffer_Pool.size(); ++i)
            {
                if (i != posicion_ultimo_frame_llamado && Buffer_Pool[i].pin_count == 0)
                {
                    if (Buffer_Pool[i].lastUsedCount < min_last_used_count)
                    {
                        min_last_used_count = Buffer_Pool[i].lastUsedCount;
                        posicion = i;
                    }
                }
            }
        }

        return posicion;
    }

    int posicionRecientementeMasUsadoMRUMasOtrasEvaluaciones()
    {
        int max_last_used_count = INT_MIN;
        int posicion = -1;

        for (int i = 0; i < Buffer_Pool.size(); ++i)
        {
            if (Buffer_Pool[i].pin_count == 0 && !Buffer_Pool[i].dirty && Buffer_Pool[i].lastUsedCount > max_last_used_count)
            {
                max_last_used_count = Buffer_Pool[i].lastUsedCount;
                posicion = i;
            }
        }

        // Special Case: All frames are pinned
        if (posicion == -1 && poolSaturated())
        {
            cout << "All frames are pinned. Blocking request until a frame is unpinned." << endl;
            return -1; // Indicate blocking situation
        }

        // Special Case: All frames are either pinned or dirty
        if (posicion == -1)
        {
            cout << "All frames are either pinned or dirty. Applying MRU among dirty frames." << endl;
            max_last_used_count = INT_MIN;
            for (int i = 0; i < Buffer_Pool.size(); ++i)
            {
                if (Buffer_Pool[i].pin_count == 0 && Buffer_Pool[i].lastUsedCount > max_last_used_count)
                {
                    max_last_used_count = Buffer_Pool[i].lastUsedCount;
                    posicion = i;
                }
            }

            if (posicion != -1)
            {
                // Perform flushing of the dirty frame
                cout << "Flushing the dirty frame at position " << posicion << endl;
                // Add flushing logic here
                Buffer_Pool[posicion].dirty = false; // Assuming flushing is done successfully
            }
        }

        return posicion;
    }



    //CHEQUEAR
    /*int posicionRecientementeMasUsadoMRUMasOtrasEvaluaciones() {
        int pos = -1;
        int maxLastUsedCount = -1;
        const string estado_frames = comprobarEstadoDeTodosLosFrames();

        if(estado_frames != "P"){
            if(estado_frames == "PD"){
                for (int i = 0; i < Buffer_Pool.size(); i++) {
                    if (Buffer_Pool[i].lastUsedCount > maxLastUsedCount && Buffer_Pool[i].dirty) 
                    {
                        maxLastUsedCount = Buffer_Pool[i].lastUsedCount;
                        cout<<"Frame Flusheado"<<endl;
                        pos = i;
                    }
                }
            }else if(estado_frames == "PDR" || estado_frames == "L"){
                for (int i = 0; i < Buffer_Pool.size(); i++) {
                    if (Buffer_Pool[i].pin_count == 0 && Buffer_Pool[i].dirty == false && Buffer_Pool[i].lastUsedCount > maxLastUsedCount) 
                    {
                        maxLastUsedCount = Buffer_Pool[i].lastUsedCount;
                        pos = i;
                    }
                }
            }
        }

        return pos;
    }*/

    /*int posicionPrimerFrameNoPinneadoCLOCK(){
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
    }*/

    int posicionPrimerFrameNoPinneadoClock()
    {
        int start_pos = ptr_clock - &Buffer_Pool[0];
        int n = Buffer_Pool.size();
        int rounds = 0;

        while (rounds < 2) // Go around the buffer pool twice if necessary
        {
            for (int i = 0; i < n; ++i)
            {
                int idx = (start_pos + i) % n;

                // Skip pinned frames
                if (Buffer_Pool[idx].pin_count > 0)
                {
                    continue;
                }

                // Skip dirty frames initially
                if (Buffer_Pool[idx].dirty)
                {
                    continue;
                }

                // Check the usage bit for CLOCK algorithm
                if (Buffer_Pool[idx].bit_de_uso_CLOCK)
                {
                    Buffer_Pool[idx].bit_de_uso_CLOCK = false;
                }
                else
                {
                    ptr_clock = &Buffer_Pool[(idx + 1) % n];
                    return idx;
                }
            }
            ++rounds;
        }

        // Special Case: All frames are pinned
        if (poolSaturated())
        {
            cout << "All frames are pinned. Blocking request until a frame is unpinned." << endl;
            return -1; // Indicate blocking situation
        }

        // Special Case: All frames are either pinned or dirty
        cout << "All frames are either pinned or dirty. Applying CLOCK among dirty frames." << endl;
        rounds = 0;
        while (rounds < 2)
        {
            for (int i = 0; i < n; ++i)
            {
                int idx = (start_pos + i) % n;

                // Skip pinned frames
                if (Buffer_Pool[idx].pin_count > 0)
                {
                    continue;
                }

                // Consider dirty frames now
                if (Buffer_Pool[idx].dirty)
                {
                    // Check the usage bit for CLOCK algorithm
                    if (Buffer_Pool[idx].bit_de_uso_CLOCK)
                    {
                        Buffer_Pool[idx].bit_de_uso_CLOCK = false;
                    }
                    else
                    {
                        cout << "Flushing the dirty frame at position " << idx << endl;
                        // Add flushing logic here
                        Buffer_Pool[idx].dirty = false; // Assuming flushing is done successfully
                        ptr_clock = &Buffer_Pool[(idx + 1) % n];
                        return idx;
                    }
                }
            }
            ++rounds;
        }

        return -1;
    }



    /*
    void actualizarPinCounts(int exceptIndex) {
        for (int i = 0; i < Buffer_Pool.size(); i++) {
            if (i != exceptIndex && Buffer_Pool[i].pin_count > 0) {
                Buffer_Pool[i].unPinPage();
            }
        }
    }*/

    void flushFrame(int posicion){
        Buffer_Pool[posicion].flushing();
    }

    void unPinFrame(int posicion){
        Buffer_Pool[posicion].unPinPage();
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
                    vector_Bloques.push_back(newBloque);
                    
                }
            } else {
                int pos = posicionRecientementeMasUsadoMRUMasOtrasEvaluaciones(); // Encontrar el frame menos recientemente usado con pin_count 0
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
                    vector_Bloques.push_back(newBloque);
                    
                } else {
                    cout << "No hay frames disponibles para reemplazar." << endl;
                }
            }
        }
    }
};
