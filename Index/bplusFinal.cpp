#include <bits/stdc++.h>

#include <iostream>
#include <utility>
#include <vector>
#include<tuple>
#include <algorithm>
using namespace std;
template< class T>
class Nodo{
    public:

        
        Nodo* padre;
        Nodo* siguiente;
        Nodo* atras;
        vector<T> claves;
        vector<T> valores;
        vector<Nodo*> hijos;

        bool esHoja;

        Nodo(Nodo *padre = nullptr, bool esHoja = false, Nodo* _atras = nullptr, Nodo* _siguiente = nullptr)
            : padre(padre), esHoja(esHoja), atras(_atras), siguiente(_siguiente) {
            if(_siguiente){
                _siguiente->atras = this;
            }
            if(_atras){
                _atras->siguiente = this;
            }
        }

        //int indiceDeHijo(T );
        //int indiceDeClave(T );
        //Nodo* getHijo(T);
        //void setHijo(T, vector<Nodo *>);

         
        int indiceDeHijo(T clave_){
            for(int i = 0; i< claves.size(); i++){
                if(clave_ <claves[i]){
                    return i;
                }
            }
            return claves.size();
        }

        int indiceDeClave(T clave_){
            for(int i = 0; i< claves.size(); i++){
                if(clave_ ==claves[i]){
                    return i;
                }
            }
            return -1;
        }

        Nodo* getHijo(T clave_){
            return hijos[indiceDeHijo(clave_)];
        }

        void setHijo(T clave_, vector<Nodo*> valor_){
            int i = indiceDeHijo(clave_);
            claves.insert(claves.begin() + i, clave_);
            hijos.erase(hijos.begin()+i);
            hijos.insert(hijos.begin() + i, valor_.begin(), valor_.end());
        }

        tuple<T, Nodo*, Nodo*> dividirInternos(){
            Nodo* izquierda = new Nodo(padre, false,nullptr, nullptr);
            int mitad = claves.size()/2;
            copy(claves.begin(), claves.begin()+mitad, back_inserter(izquierda->claves));
            copy(hijos.begin(), hijos.begin() + mitad + 1, back_inserter(izquierda->hijos));
            
            for(Nodo* hijo : izquierda->hijos){
                hijo->padre = izquierda;
            }

            T clave = claves[mitad];
            claves.erase(claves.begin(), claves.begin() + mitad + 1 );
            hijos.erase(hijos.begin(), hijos.begin() + mitad + 1);

            return make_tuple(clave,izquierda,this);
        }


        T get(T _clave){
            int index = indiceDeClave(_clave);
            if( index == -1){
                cout << "Clave = " << _clave << " no encontrada\n";
                return T();
            }
            return valores[index];
        }

        void set(T clave, T valor){
            int i = indiceDeHijo(clave);
            
            if(find(claves.begin(), claves.end(),clave) == claves.end()){
                
                claves.insert(claves.begin() + i, clave);
                
                valores.insert(valores.begin() + i, valor);
                
            }
            else {
                //cout<<"here 5";
                valores[i-1] = valor;
            }
        }


        tuple<T, Nodo*, Nodo*> dividirHoja(){
            Nodo* izquierda = new Nodo(padre, true, atras, this);
            int mitad = claves.size() / 2;

            izquierda->claves = vector<T>(claves.begin(), claves.begin() + mitad);
            izquierda->valores = vector<T>(valores.begin(), valores.begin() + mitad);

            claves.erase(claves.begin(), claves.begin() + mitad);
            valores.erase(valores.begin(), valores.begin() + mitad);

            return make_tuple(claves[0], izquierda, this);
        }


};


template <typename T>
class BPTree{
    public:
        Nodo<T>* raiz;
        int profundidad;
        int maxCapacidad;
        int minCapacidad;
        BPTree(int _maxCapacidad = 4){
            raiz = new Nodo<T>(nullptr, true, nullptr, nullptr);
            maxCapacidad = _maxCapacidad > 2? _maxCapacidad : 2;
            minCapacidad= maxCapacidad /2;
            profundidad = 0;
        }


        

        Nodo<T>* encontrarHoja( T clave){
            Nodo<T>* nodo = raiz;
            while (!nodo->esHoja){
                nodo = nodo->getHijo(clave);
            }
            return nodo;
            
        }

        T get(T clave ){
            return encontrarHoja(clave)->get(clave);
        }

        void set(T clave, T valor){
            Nodo<T>* hoja = encontrarHoja(clave);

            hoja->set(clave, valor);

            if( hoja -> claves.size() > maxCapacidad){

                insertar(hoja->dividirHoja());
            }
        }


