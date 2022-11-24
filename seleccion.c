#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "seleccion.h"

int selprim(Nodo **pa, int k) {
    Nodo *a = *pa;                                  
    if(a == NULL){                                  //Caso base, a esta vacio
        return 0;                                   //retorna 0 porque no habia un nodo
    }
    
    int cnt_left = selprim(&a->izq, k);             //iniciamos un contador que recuerda cuantos nodos llevamos guardados
    if (cnt_left == k){                             //Si a la izquierda hay k nodos
        *pa = a -> izq;                             //movemos el puntero a la izquierda
        selprim(&a ->der, 0);                       //mandamos a liberar recursivamente todos los nodos de la derecha (k=0 significa que guardamos 0 nodos)
        free(a);                                    //liberamos el nodo actual
        return cnt_left;                            //retornamos el numero de nodos guardados
    }
    
    int cnt_right = selprim(&a->der, k-cnt_left-1); //si los nos izquierdos no bastan
    return cnt_left+1+cnt_right;                    //vemos los nodos derechos
                                                    //buscamos a la derecha con k- nodos izquierdos-1(donde el 1 representa el nodo raiz anterior)
                                                    //retornamos el numero de nodos que pudimos guardar
}

Nodo *ultimos(Nodo *a, int *pk) {
    int guardar = *pk;                              //guardamos el valor al que apunta el puntero k (ultimos nodos a elegir)
    if(a == NULL){
        *pk=0;                                      //Caso base, a esta vacio
        return NULL;                                //retorna NULL porque no habia un nodo
    }

    Nodo* cnt_right = ultimos(a->der, &guardar);    //Iniciamos un contador derecho
    if(guardar == *pk){                             //Si guardar es igual a k
        return cnt_right;                           //retornamos el contador
    }
    int guardar2 = (*pk) - guardar -1;              //creamos una variable equivalente a los nodos pedidos - guardar derecho - el nodo actual
    Nodo* cnt_left = ultimos(a->izq, &guardar2 );
    Nodo *cpy = malloc(sizeof(Nodo));               //Copia de nodo actual a memoria reservada
    cpy->x = a->x;                                  //copia del valor del nodo
    cpy->izq = cnt_left;                            // a la izquierda esta lo que viene del contador izq
    cpy->der = cnt_right;                           // a la derecha estan los nodos que vienen del contador derecho    
    *pk= guardar + guardar2 + 1;                    //nuevo pk es la suma de ambos + nodo actual
    return cpy;                                     //retornamos el arbol copiado
}


