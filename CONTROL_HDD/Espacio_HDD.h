struct Espacio_HDD
{
    string tipo; // HDD, PLATO_CARA, PISTA, BLOQUE
    string id;
    string direccion;
    int capacidad_total;
    int capacidad_usada;
    vector<Espacio_HDD> vector_espacios_hdd;

    vector<const Espacio_HDD*> nodos_espacio; //Raiz

    //Espacio_HDD* proximo_bloque_hoja;

    Espacio_HDD* siguiente;
    Espacio_HDD* anterior;


    Espacio_HDD(){
        this->anterior = nullptr;
        this->siguiente = nullptr;
    }

    vector<string> listadoDeDireccionesHijos()
    {
        vector<string> direcciones;
        listadoDeDireccionesHijosRecursivo(this, direcciones);
        return direcciones;
    }

    void listadoDeDireccionesHijosRecursivo(const Espacio_HDD* nodo, vector<string>& direcciones)
    {
        direcciones.push_back(nodo->direccion);
        for (const auto& espacio : nodo->vector_espacios_hdd)
        {
            listadoDeDireccionesHijosRecursivo(&espacio, direcciones);
        }
    }

    int calcularCapacidadTotal() 
    {
        int capacidadTotal = capacidad_total;
        for ( auto &espacio : vector_espacios_hdd)
        {
            capacidadTotal += espacio.calcularCapacidadTotal();
        }
        this->capacidad_total = capacidadTotal;
        return capacidadTotal;
    }

    int calcularEspacioUsado()
    {
        int capacidadUsada = capacidad_usada;
        for (auto &espacio : vector_espacios_hdd)
        {
            capacidadUsada += espacio.calcularEspacioUsado();
        }
        this->capacidad_usada = capacidadUsada;
        return capacidadUsada;
    }

    //Revisar porque no funciona con recursividad
    /*void Espacio_HDD::setNodosEspacio() {
        nodos_espacio.push_back(this);
        for (auto& espacio : vector_espacios_hdd) {
            espacio.setNodosEspacio(); // Llamada recursiva para establecer los nodos de los espacios hijos
        }
    }*/

    void setNodosEspacio(){
        nodos_espacio.push_back(this);
        for (auto &espacio : vector_espacios_hdd){
            nodos_espacio.push_back(&espacio);
            for (auto &espacio_2 : espacio.vector_espacios_hdd){
                nodos_espacio.push_back(&espacio_2);
                for (auto &espacio_3 : espacio_2.vector_espacios_hdd){
                    nodos_espacio.push_back(&espacio_3);
                }
            }
        }
    }
};