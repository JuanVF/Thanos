#include <Model/thanos.h>

#include <Model/dataStructures/HashMap.h>

Acciones::Acciones(){
    listaPecados = new Hashmap<Pecados,int>;
    listaVirtudes = new Hashmap<Virtudes,int >;

    listaPecados->insert(Lujuria,0);
    listaPecados->insert(Gula,0);
    listaPecados->insert(Avaricia,0);
    listaPecados->insert(Pereza,0);
    listaPecados->insert(Ira,0);
    listaPecados->insert(Envidia,0);
    listaPecados->insert(Soberbia,0);

    listaVirtudes->insert(Castidad,0);
    listaVirtudes->insert(Ayuno,0);
    listaVirtudes->insert(Donacion,0);
    listaVirtudes->insert(Diligencia,0);
    listaVirtudes->insert(Calma,0);
    listaVirtudes->insert(Solidaridad,0);
    listaVirtudes->insert(Humildad,0);
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
