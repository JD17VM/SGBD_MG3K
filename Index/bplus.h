#include <bits/stdc++.h>
using namespace std;

template <class T>
class Nodo {
public:
    Nodo* padre;
    Nodo* siguiente;
    Nodo* atras;
    vector<T> claves;
    vector<vector<pair<T, pair<string, int>>>> valores; // Cambiado para manejar listas de valores con información adicional
    vector<Nodo*> hijos;
    bool esHoja;

    Nodo(Nodo* padre = nullptr, bool esHoja = false, Nodo* _atras = nullptr, Nodo* _siguiente = nullptr)
        : padre(padre), esHoja(esHoja), atras(_atras), siguiente(_siguiente) {
        if (_siguiente) {
            _siguiente->atras = this;
        }
        if (_atras) {
            _atras->siguiente = this;
        }
    }

    int indiceDeHijo(T clave_) {
        for (int i = 0; i < claves.size(); i++) {
            if (clave_ < claves[i]) {
                return i;
            }
        }
        return claves.size();
    }

    int indiceDeClave(T clave_) {
        for (int i = 0; i < claves.size(); i++) {
            if (clave_ == claves[i]) {
                return i;
            }
        }
        return -1;
    }

    Nodo* getHijo(T clave_) {
        return hijos[indiceDeHijo(clave_)];
    }

    void setHijo(T clave_, vector<Nodo*> valor_) {
        int i = indiceDeHijo(clave_);
        claves.insert(claves.begin() + i, clave_);
        hijos.erase(hijos.begin() + i);
        hijos.insert(hijos.begin() + i, valor_.begin(), valor_.end());
    }

    tuple<T, Nodo*, Nodo*> dividirInternos() {
        Nodo* izquierda = new Nodo(padre, false, nullptr, nullptr);
        int mitad = claves.size() / 2;
        copy(claves.begin(), claves.begin() + mitad, back_inserter(izquierda->claves));
        copy(hijos.begin(), hijos.begin() + mitad + 1, back_inserter(izquierda->hijos));
        
        for (Nodo* hijo : izquierda->hijos) {
            hijo->padre = izquierda;
        }

        T clave = claves[mitad];
        claves.erase(claves.begin(), claves.begin() + mitad + 1);
        hijos.erase(hijos.begin(), hijos.begin() + mitad + 1);

        return make_tuple(clave, izquierda, this);
    }

    vector<pair<T, pair<string, int>>> get(T _clave) {
        int index = indiceDeClave(_clave);
        if (index == -1) {
            cout << "Clave = " << _clave << " no encontrada\n";
            return vector<pair<T, pair<string, int>>>();
        }
        return valores[index];
    }

    void set(T clave, T valor, string dirPagina, int posicionRegistro) {
        int i = indiceDeHijo(clave);

        pair<T, pair<string, int>> nuevoValor = make_pair(valor, make_pair(dirPagina, posicionRegistro));

        if (find(claves.begin(), claves.end(), clave) == claves.end()) {
            claves.insert(claves.begin() + i, clave);
            valores.insert(valores.begin() + i, { nuevoValor });
        } else {
            int index = indiceDeClave(clave); // Encuentra el índice de la clave existente
            valores[index].push_back(nuevoValor); // Añadir el nuevo valor a la lista de valores
        }
    }

    tuple<T, Nodo*, Nodo*> dividirHoja() {
        Nodo* izquierda = new Nodo(padre, true, atras, this);
        int mitad = claves.size() / 2;

        izquierda->claves = vector<T>(claves.begin(), claves.begin() + mitad);
        izquierda->valores = vector<vector<pair<T, pair<string, int>>>>(valores.begin(), valores.begin() + mitad);

        claves.erase(claves.begin(), claves.begin() + mitad);
        valores.erase(valores.begin(), valores.begin() + mitad);

        return make_tuple(claves[0], izquierda, this);
    }
};

template <typename T>
class BPTree {
public:
    Nodo<T>* raiz;
    int profundidad;
    int maxCapacidad;
    int minCapacidad;

    BPTree(int _maxCapacidad = 4) {
        raiz = new Nodo<T>(nullptr, true, nullptr, nullptr);
        maxCapacidad = _maxCapacidad > 2 ? _maxCapacidad : 2;
        minCapacidad = maxCapacidad / 2;
        profundidad = 0;
    }

    Nodo<T>* encontrarHoja(T clave) {
        Nodo<T>* nodo = raiz;
        while (!nodo->esHoja) {
            nodo = nodo->getHijo(clave);
        }
        return nodo;
    }

    vector<pair<T, pair<string, int>>> get(T clave) {
        return encontrarHoja(clave)->get(clave);
    }