        void insertar(tuple<T,Nodo<T> * ,Nodo<T> *> res){
            T clave = std::get<0>(res);

            Nodo<T>* izquierda = std::get<1>(res);
            Nodo<T>* derecha = std::get<2>(res);
            Nodo<T>* padre =derecha->padre;

            if(padre == nullptr){
                izquierda->padre = derecha->padre = raiz = new Nodo<T>(nullptr, false, nullptr, nullptr);
                profundidad +=1;
                raiz->claves  = {clave};
                raiz -> hijos = {izquierda, derecha};
                return;
            }

            padre->setHijo(clave,{izquierda,derecha});
            if(padre->claves.size() > maxCapacidad){
                insertar(padre->dividirInternos());
            }

        }


        void imprimirArbol(Nodo<T> *nodo = nullptr, string a="", bool b=true){
            if(!nodo)
                nodo = raiz;
            
            cout<<a<<"-->  [";
            for(int i = 0; i< nodo->claves.size(); i++){
                cout << nodo->claves[i];
                if(i!=nodo->claves.size() - 1){
                    cout << ",";
                }
            }

            cout << "]\n";
            a +=b? "   " : "    ";

            if(!nodo->esHoja){
                for (int i = 0; i < nodo->hijos.size(); i++){
                    bool b = (i == nodo->hijos.size()-1);
                    imprimirArbol(nodo->hijos[i], a,b);
                }
                
            }
            //cout<<endl<<endl;
        }

