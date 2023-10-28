#include "VuelaFlight.h"
/**
 * @brief Destructor
 */
VuelaFlight::~VuelaFlight(){}
/**
 * @brief Constructor por defecto
 */
VuelaFlight::VuelaFlight():aeropuertos(),rutas(){}
/**
 * @brief Constructor Copia
 * @param vl
 */
VuelaFlight::VuelaFlight(const VuelaFlight &orig):aeropuertos(orig.aeropuertos),rutas(orig.rutas){}

Ruta &VuelaFlight::buscarRutasOriDes(std::string idOrigen, std::string idDestino) {
    ListaEnlazada<Ruta>::Iterador i;
    for (i=rutas.iterador();!i.fin();i.siguiente()) {
        if(i.dato().getOrigen()->getIata()==idOrigen && i.dato().getDestino()->getIata()==idDestino)
            return i.dato();
    }
    throw std::invalid_argument("VuelaFlight:: buscarRutasOriDes:: No hay ninguna ruta mencionada");
}
/**
 * @brief BuscarRutasOrigen
 * @param idOrigen
 * @return
 */
ListaEnlazada<Ruta*> VuelaFlight::buscarRutasOrigen(std::string idOrigen) {
    ListaEnlazada<Ruta>::Iterador i;
    ListaEnlazada<Ruta*> lista;

    for (i=rutas.iterador();!i.fin();i.siguiente()) {
        if(i.dato().getOrigen()->getIata()==idOrigen)
            lista.insertaFin(&i.dato());
    }
    return lista;
}
/**
 * @brief Buscar Aeropuerto por Pais
 * @param pais
 * @return
 */
VDinamico<Aeropuerto*> VuelaFlight::buscarAeropuertoPais(std::string pais) {
    //Creo un vector para los encontrados
    VDinamico<Aeropuerto*> encontrados;
    for (int i = 0; i < aeropuertos.Tamlog(); ++i) {
        if (aeropuertos[i].getIsoPais()==pais)
            encontrados.insertar(&(aeropuertos[i]));
    }
    return encontrados;
}
/**
 * @brief Metodo para añadir nueva ruta
 * @param AerOrig
 * @param AerDest
 * @param aerolin
 */
void VuelaFlight::addNuevaRuta( Aeropuerto* AerOrig, Aeropuerto* AerDest, std::string aerolin) {
    Ruta ruta(aerolin,AerDest,AerOrig);
    rutas.insertaFin(ruta);

}
/**
 * @brief Añade aeropuerto
 * @param orig
 */

void VuelaFlight::addNuevoAeropuerto(const Aeropuerto &orig) {
    aeropuertos.insertar(orig);
}

const VDinamico<Aeropuerto> &VuelaFlight::getAeropuertos() const {
    return aeropuertos;
}

void VuelaFlight::setAeropuertos( VDinamico<Aeropuerto> &aeropuertos) {
    this->aeropuertos= aeropuertos;
}

const ListaEnlazada<Ruta> &VuelaFlight::getRutas() const {
    return rutas;
}

void VuelaFlight::setRutas(const ListaEnlazada<Ruta> &rutas) {
    VuelaFlight::rutas = rutas;
}

