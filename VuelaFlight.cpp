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
VuelaFlight::VuelaFlight(VDinamico<Aeropuerto> vector, ListaEnlazada<Ruta> ruta,AVL<Aerolinea> work):aeropuertos(vector),rutas(ruta),work(work) {}
/**
 * @brief Destructor
 */
VuelaFlight::~VuelaFlight() {
}
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
        string origenBusq = i.dato().getOrigin()->getIata();
        string destinoBusq = i.dato().getDestination()->getIata();
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
        string origenBusq = i.dato().getOrigin()->getIata();
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
void VuelaFlight::addNuevaRuta(Aeropuerto* AerOrig, Aeropuerto* AerDest, Aerolinea* aerolineaEncontrada) {
            //Añadimos las rutas ya con la aerolinea  y los aeropertos
            rutas.insertaFin(*new Ruta(aerolineaEncontrada,AerDest,AerOrig));
            //d. Obtener la dirección del objeto ruta recién insertado en la lista (en la última posición).
            //e. Enlazar la aerolínea encontrada antes con la ruta anterior mediante
            //Aerolinea::linkAerolRuta.
            aerolineaEncontrada->linkAerolRuta(&rutas.fin());

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
/**
 * @brief Metodo AddAerolinea
 * @param aerolinea
 */
void VuelaFlight::addAerolinea(Aerolinea &aerolinea) {
    work.insertar(aerolinea);

}
/**
 * @brief Metodo Buscar Aerolinea por Icao
 * @param icaoAerolinea
 * @return
 */
Aerolinea &VuelaFlight::buscaAerolinea(std::string icaoAerolinea) {
    Aerolinea aerol;
    aerol.setIcao(icaoAerolinea);
    Aerolinea *t = work.busquedaRecursiva(aerol);
    if(!t){
        throw std::invalid_argument("No se ha encontrado la aerolinea");
    }
    return  *t;

}
/**
 * @brief Metodo que busca las Aerolineas Activas
 * @return
 */
VDinamico<Aerolinea*> VuelaFlight::buscaAerolineasActiva() {
    VDinamico<Aerolinea*> buscaAerolinea = work.recorreInorden();
    VDinamico<Aerolinea*> devuelveAerolinea;
    for (int i = 0; i < buscaAerolinea.tamlog(); ++i) {
        if(buscaAerolinea[i]->isActivo()){
            devuelveAerolinea.insertar(buscaAerolinea[i]);
        }
    }

    return  devuelveAerolinea;

}
/**
 * @brief Metodo que busca la Aerolinea por el pais
 * @param idPais
 * @return
 */
VDinamico<Aerolinea*> VuelaFlight::getAerolineasPais(std::string idPais) {
    VDinamico<Aerolinea*> buscaAerolinea = work.recorreInorden();
    VDinamico<Aerolinea*> devuelveAerolinea;
    for (int i = 0; i < buscaAerolinea.tamlog(); ++i) {
        if(buscaAerolinea[i]->getPais() == idPais){
            devuelveAerolinea.insertar(buscaAerolinea[i]);
        }
    }

    return  devuelveAerolinea;
}

 VDinamico<Aeropuerto> &VuelaFlight::getAeropuertos()  {
    return aeropuertos;
}



 ListaEnlazada<Ruta> &VuelaFlight::getRutas()  {
    return rutas;
}



 AVL<Aerolinea> &VuelaFlight::getWork()  {
    return work;
}



