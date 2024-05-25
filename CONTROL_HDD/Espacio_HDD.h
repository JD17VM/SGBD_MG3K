struct Espacio_HDD
{
    string tipo; // HDD, PLATO_CARA, PISTA, BLOQUE
    string id;
    string direccion;
    int capacidad_total;
    int capacidad_usada;
    vector<Espacio_HDD> vector_espacios_hdd;

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

    vector<int> listado_de_tamanio_direcciones_hijos()
    {
        vector<int> tamanios;
        tamanios.push_back(calcularCapacidadTotal());
        for (const auto &espacio : vector_espacios_hdd)
        {
            tamanios.push_back(espacio.calcularCapacidadTotal());
            for (const auto &espacio_2 : espacio.vector_espacios_hdd)
            {
                tamanios.push_back(espacio_2.calcularCapacidadTotal());
                for (const auto &espacio_3 : espacio_2.vector_espacios_hdd)
                {
                    tamanios.push_back(espacio_3.calcularCapacidadTotal());
                }
            }
        }
        return tamanios;
    };

    vector<int> listado_de_tamanio_usado_direcciones_hijos()
    {
        vector<int> tamanios;
        tamanios.push_back(calcularEspacioUsado());
        for (const auto &espacio : vector_espacios_hdd)
        {
            tamanios.push_back(espacio.calcularEspacioUsado());
            for (const auto &espacio_2 : espacio.vector_espacios_hdd)
            {
                tamanios.push_back(espacio_2.calcularEspacioUsado());
                for (const auto &espacio_3 : espacio_2.vector_espacios_hdd)
                {
                    tamanios.push_back(espacio_3.calcularEspacioUsado());
                }
            }
        }
        return tamanios;
    };

    vector<string> listado_de_nombres_id_hijos()
    {
        vector<string> tamanios;
        tamanios.push_back(id);
        for (const auto &espacio : vector_espacios_hdd)
        {
            tamanios.push_back(espacio.id);
            for (const auto &espacio_2 : espacio.vector_espacios_hdd)
            {
                tamanios.push_back(espacio_2.id);
                for (const auto &espacio_3 : espacio_2.vector_espacios_hdd)
                {
                    tamanios.push_back(espacio_3.id);
                }
            }
        }
        return tamanios;
    };
};