    void set(T clave, T valor, string dirPagina, int posicionRegistro) {
        Nodo<T>* hoja = encontrarHoja(clave);

        hoja->set(clave, valor, dirPagina, posicionRegistro);

        if (hoja->claves.size() > maxCapacidad) {
            insertar(hoja->dividirHoja());
        }
    }

    void insertar(tuple<T, Nodo<T>*, Nodo<T>*> res) {
        T clave = std::get<0>(res);

        Nodo<T>* izquierda = std::get<1>(res);
        Nodo<T>* derecha = std::get<2>(res);
        Nodo<T>* padre = derecha->padre;

        if (padre == nullptr) {
            izquierda->padre = derecha->padre = raiz = new Nodo<T>(nullptr, false, nullptr, nullptr);
            profundidad += 1;
            raiz->claves = { clave };
            raiz->hijos = { izquierda, derecha };
            return;
        }

        padre->setHijo(clave, { izquierda, derecha });
        if (padre->claves.size() > maxCapacidad) {
            insertar(padre->dividirInternos());
        }
    }

    void imprimirArbol(Nodo<T>* nodo = nullptr, string a = "", bool b = true) {
        if (!nodo)
            nodo = raiz;

        cout << a << "-->  [";
        for (int i = 0; i < nodo->claves.size(); i++) {
            cout << nodo->claves[i];
            if (i != nodo->claves.size() - 1) {
                cout << ",";
            }
        }

        cout << "]\n";
        a += b ? "   " : "    ";

        if (!nodo->esHoja) {
            for (int i = 0; i < nodo->hijos.size(); i++) {
                bool b = (i == nodo->hijos.size() - 1);
                imprimirArbol(nodo->hijos[i], a, b);
            }
        } else {
            // Imprimir hojas con valores
            for (int i = 0; i < nodo->valores.size(); i++) {
                cout << a << "\t\tClave " << nodo->claves[i] << "  [";
                for (int j = 0; j < nodo->valores[i].size(); j++) {
                    cout << nodo->valores[i][j].first << " (Pag: " << nodo->valores[i][j].second.first << ", Pos: " << nodo->valores[i][j].second.second << ")";
                    if (j != nodo->valores[i].size() - 1) {
                        cout << ",";
                    }
                }
                cout << "]\n";
            }
        }
    }


    

    //Eliminacion
    ////////////////////////////////////////////////////
    void eliminarDeHoja(T clave, Nodo<T>* nodo) {
        int indice = nodo->indiceDeClave(clave);
        if (indice == -1) {
            cout << "clave " << clave << " not encontrada! fin ..." << endl;
            exit(0);
        }
        nodo->claves.erase(nodo->claves.begin() + indice);
        nodo->valores.erase(nodo->valores.begin() + indice);
        if (nodo->padre) {
            int indiceEnPadre = nodo->padre->indiceDeHijo(clave);
            if (indiceEnPadre)
                nodo->padre->claves[indiceEnPadre - 1] = nodo->claves.front();
        }
    }

    void eliminarDeInternos(T clave, Nodo<T>* nodo) {
        int indice = nodo->indiceDeClave(clave);
        if (indice != -1) {
            Nodo<T>* leftMostLeaf = nodo->hijos[indice + 1];
            while (!leftMostLeaf->esHoja)
                leftMostLeaf = leftMostLeaf->hijos.front();

            nodo->claves[indice] = leftMostLeaf->claves.front();
        }
    }

    void clavePrestadaDeHojaDerecha(Nodo<T>* nodo, Nodo<T>* next) {
        nodo->claves.push_back(next->claves.front());
        nodo->valores.push_back(next->valores.front());
        next->claves.erase(next->claves.begin());
        next->valores.erase(next->valores.begin());

        if (nodo->padre) {
            int indiceEnPadre = nodo->padre->indiceDeHijo(nodo->claves.front());
            if (indiceEnPadre)
                nodo->padre->claves[indiceEnPadre - 1] = nodo->claves.front();
        }
    }

    void clavePrestadaDeHojaIzquierda(Nodo<T>* nodo, Nodo<T>* prev) {
        nodo->claves.insert(nodo->claves.begin(), prev->claves.back());
        nodo->valores.insert(nodo->valores.begin(), prev->valores.back());
        prev->claves.pop_back();
        prev->valores.pop_back();

        if (nodo->padre) {
            int indiceEnPadre = nodo->padre->indiceDeHijo(nodo->claves.front());
            if (indiceEnPadre)
                nodo->padre->claves[indiceEnPadre - 1] = nodo->claves.front();
        }
    }

