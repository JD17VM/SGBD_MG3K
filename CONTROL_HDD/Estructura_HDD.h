struct Estructura_HDD
{
    Espacio_HDD HDD;

    string nombre_disco;
    string nombre_platos;
    int cant_platos_por_disco;
    char caras_a;
    char caras_b;
    string nombre_pistas;
    int cant_pistas_por_cara;
    string nombre_bloques;
    int cant_bloques_por_pista;

    // Solo para bloques
    int bytes_por_bloque;

    Estructura_HDD(string nombre_disco, string nombre_platos, int cant_platos_por_disco, char caras_a, char caras_b, string nombre_pistas, int cant_pistas_por_cara, string nombre_bloques, int cant_bloques_por_pista, int bytes_por_bloque)
    {
        this->nombre_disco = nombre_disco;
        this->nombre_platos = nombre_platos;
        this->cant_platos_por_disco = cant_platos_por_disco;
        this->caras_a = caras_a;
        this->caras_b = caras_b;
        this->nombre_pistas = nombre_pistas;
        this->cant_pistas_por_cara = cant_pistas_por_cara;
        this->nombre_bloques = nombre_bloques;
        this->cant_bloques_por_pista = cant_bloques_por_pista;
        this->bytes_por_bloque = bytes_por_bloque;

        HDD.tipo = "HDD";
        HDD.direccion = nombre_disco;
        HDD.capacidad_total = 0;
        HDD.capacidad_usada = 0;
        HDD.id = "H";

        for (int i = 1; i <= cant_platos_por_disco; i++)
        {
            const string plato_a = this->nombre_disco + "/" + nombre_platos + "_" + completarNumeroConCeros(i, 2) + "_" + caras_a;
            const string plato_b = this->nombre_disco + "/" + nombre_platos + "_" + completarNumeroConCeros(i, 2) + "_" + caras_b;
            Espacio_HDD PLATO_A;
            Espacio_HDD PLATO_B;
            PLATO_A.tipo = "PLATO_CARA";
            PLATO_B.tipo = "PLATO_CARA";
            PLATO_A.direccion = plato_a;
            PLATO_B.direccion = plato_b;
            PLATO_A.capacidad_total = 0;
            PLATO_B.capacidad_total = 0;
            PLATO_A.capacidad_usada = 0;
            PLATO_B.capacidad_usada = 0;
            const string concatenacion_id_plato_a = "HP" + completarNumeroConCeros(i, 2) + "A";
            const string concatenacion_id_plato_b = "HP" + completarNumeroConCeros(i, 2) + "B";
            PLATO_A.id = concatenacion_id_plato_a;
            PLATO_B.id = concatenacion_id_plato_b;
            for (int j = 1; j <= cant_pistas_por_cara; j++)
            {
                const string pista_a = plato_a + "/" + nombre_pistas + "_" + completarNumeroConCeros(j, 2);
                const string pista_b = plato_b + "/" + nombre_pistas + "_" + completarNumeroConCeros(j, 2);
                Espacio_HDD PISTA_A;
                Espacio_HDD PISTA_B;
                PISTA_A.tipo = "PISTA";
                PISTA_B.tipo = "PISTA";
                PISTA_A.direccion = pista_a;
                PISTA_B.direccion = pista_b;
                PISTA_A.capacidad_total = 0;
                PISTA_B.capacidad_total = 0;
                PISTA_A.capacidad_usada = 0;
                PISTA_B.capacidad_usada = 0;
                const string concatenacion_id_pista_a = concatenacion_id_plato_a + "P" + completarNumeroConCeros(j, 2);
                const string concatenacion_id_pista_b = concatenacion_id_plato_b + "P" + completarNumeroConCeros(j, 2);
                PISTA_A.id = concatenacion_id_pista_a;
                PISTA_B.id = concatenacion_id_pista_b;
                for (int k = 1; k <= cant_bloques_por_pista; k++)
                {
                    const string bloque_a = pista_a + "/" + nombre_bloques + "_" + completarNumeroConCeros(k, 2) + ".txt";
                    const string bloque_b = pista_b + "/" + nombre_bloques + "_" + completarNumeroConCeros(k, 2) + ".txt";
                    Espacio_HDD BLOQUE_A;
                    Espacio_HDD BLOQUE_B;
                    BLOQUE_A.tipo = "BLOQUE";
                    BLOQUE_B.tipo = "BLOQUE";
                    BLOQUE_A.direccion = bloque_a;
                    BLOQUE_B.direccion = bloque_b;
                    BLOQUE_A.capacidad_total = bytes_por_bloque;
                    BLOQUE_B.capacidad_total = bytes_por_bloque;
                    BLOQUE_A.capacidad_usada = 0;
                    BLOQUE_B.capacidad_usada = 0;
                    const string concatenaccion_id_bloque_a = concatenacion_id_pista_a + "A" + completarNumeroConCeros(k, 2);
                    const string concatenaccion_id_bloque_b = concatenacion_id_pista_b + "B" + completarNumeroConCeros(k, 2);
                    BLOQUE_A.id = concatenaccion_id_bloque_a;
                    BLOQUE_B.id = concatenaccion_id_bloque_b;
                    PISTA_A.vector_espacios_hdd.push_back(BLOQUE_A);
                    PISTA_B.vector_espacios_hdd.push_back(BLOQUE_B);
                }
                PLATO_A.vector_espacios_hdd.push_back(PISTA_A);
                PLATO_B.vector_espacios_hdd.push_back(PISTA_B);
            }
            HDD.vector_espacios_hdd.push_back(PLATO_A);
            HDD.vector_espacios_hdd.push_back(PLATO_B);
        }
    }

    void crearCarpetasArchivos()
    {
        for (const string direccion : HDD.listadoDeDireccionesHijos())
        {
            if (direccion[direccion.length() - 4] == '.')
            {
                ofstream archivo(direccion.c_str());
                if (archivo.is_open())
                {
                    const string espacios_vacios(bytes_por_bloque, '*');
                    archivo << espacios_vacios;
                    archivo.close();
                }
            }
            else
            {
                CreateDirectory(direccion.c_str(), NULL);
            }
        }
    }

    void crearArchivoMetadatos(string nombre_archivo)
    {
        const string direccion = nombre_disco + "/" + nombre_archivo + ".txt";
        ofstream archivo_m(direccion.c_str());
        if (archivo_m.is_open())
        {
            const string cabecera = nombre_archivo + "#id#str#direccion#str#espacio_disponible#int#espacio_usado#int\n";
            archivo_m << cabecera;

            HDD.calcularCapacidadTotal();
            HDD.calcularEspacioUsado();
            HDD.setNodosEspacio();
            for (const auto &p : HDD.nodos_espacio)
            {
                const string texto_id_hijo = p->id;
                const string texto_direccion_hijo = p->direccion;
                const string texto_tamanio_hijo = to_string(p->capacidad_total);
                const string texto_tamanio_hijo_usado = to_string(p->capacidad_usada);
                archivo_m << texto_id_hijo << "#" << texto_direccion_hijo << "#" << texto_tamanio_hijo << "#" << texto_tamanio_hijo_usado << endl;
            }
            archivo_m.close();
        }
    }

    //--------------------------------------------------------------------------------------------------------------------------------------

    vector<string> split(const string &str, const char delimiter)
    {
        vector<string> tokens;
        int start = 0;
        int end = 0;
        while (end < str.length())
        {
            if (str[end] == delimiter)
            {
                tokens.push_back(str.substr(start, end - start));
                start = end + 1;
            }
            end++;
        }
        tokens.push_back(str.substr(start, end - start));
        return tokens;
    }

    vector<string> elementos_registros(string linea)
    {
        return split(linea, '#');
    }

    vector<string> elementos_registros2(string linea)
    {
        vector<string> elementos;
        stringstream ss(linea);
        string elemento;
        while (getline(ss, elemento, '\n'))
        {
            // Verificar si el último carácter es un salto de línea y eliminarlo si es necesario
            if (!elemento.empty() && elemento.back() == '\n')
            {
                elemento.pop_back();
            }
            elementos.push_back(elemento);
        }
        return elementos;
    }

    Estructura_HDD(string direccion_disco, string direccion_metadata, int cant_platos_por_disco, int cant_pistas_por_cara, int cant_bloques_por_pista, int bytes_por_bloque)
    {
        ifstream archivo(direccion_metadata);
        string linea;
        getline(archivo, linea);
        if (!archivo.is_open())
        {
            cout << "No se pudo abrir el archivo." << endl;
        }
        else
        {
            getline(archivo, linea);
            vector<string> vec = elementos_registros(linea);
            HDD.tipo = "HDD";
            HDD.id = vec[0];
            HDD.direccion = vec[1];
            HDD.capacidad_total = stoi(vec[2]);
            HDD.capacidad_usada = stoi(vec[3]);
            for (int i = 0; i < (cant_platos_por_disco * 2); i++)
            {
                getline(archivo, linea);
                vector<string> vec1 = elementos_registros(linea);
                Espacio_HDD PLATO;
                PLATO.tipo = "PLATO_CARA";
                PLATO.id = vec1[0];
                PLATO.direccion = vec1[1];
                PLATO.capacidad_total = stoi(vec1[2]);
                PLATO.capacidad_usada = stoi(vec1[3]);
                HDD.vector_espacios_hdd.push_back(PLATO);
                // cout << "Añadido PLATO: " << PLATO.direccion << endl; // Mensaje de depuración
                for (int j = 0; j < cant_pistas_por_cara; j++)
                {
                    getline(archivo, linea);
                    vector<string> vec2 = elementos_registros(linea);
                    Espacio_HDD PISTA;
                    PISTA.tipo = "PISTA";
                    PISTA.id = vec2[0];
                    PISTA.direccion = vec2[1];
                    PISTA.capacidad_total = stoi(vec2[2]);
                    PISTA.capacidad_usada = stoi(vec2[3]);
                    HDD.vector_espacios_hdd.back().vector_espacios_hdd.push_back(PISTA); // Añadir PISTA al último PLATO
                    // cout << "Añadida PISTA: " << PISTA.direccion << " al PLATO: " << PLATO.direccion << endl; // Mensaje de depuración
                    for (int k = 0; k < cant_bloques_por_pista; k++)
                    {
                        getline(archivo, linea);
                        vector<string> vec3 = elementos_registros(linea);
                        Espacio_HDD BLOQUE;
                        BLOQUE.tipo = "BLOQUE";
                        BLOQUE.id = vec3[0];
                        BLOQUE.direccion = vec3[1];
                        BLOQUE.capacidad_total = stoi(vec3[2]);
                        BLOQUE.capacidad_usada = stoi(vec3[3]);
                        HDD.vector_espacios_hdd.back().vector_espacios_hdd.back().vector_espacios_hdd.push_back(BLOQUE); // Añadir BLOQUE a la última PISTA
                        // cout << "Añadido BLOQUE: " << BLOQUE.direccion << " a la PISTA: " << PISTA.direccion << endl; // Mensaje de depuración
                    }
                }
            }

            archivo.close();
        }
    }

    // Ocupar bloques disponibles
    
    Espacio_HDD& encontrarBloquePorID(string id_bloque){ //Funciona Ok
        for(auto& plato : HDD.vector_espacios_hdd){
            for(auto& pista : plato.vector_espacios_hdd){
                for(auto& bloque : pista.vector_espacios_hdd){
                    if(bloque.id == id_bloque){
                        return bloque;
                    }
                }
            }
        }
    }

    void unirBloques(Espacio_HDD& A, Espacio_HDD& B){ //Funciona Ok
        A.siguiente = &B;
        B.anterior = &A;
        cout<<"Se ligo el bloque "<<B.anterior->direccion<<" con el Bloque"<<A.siguiente->direccion<<endl;
    }

    void bloquesLigados(string id_A, string id_B){ //Funciona Ok
        unirBloques(
            encontrarBloquePorID(id_A),
            encontrarBloquePorID(id_B)
        );
    }

    Espacio_HDD& encontrarPrimerBloqueVacio() { //Funciona Ok
        for (auto& plato : HDD.vector_espacios_hdd) {
            for (auto& pista : plato.vector_espacios_hdd){
                for (auto& bloque : pista.vector_espacios_hdd){
                    if (bloque.tipo == "BLOQUE" && bloque.capacidad_usada == 0) {
                        return bloque;
                    }
                }
            }
        }
    }

};
