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
 * @brief Practica 3 EEDD
 * @date 02/11/2023
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
                fila = "";
                columnas.clear();
                //Insertamos en el Vector Dinamico el Aeropuerto
                vl.añadeAeropuerto(Aeropuerto(id,iata,tipo,nombre,continente,iso_pais, UTM(stof(latitud_str),stof(longitud_str))));


            }
        }
        //Tras leer ordenamos el vector por Codigo Iata
        vl.ordenarAeropuertos();
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

    clock_t lecturaAerolineas = clock();
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
                vl.addAerolinea(Aerolinea(id,icao,nombreAero,pais,activoBool));
                fila = "";
                columnas.clear();
            }
        }
    }
    else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    is.close();
    std::cout << "Tiempo lectura de las aerolineas: " << ((clock() - lecturaAerolineas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

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
                vl.cargarRutas(icaoRuta,origen2,destino2);

            }
        }

    } else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    is.close();
    std::cout << "Tiempo lectura de las rutas: " << ((clock() - lecturaRutas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

#pragma endregion

    cout<< "Tamaño Aerolineas: " << vl.tamaWork() <<endl
         << "Tamaño aeropuertos: " << vl.tamaAeropuertos() << endl
         << "Tamaño rutas: " << vl.tamaRutas() << endl <<endl;

    try {
#pragma region Visualiza toda la información de la aerolínea Ryanair, RYR

    cout<<endl<<"------------------------------Información de la aerolínea Ryanair------------------------------"<<endl<<endl;
    Aerolinea aerolinea =  vl.buscaAerolinea("RYR");
     cout<<"Id: "<<aerolinea.getId() <<" Aerolinea: "<< aerolinea.getNombre() <<  " Icao : "
     <<  aerolinea.getIcao() << " Pais: " << aerolinea.getPais() << endl;
#pragma endregion
#pragma  region Muestra todas las aerolíneas activas.

        cout<<endl<<"--------------------------Aerolíneas activas--------------------------"<<endl<<endl;
        VDinamico<Aerolinea*> vectorActivas(vl.buscaAerolineasActiva());
        cout<<"Numero de aerolineas activas: "<< vectorActivas.tamlog()<<endl<<endl;
        for (int i = 0; i < vectorActivas.tamlog(); ++i) {
            string activo = " ";
            vectorActivas[i]->isActivo() ? activo = "Si" : activo ="No";
            cout<< "Id: "<< vectorActivas[i]->getId() << " Nombre: "<< vectorActivas[i]->getNombre()<< " Pais: " << vectorActivas[i]->getPais() <<" Activo: "<< activo <<endl;

        }

#pragma endregion
#pragma  region Busca todos los aeropuertos (origen) en los que opera Iberia Airlines, con icao IBE
    cout<<endl<<"------------------------------Aeropuertos (origen) en los que opera Iberia Airlines-------------------------------"<<endl<<endl;
    Aerolinea iberiaAirlines = vl.buscaAerolinea("IBE");
    VDinamico<Aeropuerto*> aeropuertosIberia  =  iberiaAirlines.getAeropuertosOrig();
    cout<<"Numero de aeropuertos que operan con iberia: "<< aeropuertosIberia.tamlog()<<endl<<endl;
    for (int j = 0; j < aeropuertosIberia.tamlog(); ++j) {
        cout<<"Id: "<<aeropuertosIberia[j]->getId()<<" Aeropuerto: "<< aeropuertosIberia[j]->getNombre() <<  " Iata : "
            <<  aeropuertosIberia[j]->getIata() << " Iso Pais: " << aeropuertosIberia[j]->getIsoPais() <<endl;

    }

#pragma  endregion
#pragma  region   Busca todas las rutas operadas por Iberia Airlines con origen en el aeropuerto de Málaga(AGP).
    cout<<endl<<"-----------------Rutas operadas por Iberia Airlines con origen en el aeropuerto de Málaga(AGP)-----------------"<<endl<<endl;
    //AeroRutasAGP
    VDinamico<Ruta*> aerorutasAGP = iberiaAirlines.getRutasAeropuerto("AGP");
    VDinamico<Ruta*> aerorutasMalaga;
    for (int j = 0; j < aerorutasAGP.tamlog(); ++j) {
        if(aerorutasAGP[j]->getOrigin()->getNombre() == "Málaga-Costa del Sol Airport"){
            aerorutasMalaga.insertar(aerorutasAGP[j]);
        }
    }

    cout<<"Numero de rutas: "<< aerorutasMalaga.tamlog()<<endl<<endl;
    for (int i = 0; i < aerorutasMalaga.tamlog(); ++i) {
        cout<<"Origen: "<<aerorutasMalaga[i]->getOrigin()->getNombre()<<"---> Destino: "<< aerorutasMalaga[i]->getDestination()->getNombre() <<endl;

    }

#pragma  endregion
#pragma region Aerolíneas que operan en España.
        cout<<endl<<"------------------------------Aerolíneas que operan en España------------------------------"<<endl<<endl;
        VDinamico<Aerolinea*> aerolineaEsp =  vl.getAerolineasPais("Spain");
        cout<<"Numero de aerolineas que operan en España: "<<aerolineaEsp.tamlog()<<endl<<endl;
        for (int i = 0; i < aerolineaEsp.tamlog(); ++i) {
            cout<< "Id: "<< aerolineaEsp[i]->getId() << " Nombre: "<< aerolineaEsp[i]->getNombre()<< " Pais: " << aerolineaEsp[i]->getPais() <<endl;
        }


#pragma endregion
    }catch (invalid_argument &e){
        cout<<e.what()<<endl;
    }
    catch(out_of_range &o){
        cout<<o.what()<<endl;
    }
    catch(bad_alloc &b){
        cout<<b.what()<<endl;
    }
    return 0;
}