    void clavePrestadaDeInternoIzquierda(Nodo<T>* nodo, Nodo<T>* prev) {
        nodo->claves.insert(nodo->claves.begin(), nodo->padre->claves.back());
        nodo->padre->claves.back() = prev->claves.back();
        prev->claves.pop_back();
        nodo->hijos.insert(nodo->hijos.begin(), prev->hijos.back());
        prev->hijos.pop_back();
        nodo->hijos.front()->padre = nodo;
    }

    void clavePrestadaDeInternoDerecha(Nodo<T>* nodo, Nodo<T>* next) {
        nodo->claves.push_back(nodo->padre->claves.front());
        nodo->padre->claves.front() = next->claves.front();
        next->claves.erase(next->claves.begin());
        nodo->hijos.push_back(next->hijos.front());
        next->hijos.erase(next->hijos.begin());
        nodo->hijos.back()->padre = nodo;
    }

    void fusionarHojas(Nodo<T>* nodo, Nodo<T>* next) {
        nodo->claves.insert(nodo->claves.end(), next->claves.begin(), next->claves.end());
        nodo->valores.insert(nodo->valores.end(), next->valores.begin(), next->valores.end());
        nodo->siguiente = next->siguiente;
        if (next->siguiente)
            next->siguiente->atras = nodo;
        next->claves.clear();
        next->valores.clear();
    }

    void fusionarInternos(Nodo<T>* nodo, Nodo<T>* next) {
        nodo->claves.push_back(nodo->padre->claves.front());
        nodo->claves.insert(nodo->claves.end(), next->claves.begin(), next->claves.end());
        nodo->hijos.insert(nodo->hijos.end(), next->hijos.begin(), next->hijos.end());
        for (Nodo<T>* hijo : next->hijos)
            hijo->padre = nodo;
        next->claves.clear();
        next->hijos.clear();
    }

    void actualizarRaiz(Nodo<T>* nodo) {
        if (raiz->claves.empty()) {
            raiz = nodo;
            raiz->padre = nullptr;
            profundidad -= 1;
        }
    }

    void merge(Nodo<T>* nodo) {
        if (nodo->padre == nullptr) {
            actualizarRaiz(nodo);
            return;
        }
        if (nodo->padre) {
            if (nodo->padre->hijos.front() != nodo) {
                int indice = nodo->padre->indiceDeHijo(nodo->claves.front());
                Nodo<T>* prev = nodo->padre->hijos[indice - 1];

                if (nodo->esHoja) {
                    if (prev->claves.size() > minCapacidad) {
                        clavePrestadaDeHojaIzquierda(nodo, prev);
                    } else {
                        fusionarHojas(prev, nodo);
                        nodo->padre->claves.erase(nodo->padre->claves.begin() + indice - 1);
                        nodo->padre->hijos.erase(nodo->padre->hijos.begin() + indice);
                        actualizarRaiz(prev);
                        merge(prev);
                    }
                } else {
                    if (prev->claves.size() > minCapacidad) {
                        clavePrestadaDeInternoIzquierda(nodo, prev);
                    } else {
                        fusionarInternos(prev, nodo);
                        nodo->padre->claves.erase(nodo->padre->claves.begin() + indice - 1);
                        nodo->padre->hijos.erase(nodo->padre->hijos.begin() + indice);
                        actualizarRaiz(prev);
                        merge(prev);
                    }
                }
            } else {
                Nodo<T>* next = nodo->padre->hijos[1];
                if (nodo->esHoja) {
                    if (next->claves.size() > minCapacidad) {
                        clavePrestadaDeHojaDerecha(nodo, next);
                    } else {
                        fusionarHojas(nodo, next);
                        nodo->padre->claves.erase(nodo->padre->claves.begin());
                        nodo->padre->hijos.erase(nodo->padre->hijos.begin() + 1);
                        actualizarRaiz(nodo);
                        merge(nodo);
                    }
                } else {
                    if (next->claves.size() > minCapacidad) {
                        clavePrestadaDeInternoDerecha(nodo, next);
                    } else {
                        fusionarInternos(nodo, next);
                        nodo->padre->claves.erase(nodo->padre->claves.begin());
                        nodo->padre->hijos.erase(nodo->padre->hijos.begin() + 1);
                        actualizarRaiz(nodo);
                        merge(nodo);
                    }
                }
            }
        }
    }

    void eliminar(T clave, Nodo<T>* nodo = nullptr) {
        nodo = nodo ? nodo : raiz;
        if (nodo->esHoja) {
            eliminarDeHoja(clave, nodo);
        } else {
            eliminarDeInternos(clave, nodo);
            eliminar(clave, nodo->getHijo(clave));
        }

        if (nodo->claves.size() < minCapacidad) {
            merge(nodo);
        }
    }






