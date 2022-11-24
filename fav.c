#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "fav.h"

int favorables_par(int n, int sum, int rep, int p) {
  pid_t pids[p];
  int in_fds[p];
  for(int j=0; j<p; j++){
    int fds[2];
    pipe(fds);
    init_rand_seed();
    pids[j] = fork();
    if(pids[j] == 0){ // caso hijo
      close(fds[0]); // cerramos lectura, hijo solo escribe
      int fav_hijo = favorables(n, sum, rep/p);
      write(fds[1], &fav_hijo, sizeof(fav_hijo));
      exit(0); // sale del fork
    }
    else{ // caso padre
      close(fds[1]); // Cerramos escritura
      in_fds[j] = fds[0];
    }
  }
  ///////padre///////
  int fav= 0;    // número de casos favorables
  for(int j=0; j<p; j++){ //para cada hijo
    int fav_hijo;         //int favorables de hijos
    leer(in_fds[j], &fav_hijo, sizeof(fav_hijo));   //leemos hijo actual
    fav+=fav_hijo;                     //agregamos sus casos favorables al total
    close(in_fds[j]);                  //cerramos
    waitpid(pids[j], NULL, 0);
  }
  return fav;                         //al final retornamos los fav totales
}
