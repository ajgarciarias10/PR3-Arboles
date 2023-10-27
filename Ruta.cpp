#include "Ruta.h"

Ruta::~Ruta() {
}

Ruta::Ruta():aerolinea(""),origin(nullptr),destination(nullptr) {}
Ruta::Ruta(const Ruta &orig) :aerolinea(orig.aerolinea),origin(orig.origin),destination(orig.destination) {}
Ruta::Ruta(const std::string &aerolinea, Aeropuerto *dest, Aeropuerto *orig) :aerolinea(aerolinea),origin(orig),destination(dest) {}

const std::string &Ruta::getAerolinea() const {
    return aerolinea;
}

void Ruta::setAerolinea(const std::string &aerolinea) {
    Ruta::aerolinea = aerolinea;
}

Aeropuerto *Ruta::getDestino() const {
    return destination;
}

void Ruta::setDestino(Aeropuerto *destino) {
    Ruta::destination = destino;
}

Aeropuerto *Ruta::getOrigen() const {
    return origin;
}

void Ruta::setOrigen(Aeropuerto *origen) {
    Ruta::origin = origen;
}
