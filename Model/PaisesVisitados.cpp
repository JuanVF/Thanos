#include <iostream>
#include <string>
#include <Model/utils.h>
#include <Model/thanos.h>
//#include <Model/jsonmanager.h>


// Rango 1 = 30%    | 0-2 paises visitados
// Rango 2 = 25%    | 3-10 paises visitados
// Rango 3 = 20%    | 11-15 paises visitados
// Rango 4 = 15%    | 16-25 paises visitados
// Rango 5 = 10%    | 26+   paises visitados
//Esta funcion se encargara de seleccionar el numero de paises visitados
//Esto se hace mediante un random y la probabilidad de cada rango
int PaisesVisitados::seleccionarRangoViajes(){
    int random_int = Utils().getRandom(1,100);
    if (random_int<31){
        return Utils().getRandom(0,2);
    }
    else if (random_int>=31 and random_int<56){
        return Utils().getRandom(3,10);
    }
    else if (random_int>=56 and random_int<76){
        return Utils().getRandom(11,15);
    }
    else if (random_int>=76 and random_int<91){
        return Utils().getRandom(16,25);
    }
    else return Utils().getRandom(26,50);;
}

void PaisesVisitados::generarPaises(){
    int totalPaises = seleccionarRangoViajes();
    listaPaisesVisitados = JsonManager().getPaises(totalPaises);
}
