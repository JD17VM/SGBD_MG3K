struct Frame{
    Espacio_HDD* Bloque;

    string direccion_frame;
    int pin_count;
    bool dirty;

    int lastUsedCount;

    Frame(string direccion_frame){
        this->direccion_frame = direccion_frame;
        this->pin_count = 0;
        this->dirty = false;
        this->Bloque = nullptr;
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

    void setBloque(Espacio_HDD &Bloque){
        this->Bloque = &Bloque;
        //Copiar texto de Bloque a Frame
    }

    void setLastUsedCount(int n){
        this->lastUsedCount = n;
    }

    void flushing(){
        if(this->dirty){
            //copiar texto de Frame sobre Bloque
        }
    }

    void resetearFrame(){
        this->pin_count = 0;
        this->dirty = false;
        this->Bloque = nullptr;
    }

};


