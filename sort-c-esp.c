#include <string.h>

void sort(char **noms, int n) {
  char **ult= &noms[n-1];
  char **p= noms;
  while (p<ult) {
    ////////////////////////////////////////////
    // Comienza el codigo que Ud. debe modificar
    ////////////////////////////////////////////

    int rc;

    char *r1=p[0];
    int cnt1 = 0;
    while (*r1 != 0) {
        if (*r1 == ' ') {
            cnt1++;
        }
        r1++;
    }                                  //Contamos espacios de p0

    int cnt2 = 0;
    char *r2=p[1];
    while (*r2 != 0) {
        if (*r2 == ' ') {
            cnt2++;
        }
        r2++;        
    }                                  //Contamos epacios de p1
    
    if (cnt1<=cnt2){                   // si p0 tiene menos espacios que p1
        rc=0;
    }
    else{
        rc=1;
    }
    //si p0 tiene menos o iguales espacios a p1, rc debe ser -1 o 0 respectivamente
    //si p0 tiene mas espacios que p1, rc debe ser 1
    ////////////////////////////////////////////
    // Fin del codigo que Ud. debe modificar
    ////////////////////////////////////////////
    if (rc<=0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= noms;
    }
  }
}
