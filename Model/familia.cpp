#include <Model/thanos.h>
#include <Model/estado.h>

Familia::Familia(){}

void Familia::generarConyugue(){
    int estado = EstadoMarital().getEstado();
    cout << estado << endl;
}

void Familia::generarHijos(){}
