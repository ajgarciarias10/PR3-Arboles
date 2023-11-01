#ifndef PRACTICA_3_AVL_H
#define PRACTICA_3_AVL_H
#include <string>
#include <iostream>
template<class T>
class Nodo{
public:
    Nodo<T> *izq;
    Nodo<T> *der;
    T dato;
    //Factor de equilibrio
    char  bal;
    //Constructor por defecto de nodo
    Nodo():izq(nullptr),der(nullptr){}
    //Constructor parametrizado de nodo
    Nodo(const T &dato): izq(nullptr),der(nullptr),dato(dato){}
};
template<class T>
class AVL {
private:
    //Raiz del arbol
    Nodo<T> *raiz;
    //Recorre en Inorden
    void inorden(Nodo<T> *p, int nivel, VDinamico<T*> &v);
    //Funcion insertarDatoPrivado
    int insertaDato(const T &ele, Nodo<T>* &p);
    //Funcion  privada rotar izquierda
    void rotIzq(Nodo<T>* &p);
    //Funcion privada rotar derecha
    void rotDer(Nodo<T>* &p);
    //Metodo BorraArbol
    void borraArbol(Nodo<T>* nodoABorrar);
    //Constructor copia privado
    Nodo<T>*  copiaAVL(const Nodo<T> *orig) ;
    //Metodo buscarClave privadp
    Nodo<T> *buscaClave(const T &ele,Nodo<T> *p);
public:
    int tama;
    //Constructor por defecto
    AVL();
    //Constructor copia
    AVL(const AVL<T> &orig);
    //Operator =
    AVL<T>& operator=(const AVL<T>& orig);
    //Recorre publico en Inorden
    VDinamico<T*> recorreInorden() ;
    //Metodo de inserccion de un dato
    bool insertar (const T &ele);
    //Obtenemos el numero de elementos del arbol
    unsigned int numElementos(Nodo<T> *p, int nivel);
    //Obtengo la altura del árbol
    unsigned int altura(Nodo<T> *nodo);
    //Destructor de AVL
    ~AVL(){ borraArbol(raiz);};
    //Metodo de busquedaRecursiva
    T* busquedaRecursiva(const T &ele);
    //Metodo de busqueda iterativa
    T* busquedaIterativa(const T &dato);

    int getTama() const {
        return tama;
    }
};

/**
 * @brief Constructor por defecto
 * @tparam T
 */
template<class T>
AVL<T>::AVL():raiz(nullptr){}
/**
 * @brief Metodo publico constructor copia con acceso al privado
 * @tparam T
 * @param orig
 */
template<class T>
AVL<T>::AVL(const AVL<T> &orig) {
        raiz =  copiaAVL(orig.raiz);


}
/**
 * @brief Metodo Constructor Copia privado //Reccorre en preorden
 * @tparam T
 * @param orig
 */
template<class T>
Nodo<T>* AVL<T> ::copiaAVL(const Nodo<T> *orig){
    Nodo<T> *nuevaBola = nullptr;
    if (orig) {
        nuevaBola =new Nodo<T>(*orig);
            nuevaBola->izq = copiaAVL(orig->izq);
            nuevaBola->der = copiaAVL(orig->der);
    }
    return nuevaBola;
}
/**
 * @brief Operador de asignacion =
 * @tparam T
 * @param orig
 * @return
 */
template <class T>
AVL<T> &AVL<T>::operator=(const AVL<T> &orig) {
    //En caso de que lo que me pase no sea igual a lo que ya tengo
    if(this!=orig){
        //Borramos el arbol actual
        borraArbol(raiz);
        //Copiamos el nuevo con la raiz que teniamos
        copiaAVL(orig.raiz);
    }
    return *this;

}
/**
 * @brief Metodo que borra el árbol en postOrden
 * @tparam T
 * @param orig
 */
template <class  T>
void AVL<T>::borraArbol(Nodo<T>* orig) {
    if(orig){
        borraArbol(orig->izq);
        borraArbol(orig->der);
        //Borramos en posroden
        delete orig;
        orig = nullptr;
    }
}

/**
 * @brief Metodo que rota a derechas los nodos
 * @tparam T
 * @param p
 * @param nivel
 */
template<typename T>
void AVL<T>::rotDer(Nodo<T>* &p){
    Nodo<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;
}
/**
 * @brief Metodo que rota a izquierda los nodos
 * @tparam T
 * @param p
 */
template<typename T>
void AVL<T>::rotIzq(Nodo<T>* &p){
    Nodo<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0) r->bal += q->bal;
}

/**
 * @brief Metodo publico insertar
 * @tparam T
 * @param ele
 * @return
 */
template<typename T>
bool AVL<T>::insertar(const T &ele) {
    //Vemos si el dato esta repetido
    if(!busquedaRecursiva(ele)){
        //Inserto el dato si la busqueda recursiva es nula
        insertaDato(ele,raiz);
        return true;
    }
    //Si esta repetido
    return false;
}

/***
 * @brief Metodo que recorre en Innorden
 * @post Empieza por los nodos de la izquierda luego llega al raiz y por ultimo se mete en los nodos de la derecha
 * @tparam T
 * @param p
 * @param nivel
 */
