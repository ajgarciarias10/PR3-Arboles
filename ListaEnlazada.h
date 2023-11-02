#ifndef PRACTICA_2_LISTAENLAZADA_H
#define PRACTICA_2_LISTAENLAZADA_H

#include <stdexcept>
#include "Ruta.h"

/**
 * @file ListaEnlazada.h
 * @brief Practica 2 EEDD
 * @date 19/10/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @return
 */

template<class T>
class ListaEnlazada {
    /**
     * Utilizaremos nodos enlazados para utilizar Listas Enlazadas
     * @tparam N
     */
    template<class N>
    class Nodo {
        public:
            N dato;
            Nodo *sig;
            //Destructor de nodo
            ~Nodo(){}
            //Constructor parametrizado
            Nodo(const N &_dato, Nodo *_sig=nullptr): dato(_dato),sig(_sig){}
    };
    //Declaramos los nodos a utilizar en la lista y el tam de la lista
    Nodo<T> * cabecera;
    Nodo<T> * cola;
    unsigned long int tam;

public:
/**
 * @brief Declaramos la clase Iterador que la vamos a utilizar para movernos por las listas Enlazadas
 * @tparam I
 */
    class Iterador{
        private:
            Nodo<T> *nodo;
        public:
            //Devuelve el nodo en el que estamos
            Nodo<T> *getNodo() const {return nodo;}
            Iterador(Nodo<T> *_nodo= nullptr):nodo(_nodo){}
            //Devuelve un bool que indica si el iterador esta en el fin
            bool fin(){return nodo== nullptr;}
            //Devuelve el nodo siguiente
            void siguiente(){ nodo=nodo->sig;}
            //Devuelve el dato a donde apunta el iterador
            T &dato(){return nodo->dato;}
            ~Iterador(){}
    };

    //Constructor por defecto de lisata enlazada
    ListaEnlazada();
    //Destructor de lista enlazada
    ~ListaEnlazada();
    //Constructor de copia
    ListaEnlazada(const ListaEnlazada &orig);
    //Operador=
    ListaEnlazada &operator=(const ListaEnlazada &orig);
    //Constructor por defecto de iterador
    Iterador iterador() ;
    void insertaInicio(const T &dato);
    void insertaFin(const T &dato);
    void inserta(Iterador &i,const T &dato);
    void insertaDetras(Iterador &i,const T& dato);
    void borraInicio();
    void borraFinal();
    void borra(Iterador &i);
    int Tam();
    ListaEnlazada<T>& concatena(const ListaEnlazada<T> &lista);
    ListaEnlazada<T> operator+(const ListaEnlazada<T> &lista);

    /**
     * @brief Metodo que devuelve puntero inicial
     * @return cabecera->dato
     */
    T &inicio(){
        if (!cabecera)
            throw std::invalid_argument("No existe ese elemento");
        return cabecera->dato;
    };
    /**
     * @brief Metodo que devuelve el puntero final
     * @return cola->dato
     */

    T &fin(){
        if (!cola)
            throw std::invalid_argument("No existe ese elemento");
        return cola->dato;
    };

};

/**
 * @brief Obtiene el tamaño de la lista enlazada
 * @return Tamaño de la lista
 */
template<class T>
int ListaEnlazada<T>::Tam() {return tam;}

/**
 * @brief Obtiene iterador para recorrer la lista enlazada
 * @tparam T
 * @return Iterador que apunta al primer nodo de la lista
 */
template<class T>
typename ListaEnlazada<T>::Iterador ListaEnlazada<T>::iterador(){
    return Iterador(cabecera);
}

/**
 * @brief Operator + de dos listas
 * @tparam T
 * @param lista lista que vamos a enlazar
 * @return Nueva lista con las dos listas concatenadas
 */
template<class T>
ListaEnlazada<T> ListaEnlazada<T>::operator+(const ListaEnlazada<T> &lista){
    ListaEnlazada<T> suma(*this);
    Nodo<T>* p=lista.cabecera;
    //While para ir creando memoria e ir insertando ambas listas
    while (p){
        Nodo<T> *nuevo;
        suma.tam++;
        nuevo = new Nodo<T>(p->dato,0);
        //Si la lista estaba vacia, ponemos la cabecera apuntando al nuevo nodo
        if (suma.cabecera == 0)
            suma.cabecera = nuevo;
        if (suma.cola != 0)
            suma.cola->sig = nuevo;
        suma.cola = nuevo;

        p=p->sig;
    }
    return suma;
}

