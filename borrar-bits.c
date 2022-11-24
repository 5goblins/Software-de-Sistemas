#include <stdio.h> 
#include <stdlib.h>
#include "borrar-bits.h"


typedef unsigned int uint;
uint borrar_bits(uint x, uint pat, int len) {
	unsigned int mask1 = ~((~0U << (len-1))<< 1); //deja (len) 1's a la derecha
	for (int i = 0; i < (sizeof(uint)<<3) -len +1; i++) { //para todo bit
	    if (((x>>i) & mask1) == pat) {            //si encuentro el patron con i shifts
	        unsigned mask2 = mask1 << i; // 0...0 1^{k} 0^{i}
	        x &= ~mask2;                 // borramos los bits iguales al patron
            i+=len-1;                    //nos saltamos el largo del patron para seguir buscando
		}
	}
  return x;
}
