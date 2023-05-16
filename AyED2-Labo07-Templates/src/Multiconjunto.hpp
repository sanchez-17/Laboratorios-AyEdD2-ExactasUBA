#include "Diccionario.hpp"

template<class T>
class Multiconjunto{
public:
    Multiconjunto();
    void agregar(T x);
    int ocurrencias(T x) const;
private:
    struct Ocurrencia{
        Ocurrencia(T x, int c);
        T valor;
        int cantidad;
    };

};

template