
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
void Conjunto<T>::remover(const T& clave) {
    //Pre: el elemento existe en el conjunto
    //Nos posicionamos en el nodo que contiene al elemento y referenciamos al padre
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;
    while(actual->valor != clave){
        padre = actual;
        actual = actual->valor < clave ? actual->der : actual->izq;
    }
    //Si el nodo a borrar es hoja:
    if(actual->izq == nullptr & actual->der == nullptr){
        if(padre->der->valor == clave){
            padre->der = nullptr;
            delete actual;
        }
        else{
            padre->izq=nullptr;
            delete actual;
        }
    }else{
        //El padre del nodo tiene un hijo
        if(hijos(p))

    }
    _size--;
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
    //return _cardinal(0,_raiz); //solucion recursiva
    return this->_size;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    //assert(false);
}

/*
template <class T>
unsigned int Conjunto<T>::_cardinal(int count, Nodo* n) const{
    if(n->valor == nullptr){
        return 0;
    }else{
        return count + _cardinal(count,n->izq) + _cardinal(count,n->der) + 1;
    }
}
*/
template <class T>
unsigned int Conjunto<T>:: _hijosInmediatos(Nodo* n) const{
    unsigned int cant = 0;
    cant = n->der != nullptr ? cant + 1 : cant;
    cant = n->izq != nullptr ? cant + 1: cant;
    return cant;
}