/**
 * @brief Concatena dos listas
 * @tparam T
 * @param lista
 * @return Lista modificada concatenada con la lista que llega por cabecera
 */
template<class T>
ListaEnlazada<T> &ListaEnlazada<T>::concatena(const ListaEnlazada<T> &lista) {
    Nodo<T>* puntCab= lista.cabecera;
    while(puntCab){
        Nodo<T> *pnew  =new Nodo<T>(puntCab->dato,0);
        tam++;
        if(cabecera == 0){
            cabecera = pnew;
        }
        if(cola !=0){
            cola->sig = pnew;
        }
        cola = pnew;
        puntCab = puntCab->sig;
    }
    return *this;
}

/**
 * @brief Borra un nodo de la lista con iterador
 * @tparam T
 * @param iterador que apunta al nodo al que se va a borrar
 */
template<class T>
void ListaEnlazada<T>::borra(ListaEnlazada::Iterador &iterador) {
    Nodo<T> *anterior;
    if (!iterador.fin()) {
        tam--;
        if (iterador.getNodo() == cabecera){
            borraInicio();
            return;
        }
        if (iterador.getNodo()==cola){
            borraFinal();
            return;
        }
        anterior=cabecera;
        while(anterior->sig->dato!=iterador.getNodo()->dato)
            anterior=anterior->sig;
        anterior->sig = iterador.getNodo()->sig;
        delete iterador.getNodo();
    }
}

/**
 * @brief Borra el ultimo nodo de la lista
 * @tparam T
 */
template<class T>
void ListaEnlazada<T>::borraFinal() {
    Nodo<T> *aux= nullptr;
    if (cabecera!=cola){
        tam--;
        aux=cabecera;
        while(aux->sig!=cola)
            aux=aux->sig;

        delete cola;
        cola=aux,
        aux->sig= nullptr;
    }else{ //Por si hay 1 o ninguno
        if(cabecera){
            delete cabecera;
            cabecera= nullptr;
            cola= nullptr;
            tam=0;
        }
    }
}

/**
 * @brief Borra el primer nodo de la lista
 * @tparam T
 */
template<class T>
void ListaEnlazada<T>::borraInicio() {
    //Primero comprobamos que hay elementos
    if (cabecera){
        tam--;
        Nodo<T> *aux=cabecera;
        cabecera=cabecera->sig;
        delete aux;
        //Si cuando hemos borrado, cabecera, era el unico elemento que habia, quitamos la cola
        if(!cabecera)
            cola= nullptr;
    }
}

/**
 * @brief Inserta un nuevo nodo delante del iterador
 * @tparam T
 * @param iterador que apunta a un nodo
 * @param dato contenido del nodo que vamos a insertar
 */
template<class T>
void ListaEnlazada<T>::insertaDetras(ListaEnlazada::Iterador &iterador, const T &dato) {
    if (!iterador.fin()){
        tam++;
        Nodo<T>* nuevo;
        nuevo=new Nodo<T>(dato,iterador.getNodo()->sig);
        iterador.getNodo()->sig=nuevo;
        //Si se da el caso de que el iterador sea igual que la cola, la actualizamos
        if (iterador.getNodo()==cola){
            cola->sig=nuevo;
            cola=nuevo;
        }
    }
}

/**
 * @brief Inserta un nuevo nodo detras del iterador
 * @tparam T
 * @param iterador que apunta a un nodo
 * @param dato contenido del nodo que vamos a insertar
 */
template<class T>
void ListaEnlazada<T>::inserta(ListaEnlazada::Iterador &iterador,const T &dato) {
    if (!iterador.fin()){
        tam++;
        //Si es el primer elemento de la lista, insertamos en el inicio
        if(iterador.getNodo()==cabecera) {
            insertaInicio(dato);
            return;
        }
        Nodo<T>* aux= nullptr;
        aux=cabecera;
        //Buscamos hasta que lleguemos al iterador
        while (aux->sig!=iterador.getNodo())
            aux=aux->sig;
        //Al terminar el while, aux esta en la posicion del iterador
        //insertamos en la siguiente posicion del iterador el nuevo nodo
        Nodo<T> *nuevo;
        nuevo=new Nodo<T>(dato,iterador.getNodo());
        aux->sig=nuevo;
    }
}

