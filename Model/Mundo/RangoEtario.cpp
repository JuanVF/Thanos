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
    int random_year = Utils::getRandom(1935, 2020);
    int random_month = Utils::getRandom(1,12);
    int random_day;
    
    if (random_month == 2){
        if(isLeap(random_year)){
            random_day = Utils::getRandom(1, 29);
        }
        else{
            random_day =  Utils::getRandom(1, 28);
        }
    }
    
    else if (random_month == 1 or random_month == 3 or random_month == 5 or random_month == 7
         or random_month == 8  or random_month == 10  or random_month == 12){
        random_day =  Utils::getRandom(1, 31);
    }
    
    else{
        random_day =  Utils::getRandom(1, 30);
    }

    fechaDeNacimiento[0]= random_day;
    fechaDeNacimiento[1]= random_month;
    fechaDeNacimiento[2]= random_year;
}

void RangoEtario::asignarRango(){
    int edad = 2020 - fechaDeNacimiento[2];

    if (edad<2){
        rango = infantil;
        rango_etario = static_cast<RangosEtarios>(0);

    } else if (edad<5){
        rango = preescolar;
        rango_etario = static_cast<RangosEtarios>(1);
    }
    else if (edad<11){
        rango = escolar;
        rango_etario = static_cast<RangosEtarios>(2);
    }
    else if (edad<15){
        rango = pubertad;
        rango_etario = static_cast<RangosEtarios>(3);
    }
    else if (edad<20){
        rango = adolescencia;
        rango_etario = static_cast<RangosEtarios>(4);
    }
    else if (edad<25){
        rango = joven;
        rango_etario = static_cast<RangosEtarios>(5);
    }
    else if (edad<35){
        rango = adultoJoven;
        rango_etario = static_cast<RangosEtarios>(6);
    }
    else if (edad<65){
        rango = adultoMaduro;
        rango_etario = static_cast<RangosEtarios>(7);

    } else {
        rango = adultoMayor;
        rango_etario = static_cast<RangosEtarios>(8);
    }
}

bool RangoEtario::esMenor(RangosEtarios rango){
    if (rango == infantil)
        return true;
    else if (rango == preescolar)
        return true;
    else if (rango == escolar)
        return true;
    else if (rango == pubertad)
        return true;
    else if (rango == adolescencia)
        return true;

    return false;
}

bool RangoEtario::puedeSerHijo(RangosEtarios padre, RangosEtarios hijo){
    bool caseJoven = hijo == infantil || hijo == preescolar;
    bool caseAdultoJoven = caseJoven || hijo == escolar || hijo == pubertad;

    bool caseMaduro = hijo == adolescencia || hijo == joven || hijo == adultoJoven;
    bool caseAdultoMayor = hijo == adultoJoven || hijo == adultoMaduro;

    switch(padre){
        case joven:
            return caseJoven;
        case adultoJoven:
            return caseAdultoJoven;
        case adultoMaduro:
            return caseMaduro;
        case adultoMayor:
            return caseAdultoMayor;
        default:
            break;
    }

    return false;
}