        //Eliminacion
        ////////////////////////////////////////////////////
        void eliminarDeHoja(T clave, Nodo<T> *nodo) {
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

        void eliminarDeInternos(T clave, Nodo<T> *nodo) {
            int indice = nodo->indiceDeClave(clave);
            if (indice != -1) {
                Nodo<T> *leftMostLeaf = nodo->hijos[indice + 1];
                while (!leftMostLeaf->esHoja)
                    leftMostLeaf = leftMostLeaf->hijos.front();

                nodo->claves[indice] = leftMostLeaf->claves.front();
            }
        }


        void clavePrestadaDeHojaDerecha(Nodo<T> *nodo, Nodo<T> *next) {
            nodo->claves.push_back(next->claves.front());
            next->claves.erase(next->claves.begin());
            nodo->valores.push_back(next->valores.front());
            next->valores.erase(next->valores.begin());
            for (int i = 0; i < nodo->padre->hijos.size(); i++) {
                if (nodo->padre->hijos[i] == next) {
                    nodo->padre->claves[i - 1] = next->claves.front();
                    break;
                }
            }
        }

        void clavePrestadaDeHojaIzquierda(Nodo<T> *node, Nodo<T> *prev) {
            node->claves.insert(node->claves.begin(), prev->claves.back());
            prev->claves.erase(prev->claves.end() - 1);
            node->valores.insert(node->valores.begin(), prev->valores.back());
            prev->valores.erase(prev->valores.end() - 1);
            for (int i = 0; i < node->padre->hijos.size(); i++) {
                if (node->padre->hijos[i] == node) {
                    node->padre->claves[i - 1] = node->claves.front();
                    break;
                }
            }
        }


        void fusionarNodoConHojaDerecha(Nodo<T> *node, Nodo<T> *next) {
            node->claves.insert(node->claves.end(), next->claves.begin(), next->claves.end());
            node->valores.insert(node->valores.end(), next->valores.begin(), next->valores.end());
            node->siguiente = next->siguiente;
            if (node->siguiente) node->siguiente->atras = node;
            for (int i = 0; i < next->padre->hijos.size(); i++) {
                if (node->padre->hijos[i] == next) {
                    node->padre->claves.erase(node->padre->claves.begin() + i - 1);
                    node->padre->hijos.erase(node->padre->hijos.begin() + i);
                    break;
                }
            }
        }


        void fusionarNodoConHojaIzquierda(Nodo<T> *node, Nodo<T> *prev) {
            prev->claves.insert(prev->claves.end(), node->claves.begin(), node->claves.end());
            prev->valores.insert(prev->valores.end(), node->valores.begin(), node->valores.end());
            prev->siguiente = node->siguiente;
            if (prev->siguiente) prev->siguiente->atras = prev;
            for (int i = 0; i < node->padre->hijos.size(); i++) {
                if (node->padre->hijos[i] == node) {
                    node->padre->claves.erase(node->padre->claves.begin() + i - 1);
                    node->padre->hijos.erase(node->padre->hijos.begin() + i);
                    break;
                }
            }
        }


        void clavePrestadaDeInternoDerecho(int posEnPadre, Nodo<T> *node, Nodo<T> *next) {
            node->claves.insert(node->claves.end(), node->padre->claves[posEnPadre]);
            node->padre->claves[posEnPadre] = next->claves.front();
            next->claves.erase(next->claves.begin());
            node->hijos.insert(node->hijos.end(), next->hijos.front());
            next->hijos.erase(next->hijos.begin());
            node->hijos.back()->padre = node;
        }


        void clavePrestadaDeInternoIzquierdo(int posEnPadre, Nodo<T> *node, Nodo<T> *prev) {
            node->claves.insert(node->claves.begin(), node->padre->claves[posEnPadre - 1]);
            node->padre->claves[posEnPadre - 1] = prev->claves.back();
            prev->claves.erase(prev->claves.end() - 1);
            node->hijos.insert(node->hijos.begin(), prev->hijos.back());
            prev->hijos.erase(prev->hijos.end() - 1);
            node->hijos.front()->padre = node;
        }


        void fusionarNodoConInternoDerecho(int posEnPadre, Nodo<T> *node, Nodo<T> *next) {
            node->claves.insert(node->claves.end(), node->padre->claves[posEnPadre]);
            node->padre->claves.erase(node->padre->claves.begin() + posEnPadre);
            node->padre->hijos.erase(node->padre->hijos.begin() + posEnPadre + 1);
            node->claves.insert(node->claves.end(), next->claves.begin(), next->claves.end());
            node->hijos.insert(node->hijos.end(), next->hijos.begin(), next->hijos.end());
            for (auto hijo : node->hijos)
                hijo->padre = node;
            
            /*node->claves.insert(node->claves.end(), node->padre->claves[posEnPadre]);
            node->claves.insert(node->claves.end(), next->claves.begin(), next->claves.end());
            node->hijos.insert(node->hijos.end(), next->hijos.begin(), next->hijos.end());
            for (auto hijo : next->hijos)
                hijo->padre = node;
            node->padre->claves.erase(node->padre->claves.begin() + posEnPadre);
            node->padre->hijos.erase(node->padre->hijos.begin() + posEnPadre + 1);*/
        }

        void fusionarNodoConInternoIzquierdo(int posEnPadre, Nodo<T> *node, Nodo<T> *prev) {
            prev->claves.insert(prev->claves.end(), node->padre->claves[posEnPadre - 1]);
            node->padre->claves.erase(node->padre->claves.begin() + posEnPadre - 1);
            node->padre->hijos.erase(node->padre->hijos.begin() + posEnPadre);
            prev->claves.insert(prev->claves.end(), node->claves.begin(), node->claves.end());
            prev->hijos.insert(prev->hijos.end(), node->hijos.begin(), node->hijos.end());
            for (auto hijo : prev->hijos)
                hijo->padre = prev;
            
        }

        void remove(T clave, Nodo<T> * node = nullptr) {
            if (node == nullptr){
                node = encontrarHoja(clave);
            }
            if (node->esHoja){
                eliminarDeHoja(clave, node);
            }else{
                eliminarDeInternos(clave, node);
            }

            if(node->claves.size() < minCapacidad){
                if(node == raiz){
                    if(raiz->claves.empty() && !raiz->hijos.empty()){
                        raiz = raiz->hijos[0];
                        raiz->padre = nullptr;
                        profundidad -=1;
                    }
                    return;
                }else if(node->esHoja){
                    Nodo<T>* _sig  = node->siguiente;
                    Nodo<T>* _atras = node->atras;

                    if(_sig && _sig->padre == node->padre && _sig->claves.size() > minCapacidad){
                        clavePrestadaDeHojaDerecha(node, _sig);
                    }else if(_atras && _atras->padre ==node->padre && _atras->claves.size()>minCapacidad){
                        clavePrestadaDeHojaIzquierda(node, _atras);
                    }else if(_sig && _sig->padre == node->padre && _sig->claves.size() <= minCapacidad){
                        fusionarNodoConHojaDerecha(node, _sig);
                    }else if(_atras && _atras->padre == node->padre && _atras->claves.size() <=minCapacidad){
                        fusionarNodoConHojaIzquierda(node,_atras);
                    }
                }else{
                    int posEnPadre =-1;
                    for(int i=0;i<node->padre->hijos.size(); i++){
                        if(node->padre->hijos[i] == node){
                            posEnPadre =i;
                            break;
                        }
                    }

                    Nodo<T>* _next;
                    Nodo<T>* _prev;

                    if(node->padre->hijos.size() > posEnPadre+1){
                        _next=node->padre->hijos[posEnPadre+1];
                    }else{
                        _next = nullptr;
                    }

                    if(posEnPadre){
                        _prev=node->padre->hijos[posEnPadre-1];
                    }else{
                        _prev =nullptr;
                    }

                    if(_next && _next->padre == node->padre && _next->claves.size() > minCapacidad){
                        clavePrestadaDeInternoDerecho(posEnPadre, node, _next);

                    }else if(_prev && _prev->padre == node->padre && _prev->claves.size() > minCapacidad){
                        clavePrestadaDeInternoIzquierdo(posEnPadre, node, _prev);
                    }else if(_next && _next->padre == node->padre && _next->claves.size() <= minCapacidad){
                        fusionarNodoConInternoDerecho(posEnPadre, node, _next);
                    }else if(_prev && _prev->padre == node->padre && _prev->claves.size() <= minCapacidad){
                        fusionarNodoConInternoIzquierdo(posEnPadre, node, _prev);
                    }
                }
            }
            if(node->padre){
                remove(clave,node->padre);
            }
            /*
            Nodo<T> *hoja = encontrarHoja(clave);
            eliminarDeHoja(clave, hoja);
            if (hoja->claves.size() < minCapacidad) {
                if (hoja->siguiente && hoja->siguiente->padre == hoja->padre && hoja->siguiente->claves.size() > minCapacidad) {
                    clavePrestadaDeHojaDerecha(hoja, hoja->siguiente);
                } else if (hoja->atras&& hoja->atras->padre == hoja->padre && hoja->atras->claves.size() > minCapacidad) {
                    clavePrestadaDeHojaIzquierda(hoja,hoja->atras);
                } else if (hoja->siguiente && hoja->siguiente->padre == hoja->padre) {
                    fusionarNodoConHojaDerecha(hoja, hoja->siguiente);
                } else if (hoja->atras && hoja->atras->padre == hoja->padre) {
                    fusionarNodoConHojaIzquierda(hoja, hoja->atras);
                }
            }*/
        }



        ////////////////////////////////////////////////////
        


};


template <typename T>
void generarDOT(Nodo<T>* nodo, ofstream& file, string idPadre = "") {
    if (!nodo) return;

    static int idCounter = 0;
    string idNodo = "node" + to_string(idCounter++);
    file << idNodo << " [label=\"";

    for (size_t i = 0; i < nodo->claves.size(); ++i) {
        file << nodo->claves[i];
        if (i != nodo->claves.size() - 1) {
            file << "|";
        }
    }

    file << "\"];\n";

    if (!idPadre.empty()) {
        file << idPadre << " -> " << idNodo << ";\n";
    }

    if (!nodo->esHoja) {
        for (size_t i = 0; i < nodo->hijos.size(); ++i) {
            generarDOT(nodo->hijos[i], file, idNodo);
        }
    }
}

template <typename T>
void guardarArbolEnDOT(BPTree<T>& tree, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        file << "digraph g {\n";
        file << "node [shape=record, height=.1];\n";
        
        Nodo<T>* raiz = tree.raiz; // Obtén la raíz del árbol
        generarDOT(raiz, file);

        file << "}\n";
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir.\n";
    }
}

