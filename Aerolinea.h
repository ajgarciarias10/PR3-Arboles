#ifndef PRACTICA_3_AEROLINEA_H
#define PRACTICA_3_AEROLINEA_H
#include <string>
#include "VDinamico.h"
#include "Ruta.h"
class Ruta;
class Aerolinea {
private:
    unsigned int id;
    std::string icao;
    std::string nombre;
    std::string pais;
    bool activo;
    VDinamico<Ruta*> ruta;
public:
    Aerolinea();
    Aerolinea(const Aerolinea &orig);
    ~Aerolinea();

    VDinamico<Aeropuerto>& getAeropuertosOrig();
};


#endif //PRACTICA_3_AEROLINEA_H
