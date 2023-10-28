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
    Aerolinea();
    Aerolinea(const Aerolinea &orig);
    ~Aerolinea();

    //TODO
    VDinamico<Aeropuerto*>getAeropuertosOrig();
    VDinamico<Ruta*> getRutasAeropuerto(string iataAirport);
    void linkAerolRuta(Ruta r);
};


#endif //PRACTICA_3_AEROLINEA_H