int main(){
    BPTree<int> tree(4);
    //vector<int> x= {100, 75, 1,99,30,80,3, 40, 105,8,20,35, 60, 10, 30}; 




    //vector<int> x = {10,27,29,17,25,21,15,31,13,51,20,24,48,19,60,35,66};
    //vector<int> x = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
    //vector<int> x = {2,3,5,7,14,16,19,20,22,24,27,29,33,34,38,39};
    /*vector<int> x = {11150,11000,12150,10050,
    10150,16000,11000,15000,
    10880,10045,12540,16000,
    13200,11000,11000,11500,
    13421,17000,13421,11234,11000,
    11020,11000,11000,13421,
    15000,11150,10034,11500,
    11020,11234,13650,10150,
    13652,13652,10703,14590,
    16000,11000,14590,11000,
    10703,11000,15000,18001,
    13500,10111,10703,15000,10150};*/
    vector<int> x = {11150,11000,12150,10050,
    10150,16000,11000,15000};

    for(int i : x){
        cout<<"Insertando: "<<i<<endl;
        tree.set(i,i);
        //tree.imprimirArbol();
    }

    cout<<"Arbol B+Tree\n";
    tree.imprimirArbol();
    guardarArbolEnDOT(tree, "arbol.txt");
    tree.remove(15000);
    guardarArbolEnDOT(tree, "arbol.txt");


    /*cout<<"=====================================\n";
    tree.remove(17);
    tree.imprimirArbol();
    cout<<endl;
    tree.remove(20);
    tree.imprimirArbol();
    cout<<endl;
    tree.remove(15);
    tree.imprimirArbol();
    cout<<endl;
    tree.remove(19);
    tree.imprimirArbol();
    cout<<endl;
    tree.remove(24);
    cout<<"=====================================\n";
    tree.imprimirArbol();
    
    cout<<"=====================================\n\n";
    BPTree<string> arbol(4);
    vector<string> animals ={"pato", "vaca", "avestruz","zorro", "koala" };
    for (string i : animals) {
        cout<<"Insertando: "<<i<<endl;
        arbol.set(i, i);
    }
    arbol.imprimirArbol();*/
    return 0;

}