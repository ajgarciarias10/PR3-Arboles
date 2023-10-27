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

    void preorden(Nodo<T> *p, int nivel);
    void inorden(Nodo<T> *p, int nivel);
    void postorden(Nodo<T> *p, int nivel);
    Nodo<T>* buscaClave(T &ele, Nodo<T> *p);    //Funcion privada de Busca()
    bool insertaDato(T &ele, Nodo<T>* &p);    //Funcion privada de Insertar()
    void rotIzq(Nodo<T>* &p);
    void rotDer(Nodo<T>* &p);
    Nodo<T>*  copiaAVL(const Nodo<T> &orig) ;
public:
    AVL();
    AVL(const AVL<T> &orig);
    void recorrePreorden() { preorden(raiz,0); }
    void recorreInorden() { inorden(raiz,0); }
    void recorrePostorden() { postorden(raiz,0); }
    bool buscar (T &ele, T &result);    //Funcion pública de
    bool insertar (T &ele);    //Funcion publica de insertaDato()

};

/*Falta copia, reccorre que guarda el arbol en un vector, inserta dato tema 11, de izquierda derecha
*/


template<class T>
AVL<T>::AVL():raiz(nullptr){}

template <class T>
void AVL<T>::preorden (Nodo<T> *p, int nivel){
    if (p){
        preorden (p->izq, nivel+1);
        preorden (p->der, nivel+1);
    }
}

template <class T>
void AVL<T>::inorden (Nodo<T> *p, int nivel){
    if (p){
        inorden (p->izq, nivel+1);
        inorden (p->der, nivel+1);
    }
}

template <class T>
void AVL<T>::postorden (Nodo<T> *p, int nivel){
    if (p){
        postorden (p->izq, nivel+1);
        postorden (p->der, nivel+1);
    }
}

template <class T>
Nodo<T> *AVL<T>::buscaClave (T &ele, Nodo<T> *p){
    if (!p)
        return 0;
    else if (ele < p->dato)
        return buscaClave (ele, p->izq);
    else if (ele > p-> dato)
        return buscaClave (ele, p->der);
    else return p;
}

template <class T>
bool AVL<T>::buscar (T &ele, T &result){
    Nodo<T> *p = buscaClave (ele, raiz);
    if (p) {
        result = p->dato;
        return true;
    }
    return false;
}

template<typename T>
bool AVL<T>::insertaDato(T &ele, Nodo<T>* &p) {
    if (!p) {
        p = new Nodo<T> (ele);
        return true;
    } else {
        if ( ele < p->dato )
            return insertaDato(ele, p->izq);
        else if ( ele > p->dato )
            return insertaDato (ele, p->der);
    }
    //Si el elemento está duplicado
    return false;
}

template<typename T>
bool AVL<T>::insertar(T &ele) {
    return insertaDato(ele, raiz);
}

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
 * @brief Metodo publico constructor copia con acceso al privado
 * @tparam T
 * @param orig
 */
template<class T>
AVL<T>::AVL(const AVL<T> &orig) {
    //Si no es el mismo árbol entonces devolvemos una copia
    if(this !=orig){
        return copiaAVL(orig);
    }

}
/**
 * @brief Metodo Constructor Copia privado
 * @tparam T
 * @param orig
 */
template<class T>
Nodo<T>* AVL<T> ::copiaAVL(const Nodo<T> &orig){
    Nodo<T> *nuevaBola;
    if (orig) {
        //raiz=orig.raiz;
        if (orig.izq) {
            nuevaBola =new Nodo<T>(orig.dato);
            nuevaBola->izq = copiaAVL(orig.izq);
            nuevaBola->dato = orig.dato;
        }
        if (orig.der) {
            nuevaBola=new Nodo<T>(orig.dato);
            nuevaBola->der = copiaAVL(orig.der);
            nuevaBola->dato = orig.dato;
        }
    }
    return nuevaBola;
}

#endif //PRACTICA_3_AVL_H

