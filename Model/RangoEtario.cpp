#include <iostream>
#include <string>
#include <Model/utils.h>
#include <Model/thanos.h>


bool RangoEtario::isLeap(int num){
    if((num%4 == 0 and num%100 != 0) or num%400==0){
        return true;
    }
    return false;
}


void RangoEtario::generarFecha(){
    int random_year = Utils().getRandom(1935,2020);
    int random_month = Utils().getRandom(1,12);
    int random_day;
    
    if (random_month == 2){
        if(isLeap(random_year)){
            random_day = Utils().getRandom(1, 29);
        }
        else{
            random_day =  Utils().getRandom(1, 28);
        }
    }
    
    else if (random_month == 1 or random_month == 3 or random_month == 5 or random_month == 7
         or random_month == 8  or random_month == 10  or random_month == 12){
        random_day =  Utils().getRandom(1, 31);
    }
    
    else{
        random_day =  Utils().getRandom(1, 30);
    }
    fechaDeNacimiento[0]= random_day;
    fechaDeNacimiento[1]= random_month;
    fechaDeNacimiento[2]= random_year;
}

// Rango 1 = 30%    | 0-2 paises visitados
// Rango 2 = 25%    | 3-10 paises visitados
// Rango 3 = 20%    | 11-15 paises visitados
// Rango 4 = 15%    | 16-25 paises visitados
// Rango 5 = 10%    | 26+   paises visitados
//Esta funcion se encargara de seleccionar el numero de paises visitados
//Esto se hace mediante un random y la probabilidad de cada rango
int RangoEtario::seleccionarRangoViajes(){
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

void RangoEtario::asignarRango(){
    int edad = 2020 - fechaDeNacimiento[2];
    if (edad<2){
        rango_etario = static_cast<RangosEtarios>(0) ;
    }
    else if (edad<5){
        rango_etario = static_cast<RangosEtarios>(1);
    }
    else if (edad<11){
        rango_etario = static_cast<RangosEtarios>(2);
    }
    else if (edad<15){
        rango_etario = static_cast<RangosEtarios>(3);
    }
    else if (edad<20){
        rango_etario = static_cast<RangosEtarios>(4);
    }
    else if (edad<25){
        rango_etario = static_cast<RangosEtarios>(5);
    }
    else if (edad<35){
        rango_etario = static_cast<RangosEtarios>(6);
    }
    else if (edad<65){
        rango_etario = static_cast<RangosEtarios>(7);
    }
    else rango_etario = static_cast<RangosEtarios>(8);
}