template <class T>
void AVL<T>::inorden (Nodo<T> *p, int nivel, VDinamico<T*>& vaerolinea){
    if (p){
        //Recorremos primero por la izquierda aumentando profundidad hasta llegar a null
        inorden (p->izq, nivel+1,vaerolinea);
        //Insertamos la direccion del dato de la raiz
        vaerolinea.insertar(&(p->dato));
        //Recorremos SEGUNDO por la derecha aumentando profundidad hasta llegar a null
        inorden (p->der, nivel+1,vaerolinea);
    }
}




/**
 * @brief Metodo Tema 11 que inserta dato en una arbol de tipo AVL
 * @post Inserccion en innorden
 * @tparam T
 * @param dato
 * @param c
 * @return
 */
template <class  T>
int AVL<T>::insertaDato(const T &dato, Nodo<T> *&c) {
    Nodo<T> *p = c;
        int deltaH = 0;
        if (!p){
            p = new Nodo<T>(dato);
            c = p; deltaH=1;
        }
        else if (dato > p->dato){
            if (insertaDato(dato, p->der)){
                p->bal--;
                if (p->bal == -1) deltaH=1;
                else if (p->bal == -2) {
                    if (p->der->bal == 1) rotDer(p->der);
                    rotIzq(c);
                } } }
        else if (dato < p->dato){
            if (insertaDato(dato, p->izq)){
                p->bal++;
                if (p->bal==1) deltaH = 1;
                else if (p->bal == 2){
                    if (p->izq->bal == -1) rotIzq(p->izq);
                    rotDer(c);
                } } }
        return deltaH;


}
/**
 * @brief Devuelve el numElementos
 * @post Devuelve el numero de elementos recorriendo el arbol en preorden
 * @tparam T
 * @param p
 * @param nivel
 * @return
 */
template <class T>
unsigned  int AVL<T>::numElementos(Nodo<T> *p, int nivel) {
    if (p){
        //Aumentamos el tamaño para ir recorriendo
        tama++;
        numElementos (p->izq, nivel+1);
        numElementos (p->der, nivel+1);
    }
    //Devuelvo el tamaño del arbol
    return  tama;

}

/**
 * @brief Metodo que calcula la altura de los arboles
 * @tparam T
 * @param nodo
 * @return
 */
template <class T>
unsigned int AVL<T>::altura(Nodo<T> *nodo) {
    //1er lugar vemos si el nodo es nulo
    if(nodo){
        //Calculamos la altura del arbol por la izquierda de manera recursiva;
        int alturaArbolIzquierda = altura(nodo->izq);
        //Idem Derecha
        int alturaArbolDerecha = altura(nodo->der);
        //Calcular AlturaMasAlta del arbol
        int alturaMasAlta =  alturaArbolIzquierda>alturaArbolDerecha ? alturaArbolIzquierda : alturaArbolDerecha;

        //Mas 1 por que tengo que contar el nodo raiz
        return alturaMasAlta+1;

    }else{
        return 0;
    }

}
/**
 * @brief Metodo que busca la clave dentro de un árbol, privado
 * @tparam T
 * @param ele
 * @param p
 * @return
 */
template <class T> // función privada
Nodo<T> *AVL<T>::buscaClave (const T &ele, Nodo<T> *p){
    if (!p)
        return 0;
    else if (ele < p->dato)
        return buscaClave (ele, p->izq);
    else if (ele > p-> dato)
        return buscaClave (ele, p->der);
    else return p;
}

template<class T>
T*  AVL<T>::busquedaRecursiva(const T &ele) {
    Nodo<T> *p = buscaClave (ele, raiz);
    //En caso de que se encuentre
    if (p) {
        //Devolvemos la direccion de memoria tras la busqueda
        return  &(p->dato);
    }
    //En caso de no encontrar nada devolvemos nullptr
    return nullptr;

}
/**
 * @brief Metodo que realiza la busqueda iterativa
 * @tparam T
 * @param dato
 * @return
 */
template <class  T>
T* AVL<T>::busquedaIterativa(const T &dato) {
    T* buscado;
    Nodo<T> *p=raiz;
    while (raiz){
        //Si el dato es menor nos vamos para la izquierda
        if (dato<p->dato){
            p=p->izq;
        }else {
            //Si el dato es mayor nos vamos para la derecha
            if (dato > p->dato) {
                p - p->der;
                //Si tampoco esta en la derecha significa que estamos en el resultado
            } else {
                buscado = &p->dato;
                return buscado;
            }
        }
    }
    return 0;
}
/**
 * @brief Metodo para recorrer en innorden publico que llama al innorden privado
 * @tparam T
 * @return
 */
template <class  T>
VDinamico<T*> AVL<T>::recorreInorden() {
    //Vector de aeropuertos ya ordenado
    VDinamico<T*> vaerolinea;
    //Lo envio a ordenar
    inorden(raiz,0,vaerolinea);
    //Tras ordenarse
    return vaerolinea;

}









#endif //PRACTICA_3_AVL_H

