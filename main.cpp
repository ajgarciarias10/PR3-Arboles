#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "time.h"
#include "string"
#include "Aeropuerto.h"
#include "VDinamico.h"
#include "VuelaFlight.h"

using  namespace std;
/**
 * @brief Practica 2 EEDD
 * @date 19/10/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[]) {
    VuelaFlight vl;
    ifstream is;
    stringstream  columnas;
    string fila;
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
*/
 #pragma region Aeropuerto valores

    float latitud, longitud;
    string id = "";
    string iata = "";
    string ident="";
    string tipo="";
    string nombre="";
    string latitud_str="";
    string longitud_str="";
    string continente="";
    string iso_pais="";
#pragma endregion
#pragma region Valores Rutas
    string aerolinea = "";
    string  origen2 = "";
    string destino2 = "";
    Aeropuerto *origen = nullptr;
    Aeropuerto *destino = nullptr;
#pragma endregion
#pragma region Carga aeropuertos
    clock_t lecturaAero = clock();
    is.open("../aeropuertos_v2.csv"); //carpeta de proyecto
    if ( is.good() ) {
        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                //formato de fila: id;ident;tipo;nombre;latitud;longitud;continente;iso_pais
                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, iata, ';');
                getline(columnas, tipo, ';');
                getline(columnas, nombre, ';');
                getline(columnas, latitud_str, ';');
                getline(columnas, longitud_str, ';');
                getline(columnas, continente, ';');
                getline(columnas, iso_pais, ';');
                //  Transformamos la latitud y longitud a float
                stof(latitud_str);
                stof(longitud_str);

                fila = "";
                columnas.clear();
                //Insertamos en el Vector Dinamico el Aeropuerto
                vl.añadeAeropuerto(new Aeropuerto(id,iata,tipo,nombre,continente,iso_pais,* new UTM(latitud,longitud)));


            }
        }
        //Tras leer ordenamos el vector por Codigo Iata
        vl.aeropuertos.ordenar();
        is.close();
    }else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    std::cout << "Tiempo lectura de aeropuertos: " << ((clock() - lecturaAero) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

#pragma endregion
#pragma region Carga Ruta
    clock_t lecturaRutas = clock();
    is.open("../rutas_v1.csv"); //carpeta de proyecto
    if ( is.good() ) {
        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, aerolinea, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, origen2, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, destino2, ';'); //leemos caracteres hasta encontrar y omitir ';'
                fila = "";
                columnas.clear();

                //Declaro un aeropuerto
                Aeropuerto aero;
                aero.setIata(origen2);
                //Compruebo la posicion dentro del vector dinamico en el que esta Tanto la ruta de origen con la de destino
                //Y así descubro el aeropuerto
                int posOrigen = vl.aeropuertos.busquedaBinaria(aero);
                aero.setIata(destino2);
                int posDest = vl.aeropuertos.busquedaBinaria(aero);
                if(posOrigen !=-1 && posDest !=-1){
                    //Añadimos las rutas
                    vl.addNuevaRuta(&vl.aeropuertos[posOrigen],&vl.aeropuertos[posDest],aerolinea);
                }

            }
        }

    } else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    std::cout << "Tiempo lectura de las rutas: " << ((clock() - lecturaRutas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
#pragma endregion
#pragma region Programa de prueba 2
#pragma  region Apartado 2 y Apartado 3
    try {
        cout<<"Buscar si hay ruta entre el aeropuerto del Barcelona con el de Estambul"<<endl;
        //Buscar si hay ruta entre el aeropuerto del Barcelona con el de Estambul
        vl.buscarRutasOriDeS("BCN", "IST");
        cout<<"Se ha encontrado la ruta de BCN a IST"<<endl;
        cout<<"--------------------------------------"<<endl;

        //Buscar si hay ruta entre el aeropuerto de Granada Jaen, con algun aeropuerto ingles
        cout<<"Buscar si hay ruta entre el aeropuerto de Granada Jaen, con algun aeropuerto ingles"<<endl;
        //1º Busco las rutas desde granada a donde sea
        ListaEnlazada<Ruta *> listaDRutas(vl.buscarRutasOrigen("GRX"));
        ListaEnlazada<Ruta *> :: Iterador i = listaDRutas.iterador();
        //2º Itero la lista de Ruta de Granada hasta encontrar un destion que sea GB
        while(!i.fin()){
            if(i.dato()->getDestino()->getIsoPais() == "GB"){
                cout<< "Aerolinea " << i.dato()->getAerolinea()<< "\n"
                    <<"Ruta encontrada de : "<< "GRX" << "--- " << i.dato()->getDestino()->getNombre()<<endl;
            }
            i.siguiente();
        }

        cout<<"--------------------------------------"<<endl;
    }catch (invalid_argument &e){
        cout<<e.what()<<endl;
    }
#pragma  endregion
#pragma region Apartado 4
    //Añadir en O(1) ruta entre aeropuerto Granada-Jaen con el de Paris de la compañia IBE
    //Para ello tendremos que aplicar lo siguiente tendre que buscar el
    // aeropuerto de Granada Jaen donde esta en el vector dinammico de aeropuertos
    //Asi mismo con el de Paris
    Aeropuerto aeroport;
    aeroport.setIata("GRX");
    int posGar=vl.aeropuertos.busquedaBinaria(aeroport);
    aeroport.setIata("CDG");
    int posCDG=vl.aeropuertos.busquedaBinaria(aeroport);
    if(posGar != -1  && posCDG != -1)
        vl.addNuevaRuta(&vl.aeropuertos[posGar],&vl.aeropuertos[posCDG],"IBE");
    vl.addNuevaRuta(&vl.aeropuertos[posCDG],&vl.aeropuertos[posGar],"IBE");

    // Compruebo si hay alguna ruta desde Granada a CDG
    vl.buscarRutasOriDeS("GRX", "CDG");
    cout<<"Se ha encontrado la ruta de GRX a CDG"<<endl;
    cout<<"--------------------------------------"<<endl;
    // Compruebo si hay alguna ruta desde CDG a Granada
    vl.buscarRutasOriDeS("CDG", "GRX");
    cout<<"Se ha encontrado la ruta de CDG a GRX"<<endl;
    cout<<"--------------------------------------"<<endl;

#pragma  endregion
#pragma  region Apartado 5

#pragma region Buscar rutas existentes Espana y Portugal
    cout<<"Buscar si hay ruta  Espana con Portugal"<<endl;
    clock_t busquedaESPT = clock();
    //1º Busco aeropuertos españoles
    VDinamico<Aeropuerto*> aeroESP=vl.buscarAeropuertoPais("ES");
    int nrutasESPPT=0;
    for (int i = 0; i < aeroESP.tamlog() ; ++i) {
        //2º Busco las rutas desde España a donde sea
        ListaEnlazada<Ruta *> listaDRutas(vl.buscarRutasOrigen(aeroESP[i]->getIata()));
        ListaEnlazada<Ruta *> :: Iterador it = listaDRutas.iterador();

        //3º Itero la lista dde España  hasta encontrar un destino  que sea PT
        while(!it.fin()){
            if(it.dato()->getDestino()->getIsoPais() == "PT"){
                nrutasESPPT++;
                cout<< "Aerolinea " << it.dato()->getAerolinea()<< "\n"
                    <<"Ruta encontrada de : "<<  it.dato()->getOrigen()->getIata() << "-to-> " << it.dato()->getDestino()->getIata()<<endl;
            }
            it.siguiente();
        }
    }
    std::cout <<"Numero de rutas ESP A PT: "<< nrutasESPPT<< std::endl;
    std::cout << "Tiempo de busqueda de rutas de España hacia  Portugal: " << ((clock() - busquedaESPT) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    cout<<"--------------------------------------"<<endl;
#pragma region Buscar rutas existentes Portugal y España
    clock_t busquedaPTES = clock();
    cout<<"Buscar si hay ruta  Portugal con Espana"<<endl;
    //1º Busco aeropuertos españoles
    VDinamico<Aeropuerto*> aeroPOT=vl.buscarAeropuertoPais("PT");
    int nrutasPTESP=0;
    for (int i = 0; i < aeroPOT.tamlog() ; ++i) {

        //2º Busco las rutas desde España a donde sea
        ListaEnlazada<Ruta *> listaDRutas(vl.buscarRutasOrigen(aeroPOT[i]->getIata()));
        ListaEnlazada<Ruta *> :: Iterador it = listaDRutas.iterador();
        //3º Itero la lista dde España  hasta encontrar un destino  que sea PT
        while(!it.fin()){
            if(it.dato()->getDestino()->getIsoPais() == "ES"){
                nrutasPTESP++;
                cout<< "Aerolinea " << it.dato()->getAerolinea()<< "\n"
                    <<"Ruta encontrada de : "<<  it.dato()->getOrigen()->getIata() << "-to-> " << it.dato()->getDestino()->getIata()<<endl;
            }
            it.siguiente();
        }
    }
    std::cout <<"Numero de rutas PT A ESP: "<< nrutasPTESP<< std::endl;
    std::cout << "Tiempo de busqueda de rutas de Portugal hacia España: " << ((clock() - busquedaPTES) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    cout<<"--------------------------------------"<<endl;
#pragma  endregion


#pragma    endregion

#pragma endregion
#pragma  endregion
    return 0;
}
