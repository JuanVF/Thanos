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
    if (virtudesAnteriores+num <= 100){
        listaVirtudes->set(virtue,virtudesAnteriores+num);
    }
    else listaVirtudes->set(virtue, 100);
}


void Acciones::agregarPecados(int num, Pecados sin){
    int pecadosAnteriores = listaPecados->get(sin);
    if (pecadosAnteriores+num <= 100){
        listaPecados->set(sin,pecadosAnteriores+num);
    }
    else listaPecados->set(sin, 100);
}


void Acciones::setVirtud(int num, Virtudes virtue){
    listaVirtudes->set(virtue,num);
}

void Acciones::setPecado(int num, Pecados sin){
    listaPecados->set(sin,num);
}

void Acciones::agregarPecadosRandom(){
    Pecados pecados[] = {Lujuria, Gula, Avaricia, Pereza, Ira, Envidia, Soberbia};
    int random;// = Utils::getRandom(0, 100);

    for(int i=0; i<7; i++){
        random = Utils::getRandom(0, 100);
        agregarPecados(random,pecados[i]);
    }
}

void Acciones::agregarVirtudesRandom(){
    Virtudes virtudes[] = {Castidad, Ayuno, Donacion, Diligencia, Calma, Solidaridad, Humildad};
    int random;

    for(int i=0; i<7; i++){
        random = Utils::getRandom(0, 100);
        agregarBuenasAcciones(random,virtudes[i]);
    }
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

string Acciones::getInfo(){
    Virtudes virtudes[] = {Castidad, Ayuno, Donacion, Diligencia, Calma, Solidaridad, Humildad};
    Pecados pecados[] = {Lujuria, Gula, Avaricia, Pereza, Ira, Envidia, Soberbia};

    string info = "Lujuria: " + to_string(listaPecados->get(Lujuria)) + "\n";
    info += "Gula: " + to_string(listaPecados->get(Gula)) + "\n";
    info += "Avaricia: " + to_string(listaPecados->get(Avaricia)) + "\n";
    info += "Pereza: " + to_string(listaPecados->get(Pereza)) + "\n";
    info += "Ira: " + to_string(listaPecados->get(Ira)) + "\n";
    info += "Envidia: " + to_string(listaPecados->get(Envidia)) + "\n";
    info += "Soberbia: " + to_string(listaPecados->get(Soberbia)) + "\n";

    info += "Castidad: " + to_string(listaVirtudes->get(Castidad)) + "\n";
    info += "Ayuno: " + to_string(listaVirtudes->get(Ayuno)) + "\n";
    info += "Donacion: " + to_string(listaVirtudes->get(Donacion)) + "\n";
    info += "Diligencia: " + to_string(listaVirtudes->get(Diligencia)) + "\n";
    info += "Calma: " + to_string(listaVirtudes->get(Calma)) + "\n";
    info += "Solidaridad: " + to_string(listaVirtudes->get(Solidaridad)) + "\n";
    info += "Humildad: " + to_string(listaVirtudes->get(Humildad)) + "\n";

    return info;
}

