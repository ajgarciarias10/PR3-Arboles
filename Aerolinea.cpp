#include "Aerolinea.h"
#include "Ruta.h"
#include "AVL.h"
/**
 * @brief Constructor por defecto
 */
Aerolinea::Aerolinea():id(0),icao(""),nombre(""),pais(""),activo(false) {}
/**
 * @brief Constructor parametrizado
 * @param orig
 */
Aerolinea::Aerolinea(const Aerolinea &orig):id(orig.id),icao(orig.icao),nombre(orig.nombre),pais(orig.pais),activo(orig.activo) {}
/**
 * @brief Metodo que obtiene los aeropuerto de origen
 * @return
 */
VDinamico<Aeropuerto*> Aerolinea::getAeropuertosOrig() {
    //Creo un vector dinamico de aeropuertos que en el que voy a devolver los aeropuertos
    VDinamico<Aeropuerto *> vAeroOrig;
    //Creo un arbol para almacenar los aeropuertos de origen
    AVL<Aeropuerto *> arbolDeAeroOrig;
    //Obtengo del vector dinamico de rutas  los Aeropuertos de Origen
    for (int i = 0; i < aerorutas.tamlog(); ++i) {
        Aeropuerto *pAeroOrig = aerorutas[i]->getOrigen();
        if(pAeroOrig){
            //Insertamos los aeropuertos de origen no nulos
            arbolDeAeroOrig.insertar(pAeroOrig);
        }
    }
    //Accedemos al aeropuerto de origen
    //Es doble puntero ya que el primero es por la direccion y el segundo donde esta el dato
    VDinamico<Aeropuerto **> vAeroOr(arbolDeAeroOrig.recorreInorden());
    //Accedemos al doble puntero
    for (int i = 0; i < vAeroOrig.tamlog(); ++i) {
        //Accedemos al dato que es el aeropuerto y lo insertamos en el vector de aeropuertos
        vAeroOrig.insertar(*vAeroOr[i]);
    }
    //Devolvemos el vector con los aeropuertos de origen
    return  vAeroOrig;
}
/***
 * @brief Devuelve todas las rutas cuyo AeroPuerto de origen o destino tenga ese iata
 * @param iataAirport
 * @return
 */
VDinamico<Ruta*> Aerolinea::getRutasAeropuerto(std::string iataAirport) {
    //Vector que vamos a llenar
    VDinamico<Ruta*> vRutasAero;
    //Recorremos las rutas de la aerolinea
    for (int i = 0; i < aerorutas.tamlog(); ++i) {
        string iataOrig = aerorutas[i]->getOrigen()->getIata();
        string iataDest = aerorutas[i]->getDestino()->getIata();
        //Si tiene ese iata  insertamos  la ruta
            if(iataOrig == iataAirport ||iataDest == iataAirport ){
                    vRutasAero.insertar(aerorutas[i]);
            }
    }
    //Devolvemos el vector de rutas
    return  vRutasAero;
}
/**
 * @brief Metodo que enlaza la Aerolinea con su ruta
 * @param r
 */
void Aerolinea::linkAerolRuta(Ruta *r) {
    aerorutas.insertar(r);
}
/**
 * @brief Destructor de Aerolinea
 */
Aerolinea::~Aerolinea() {
}
/**
 * @brief Metodo que compara si una aerolinea es menor que otra por icao
 * @param orig
 * @return
 */
bool Aerolinea::operator<(const Aerolinea &orig) {
    return (this->icao<orig.icao);

}
/**
 * @brief  Metodo que compara si una aerolinea es mayor que otra por icao
 * @param orig
 * @return
 */
bool  Aerolinea::operator>(const Aerolinea &orig) {
    return (this->icao>orig.icao);

}

unsigned int Aerolinea::getId() const {
    return id;
}

void Aerolinea::setId(unsigned int id) {
    Aerolinea::id = id;
}

const string &Aerolinea::getIcao() const {
    return icao;
}

void Aerolinea::setIcao(const string &icao) {
    Aerolinea::icao = icao;
}

const string &Aerolinea::getNombre() const {
    return nombre;
}

void Aerolinea::setNombre(const string &nombre) {
    Aerolinea::nombre = nombre;
}

const string &Aerolinea::getPais() const {
    return pais;
}

void Aerolinea::setPais(const string &pais) {
    Aerolinea::pais = pais;
}

bool Aerolinea::isActivo() const {
    return activo;
}

void Aerolinea::setActivo(bool activo) {
    Aerolinea::activo = activo;
}

const VDinamico<Ruta *> &Aerolinea::getAerorutas() const {
    return aerorutas;
}

void Aerolinea::setAerorutas(const VDinamico<Ruta *> &aerorutas) {
    Aerolinea::aerorutas = aerorutas;
}



