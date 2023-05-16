template <typename T>
string_map<T>::string_map() : _size(0), raiz(nullptr){

}

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
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if( raiz == nullptr){
        return 0;
    }else{
        Nodo* actual =raiz;
        for(char i:clave){
            if(actual->siguientes[int(i)] == nullptr){
                return 0;
            }else{
                actual = actual->siguientes[int(i)];
            }
        }
        if(actual->definicion != nullptr){
            return 1;
        }else{
            return 0;
        }
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // COMPLETAR
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