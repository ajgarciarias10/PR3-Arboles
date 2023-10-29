#include "VuelaFlight.h"
/**
 * @brief VuelaFlight
 */
VuelaFlight::VuelaFlight() :aeropuertos(),rutas() {}
/**
 * @brief Constructor parametrizado
 * @param vector
 * @param ruta
 */
VuelaFlight::VuelaFlight(VDinamico<Aeropuerto> vector, ListaEnlazada<Ruta> ruta):aeropuertos(vector),rutas(ruta) {}
/**
 * @brief BuscarRutasOrigenDestino
 * @param idAerOrig
 * @param idAerDest
 * @return
 */
Ruta &VuelaFlight::buscarRutasOriDeS(string idAerOrig, string idAerDest) {
    ListaEnlazada<Ruta>::Iterador i;
    //Recorremos todos los aeropuertos
    for(i = rutas.iterador();!i.fin();i.siguiente()){
        //Obtenemos los datos
        string origenBusq = i.dato().getOrigen()->getIata();
        string destinoBusq = i.dato().getDestino()->getIata();
        //En caso de que se encuentre
        if(origenBusq==idAerOrig && destinoBusq==idAerDest)
            //Devolvemos el dato
            return i.dato();
    }
    throw std::invalid_argument("La ruta no ha sido encontrado" "\n" "Intente cambiar su origen y destino" );
}
/**
 * @brief BuscarRutasOrigen
 * @param idAerOrig
 * @return
 */
ListaEnlazada<Ruta *> VuelaFlight::buscarRutasOrigen(string idAerOrig) {
    ListaEnlazada<Ruta>::Iterador i;
    ListaEnlazada<Ruta *> lista;
    //Recorremos todos los aeropuertos
    for(i = rutas.iterador();!i.fin();i.siguiente()){
        //Obtenemos los datos
        string origenBusq = i.dato().getOrigen()->getIata();
        //En caso de que se encuentre
        if(origenBusq==idAerOrig){
            //Devolvemos el dato
            lista.insertaFin(&i.dato());
        }
    }
    return  lista;


}

/**
 * @brief Buscar Aeropuerto por Pais
 * @param pais
 * @return
 */
VDinamico<Aeropuerto * > VuelaFlight::buscarAeropuertoPais(string pais) {
    //Donde lo vamos a meter
    VDinamico<Aeropuerto*> encontrado;
    //Recorremos el tamaño fisico
    for (int i = 0; i < aeropuertos.tamlog(); ++i) {
        if(aeropuertos[i].getIsoPais() == pais){
            //Insertamso el vector de aeropuertos
            encontrado.insertar(&aeropuertos[i]);
        }
    }
    return  encontrado;


}
/**
 * @brief Metodo para añadir nueva ruta
 * @param idAerOrig
 * @param idAerDest
 * @param aerolinea
 */
void VuelaFlight::addNuevaRuta(Aeropuerto *idAerOrig, Aeropuerto * idAerDest, string aerolinea) {
    Ruta ruta(aerolinea,idAerOrig,idAerDest);
    rutas.insertaFin(ruta);

}
/**
 * @brief Destructor
 */
VuelaFlight::~VuelaFlight() {
}
/**
 * @brief Constructor Copia
 * @param vl
 */

VuelaFlight::VuelaFlight(const VuelaFlight &vl) : aeropuertos(vl.aeropuertos), rutas(vl.rutas),work(vl.work){}
/**
 * @brief Añade aeropuerto
 * @param aeropuerto
 */

void VuelaFlight::añadeAeropuerto(const Aeropuerto *aeropuerto) {
    aeropuertos.insertar(*aeropuerto);

}
