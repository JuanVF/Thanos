#include "Model/thanos.h"

Ejercicio::Ejercicio(){
    cantidad = 0;
}

void Ejercicio::generarDeportes(vector<string> _deportes){
    int cant = Utils::getRandom(0, 8);
    int start = Utils::getRandom(0, _deportes.size() - 1 - cant);

    deportes.resize(cant);

    for (int i = start; i < start + cant; i++){
        deportes[i - start] = _deportes[i];
    }

    cantidad = Utils::getRandom(0, 7);
}
