#include <Model/thanos.h>
#include <Model/dataStructures/HashMap.h>
#include <Model/dataStructures/LinkedList.h>

BlackDwarf::BlackDwarf(Mundo * _mundo){
    mundo = _mundo;
}

void BlackDwarf::kill(string deporte){
    vector<Persona *> kills = mundo->getBySport(deporte);

    int cant = kills.size() * 0.5;
    int real = 0;

    for (int i = 0; i < cant; i++){
        if (!kills[i]->isAlive) continue;

        kills[i]->isAlive = false;
        kills[i]->killLog->add("Asesinado por BlackDwarf por practicar: " + deporte);

        real++;
    }

    cout << "Asesinatos de bd: " << real << endl;
    cout << "Total de personas que practicaban ese deporte: " << kills.size() << endl;
    cout << "Porcentaje de asesinatos: " << ((double) real / (double) kills.size())*100.0 << "%" << endl;
}