/**
 * @brief Inserta un nodo en el final de una lista
 * @tparam T
 * @param dato del nodo que vamos a insertar
 */
template<class T>
void ListaEnlazada<T>::insertaFin(const T &dato) {
    Nodo<T> *nuevo=new Nodo<T>(dato, nullptr);
    //Si la lista no estaba vacia, actualizamos la cola siguiente a nuevo
    if (cola)
        cola->sig=nuevo;
    //Si la cabecera es igual a null, significa que estaba vacia y la cabecera ahora es el nuevo nodo
    if (!cabecera)
        cabecera=nuevo;
    cola=nuevo;
    tam++;
}

/**
 * @brief Inserta un nodo en el principio de una lista
 * @tparam T
 * @param dato del nodo que vamos a insertar
 */
template<class T>
void ListaEnlazada<T>::insertaInicio(const T &dato) {
    Nodo<T> *nuevo=new Nodo<T>(dato, cabecera);
    //Si cola esta en null, significa que no habia ningun elemento y apuntamos cola al nuevo nodo
    if (!cola)
        cola=nuevo;
    //Actualizamos la cabecera
    cabecera=nuevo;
    tam++;
}

/**
 * @brief Operador = que asigna a un lista otra lista
 * @tparam T
 * @param orig lista que vamos a obtener
 * @return lista orig
 */
template<class T>
ListaEnlazada<T> &ListaEnlazada<T>::operator=(const ListaEnlazada<T> &orig) {
    if(this!=&orig){
        //Si la lista esta llena, la borramos
        if(cabecera){
            Nodo<T> *aux=cabecera;
            while (aux){
                cabecera=cabecera->sig,
                delete aux;
                aux=cabecera;
            }
            cola= nullptr;
        }

        //Empezamos a copiar, para ello inicializamos los atributos de la lista
        cabecera= nullptr;
        cola= nullptr;
        tam=orig.tam;
        Nodo<T> *p=orig.cabecera;

        while (p){
            Nodo<T>*aux= new Nodo<T>(p->dato, nullptr);
            //Si la cola existe actualizamos la cola siguiente al nuevo nodo
            if (cola)
                cola->sig=aux;
            //Inicializo la cabecera cuando empiece a copiarla, es decir, cuando vale nullptr
            if (!cabecera)
                cabecera=aux;
            //Actualizamos la cola y pasamos al siguiente nodo de la lista
            cola=aux;
            p=p->sig;
        }
    }
    return *this;
}

/**
 * @brief Constructor copia de una lista
 * @tparam T
 * @param orig lista que vamos a copiar
 */
template<class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &orig) {
    cabecera= nullptr;
    cola= nullptr;
    tam=orig.tam;
    Nodo<T> *p=orig.cabecera;
    while (p){
        Nodo<T>*aux= new Nodo<T>(p->dato, nullptr);
        //Si la cola existe actualizamos la cola siguiente al nuevo nodo
        if (cola)
            cola->sig=aux;
        //Inicializo la cabecera cuando empiece a copiarla, es decir, cuando vale nullptr
        if (!cabecera)
            cabecera=aux;
        //Actualizamos la cola y pasamos al siguiente nodo de la lista
        cola=aux;
        p=p->sig;
    }
}

/**
 * @brief Constructor por defecto de una lista
 * @tparam T
 */
template <class T>
ListaEnlazada<T>::ListaEnlazada():cabecera(nullptr),cola(nullptr),tam(0){}

/**
 * @brief Destructor de una lista
 * @post Borra desde la cabecera hasta que llega a null
 * @tparam T
 */
template <class T>
ListaEnlazada<T>::~ListaEnlazada(){
    //Borra si esta llena
    if(cabecera){
        Nodo<T> *aux=cabecera;
        while (aux){
            cabecera=cabecera->sig;
            delete aux;
            aux=cabecera;
        }
        cola= nullptr;
    }
}


#endif //PRACTICA_2_LISTAENLAZADA_H
