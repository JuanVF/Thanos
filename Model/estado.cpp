#include "estado.h"
#include <Model/utils.h>
#include <Model/thanos.h>


EstadoMarital::EstadoMarital(){}

/*
enum eEstadoMarital{
    soltero,
    casado,
    divorciado,
};
*/


//Estado marital: soltero (10% 0-10), Divorciado (10% 10-20), casado(80% 20-100)
// Soltero - 1, Divorciado - 2, Casado - 3
//Nota:Lo mejor seria devolver el enum de un solo;
int EstadoMarital::getEstado(){
    int per= Utils().getRandom(0,100);
    if (per<10){
        return 1;//Soltero
    }else if(per<20){
        return 2;//Divorciado
    }else {
        return 3;//Casado
    }
}

