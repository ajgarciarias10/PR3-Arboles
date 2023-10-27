#include "ListaEnlazada.h"
#include "VDinamico.h"
#include "Aeropuerto.h"
#include "Ruta.h"

#ifndef PRACTICA_2_VUELAFLIGHT_H
#define PRACTICA_2_VUELAFLIGHT_H


class VuelaFlight {
    //Declaramos los metodo publicos y constructores
public:
    VDinamico<Aeropuerto> aeropuertos;
    ListaEnlazada<Ruta> rutas;
public:
    const VDinamico<Aeropuerto> &getAeropuertos() const;
    void setAeropuertos( VDinamico<Aeropuerto> &aeropuertos);
    const ListaEnlazada<Ruta> &getRutas() const;
    void setRutas(const ListaEnlazada<Ruta> &rutas);


public:
    //Constructor por defecto
    VuelaFlight();
    //Constructor copia
    VuelaFlight(const VuelaFlight &orig);
    //Destructor VuelaFlight
    virtual ~VuelaFlight();
    //Metodos que tenemos que utilizar en esta practica
    //BuscarRutaDeOrigenDestino
    Ruta& buscarRutasOriDes(std::string idOrigen,std::string idDestino);
    //BuscarRutasDeOrigen
    ListaEnlazada<Ruta*> buscarRutasOrigen (std::string idOrigen);
    //Buscar AeropuertoPais
    VDinamico<Aeropuerto*> buscarAeropuertoPais(std::string pais);
    //AñadirNuevoAeropuerto
    void addNuevoAeropuerto(const Aeropuerto &orig);
    //AñadirNuevaRuta
    void addNuevaRuta( Aeropuerto* AerOrig, Aeropuerto* AerDest, std::string aerolin);
};


#endif //PRACTICA_2_VUELAFLIGHT_H
