#include "ListaEnlazada.h"
#include "VDinamico.h"
#include "Aeropuerto.h"
#include "Ruta.h"
#include "AVL.h"
#ifndef PRACTICA_2_VUELAFLIGHT_H
#define PRACTICA_2_VUELAFLIGHT_H
/**
 * @file VuelaFlight.h
 * @date 03/11/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @brief Vuela Flight
 */

class VuelaFlight {
private:
    //Declaramos los metodo publicos y constructores
    VDinamico<Aeropuerto> aeropuertos;
    ListaEnlazada<Ruta> rutas;
    AVL<Aerolinea> work;
public:
    //Constructor por defecto
    VuelaFlight();
    //Constructor copia
    VuelaFlight(const VuelaFlight &vl);
    //Constructor parametrizado
    VuelaFlight(VDinamico<Aeropuerto> aeropuerto, ListaEnlazada<Ruta> ruta ,AVL<Aerolinea> work);
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
    void addNuevaRuta(Aeropuerto* AerOrig, Aeropuerto* AerDest, Aerolinea* aerolineaEncontrada);
    //Añade Aerolinea
    void addAerolinea(Aerolinea &aerolinea);
    //Buscar Aerolinea por icao
    Aerolinea &buscaAerolinea(string icaoAerolinea);
    //Buscar Aerolinea activa
    VDinamico<Aerolinea*> buscaAerolineasActiva();
    //Metodo que obtiene la aerolineas por el Pais
    VDinamico<Aerolinea*> getAerolineasPais(string idPais);

     VDinamico<Aeropuerto> &getAeropuertos() ;
     ListaEnlazada<Ruta> &getRutas() ;
     AVL<Aerolinea> &getWork() ;

};


#endif //PRACTICA_2_VUELAFLIGHT_H
