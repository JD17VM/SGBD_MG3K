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

    Espacio_HDD Espacio_HDD_no_encontrado; // Op para return

    Estructura_HDD(
        string nombre_disco,
        string nombre_platos, int cant_platos_por_disco,
        char caras_a, char caras_b,
        string nombre_pistas, int cant_pistas_por_cara,
        string nombre_bloques, int cant_bloques_por_pista,
        int bytes_por_bloque);

    Estructura_HDD(
        string direccion_disco,
        string direccion_metadata,
        int cant_platos_por_disco,
        int cant_pistas_por_cara,
        int cant_bloques_por_pista,
        int bytes_por_bloque);

    void crearDirectoriosYArchivos();
    void crearArchivoMetadatos(string nombre_archivo);
    vector<string> split(const string &str, const char delimiter);
    vector<string> splitRegistroEnElementos(string linea);
    vector<string> elementos_red(string linea);
    void enlazarBloquesLinkeadosPorIdDeMetadata();
    Espacio_HDD &getReferenciaBloquePorID(string id_bloque);
    void enlazarBloques(Espacio_HDD &A, Espacio_HDD &B);
    void enlazarBloquesPorID(string id_A, string id_B);
    Espacio_HDD &getReferenciaPrimerBloqueVacioDisponible();
    void llenarBloque(string id, int capacidad);
    void insertarTextoABloquePorID(string texto, string id_bloque);
    void insertarTextoABloque(string texto, Espacio_HDD &Bloque);

    void resetCapacidadesNivel_0_1_2()
    {
        HDD.capacidad_total = 0;
        HDD.capacidad_usada = 0;
        for (auto &espacio : HDD.vector_espacios_hdd)
        {
            espacio.capacidad_total = 0;
            espacio.capacidad_usada = 0;
            for (auto &espacio_2 : espacio.vector_espacios_hdd)
            {
                espacio_2.capacidad_total = 0;
                espacio_2.capacidad_usada = 0;
            }
        }
    }
};

Estructura_HDD::Estructura_HDD(string nombre_disco, string nombre_platos, int cant_platos_por_disco, char caras_a, char caras_b, string nombre_pistas, int cant_pistas_por_cara, string nombre_bloques, int cant_bloques_por_pista, int bytes_por_bloque)
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

void Estructura_HDD::crearDirectoriosYArchivos()
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

void Estructura_HDD::crearArchivoMetadatos(string nombre_archivo)
{
    const string direccion = nombre_disco + "/" + nombre_archivo + ".txt";
    cout << direccion << endl;
    ofstream archivo_m(direccion.c_str());
    if (archivo_m.is_open())
    {
        const string cabecera = nombre_archivo + "#id#str#direccion#str#espacio_disponible#int#espacio_usado#int#bloque_ligado#str\n";
        archivo_m << cabecera;
        cout << "Se entró a metadata";
        resetCapacidadesNivel_0_1_2();
        HDD.resetearNodosEspacio();
        HDD.calcularCapacidadTotal();
        HDD.calcularEspacioUsado();
        HDD.setNodosEspacio();
        for (const auto &p : HDD.nodos_espacio)
        {
            const string texto_id_hijo = p->id;
            const string texto_direccion_hijo = p->direccion;
            const string texto_tamanio_hijo = to_string(p->capacidad_total);
            const string texto_tamanio_hijo_usado = to_string(p->capacidad_usada);
            const string id_siguiente = p->id_siguiente_bloque;
            archivo_m << texto_id_hijo << "#" << texto_direccion_hijo << "#" << texto_tamanio_hijo << "#" << texto_tamanio_hijo_usado << "#" 
            << id_siguiente 
             << endl;
        }
        archivo_m.close();
    }
}

vector<string> Estructura_HDD::split(const string &str, const char delimiter)
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

vector<string> Estructura_HDD::splitRegistroEnElementos(string linea)
{
    return split(linea, '#');
}

vector<string> Estructura_HDD::elementos_red(string linea)
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

Estructura_HDD::Estructura_HDD(string direccion_disco, string direccion_metadata, int cant_platos_por_disco, int cant_pistas_por_cara, int cant_bloques_por_pista, int bytes_por_bloque)
{
    this->nombre_disco = direccion_disco;
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
        vector<string> vec = splitRegistroEnElementos(linea);
        HDD.tipo = "HDD";
        HDD.id = vec[0];
        HDD.direccion = vec[1];
        HDD.capacidad_total = stoi(vec[2]);
        HDD.capacidad_usada = stoi(vec[3]);
        for (int i = 0; i < (cant_platos_por_disco * 2); i++)
        {
            getline(archivo, linea);
            vector<string> vec1 = splitRegistroEnElementos(linea);
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
                vector<string> vec2 = splitRegistroEnElementos(linea);
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
                    vector<string> vec3 = splitRegistroEnElementos(linea);
                    Espacio_HDD BLOQUE;
                    BLOQUE.tipo = "BLOQUE";
                    BLOQUE.id = vec3[0];
                    BLOQUE.direccion = vec3[1];
                    BLOQUE.capacidad_total = stoi(vec3[2]);
                    BLOQUE.capacidad_usada = stoi(vec3[3]);
                    BLOQUE.id_siguiente_bloque = vec3[4];

                    HDD.vector_espacios_hdd.back().vector_espacios_hdd.back().vector_espacios_hdd.push_back(BLOQUE); // Añadir BLOQUE a la última PISTA
                    // cout << "Añadido BLOQUE: " << BLOQUE.direccion << " a la PISTA: " << PISTA.direccion << endl; // Mensaje de depuración
                }
            }
        }

        archivo.close();
    }
    enlazarBloquesLinkeadosPorIdDeMetadata();
}

