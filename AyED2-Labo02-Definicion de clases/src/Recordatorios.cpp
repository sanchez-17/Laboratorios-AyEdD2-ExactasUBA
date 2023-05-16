#include <iostream>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(uint mes,uint dia);
    uint mes();
    uint dia();
    void incrementar_dia();

    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif

  private:
    uint mes_;
    uint dia_;
};

Fecha::Fecha(uint mes, uint dia) : mes_(mes), dia_(dia) {}

uint Fecha::mes(){
    return mes_;
}

uint Fecha::dia(){
    return dia_;
}

#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_fecha = this->dia() == o.dia() && this->mes() == o.mes();
    return igual_fecha;
}
#endif

ostream& operator<<(ostream& os, Fecha f) {
    os << f.dia()<< "/" <<f.mes();
    return os;
}

//Ejercicio 10
void Fecha::incrementar_dia(){
    if(mes_ == 12 && dia_ == 31){
        mes_ = 1;
        dia_ = 1;
    }
    else{
        if(dia_ < dias_en_mes(mes_)){
            dia_ = dia_ + 1;
        }
        else{
            mes_ = mes_ + 1;
            dia_ = 1;
        }
    }
};

// Clase Horario

//Ejercicio 11
class Horario{
    public:
        Horario(uint hora, uint minutos);
        uint hora();
        uint min();
        bool operator==(Horario h);
        bool operator<(Horario h);
    private:
        uint hora_;
        uint minutos_;
};

Horario::Horario(uint hora, uint min): hora_(hora),minutos_(min){};

uint Horario::hora(){
    return hora_;
};

uint Horario::min(){
    return minutos_;
};

ostream& operator<<(ostream& os, Horario h) {
    os << h.hora() << ":" << h.min();
    return os;
};

bool Horario::operator==(Horario h) {
    bool igual_horario = this->hora() == h.hora() && this->min() == h.min();
    return igual_horario;
};

//Ejercicio 12
bool Horario::operator<(Horario h){
    if(this->hora() == h.hora()) {
        return this->min() < h.min();
    }
    else{
        return this->hora() < h.hora();
    }
};

// Ejercicio 13

// Clase Recordatorio


// Ejercicio 14

// Clase Agenda

