#include "Model/thanos.h"
#include <Model/dataStructures/HashMap.h>

Ejercicio::Ejercicio(){
    cantidad = 0;

    deportes = new Hashmap<string, bool>();
}

void Ejercicio::generarDeportes(vector<string> _deportes){
    int cant = Utils::getRandom(0, 8);
    int start = Utils::getRandom(0, _deportes.size() - 1 - cant);

    vDeportes.resize(cant);

    for (int i = start; i < start + cant; i++){
        vDeportes[i - start] = _deportes[i];
        deportes->insert(_deportes[i], true);
    }

    cantidad = Utils::getRandom(0, 7);
}
