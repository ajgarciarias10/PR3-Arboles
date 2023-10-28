#include "Aerolinea.h"

Aerolinea::Aerolinea():id(0),icao(""),nombre(""),pais(""),activo(false) {}

Aerolinea::Aerolinea(const Aerolinea &orig):id(orig.id),icao(orig.icao),nombre(orig.nombre),pais(orig.pais),activo(orig.activo) {}

