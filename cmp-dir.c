#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

//nom subconjunto de nom2
//si nom y nom2 son files, deben ser iguales
//directorios nom2 pueden contener entradas que no estan en nom
void cmpdir(char *nom, char *nom2) {
    struct stat st_nom;
    struct stat st_nom2;
    int rc;
    int rc2;
    rc= stat(nom, &st_nom);
    rc2= stat(nom2, &st_nom2);

    if (rc!=0) { // No existe A
        printf("%s no existe\n",nom);
        exit(0);
    }
//////////////////////////////////////
    if (rc2!=0) { // No existe B
        printf("%s si existe, %s no existe\n",nom,nom2);
        exit(0);
    }
///////////////////////////////////////////
//DISTINTOS TIPOS DE ARCHIVO
    if ((S_ISREG(st_nom.st_mode) && S_ISDIR(st_nom2.st_mode)) || (S_ISDIR(st_nom.st_mode) && S_ISREG(st_nom2.st_mode))){
        //Error si son de tipos distintos
        if (S_ISREG(st_nom.st_mode)){
            printf("%s no es directorio, %s si es directorio\n",nom,nom2);
            exit(0);
        }
        else{
            printf("%s es directorio, %s no es directorio\n",nom,nom2);
            exit(0);
        }
    }
/////////////////////////////////////////////////
//ARCHIVOS SON REG FILES
    else if (S_ISREG(st_nom.st_mode) && S_ISREG(st_nom2.st_mode)) {
        char buf[st_nom.st_size+1];
        char buf2[st_nom2.st_size+1];
        int file = open( nom, O_RDONLY);
        if ( file == -1) {
            perror(nom);
            exit(1);
        }
        int file2 = open( nom2, O_RDONLY);
        if ( file2 == -1) {
            perror(nom);
            exit(1);
        }
        read(file, buf, st_nom.st_size);
        read(file2, buf2, st_nom2.st_size);
        int filecomp;
        filecomp = memcmp(buf,buf2,st_nom.st_size);
        close(file);
        close(file2);
        if (st_nom.st_size != st_nom2.st_size){
            //TAMAÑO ARCHIVOS NO SON IGUALES
            printf("%s y %s son de distinto tamanno\n",nom,nom2);
            exit(0);
        }
        if (filecomp !=0){
            //ARCHIVOS NO SON IGUALES
            printf("Contenidos de %s y %s difieren\n",nom,nom2);
            exit(0);
        }
        //archivos son iguales si no hubo error :)
    }
    
    //ARCHIVOS SON DIRECTORIOS

    else if (S_ISDIR(st_nom.st_mode) && S_ISDIR(st_nom2.st_mode)) {
        DIR *dir = opendir(nom);
        DIR *dir2 = opendir(nom2);
        if (dir == NULL) {
            perror(nom);
            exit(1);
        }
        if (dir2 == NULL) {
            perror(nom2);
            exit(1);
        }

        for (struct dirent *entry = readdir(dir); //PARA TODOS LOS ELEMENTOS DE A, DEBE HABER UNO EQUIVALENTE EN B
             entry != NULL;
             entry = readdir(dir)) {
            if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) {
                continue;
            }
            char *nom_arch= malloc(strlen(nom)+strlen(entry->d_name)+2);
            strcpy(nom_arch, nom);
            strcat(nom_arch, "/");
            strcat(nom_arch, entry->d_name);

            char *nom_arch2= malloc(strlen(nom2)+strlen(entry->d_name)+2);
            strcpy(nom_arch2, nom2);
            strcat(nom_arch2, "/");
            strcat(nom_arch2, entry->d_name);
            cmpdir(nom_arch, nom_arch2);
            free(nom_arch);
            free(nom_arch2);
        }
        closedir(dir);
        closedir(dir2);
    }
    else {
        fprintf(stderr, "Archivo %s es de tipo desconocido\n", nom);
        exit(1);
    }
}
int main(int argc, char *argv[]) {
    if (argc!=3) {
        fprintf(stderr, "uso: %s <arch|dir> <arch|dir>\n", argv[0]);
        exit(2);
    }
    //... complete aca la funcion main ...
    cmpdir(argv[1],argv[2]);
    printf("Es subconjunto\n");
    return 0;
}

