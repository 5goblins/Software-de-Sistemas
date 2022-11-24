#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SIZELIN 10

int main(int argc, char *argv[]) {
    if (argc<3) {
        fprintf(stderr, "Uso: %s <archivo> <l1> <l2> <l3> ...\n", argv[0]);
        exit(1);
    }
    char *nom= argv[1];  // El nombre del archivo
    // l1 es atoi(argv[2]), l2 es atoi(argv[3]), ..., ln es atoi(argv[argc-1])
    char bufferW [10];
    char bufferR [10];

    FILE *f = fopen(nom, "r+" );


    for (int i= 2; i<argc; i++){
        fseek(f, 10*(atoi(argv[i])), SEEK_SET);        //busca la linea actual
        fread( bufferR, sizeof(char), 10, f);          //la lee
        fseek(f, 10*(atoi(argv[i])), SEEK_SET);        //vuelve a linea actual
        fwrite(bufferW, sizeof(char), 10, f);          //escribe la linea anterior sobre la actual
        strncpy(bufferW,bufferR,10);                   //copia el contenido de la linea actual para sobreescribir la siguiente
    }
    fseek(f, 10*(atoi(argv[2])), SEEK_SET);            //sobreescribo el primer elemento de la lista
    fwrite(bufferW, sizeof(char), 10, f);              //con el ultimo obtenido
    fclose(f);                                         //cerramos el archivo
    return 0;
}

