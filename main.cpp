#include <iostream>
#include <fstream>
#include <sstream>
#include "UTM.h"
#include "Aeropuerto.h"
#include "VDinamico.h"
#include "ListaEnlazada.h"
#include "VuelaFlight.h"
#include "AVL.h"

/**
 * @brief Practica 3 EEDD
 * @date 19/10/2023
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, const char * argv[]) {
/*
#pragma region Programa de prueba 1
    ListaEnlazada<int>::Iterador it;
    ListaEnlazada<int> listaEnlazada;

    for (int i = 101; i <= 200; ++i) {
        listaEnlazada.insertaFin(i);
    }


    for (int i = 98; i >= 1; --i) {
        listaEnlazada.insertaInicio(i);
    }

    it=listaEnlazada.iterador();
    while (it.dato()!=101){
        it.siguiente();
    }

    listaEnlazada.inserta(it,100);

    it=listaEnlazada.iterador();
    while (it.dato()!=98){
        it.siguiente();
    }

    listaEnlazada.insertaDetras(it,99);

    for (int i = 0; i <10 ; ++i) {
        listaEnlazada.borraInicio();
    }
    for (int i = 0; i <10 ; ++i) {
        listaEnlazada.borraFinal();
    }

    it=listaEnlazada.iterador();
    ListaEnlazada<int>::Iterador aux;
    while (!it.fin()) {
        int dato = it.dato();
        if ((dato%10)==0){
            //Creamos un iterador auxiliar que guarde la pos siguiente
            aux=it;
            aux.siguiente();
            //Borramos la posicion anterior a la del siguiente que era la pos buscada
            listaEnlazada.borra(it);
            //Pasamos el iterador aux que guardamos al iterador real para seguir con la busqueda
            it=aux;
        }else{
            it.siguiente();
        }

    }

    std::cout<<"LISTA POST PROCESOS: "<<std::endl;
    for (it=listaEnlazada.iterador();!it.fin();it.siguiente()) {
        std::cout<<"El dato es: "<< it.dato()<<std::endl;
    }
    std::cout<<"El tamaño final de la lista es: "<< listaEnlazada.Tam()<<std::endl;
    std::cout<<std::endl;
#pragma endregion

    VuelaFlight vuelaFlight;

#pragma region Carga de aeropuertos
    clock_t lecturaAero = clock();

    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id;
    std::string iata;
    std::string tipo;
    std::string nombre;
    std::string latitud_str;
    std::string longitud_str;
    std::string continente;
    std::string iso_pais;

    float latitud, longitud;


    is.open("aeropuertos_v2.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t lectura = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id;ident;tipo;nombre;latitud;longitud;continente;iso_pais

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas,iata,';');
                getline(columnas,tipo,';');
                getline(columnas,nombre,';');
                getline(columnas,latitud_str,';');
                getline(columnas,longitud_str,';');
                getline(columnas,continente,';');
                getline(columnas,iso_pais,';');

                //  Transformamos la latitud y longitud a float
                latitud=std::stof(latitud_str);
                longitud=std::stof(longitud_str);


                UTM *utm= new UTM(latitud,longitud);
                Aeropuerto *aeropuerto=new Aeropuerto(id,iata,tipo,nombre,continente,iso_pais,*utm);
                vuelaFlight.addNuevoAeropuerto(*aeropuerto);
                delete aeropuerto;
                delete utm;
                fila="";
                columnas.clear();
            }
        }

        is.close();

        std::cout << "Tiempo lectura de aeropuertos: " << ((clock() - lecturaAero) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
#pragma endregion

#pragma region Carga de rutas
    clock_t lecturaRutas = clock();
    contador=0;

    std::string aerolinea;
    std::string aero_origen;
    std::string aero_destino;
    vuelaFlight.aeropuertos.ordena();

    is.open("rutas_v1.csv"); //carpeta de proyecto
    if ( is.good() ) {

        clock_t lecturaRutas = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: airline;airport_orig;airport_dest

                getline(columnas, aerolinea, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas,aero_origen,';');
                getline(columnas,aero_destino,';');

                fila="";
                columnas.clear();

                Aeropuerto aerobusca;
                aerobusca.setIata(aero_origen);
                int posOrig=vuelaFlight.aeropuertos.busquedaBin(aerobusca);
                aerobusca.setIata(aero_destino);
                int posDest=vuelaFlight.aeropuertos.busquedaBin(aerobusca);

                if(posDest!=-1 && posOrig!=-1) {
                    vuelaFlight.addNuevaRuta(&vuelaFlight.aeropuertos[posOrig], &vuelaFlight.aeropuertos[posDest],aerolinea);
                }
            }
        }

        is.close();

        std::cout << "Tiempo lectura de las rutas: " << ((clock() - lecturaRutas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
#pragma endregion

#pragma region Programa de prueba 2
#pragma  region Apartado 2 y 3
    std::cout<<std::endl<<std::endl<<"-----------------------RUTAS DESDE BARCELONA HACIA INSTAMBUL-----------------------"<<std::endl<<std::endl;

    try {
        //Si no existen rutas no se ejecutaria el cout, simplemente el catch del throw de la funcion
        Ruta bcnist(vuelaFlight.buscarRutasOriDes("BCN","IST"));
        std::cout<<"Hay rutas entre Barcelona e Instambul";
        //Buscar si hay ruta entre el aeropuerto de Granada Jaen, con algun aeropuerto ingles
        //1º Busco las rutas desde granada a donde sea
        ListaEnlazada<Ruta*> granada(vuelaFlight.buscarRutasOrigen("GRX"));
        ListaEnlazada<Ruta*>::Iterador iterador=granada.iterador();
        bool encontrado=false;
        //2º Itero la lista de Ruta de Granada hasta encontrar un destino que se GB
        while (!iterador.fin()){
            if(iterador.dato()->getDestino()->getIsoPais()=="GB"){
                if (!encontrado){
                    encontrado=true;
                    std::cout<<std::endl<<"Existen rutas entre GRX y GB"<<std::endl;
                }
                std::cout<<"Aerolinea: "<<iterador.dato()->getAerolinea()<<", origen: "<<iterador.dato()->getOrigen()->getNombre()<<", destino: "<<iterador.dato()->getOrigen()->getNombre()<<std::endl;
            }
            iterador.siguiente();
        }
    } catch (std::invalid_argument &e) {
        std::cerr<<e.what();
    }

#pragma endregion
#pragma region Apartado 4
    //Añadir en O(1) ruta entre aeropuerto GranadaJaen con el de paris de la compañia IBE
    //Para ello tendremos que aplicar lo siguiente:
    //Tendremos que buscar el aeropuerto de Granada donde esta en el vector Dinamico de Aeropuertos
    //Asi mismo con el de Paris CDG
    std::cout<<std::endl<<std::endl<<"-----------------------RUTAS DESDE GRANADA HACIA PARIS-----------------------"<<std::endl<<std::endl;

    Aeropuerto aerobusca;
    aerobusca.setIata("GRX");
    int posgr=vuelaFlight.aeropuertos.busquedaBin(aerobusca);
    aerobusca.setIata("CDG");
    int posparis=vuelaFlight.aeropuertos.busquedaBin(aerobusca);

    if (posgr!=-1 && posparis!=-1){
        std::cout<<"Ruta añadida entre GRX y CDG"<<std::endl;
        vuelaFlight.addNuevaRuta(&vuelaFlight.aeropuertos[posparis],&vuelaFlight.aeropuertos[posgr],"IBE");
        vuelaFlight.addNuevaRuta(&vuelaFlight.aeropuertos[posgr],&vuelaFlight.aeropuertos[posparis],"IBE");
    }

    //Compruebo si se han creado las rutas entre Granada y CDG
    try {
        //Si no se encuentran salta al catch directamente
        vuelaFlight.buscarRutasOriDes("GRX", "CDG");
        std::cout << "Se ha encontrado la ruta de GRX a CDG"<< std::endl;
        vuelaFlight.buscarRutasOriDes("CDG", "GRX");
        std::cout << "Se ha encontrado la ruta de CDG a GRX"<< std::endl;
    } catch (std::invalid_argument &e) {
        std::cerr<<e.what();
    }
#pragma endregion
#pragma region Apartado 5

    std::cout<<std::endl<<std::endl<<"-----------------------RUTAS DESDE ESPANA HACIA PORTUGAL-----------------------"<<std::endl<<std::endl;

    try {
        //1º Busco todos los aeropuertos españoles
        VDinamico<Aeropuerto *> esp = vuelaFlight.buscarAeropuertoPais("ES");
        int rutasTotales = 0;
        clock_t busquedaESPT = clock();

        for (int i = 0; i < esp.Tamlog(); ++i) {
            //2º Busco todas las rutas que salen desde un aeropuerto concreto de España
            ListaEnlazada<Ruta *> rutasESPT(vuelaFlight.buscarRutasOrigen(esp[i]->getIata()));
            ListaEnlazada<Ruta *>::Iterador iterador = rutasESPT.iterador();
            //3º Recorro la lista de rutas de ese aeropuerto hasta encontrar un destino cuyo pais sea Portugal
            while (!iterador.fin()) {
                if (iterador.dato()->getDestino()->getIsoPais() == "PT") {
                    rutasTotales++;
                    std::cout << "Ruta encontrada: ";
                    std::cout << "Aerolinea: " << iterador.dato()->getAerolinea() << ", origen:  "
                              << iterador.dato()->getOrigen()->getNombre()
                              << ", destino:  " << iterador.dato()->getDestino()->getNombre() << std::endl << std::endl;
                }
                iterador.siguiente();
            }

        }

        std::cout << "Tiempo de busqueda de rutas de España hacia Portugal: "
                  << ((clock() - busquedaESPT) / (float) CLOCKS_PER_SEC) << " segs." << std::endl << std::endl;
        std::cout << std::endl << std::endl
                  << "-----------------------RUTAS DESDE PORTUGAL HACIA ESPAÑA-----------------------" << std::endl
                  << std::endl;
        //1º Busco los aeropuertos  de Portugal
        VDinamico<Aeropuerto *> pt = vuelaFlight.buscarAeropuertoPais("PT");
        clock_t busquedaPTES = clock();
        for (int i = 0; i < pt.Tamlog(); ++i) {
            //2º  Busco todas las rutas que salen desde un aeropuerto concreto de Portugal
            ListaEnlazada<Ruta *> rutasPTES(vuelaFlight.buscarRutasOrigen(pt[i]->getIata()));
            ListaEnlazada<Ruta *>::Iterador iterador = rutasPTES.iterador();

            //3º Recorro la lista de rutas de ese aeropuerto hasta encontrar un destino cuyo pais sea España
            while (!iterador.fin()) {
                if (iterador.dato()->getDestino()->getIsoPais() == "ES") {
                    rutasTotales++;
                    std::cout << "Ruta encontrada: ";
                    std::cout << "Aerolinea: " << iterador.dato()->getAerolinea() << ", origen:  "
                              << iterador.dato()->getOrigen()->getNombre()
                              << ", destino:  " << iterador.dato()->getDestino()->getNombre() << std::endl << std::endl;
                }
                iterador.siguiente();
            }

        }

        std::cout << "Tiempo de busqueda de rutas de Portugal hacia España: "
                  << ((clock() - busquedaPTES) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
        std::cout << "Hay un total de: " << rutasTotales << " rutas entre Portugal y España";


    } catch (std::invalid_argument &e) {
        std::cerr<<e.what()<<std::endl;
    } catch (std::bad_alloc &e) {
        std::cerr<<e.what()<<std::endl;
    } catch (std::range_error &e) {
        std::cerr<<e.what()<<std::endl;
    }


#pragma endregion
#pragma endregion
*/





    return 0;
}