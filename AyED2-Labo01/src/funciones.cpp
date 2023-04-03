#include <vector>
#include <set>
#include <map>
#include <string>
#include "algobot.h"

using namespace std;

// Ejercicio 1
vector<int> quitar_repetidos(vector<int> s) {
    vector<int> v;
    for(int n:s){
        bool insertar = true;
        for(int elem :v){
            if(elem == n){
                insertar = false;
            }
        }
        if(insertar){
            v.push_back(n);
        }
    }
    return v;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> conj;
    for(int n : s){
        conj.insert(n);
    }

    vector<int> res;
    for( int n:conj){
        res.push_back(n);
    }
    return res;
}

// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    bool res = true;
    for(int n : a){
        bool NestaEnB = false;
        for(int e : b){
            if(e==n){NestaEnB = true;}
        }
        res = res && NestaEnB;
    }
    return res;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    set<int> conj_a;
    set<int> conj_b;
    for(int n : a){
        conj_a.insert(n);
    }

    for(int n : b){
        conj_b.insert(n);
    }

    return conj_a == conj_b;
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int,int> dic;
    for(int n : s){
        dic[n] = 0;
        for(int e : s){
            if(n == e){
                dic[n] = dic[n] + 1;
            }
        }
    }
    return dic;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {
    map<int,int> di = contar_apariciones(s);
    vector<int> res;
    for(pair<int,int> p : di){
        if(p.second == 1){
            res.push_back(p.first);
        }
    }
    return res;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    set<int> res;
    for(int n : a){
        if(b.count(n) == 1){
            res.insert(n);
        }
    }
    return res;
}

// Ejercicio 8
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map<int,set<int>> res;
    //Recorro los modulos de 10
    for(int i=0; i<10;i++ ){
        set<int> conj;
        for(int n:s){
            if(n % 10 == i){conj.insert(n);}
        }
        if(conj.size() != 0){ res[i] = conj;}
    }
    return res;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    vector<char> res;
    //covierto tr a un diccionario
    map<char,char> d;
    for(pair<char,char> n : tr){
        d[n.first] = n.second;
    }
    //Recorro las claves de str y las comparo con las del diccionario
    for(char clave : str){
        if(d.count(clave) == 1){res.push_back(d[clave]);}
        else{res.push_back(clave);}
    }
    return res;
}

// Ejercicio 10
set<LU> interseccionLUs(set<LU> a, set<LU> b) {
    set<LU> res;
    for(LU n : a){
        if(b.count(n) == 1){
            res.insert(n);
        }
    }
    return res;
}
bool integrantes_repetidos(vector<Mail> s) {
    bool res = false;
    //Recorro todos los asuntos y los comparo entre si
    for(Mail mail1: s){
        for(Mail mail2 : s){
            set<LU> libretas1 = mail1.libretas();
            set<LU> libretas2 = mail2.libretas();
            if(interseccionLUs(libretas1,libretas2) != set<LU>({}) && libretas1!=libretas2){
                res = true;
            }
        }
    }
    return res;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
        map<set<LU>, Mail> res;
    for(Mail mail1:s){
        set<LU> libretas1 = mail1.libretas();
        int fecha = mail1.fecha();
        //Chequeo que tenga adjunto, sino descarto a priori el mail
        if(mail1.adjunto()){
            //Pido el ultimo mail por grupo
            for(Mail mail2:s){
                set<LU> libretas2 = mail2.libretas();
                //Si son el mismo grupo
                if(libretas1==libretas2 && mail2.adjunto() && fecha <= mail2.fecha()){
                    res[libretas2] = mail2;
                }

            }
        }
    }
  return res;
}