    void guardarArbolEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            guardarArbolEnArchivo(archivo, raiz);
            archivo.close();
        } else {
            cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        }
    }

    void guardarArbolEnArchivo(ofstream& archivo, Nodo<T>* nodo, string a = "", bool b = true) {
        if (!nodo)
            return;

        //archivo << a << "-->  [";
        for (int i = 0; i < nodo->claves.size(); i++) {
            //archivo << nodo->claves[i];
            if (i != nodo->claves.size() - 1) {
                //archivo << ",";
            }
        }

        //archivo << "]\n";
        a += b ? "   " : "    ";

        if (!nodo->esHoja) {
            for (int i = 0; i < nodo->hijos.size(); i++) {
                bool b = (i == nodo->hijos.size() - 1);
                guardarArbolEnArchivo(archivo, nodo->hijos[i], a, b);
            }
        } else {
            // Imprimir hojas con valores
            for (int i = 0; i < nodo->valores.size(); i++) {
                //archivo << "Clave " << nodo->claves[i] << "  [";
                archivo <<  nodo->claves[i] << " ";
                for (int j = 0; j < nodo->valores[i].size(); j++) {
                    //archivo << nodo->valores[i][j].first << " (Pag: " << nodo->valores[i][j].second.first << ", Pos: " << nodo->valores[i][j].second.second << ")";
                    archivo << nodo->valores[i][j].second.first << "," << nodo->valores[i][j].second.second << "|";
                    if (j != nodo->valores[i].size() - 1) {
                        //archivo << ",";
                    }
                }
                //archivo << "]\n";
                archivo << "\n";
            }
        }
    }
};

/*
int main() {
    BPTree<int> arbol(4);


    string dir = "Bloque.txt";
    arbol.set(11150, 11150, dir, 1);
    arbol.set(11000, 11000, dir, 2);
    arbol.set(12150, 12150, dir, 3);
    arbol.set(10050, 10050, dir, 4);
    arbol.set(10150, 10150, dir, 1);
    arbol.set(16000, 16000, dir, 2);
    arbol.set(11000, 11000, dir, 3);
    arbol.set(15000, 15000, dir, 4);
    arbol.set(10880, 10880, dir, 1);
    arbol.set(10045, 10045, dir, 2);
    arbol.set(12540, 12540, dir, 3);
    arbol.set(16000, 16000, dir, 4);
    arbol.set(13200, 13200, dir, 1);
    arbol.set(11000, 11000, dir, 2);
    arbol.set(11000, 11000, dir, 3);
    arbol.set(11500, 11500, dir, 4);
    arbol.set(13421, 13421, dir, 1);
    arbol.set(17000, 17000, dir, 2);
    arbol.set(13421, 13421, dir, 3);
    arbol.set(11234, 11234, dir, 4);
    arbol.set(11000, 11000, dir, 1);
    arbol.set(11020, 11020, dir, 2);
    arbol.set(11000, 11000, dir, 3);
    arbol.set(11000, 11000, dir, 4);
    arbol.set(13421, 13421, dir, 1);
    arbol.set(15000, 15000, dir, 2);
    arbol.set(11150, 11150, dir, 3);
    arbol.set(10034, 10034, dir, 4);
    arbol.set(11500, 11500, dir, 1);
    arbol.set(11020, 11020, dir, 2);
    arbol.set(11234, 11234, dir, 3);
    arbol.set(13650, 13650, dir, 4);
    arbol.set(10150, 10150, dir, 1);
    arbol.set(13652, 13652, dir, 2);
    arbol.set(13652, 13652, dir, 3);
    arbol.set(10703, 10703, dir, 4);
    arbol.set(14590, 14590, dir, 3847);
    arbol.set(16000, 16000, dir, 7591);
    arbol.set(11000, 11000, dir, 3459);
    arbol.set(14590, 14590, dir, 9123);
    arbol.set(11000, 11000, dir, 7812);
    arbol.set(10703, 10703, dir, 9182);
    arbol.set(11000, 11000, dir, 2834);
    arbol.set(15000, 15000, dir, 8347);
    arbol.set(18001, 18001, dir, 7518);
    arbol.set(13500, 13500, dir, 2839);
    arbol.set(10111, 10111, dir, 9814);
    arbol.set(10703, 10703, dir, 8932);
    arbol.set(15000, 15000, dir, 7685);
    arbol.set(10150, 10150, dir, 5678);

    cout << "Arbol B+Tree\n";
    arbol.imprimirArbol();
    arbol.guardarArbolEnArchivo("index.txt");

    
    return 0;
}*/