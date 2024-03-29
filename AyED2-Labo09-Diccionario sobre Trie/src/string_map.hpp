template <typename T>
string_map<T>::string_map() : _size(0), _raiz(nullptr){}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    //borramos todo lo que habia antes y creamos un nuevo nodo a partir del cual vamos a copiar
    borrarDesde(_raiz);
    _raiz = new Nodo();
    _size = d.size();
    if(d.size() > 0) copiarDesde(_raiz,d._raiz);
    return *this;
//    buscarYCopiarSignificado(this,d._raiz,"");
}

template<typename T>
void string_map<T>::copiarDesde(Nodo* n,Nodo* d){
    for(int i = 0;i<255;i++){
        //Si el nodo siguiente es valido, creo un nuevo nodo copia de este
        if(d->siguientes[i] != nullptr){
            Nodo* nuevo = new Nodo();
            if(d->siguientes[i]->definicion != nullptr){
                T* def = new T(*d->siguientes[i]->definicion);
                nuevo->definicion = def;
            }
            n->siguientes[i] = nuevo;
            copiarDesde(n->siguientes[i],d->siguientes[i]);
        }
    }

}

/*
template<typename T>
void string_map<T>::buscarYCopiarSignificado(string_map<T>* s,Nodo* p,string clave){
    if(clave == "")this->_raiz = p;
    if(p== nullptr)return;
    if(p->definicion != nullptr){
        pair<string, T> t = make_pair(clave,*p->definicion);
        this->insert(t);
    }
    for (int i=97;i<123;i++){
        if(cantHijos(p)!=0){
            buscarYCopiarSignificado(this,p->siguientes[i],clave + char(i));
        }
    }
}
 */

template <typename T>
string_map<T>::~string_map(){
    borrarDesde(_raiz);
    _size = 0;
    _raiz = nullptr;
}

template <typename T>
void string_map<T>::borrarDesde(Nodo* nodo){
    if(nodo == nullptr)return;
    if(nodo->definicion != nullptr)delete nodo->definicion;
    for(Nodo* p: nodo->siguientes){
        borrarDesde(p);
    }
    delete nodo;
}


template <typename T>
void string_map<T>::insert(const pair<string, T>& t){
    //recorremos el trie hasta hallar la clave completa
    if(_raiz == nullptr) _raiz = new Nodo;
    Nodo* actual = _raiz;
    //Recorremos el trie, si el nodo no esta definido. Lo creamos
    for(char c:t.first){
        if(actual->siguientes[c] == nullptr) actual->siguientes[c] = new Nodo;
        actual = actual->siguientes[c];
    }
    //LLegamos a la clave buscada, si el significado no esta definido. Lo definimos
    if(actual->definicion == nullptr) actual->definicion = new T;
    *(actual->definicion) = t.second;
    _size++;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){}

template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* actual = _raiz;
    //Empezamos la raiz como nodo actual, si no esta definida devolvemos false
    if(actual == nullptr)return 0;
    //recorremos el trie mirando cada caracter de la clave
    for(char c:clave){
        //Si en siguiente del nodo actual el caracter apunta a nullptr, false. Sino consideramos el siguiente caracter de la clave y vemos el nodo al que apunta en siguientes
        if(actual->siguientes[c] == nullptr){
            return 0;
        }else{
            actual = actual->siguientes[c];
        }
    }
    //Llegamos al nodo buscado, la clave esta definida si el significado esta defindida
    return actual->definicion != nullptr ? 1 : 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = _raiz;
    for(char c:clave){
        actual = actual->siguientes[int(c)];
    }
    const Nodo* definicion = actual->definicion;
    return definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = _raiz;
    for(char c:clave){
        actual = actual->siguientes[c];
    }
    return *(actual->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* ultNodo = _raiz;
    Nodo* actual = _raiz;
    int ultIndice = 0;
    //Buscamos el nodo que representa la clave y lo guardo en actual
    for(int i=0;i<clave.length();i++){
        if(actual->definicion != nullptr || cantHijos(actual) > 1){
            ultNodo = actual;
            ultIndice = i;
        }
        actual = actual->siguientes[clave[i]];
    }
    //actual es el nodo de la clave, borramos su significado. ultNodo es el nodo que no hay que borrar.
    delete (actual->definicion);
    actual->definicion = nullptr;
    _size--;

    //Si actual no tiene hijos, borramos los descendientes del ultimo nodo.
    if(cantHijos(actual) == 0){
        //siguiente apunta al hijo del ultimo nodo siguiendo la clave
        Nodo* siguiente = ultNodo->siguientes[clave[ultIndice]];
        ultIndice++;
        //desvinculamos el ultimo nodo valido
        ultNodo->siguientes[clave[ultIndice-1]] = nullptr;

        ultNodo = siguiente;
        while(ultIndice<clave.length()){
            siguiente = ultNodo->siguientes[clave[ultIndice]];
            ultIndice++;
            delete ultNodo;
            ultNodo = siguiente;
        }
        delete ultNodo;
    }
}

template <typename T>
int string_map<T>::cantHijos(Nodo* n){
    int res = 0;
    for(Nodo* p:n->siguientes){
        res = p != nullptr ? res + 1 : res;
    }
    return res;
}
template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _raiz == nullptr;
}