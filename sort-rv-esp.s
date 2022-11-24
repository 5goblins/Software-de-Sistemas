# sort: Ordena ascendentemente un arreglo de enteros sin signo usando un
# algoritmo ridiculamente ineficiente.

# La funcion sort esta programada en assembler RiscV. El codigo equivalente
# en C esta comentado, mostrando la ubicacion de las variables en los
# registros.  La funcion recorre el arreglo revisando que los elementos
# consecutivos esten ordenados.  Si encuentra 2 elementos consecutivos
# desordenados, los intercambia y reinicia el recorrido del arreglo
# desde el comienzo.  El arreglo esta ordenado cuando se recorre
# completamente sin encontrar elementos consecutivos desordenados.

.file "sort-rv.s"
.text
.globl sort         # Se necesita para que la etiqueta sea conocida en
# test-sort.c
.type sort, @function # typedef unsigned int uint;
sort:                   # void sort(uint nums[], int n) { // registros a0, a1
    addi    sp,sp,-64   #   // Apila registro de activacion
    sw      ra, 60(sp)  #   // resguarda direccion de retorno
    sw      a0,56(sp)   #   uint *p= nums; // p esta en sp+56
    addi    a1,a1,-1    #   uint *ult= &nums[n-1]; // ult esta en sp+52
    slli    a1,a1,2     #   // tamanno del arreglo
    add     a1,a0,a1
    sw      a1,52(sp)
    sw      a0,48(sp)   #   // nums esta en direccion sp+48
    mv      t0,a0       #   // p esta en registro t0
#   while (p<ult) {
    j       .while_cond #     // la condicion del while se evalua al final
    .while_begin:           #     // del ciclo para mayor eficiencia

    sw      t0,56(sp)   # resguardar p en memoria

# Hasta aca no puede modificar nada

    #################################################
    ### Comienza el codigo que Ud. debe modificar ###
    #################################################

# no puede alterar los registros sp, s0-s11, si lo hace debe resguardarlos
# en 0(sp), 4(sp), ... o 44(sp)
# El valor de p esta temporalmente en el registro t0
# No puede hacer mas trabajo que la comparacion (no puede usar ret)
/*
    lw      a0,0(t0)    #     int rc= strcmp(p[0], p[1]); // registro t1
    lw      a1,4(t0)
    sw      t0,56(sp)   # resguardar p en memoria antes de llamar a strcmp
    call    strcmp      #     // valor retornado queda en registro a0
#     // p ya no esta en el registro t0
    mv      t1,a0       #     // Dejar resultado de la comparacion en t1
*/
    
    mv      t1,x0       # inicializa variable rc      
    lw      a0,0(t0)    # string 1
    lw      a1,4(t0)    # string 2
    mv      t2,x0       # contador 1 = 0
    mv      t3,x0       # contador 2 = 0
    li      a2,32       # a2 = ' ' //espacio
    
    
.while1:
    lbu     a3,0(a0)      # a3 apunta a chars del string
    beq     a3,x0,.while2 #si char actual es 0, termina este while
    beq     a3,a2,.if1    # si: char actual distinto de ' ' ir a if1
    addi    a0,a0,1       # a0++
    j       .while1       # continuar ciclo
    
.if1:
    addi    a0,a0,1     # a0++  
    addi    t2,t2,1     # contador1 ++
    j       .while1     # volver al while1


.while2:
    lbu     a3,0(a1)      # a3 apunta a chars del string
    beq     a3,x0,.comp   #si char actual es 0, termina este while
    beq     a3,a2,.if2    # si: char actual distinto de ' ' ir a if1
    addi    a1,a1,1       # a1++
    j       .while2       # continuar ciclo
    
.if2:
    addi    a1,a1,1     # a1++  
    addi    t3,t3,1     # contador2 ++
    j       .while2     # volver al while2

.comp:
    blt     t3,t2,.rc1
    j       .decision
    
.rc1:
    addi    a4,x0,1
    mv      t1,a4
    
# En el registro t1 debe quedar la conclusion de la comparacion:
# si t1<=0 p[0] y p[1] estan en orden y no se intercambiaran.

    #################################################
    ### Fin del codigo que Ud. debe modificar     ###
    #################################################

# Desde aca no puede modificar nada
# Si t1>0 se intercambian p[0] y p[1] y se asigna p= noms para revisar
# nuevamente que los elementos esten ordenados desde el comienzo del arreglo

    .decision:              #     if (0>=rc) {
        lw      t0,56(sp)   #       // p esta en registro t0
        blt     zero,t1,.else
        addi    t0,t0,4     #       p++; // avanzar en arreglo de enteros
        j       .while_cond #     }

    .else:                  #     else { // intercambar p[0] y p[1], y reiniciar
        lw      a0,0(t0)    #       int aux= p[0]; // a0
        lw      a1,4(t0)    #       int aux2= p[1];
        sw      a0,4(t0)    #       p[0]= aux2;
        sw      a1,0(t0)    #       p[1]= aux;
        lw      t0,48(sp)   #       p= noms;
#     }

    .while_cond:            #     // se evalua la condicion del while
    lw      t1,52(sp)   #     // ult esta en t1
    bltu    t0,t1,.while_begin #  // Condicion del while es p<ult
#   }
lw      ra,60(sp)   #   // Se restaura direccion de retorno
addi    sp,sp,64    #   // Desapila registro de activacion
ret			# }
