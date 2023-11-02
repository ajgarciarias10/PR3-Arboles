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
                vl.addAerolinea(*new Aerolinea(id,icao,nombreAero,pais,activoBool));
                fila = "";
                columnas.clear();
            }
        }
    }
    else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    is.close();
#pragma  endregion
#pragma region Valores Rutas
    string icaoRuta = "";
    string  origen2 = "";
    string destino2 = "";
#pragma endregion
#pragma region Carga Ruta
    clock_t lecturaRutas = clock();
    is.open("../rutas_v1.csv"); //carpeta de proyecto
    if ( is.good() ) {
        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, icaoRuta, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, origen2, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, destino2, ';'); //leemos caracteres hasta encontrar y omitir ';'
                fila = "";
                columnas.clear();
#pragma  region   Buscar en tiempo logarítmico la aerolínea que hace la ruta en VuelaFlight::work
                Aerolinea aero2;
                aero2.setIcao(icaoRuta);
                Aerolinea *aerolineaEncontrada;
                aerolineaEncontrada = vl.work.busquedaRecursiva(aero2);
#pragma  endregion
#pragma region Buscar en tiempo logarítmico en  PR2 + añadir nueva ruta
                //Declaro un aeropuerto
                Aeropuerto aero;
                //Seteo su iata de origen
                aero.setIata(origen2);
                //Compruebo la posicion dentro del vector dinamico en el que esta Tanto la ruta de origen con la de destino
                //Y así descubro el aeropuerto ORIGEN
                int posOrigen = vl.aeropuertos.busquedaBinaria(aero);
                //Seteo su iata de destino
                aero.setIata(destino2);
                //Y así descubro el aeropuerto destino
                int posDest = vl.aeropuertos.busquedaBinaria(aero);
                if(posOrigen !=-1 && posDest !=-1 && aerolineaEncontrada){
                    //Añadimos nueva ruta a partir del origen el destino y el icao
                    vl.addNuevaRuta(&vl.aeropuertos[posOrigen],&vl.aeropuertos[posDest],aerolineaEncontrada);
                }

            }
        }

    } else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    is.close();

    std::cout << "Tiempo lectura de las rutas: " << ((clock() - lecturaRutas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
#pragma endregion
#pragma region Visualiza toda la información de la aerolínea Ryanair, RYR
    cout<<"--------------------------------------"<<endl;
    Aerolinea aerolinea =  vl.buscaAerolinea("RYR");
     cout<<"Id: "<<aerolinea.getId() <<" Aerolinea: "<< aerolinea.getNombre() <<  " Icao : "
     <<  aerolinea.getIcao() << " Pais: " << aerolinea.getPais() << endl;
    cout<<"--------------------------------------"<<endl;
#pragma endregion
#pragma  region Muestra todas las aerolíneas activas.
    VDinamico<Aerolinea*> vectorsito(vl.buscaAerolineasActiva());
    for (int i = 0; i < vectorsito.tamlog(); ++i) {
        string activo = " ";
        vectorsito[i]->isActivo() ? activo = "Si" : activo ="No";
        cout<< "Id: "<< vectorsito[i]->getId() << " Nombre: "<< vectorsito[i]->getNombre()<< " Pais: " << vectorsito[i]->getPais() <<" Activo: "<< activo <<"\n"<<endl;
        cout<<"--------------------------------------"<<endl;
    }
#pragma endregion
#pragma  region Busca todos los aeropuertos (origen) en los que opera Iberia Airlines, con icao IBE
Aerolinea iberiaAirlines = vl.buscaAerolinea("IBE");
VDinamico<Aeropuerto*> aeropuertosIbericos  =  iberiaAirlines.getAeropuertosOrig();
    for (int j = 0; j < aeropuertosIbericos.tamlog(); ++j) {
        cout<<"Id: "<<aeropuertosIbericos[j]->getId()<<" Aerolinea: "<< aeropuertosIbericos[j]->getNombre() <<  " Iata : "
            <<  aeropuertosIbericos[j]->getIata() << " Iso Pais: " << aeropuertosIbericos[j]->getIsoPais() << endl;
        cout<<"--------------------------------------"<<endl;

    }
#pragma  endregion
#pragma  region   Busca todas las rutas operadas por Iberia Airlines con origen en el aeropuerto de Málaga(AGP).
    //AeroRutasAGP
    VDinamico<Ruta*> aerorutasAGP = iberiaAirlines.getRutasAeropuerto("AGP");
    VDinamico<Ruta*> aerorutasMalaga;

    for (int j = 0; j < aerorutasAGP.tamlog(); ++j) {
        if(aerorutasAGP[j]->getOrigin()->getNombre() == "Málaga-Costa del Sol Airport"){
            aerorutasMalaga.insertar(aerorutasAGP[j]);
        }

    }
    for (int i = 0; i < aerorutasMalaga.tamlog(); ++i) {
        cout<<"Origen: "<<aerorutasMalaga[i]->getOrigin()->getNombre()<<"---> Destino: "<< aerorutasMalaga[i]->getDestination()->getNombre()  << endl;
        cout<<"--------------------------------------"<<endl;
    }

#pragma  endregion
return 0;
}
