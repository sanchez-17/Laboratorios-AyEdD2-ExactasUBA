#include <sstream>

template <class T>
Conjunto<T>::Conjunto():_raiz(nullptr) {}

template <class T>
Conjunto<T>::~Conjunto() { 
    destruirDesde(_raiz);
}

template<class T>
void Conjunto<T>::destruirDesde(Nodo* nodo){
    if(nodo != nullptr){
        destruirDesde(nodo->izq);
        destruirDesde(nodo->der);
        delete nodo;
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = _raiz;
    while (actual != nullptr && actual->valor != clave){
        actual = clave > actual->valor ? actual->der : actual->izq;
    }
    return !(actual == nullptr);
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(pertenece(clave)) return;
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
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    //Nos posicionamos en el nodo que contiene al elemento y referenciamos al padre
    if(!pertenece(clave)) return;

    Nodo* actual = _raiz;
    Nodo* padre = nullptr;

    //Busco el elemento a eliminar y lo guardo en actual
    while(actual->valor != clave){
        padre = actual;
        actual = actual->valor < clave ? actual->der : actual->izq;
    }

    //si tiene 2 hijos
    if(actual->izq != nullptr && actual->der != nullptr){
        //Intercambiamos valores del predecesor con actual, ó sucesor con actual. A eleccion del consumidor: buscaremos el min.
        Nodo* pred = actual->izq;
        while (pred->der != nullptr){
            pred = pred->der;
        }
        T pred_inmediato = pred->valor;
        remover(pred_inmediato);
        actual->valor = pred_inmediato;
    }//nodo actual tiene tiene 1 hijo
    else if(actual->izq != nullptr || actual->der != nullptr){
        Nodo* hijo = actual->izq != nullptr ? actual->izq : actual->der;
        //caso es raiz y tiene un hijo, padre es nullptr
        if(actual == _raiz){
            _raiz = hijo;
        }else{//no es raiz
            if(padre->der != nullptr && padre->der->valor == clave){
                padre->der = hijo;
            }else{
                padre->izq = hijo;
            }
        }
        delete actual;
    }
    else{//nodo actual es hoja
        if(actual == _raiz){//Si es la raiz
            _raiz = nullptr;
        }else{
            if(padre->der == actual){
                padre->der = nullptr;
            }
            else{
                padre->izq=nullptr;
            }
        }
        delete actual;
    }
}


template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* actual = _raiz;
    T* siguiente = &_raiz->valor;
    //Busco el elemento a  lo guardo en actual
    while(actual->valor != clave){
        siguiente = actual->valor > clave ? &actual->valor : siguiente;
        actual = actual->valor < clave ? actual->der : actual->izq;
    }
    //Si tiene hijo derecho
    if(actual->der != nullptr){
        actual = actual->der;
        while(actual->izq != nullptr){
            actual = actual->izq;
        }
        siguiente = &actual->valor;
    }

    return *siguiente;
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
    return _cardinal(0,_raiz);
}

template <class T>
unsigned int Conjunto<T>::_cardinal(int count, Nodo* n) const{
    if(n == nullptr){
        return 0;
    }else{
        return count + _cardinal(count,n->izq) + _cardinal(count,n->der) + 1;
    }
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
    //Mostramos los elementos en orden
    mostrarRecursivo(os, _raiz);
}

template <class T>
void Conjunto<T>::mostrarRecursivo(std::ostream& os, Nodo* nodo) const {
    if (nodo != nullptr) {
        // Recorrido in-order: primero mostramos el subarbol izquierdo,
        // luego el nodo actual y finalmente el subarbol derecho
        mostrarRecursivo(os, nodo->izq);
        os << nodo->valor << " ";
        mostrarRecursivo(os, nodo->der);
    }
}