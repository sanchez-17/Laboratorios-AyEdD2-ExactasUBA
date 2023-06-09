#ifndef TAXONOMIA_H_
#define TAXONOMIA_H_

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Taxonomia {
public:

    // Para construir una taxonomía, debe estar implementada la función:
    //   istream& operator>>(istream&, T&).
    // que lee un elemento de tipo T.

    // Constructores y mostrar (ya implementados por la cátedra)
    Taxonomia(const string&);
    ~Taxonomia();
    void mostrar(ostream&) const;
private:
        struct Nodo {
        T valor;
        vector<Nodo*> hijos;
        };

    // Invariante:
    // (1) _raiz != NULL
    // (2) para todo 0 <= i < _raiz->hijos.size():
    //     (2.1) _raiz->hijos[i] != NULL
    //     (2.2) el invariante se cumple recursivamente
    //           para _raiz->hijos[i]
        Nodo* _raiz;

    // Métodos auxiliares de taxonomía (ya implementados por la cátedra).
    void _borrar(Nodo*);
    int _espiarProximoCaracter(istream& is) const;
    Nodo* _leerDe(istream& is);
    void _identar(ostream& os, int tab) const;
    void _mostrarEn(ostream&, Nodo*, int) const;

public:
    // Iteradores (para completar la implementación)
    class iterator {
        // Permite que los métodos de Taxonomia<T>
        // accedan a la parte privada de iterator.
        friend class Taxonomia<T>;
    public:

        // Referencia mutable al nombre de la categoría actual.
        // Pre: el iterador está posicionado sobre una categoría.
        T& operator*() const;

        // Cantidad de subcategorías de la categoría actual.
        // Pre: el iterador está posicionado sobre una categoría.
        int cantSubcategorias() const;

        // Ubica el iterador sobre la i-ésima subcategoría.
        // Pre: el iterador está posicionado sobre una categoría
        // y además 0 <= i < cantSubcategorias().
        void subcategoria(int i);

        // Devuelve true sii la categoría actual es la raíz.
        // Pre: el iterador está posicionado sobre una categoría.
        bool esRaiz() const;

        // Ubica el iterador sobre la supercategoría de la categoría
        // actual.
        // Pre: el iterador está posicionado sobre una categoría
        // y además !esRaiz().
        void supercategoria();

        // Compara dos iteradores por igualdad.
        // Pre: deben ser dos iteradores de la misma taxonomía.
        bool operator==(const iterator& otro) const;

        // Ubica el iterador sobre la categoría siguiente a la actual
        // en el recorrido *preorder* de la taxonomía.
        // Si se trata de la última categoría de la taxonomía,
        // el iterador resultante debe ser igual al iterador end()
        // de la taxonomía.
        // Pre: el iterador está posicionado sobre una categoría.
        void operator++();

        // Ubica el iterador sobre la categoría anterior a la actual
        // en el recorrido *preorder* de la taxonomía.
        // Si se trata de la raíz de la taxonomía el iterador
        // resultante debe ser igual al iterador end() de la taxonomía.
        // Pre: el iterador está posicionado sobre una categoría.
        void operator--();

        // Inserta una subcategoría con el nombre indicado
        // en el lugar i-ésimo.
        // Observación: esta operación modifica la taxonomía y
        // puede invalidar otros iteradores.
        // Pre: el iterador está posicionado sobre una categoría,
        // y además 0 <= i <= cantSubcategorias().
        void insertarSubcategoria(int i, const T& nombre);

        // Elimina la categoría actual de la taxonomía
        // (y recursivamente todas sus subcategorías).
        // El iterador queda ubicado sobre la supercategoría de
        // la categoría actual.
        // Observación: esta operación modifica la taxonomía y
        // puede invalidar otros iteradores. Debe encargarse de
        // liberar la memoria.
        // Pre: el iterador está posicionado sobre una categoría,
        // y además !esRaiz().
        void eliminarCategoria();

    private:
        // Constructor por defecto del iterador.
        // (Nota: puede construir un iterador inválido).
        iterator();

        // COMPLETAR
    };

    // Devuelve un iterador válido al principio de la taxonomía.
    iterator begin();

    // Devuelve un iterador válido al final de la taxonomía.
    iterator end();

};

template<class T>
ostream& operator<<(ostream& os, const Taxonomia<T>& taxonomia) {
     taxonomia.mostrar(os);
     return os;
}

#include "Taxonomia.hpp"

#endif // TAXONOMIA_H_
