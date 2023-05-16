#include "Lista.h"
#include <cassert>

Lista::Lista():_primero(nullptr),_ultimo(nullptr),_size(0) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    destruirNodos();
}

Lista& Lista::operator=(const Lista& aCopiar) {
    destruirNodos();
    copiarNodos(aCopiar);
    _size = aCopiar._size;
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new Nodo(elem);
    if(_primero == nullptr){
        nuevo->sig = _primero;
        _primero = nuevo;
        _ultimo = nuevo;
    }else{
        nuevo->sig = _primero;
        _primero = nuevo;
    }
    _size++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo(elem);
    if(_primero != nullptr){
        nuevo->prev = _ultimo;
        _ultimo = nuevo;
        nuevo->prev->sig = nuevo;
    }else{
        _primero = nuevo;
        _ultimo = nuevo;
    }
    _size++;
}

void Lista::eliminar(Nat i) {
    Nodo* actual = _primero;
    //Me posiciono en el nodo a eliminar
    for(int j=0;j<i;j++){
        actual = actual->sig;
    }
    //Desvinculo el nodo a eliminar
    if( i!=0){
        actual->prev->sig = actual->sig;
    }
    else{
        _primero = actual->sig;
    }
    delete actual;
    _size--;
}

int Lista::longitud() const {
    return _size;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* actual = _primero;
    for(int j=0;j<i;j++){
        actual = actual->sig;
    }
    return actual->valor;
}

int& Lista::iesimo(Nat i) {
    Nodo* actual = _primero;
    for(int j=0;j<i;j++){
        actual = actual->sig;
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    // Completar
}

void Lista::copiarNodos(const Lista &o) {
    Nodo* actual = o._primero;
    while(actual != nullptr){
        agregarAtras(actual->valor);
        actual = actual->sig;
    }
}

void Lista::destruirNodos() {
    Nodo* actual = _primero;
    while(actual != nullptr){
        Nodo* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
    _primero = nullptr;
    _ultimo = nullptr;
}