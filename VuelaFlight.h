#include "ListaEnlazada.h"
#include "VDinamico.h"
#include "Aeropuerto.h"
#include "Ruta.h"
#include "AVL.h"
#ifndef PRACTICA_2_VUELAFLIGHT_H
#define PRACTICA_2_VUELAFLIGHT_H


class VuelaFlight {
    //Declaramos los metodo publicos y constructores
public:
    VDinamico<Aeropuerto> aeropuertos;
    ListaEnlazada<Ruta> rutas;
    AVL<Aerolinea> work;
    //Constructor por defecto
    VuelaFlight();
    //Constructor copia
    VuelaFlight(const VuelaFlight &vl);
    //Constructor parametrizado
    VuelaFlight(VDinamico<Aeropuerto> aeropuerto, ListaEnlazada<Ruta> ruta );
    //Destructor VuelaFlight
    ~VuelaFlight();
    //Metodos que tenemos que utilizar en esta practica
    //BuscarRutaDeOrigenDestino
    Ruta& buscarRutasOriDeS(string idAerOrig,string idAerDest);
    //BuscarRutasDeOrigen
    ListaEnlazada<Ruta*> buscarRutasOrigen (string idAerOrig);
    //Buscar AeropuertoPais
    VDinamico<Aeropuerto*> buscarAeropuertoPais(string pais);
    //AñadirNuevoAeropuerto
    void añadeAeropuerto(const Aeropuerto *aeropuerto);
    //AñadirNuevaRuta
    void addNuevaRuta(Aeropuerto *idAerOrig, Aeropuerto * idAerDest, string aerolinea);
};


#endif //PRACTICA_2_VUELAFLIGHT_H
