#ifndef PRACTICA_3_AEROLINEA_H
#define PRACTICA_3_AEROLINEA_H
#include <string>
#include "VDinamico.h"
#include "Ruta.h"
#include "ListaEnlazada.h"
using  namespace  std;
class Ruta;
class Aerolinea {
private:
    unsigned int id;
    string icao;
    string nombre;
    string pais;
    bool activo;
    VDinamico<Ruta*> aerorutas;
public:
    //Constructor por defecto
    Aerolinea();
    //Constructor copia
    Aerolinea(const Aerolinea &orig);
    //Destrcutor
    ~Aerolinea();
    //Metodo que devuelve los aeropuertos de origen
    VDinamico<Aeropuerto*>getAeropuertosOrig();
    //Metodo que devuelve todas las rutas cuya aeropuerto de origen tenga ese mismo iata
    VDinamico<Ruta*> getRutasAeropuerto(string iataAirport);
    //Enlaza Aerolina con Aeroroutes
    void linkAerolRuta(Ruta *r);
    //Operator<
    bool operator<(const Aerolinea &orig);
    //Operador>
    bool  operator>(const Aerolinea &orig);


    unsigned int getId() const;

    void setId(unsigned int id);

    const string &getIcao() const;

    void setIcao(const string &icao);

    const string &getNombre() const;

    void setNombre(const string &nombre);

    const string &getPais() const;

    void setPais(const string &pais);

    bool isActivo() const;

    void setActivo(bool activo);

    const VDinamico<Ruta *> &getAerorutas() const;

    void setAerorutas(const VDinamico<Ruta *> &aerorutas);
};




#endif //PRACTICA_3_AEROLINEA_H
