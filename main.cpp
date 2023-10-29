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
    ifstream is;
    stringstream  columnas;
    string fila;
//Declaro clase VuelaFlight
    VuelaFlight vl;
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
#pragma  region Aerolinea valores
    string idAerolineaStr;
    string icao = "";
    string nombreAero="";
    string pais="";
    string activo="";
#pragma endregion
#pragma region  Carga Aerolineas
    is.open("../aerolineas_v1.csv"); //carpeta de proyecto
    if(is.good()){
        while (getline(is, fila)){
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, idAerolineaStr, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, icao, ';');
                getline(columnas, nombreAero, ';');
                getline(columnas, pais, ';');
                getline(columnas, activo, ';');
                bool activoBool;
                //condición ? valor_si_verdadero : valor_si_falso;
                activo=="Y" ? activoBool = true : activoBool = false;
                int id = stoi(idAerolineaStr);
                fila = "";
                columnas.clear();
                vl.work.insertar(*new Aerolinea(id,icao,nombre,pais,activoBool));
            }
        }
    }
    else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    is.close();
#pragma  endregion
#pragma region Valores Rutas
    string aerolinea = "";
    string  origen2 = "";
    string destino2 = "";
    Aeropuerto *origen = nullptr;
    Aeropuerto *destino = nullptr;
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
                #pragma region Buscar en tiempo logarítmico en  PR2
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
                #pragma  endregion

            }
        }

    } else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    is.close();

    std::cout << "Tiempo lectura de las rutas: " << ((clock() - lecturaRutas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
#pragma endregion
#pragma region Busca en tiempo logaritmico en PR3
    AVL<Aerolinea>aerolineaAVL;
    ListaEnlazada<Ruta *> listaDRutas;
    ListaEnlazada<Ruta *> :: Iterador i = listaDRutas.iterador();

    //2º Itero la lista de Ruta de Granada hasta encontrar un destion que sea GB
    while(!i.fin()) {
        //Busca Aerolinea
        Aerolinea al;
        //Seteamos el nombre de la aerolinea
        al.setNombre(i.dato()->getAerolinea());

        Aerolinea *aerolineaNueva = aerolineaAVL.busquedaRecursiva(al);
        if(aerolineaNueva){
            cout<<"FRESQUISIMA LA BUSQUEDA"<<endl;

        }
        else{
            cout<<"Pocha"<<endl;
        }
        i.siguiente();
    }
#pragma endregion
    return 0;
}
