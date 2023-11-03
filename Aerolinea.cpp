#include "Aerolinea.h"
#include "Ruta.h"
#include "AVL.h"
/**
 * @brief Constructor por defecto
 */
Aerolinea::Aerolinea():id(0),icao(""),nombre(""),pais(""),activo(false),aerorutas(){}
/**
 * @brief Constructor copia
 * @param orig
 */
Aerolinea::Aerolinea(const Aerolinea &orig):id(orig.id),icao(orig.icao),nombre(orig.nombre),pais(orig.pais),activo(orig.activo),aerorutas(orig.aerorutas) {}
/**
 * @brief Constructor parametrizado
 * @param orig
 */
Aerolinea::Aerolinea(int id, std::string icao, std::string nombre, std::string pais, bool activo):id(id),icao(icao),nombre(nombre),pais(pais),activo(activo),aerorutas() {}

/**
 * @brief Metodo que obtiene los aeropuerto de origen
 * @return
 */
VDinamico<Aeropuerto*> Aerolinea::getAeropuertosOrig() {
    //Creo un vector dinamico de aeropuertos que en el que voy a devolver los aeropuertos
    VDinamico<Aeropuerto *> vAeroOrig;
    //Creo un arbol para almacenar los aeropuertos de origen
    AVL<Aeropuerto *> arbolDeAeroOrig;
    //Obtengo   aerorutas
    VDinamico<Ruta*> aerorutasMetodo = getAerorutas();
    for (int i = 0; i < aerorutasMetodo.tamlog(); ++i) {
        Aeropuerto *aeropuerto = aerorutasMetodo[i]->getOrigin();
        //Si en el árbol el dato no esta repetido
            if(!arbolDeAeroOrig.busquedaRecursiva(aeropuerto)){
                //Insertamos en el arbol
                arbolDeAeroOrig.insertar(aeropuerto);
                vAeroOrig.insertar(aeropuerto);
            }
    }

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
        string iataOrig = aerorutas[i]->getOrigin()->getIata();
        string iataDest = aerorutas[i]->getDestination()->getIata();
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
    this->aerorutas.insertar(r);
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
bool Aerolinea::operator<(const Aerolinea &orig) const {
    return (this->icao<orig.icao);

}
/**
 * @brief  Metodo que compara si una aerolinea es mayor que otra por icao
 * @param orig
 * @return
 */
bool  Aerolinea::operator>(const Aerolinea &orig) const {
    return (this->icao>orig.icao);

}
/**
 * @brief Getter Id
 * @return
 */
unsigned int Aerolinea::getId() const {
    return id;
}
/**
 * @brief Setter Id
 * @param id
 */
void Aerolinea::setId(unsigned int id) {
    Aerolinea::id = id;
}
/**
 * @brief Getter Icao
 * @return
 */
const string &Aerolinea::getIcao() const {
    return icao;
}
/**
 * @brief Setter Icao
 * @param icao
 */

void Aerolinea::setIcao(const string &icao) {
    Aerolinea::icao = icao;
}
/**
 * @brief Getter Nombre
 * @return
 */
const string &Aerolinea::getNombre() const {
    return nombre;
}
/**
 * @brief Setter Nombre
 * @param nombre
 */

void Aerolinea::setNombre(const string &nombre) {
    Aerolinea::nombre = nombre;
}
/**
 * @brief Getter Pais
 * @return
 */
const string &Aerolinea::getPais() const {
    return pais;
}
/**
 * @brief Setter Pais
 * @param pais
 */
void Aerolinea::setPais(const string &pais) {
    Aerolinea::pais = pais;
}
/**
 * @brief Getter Activo
 * @return
 */
bool Aerolinea::isActivo() const {
    return activo;
}
/**
 * @brief Setter Activo
 * @param activo
 */
void Aerolinea::setActivo(bool activo) {
    Aerolinea::activo = activo;
}
/**
 * @brief Getter Con Acceso al private aerorutas
 * @return
 */
const VDinamico<Ruta *> &Aerolinea::getAerorutas() const {
    return aerorutas;
}
/**
 * @brief Setter AeroRutas
 * @param aerorutas
 */

void Aerolinea::setAerorutas(const VDinamico<Ruta *> &aerorutas) {
    Aerolinea::aerorutas = aerorutas;
}




