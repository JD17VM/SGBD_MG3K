struct Espacio_HDD
{
    string tipo; // HDD, PLATO_CARA, PISTA, BLOQUE
    string id;
    string direccion;
    int capacidad_total;
    int capacidad_usada;
    vector<Espacio_HDD> vector_espacios_hdd;

    vector<const Espacio_HDD*> nodos_espacio; 

    vector<string> listadoDeDireccionesHijos()
    {
        vector<string> direcciones;
        direcciones.push_back(direccion);
        for (const auto &espacio : vector_espacios_hdd)
        {
            direcciones.push_back(espacio.direccion);
            for (const auto &espacio_2 : espacio.vector_espacios_hdd)
            {
                direcciones.push_back(espacio_2.direccion);
                for (const auto &espacio_3 : espacio_2.vector_espacios_hdd)
                {
                    direcciones.push_back(espacio_3.direccion);
                }
            }
        }
        return direcciones;
    };

    int calcularCapacidadTotal() const
    {
        int capacidadTotal = capacidad_total;
        for (const auto &espacio : vector_espacios_hdd)
        {
            capacidadTotal += espacio.calcularCapacidadTotal();
        }
        return capacidadTotal;
    }

    int calcularEspacioUsado() const
    {
        int capacidadUsada = capacidad_usada;
        for (const auto &espacio : vector_espacios_hdd)
        {
            capacidadUsada += espacio.calcularEspacioUsado();
        }
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
        for (const auto &espacio : vector_espacios_hdd){
            nodos_espacio.push_back(&espacio);
            for (const auto &espacio_2 : espacio.vector_espacios_hdd){
                nodos_espacio.push_back(&espacio_2);
                for (const auto &espacio_3 : espacio_2.vector_espacios_hdd){
                    nodos_espacio.push_back(&espacio_3);
                }
            }
        }
    }
};