void Estructura_HDD::enlazarBloquesLinkeadosPorIdDeMetadata()
{
    for (auto &plato : HDD.vector_espacios_hdd)
    {
        for (auto &pista : plato.vector_espacios_hdd)
        {
            for (auto &bloque : pista.vector_espacios_hdd)
            {
                const string id_siguiente = bloque.id_siguiente_bloque;
                if (id_siguiente != "-")
                {
                    cout << id_siguiente << endl;
                    enlazarBloques(bloque, getReferenciaBloquePorID(id_siguiente));
                    cout << "Bloque siguiente: " << bloque.siguiente->direccion << endl; // Mensaje de depuración
                }
            }
        }
    }
}

Espacio_HDD &Estructura_HDD::getReferenciaBloquePorID(string id_bloque)
{ // Funciona Ok
    for (auto &plato : HDD.vector_espacios_hdd)
    {
        for (auto &pista : plato.vector_espacios_hdd)
        {
            for (auto &bloque : pista.vector_espacios_hdd)
            {
                if (bloque.id == id_bloque)
                {
                    //cout<<bloque.direccion<<endl;
                    return bloque;
                }
            }
        }
    }
    throw std::runtime_error("Bloque no encontrado");
}

void Estructura_HDD::enlazarBloques(Espacio_HDD &A, Espacio_HDD &B)
{ // Funciona Ok
    A.siguiente = &B;
    B.anterior = &A;
    A.id_siguiente_bloque = B.id;
    cout << "Se ligo el bloque " << B.anterior->direccion << " con el Bloque" << A.siguiente->direccion << endl;
    cout << "A id_siguiente_bloque " << A.id_siguiente_bloque << endl;
}

void Estructura_HDD::enlazarBloquesPorID(string id_A, string id_B)
{ // Funciona Ok
    enlazarBloques(
    getReferenciaBloquePorID(id_A),
    getReferenciaBloquePorID(id_B));
}

Espacio_HDD &Estructura_HDD::getReferenciaPrimerBloqueVacioDisponible()
{ // Funciona Ok
    for (auto &plato : HDD.vector_espacios_hdd)
    {
        for (auto &pista : plato.vector_espacios_hdd)
        {
            for (auto &bloque : pista.vector_espacios_hdd)
            {
                if (bloque.tipo == "BLOQUE" && bloque.capacidad_usada == 0)
                {
                    return bloque;
                }
            }
        }
    }
    return Espacio_HDD_no_encontrado;
}

void Estructura_HDD::llenarBloque(string id, int capacidad)
{
    getReferenciaBloquePorID(id).capacidad_usada = capacidad;
}

void Estructura_HDD::insertarTextoABloquePorID(string texto, string id_bloque)
{
    Espacio_HDD &Bloque = getReferenciaBloquePorID(id_bloque);
    insertarTextoABloque(texto, Bloque);
}

void Estructura_HDD::insertarTextoABloque(string texto, Espacio_HDD &Bloque)
{
    const int capacidad_disponible = Bloque.capacidad_total - Bloque.capacidad_usada;
    const int capacidad_a_ingresar = texto.size();
    const string direccion = Bloque.direccion;
    if (capacidad_a_ingresar > capacidad_disponible)
    {
        const string texto_a = texto.substr(0, capacidad_disponible + 1);
        const string texto_b = texto.substr(capacidad_disponible, capacidad_a_ingresar);
        ofstream archivo(direccion.c_str(), ios::app);
        if (archivo.is_open())
        {
            archivo << texto_a;
            archivo.close();
            Bloque.capacidad_usada += capacidad_disponible;
        }
        else
        {
            cerr << "No se pudo abrir el archivo." << endl;
        }
        if (Bloque.siguiente == nullptr)
        {
            cout << "No hay bloque ligado" << endl;
            enlazarBloques(Bloque, getReferenciaPrimerBloqueVacioDisponible());
            cout << "Bloque ligadazo";
        }
        insertarTextoABloque(texto_b, *Bloque.siguiente);
    }
    else
    {
        ofstream archivo(direccion.c_str(), ios::app);
        if (archivo.is_open())
        {
            archivo << texto;
            archivo.close();
            Bloque.capacidad_usada = Bloque.capacidad_usada + capacidad_a_ingresar;
        }
        else
        {
            cerr << "No se pudo abrir el archivo." << endl;
        }
    }
}