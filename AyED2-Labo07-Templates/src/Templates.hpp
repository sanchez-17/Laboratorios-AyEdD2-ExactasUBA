template<class T>
T cuadrado(T x){
    return x * x;
}

template<class Contenedor, class Elem>
bool contiene(Contenedor s, Elem c) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}

template<class Contenedor>
bool esPrefijo(Contenedor a, Contenedor b){
    bool res = true;
    if(a.size() <= b.size()){
        for(int i = 0;i<a.size();i++){
            res = res && a[i] == b[i];
        }
    }else{
        res = false;
    }
    return res;
}

template<class Contenedor, class Elem>
Elem maximo(Contenedor c){
    Elem max = c[0];
    for(Elem x:c){
        max = x>=max ? x : max;
    }
    return max;
}