#include "Ruta.h"

Ruta::~Ruta() {
}

Ruta::Ruta():company(nullptr),origin(nullptr),destination(nullptr) {}
Ruta::Ruta(const Ruta &orig) :company(orig.company),origin(orig.origin),destination(orig.destination) {}
Ruta::Ruta( Aerolinea  *aerolinea, Aeropuerto *dest, Aeropuerto *orig) :company(aerolinea),origin(orig),destination(dest) {}

Aeropuerto *Ruta::getDestination() const {
    return destination;
}

Aeropuerto *Ruta::getOrigin()  {
    return origin;
}

Aerolinea *Ruta::getCompany()  {
    return company;
}

void Ruta::setDestination(Aeropuerto *destination) {
    Ruta::destination = destination;
}

void Ruta::setOrigin(Aeropuerto *origin) {
    Ruta::origin = origin;
}

void Ruta::setCompany(Aerolinea *company) {
    Ruta::company = company;
}
