#include <iostream>
#include <string>
#include <Model/utils.h>
#include <Model/thanos.h>

//Esta funcion la hice con el fin de saber cuando el año es bisiesto
// y con esto saber si febrero tiene 29 o 28 dias, a la hora de generar la fecha
bool RangoEtario::isLeap(int num){
    if((num%4 == 0 and num%100 != 0) or num%400==0){
        return true;
    }
    return false;
}

//Esta funcion se encarga de generar la fecha aleatoriamente
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

//Esta  funcion se encarga de asignar el rango de acuerdo a la edad
void RangoEtario::asignarRango(){
    edad = 2020 - fechaDeNacimiento[2];
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

//Setear la edad directamente
void RangoEtario::setEdad(int num){
    edad = num;
    fechaDeNacimiento[2]= 2020-num;
}


void RangoEtario::setEdadEtapa(string etapa){
    if (etapa == "hijo"){
        fechaDeNacimiento[2] = Utils().getRandom(2000, 2020);
    }
    else if (etapa == "padre"){
        fechaDeNacimiento[2] = Utils().getRandom(1975, 1995);
    }
    else if (etapa == "abuelo"){
        fechaDeNacimiento[2] = Utils().getRandom(1955, 1970);
    }
    else if (etapa == "bisabuelo"){
        fechaDeNacimiento[2] = Utils().getRandom(1935, 1950);
    }
}





