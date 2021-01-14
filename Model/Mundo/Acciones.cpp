#include <Model/thanos.h>

#include <Model/dataStructures/HashMap.h>

Acciones::Acciones(){
    listaPecados = new Hashmap<Pecados,int>;
    listaVirtudes = new Hashmap<Virtudes,int >;

    listaPecados->insert(Lujuria, Utils::getRandom(0, 100));
    listaPecados->insert(Gula, Utils::getRandom(0, 100));
    listaPecados->insert(Avaricia, Utils::getRandom(0, 100));
    listaPecados->insert(Pereza, Utils::getRandom(0, 100));
    listaPecados->insert(Ira, Utils::getRandom(0, 100));
    listaPecados->insert(Envidia, Utils::getRandom(0, 100));
    listaPecados->insert(Soberbia, Utils::getRandom(0, 100));

    listaVirtudes->insert(Castidad, Utils::getRandom(0, 100));
    listaVirtudes->insert(Ayuno, Utils::getRandom(0, 100));
    listaVirtudes->insert(Donacion, Utils::getRandom(0, 100));
    listaVirtudes->insert(Diligencia, Utils::getRandom(0, 100));
    listaVirtudes->insert(Calma, Utils::getRandom(0, 100));
    listaVirtudes->insert(Solidaridad, Utils::getRandom(0, 100));
    listaVirtudes->insert(Humildad, Utils::getRandom(0, 100));
}

void Acciones::agregarBuenasAcciones(int num, Virtudes virtue){
    int virtudesAnteriores = listaVirtudes->get(virtue);
    listaVirtudes->set(virtue,virtudesAnteriores+num);
}

void Acciones::agregarPecados(int num, Pecados sin){
    int pecadosAnteriores = listaPecados->get(sin);
    listaPecados->set(sin,pecadosAnteriores+num);
}

void Acciones::setVirtud(int num, Virtudes virtue){
    listaVirtudes->set(virtue,num);
}

void Acciones::setPecado(int num, Pecados sin){
    listaPecados->set(sin,num);
}

int Acciones::cantidadPecados(){
    Pecados pecados[] = {Lujuria, Gula, Avaricia, Pereza, Ira, Envidia, Soberbia};
    int cant = 0;

    for (int i = 0; i < 7; i++){
        cant += listaPecados->get(pecados[i]);
    }

    return cant;
}

int Acciones::cantidadVirtudes(){
    Virtudes virtudes[] = {Castidad, Ayuno, Donacion, Diligencia, Calma, Solidaridad, Humildad};
    int cant = 0;

    for (int i = 0; i < 7; i++){
        cant += listaVirtudes->get(virtudes[i]);
    }

    return cant;
}
