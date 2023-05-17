
template <class T>
Conjunto<T>::Conjunto():_raiz(nullptr),_size(0) {}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res = false;
    Nodo* actual = _raiz;
    while (actual != nullptr && !res){
        if(actual->valor == clave){
            res = true;
        }else{
            actual = clave > actual->valor ? actual->der : actual->izq;
        }
    }
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(!pertenece(clave)){
        //Buscamos donde insertar
        Nodo* actual = _raiz;
        Nodo* padre = nullptr;
        //Al finalizar el while padre sera el ultimo nodo de la busqueda
        while(actual != nullptr){
            padre = actual;
            actual = actual->valor > clave ? actual->izq : actual->der;
        }
        //Creamos el nodo nuevo a insertar con clave como valor
        Nodo* nuevo = new Nodo(clave);
        if(padre == nullptr){
            _raiz = nuevo;
        }else{
            if(padre->valor > clave){
                padre->izq = nuevo;
            }else{
                padre->der = nuevo;
            }
        }
        _size++;
    }
}

template <class T>
void Conjunto<T>::remover(const T&) {
    //assert(false);
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    //assert(false);
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;
    while(actual != nullptr){
        padre = actual;
        actual = actual->izq;
    }
    return padre->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;
    while(actual != nullptr){
        padre = actual;
        actual = actual->der;
    }
    return padre->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->_size;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    //assert(false);
}

