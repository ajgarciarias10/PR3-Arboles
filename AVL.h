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
    Nodo(T &dato): izq(nullptr),der(nullptr),dato(dato){}
};

template<class T>
class AVL {
private:
    Nodo<T> *raiz;
    //Funcion privada busca recrusiva elemento en el arbol
    Nodo<T>* buscaRec(T &ele, Nodo<T> *p);
    //Recorre en Inorden
    void inorden(Nodo<T> *p, int nivel, VDinamico<T*> &v);
    //Funcion insertarDatoPrivado
    int insertaDato(T &ele, Nodo<T>* &p);
    //Funcion  privada rotar izquierda
    void rotIzq(Nodo<T>* &p);
    //Funcion privada rotar derecha
    void rotDer(Nodo<T>* &p);
    //Metodo BorraArbol
    void borraArbol(Nodo<T>* nodoABorrar);
    //Constructor copia privado
    Nodo<T>*  copiaAVL(const Nodo<T> &orig) ;
public:
    int tama;
    //Constructor por defecto
    AVL();
    //Constructor copia
    AVL(const AVL<T> &orig);
    //Operator =
    AVL<T>& operator=(const AVL<T>& orig);
    //Recorre publico en Inorden
    void recorreInorden() { inorden(raiz,0); }
    //Funcion publica busca elemento iterativa en el arbol
    bool buscaIT(T &ele, T &result);
    //Metodo de inserccion de un dato
    bool insertar (T &ele);
    //Obtenemos el numero de elementos del arbol
    unsigned int numElementos(Nodo<T> *p, int nivel);
    //Obtengo la altura del árbol
    unsigned int altura(Nodo<T> *nodo);
    //Destructor de AVL
    ~AVL(){ borraArbol(raiz);};
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
    //Si no es el mismo árbol entonces devolvemos una copia
    if(this !=orig){
        raiz =  copiaAVL(orig.raiz);
    }

}
/**
 * @brief Metodo Constructor Copia privado //Reccorre en preorden
 * @tparam T
 * @param orig
 */
template<class T>
Nodo<T>* AVL<T> ::copiaAVL(const Nodo<T> &orig){
    Nodo<T> *nuevaBola;
    if (orig) {
        nuevaBola =new Nodo<T>(*orig);
        if (orig.izq) {
            nuevaBola->izq = copiaAVL(orig.izq);
        }
        if (orig.der) {
            nuevaBola->der = copiaAVL(orig.der);
        }
    }
    else{
        //Devuelve un nulo en caso de que no haya nada que copiar
        return nullptr;
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
bool AVL<T>::insertar(T &ele) {
    return insertaDato(ele, raiz);
}
/**
 * @brief Busca Clave Recursiva
 * @tparam T 
 * @param ele 
 * @param p 
 * @return 
 */
template <class T>
Nodo<T> *AVL<T>::buscaRec (T &ele, Nodo<T> *p){
    if (!p)
        return 0;
    else if (ele < p->dato)
        return buscaRec (ele, p->izq);
    else if (ele > p-> dato)
        return buscaRec (ele, p->der);
    else return p;
}
/***
 * @brief Metodo que recorre en Innorden
 * @post Empieza por los nodos de la izquierda luego llega al raiz y por ultimo se mete en los nodos de la derecha
 * @tparam T
 * @param p
 * @param nivel
 */
template <class T>
void AVL<T>::inorden (Nodo<T> *p, int nivel, VDinamico<T*> &vaerolinea){
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
int AVL<T>::insertaDato(T &dato, Nodo<T> *&c) {
    Nodo<T> *p = c;
        int deltaH = 0;
        if (!p){
            p = new Nodo<T>(dato);
            c = p; deltaH=1;
        }
        else if (dato > p->dato){
            if (inserta(p->der, dato)){
                p->bal--;
                if (p->bal == -1) deltaH=1;
                else if (p->bal == -2) {
                    if (p->der->bal == 1) rotDecha(p->der);
                    rotIzqda(c);
                } } }
        else if (dato < p->dato){
            if (inserta(p->izq, dato)){
                p->bal++;
                if (p->bal==1) deltaH = 1;
                else if (p->bal == 2){
                    if (p->izq->bal == -1) rotIzqda(p->izq);
                    rotDecha(c);
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
 * @brief Metodo que busca iterativamente. llamando a la busqueda recursiva
 * @tparam T
 * @param ele
 * @param result
 * @return
 */
template <class T>
bool AVL<T>::buscaIT (T &ele, T &result){
    Nodo<T> *p = buscaRec(ele, raiz);
    if (p) {
        result = p->dato;
        return true;
    }
    return false;
}










#endif //PRACTICA_3_AVL_H

