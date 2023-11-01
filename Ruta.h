#ifndef PRACTICA_2_RUTA_H
#define PRACTICA_2_RUTA_H
#include <string>
#include "Aeropuerto.h"
#include "Aerolinea.h"
using namespace std;
/**
 *@file Ruta.h
 * @brief Practica 2 EEDD
 * @date 19/10/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @return
 */
class  Aerolinea;
class Ruta {
private:
    Aeropuerto *destination;
    Aeropuerto *origin;
    Aerolinea *company;
public:
    //Constructor por defecto
    Ruta();
    //Constructor copia
    Ruta(const Ruta &orig);
    //Constructor paramerizado
    Ruta(Aerolinea *company,Aeropuerto *dest= nullptr,Aeropuerto* orig= nullptr);
    //Destructor
    virtual ~Ruta();

    Aeropuerto *getDestination() const;

    Aeropuerto *getOrigin() ;

    Aerolinea *getCompany() ;

    void setDestination(Aeropuerto *destination);

    void setOrigin(Aeropuerto *origin);

    void setCompany(Aerolinea *company);
};


#endif //PRACTICA_2_RUTA_H
