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
class Ruta {
private:
    string aerolinea;
    Aeropuerto *destination;
    Aeropuerto *origin;
    Aerolinea *company;
public:
    Ruta();
    Ruta(const Ruta &orig);
    Ruta(const std::string &aerolinea,Aeropuerto *dest= nullptr,Aeropuerto* orig= nullptr);
    virtual ~Ruta();
    const std::string &getAerolinea() const;
    void setAerolinea(const std::string &aerolinea);
    Aeropuerto *getDestino() const;
    void setDestino(Aeropuerto *destino);
    Aeropuerto *getOrigen() const;
    void setOrigen(Aeropuerto *origen);
};


#endif //PRACTICA_2_RUTA_H
