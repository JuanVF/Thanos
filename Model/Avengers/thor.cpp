#include <Model/thanos.h>
#include <Model/dataStructures/HashMap.h>

Thor::Thor(Mundo * _mundo){
    mundo = _mundo;
}

void Thor::save(int level){
    Hashmap<int, LinkedList<Persona *>*> * niveles = mundo->arbol->niveles();

    if (!niveles->contains(level)){
        // Pasar esto al log de la app
        cout << "El nivel no existe..." << endl;
        return;
    }

    string filename = "Thor#"+Utils::getDate()+".txt";
    string log = "Salvando al nivel: "+to_string(level)+"\n";

    LinkedList<Persona *> * nivel = niveles->get(level);
    int cant = 0;

    for (int i = 0; i < nivel->length; i++){
        Persona * tmp = nivel->get(i);

        if (tmp->isAlive) continue;

        log += "[ID#"+to_string(tmp->ID)+", "+tmp->nombre+"]\n";

        tmp->isAlive = true;
        tmp->savedLog->add("Salvado por Thor por estar en el nivel: " + to_string(level));

        cant++;
    }

    double porc = ((double) cant / (double) mundo->personas->length)*100.0;

    log += "Humanos salvados por Thor: " + to_string(cant) + "\n";
    log += "Porcentaje de personas salvadas: " + to_string(porc) + "%\n";

    FileManager::saveFile(log, filename);
}

