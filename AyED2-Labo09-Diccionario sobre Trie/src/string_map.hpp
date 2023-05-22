template <typename T>
string_map<T>::string_map() : _size(0), _raiz(new Nodo){}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
}

template <typename T>
string_map<T>::~string_map(){

}
template <typename T>
void string_map<T>::insert(const pair<string, T>& t){
    //recorremos el trie hasta hallar la clave completa
    if(_raiz == nullptr) _raiz = new Nodo; _size++;
    Nodo* actual = _raiz;
    //Recorremos el trie, si el nodo no esta definido. Lo creamos
    for(char c:t.first){
        if(actual->siguientes[c] == nullptr){
            actual->siguientes[c] = new Nodo;
            _size++;
        }else{
            actual = actual->siguientes[c];
        }
    }
    //LLegamos a la clave buscada, si el significado no esta definido. Lo definimos
    if(actual->definicion == nullptr) actual->definicion = new T;
    *(actual->definicion) = t.second;
}


template <typename T>
T& string_map<T>::operator[](const string& clave){}

template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* actual = _raiz;
    //Empezamos la raiz como nodo actual, si no esta definida devolvemos false
    if(actual == nullptr)return 0;
    //recorremos el trie mirando cada caracter de la clave
    for(char i:clave){
        //Si en siguiente del nodo actual el caracter apunta a nullptr, false. Sino consideramos el siguiente caracter de la clave y vemos el nodo al que apunta en siguientes
        if(actual->siguientes[int(i)] == nullptr){
            return 0;
        }else{
            actual = actual->siguientes[int(i)];
        }
    }
    //Llegamos al nodo buscado, la clave esta definida si el significado esta defindida
    if(actual->definicion != nullptr){
            return 1;
        }else{
            return 0;
        }
    }
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
    // COMPLETAR
}

template <typename T>
int string_map<T>::size() const{
    // COMPLETAR
}

template <typename T>
bool string_map<T>::empty() const{
    // COMPLETAR
}