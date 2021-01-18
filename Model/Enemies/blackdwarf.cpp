#include <Model/thanos.h>
#include <Model/dataStructures/HashMap.h>
#include <Model/dataStructures/LinkedList.h>

BlackDwarf::BlackDwarf(Mundo * _mundo){
    mundo = _mundo;
}

void BlackDwarf::kill(string deporte){
    vector<Persona *> kills = mundo->getBySport(deporte);
    string fileName = "BlackDwarf #" + Utils::getDate() + ".txt";

    int cant = kills.size() * 0.5;
    int real = 0;

    string log = "BlackDwarf: Asesinando a los humanos que practican: " + deporte + "\n";
    log += "Total de personas que practican el deporte: " + to_string(kills.size()) + "\n";
    log += "Total de personas a eliminar: " + to_string(cant) + "\n";
    log += "Porcentaje a eliminar: 50%\n";

    log += "Nodos marcados: \n";
    log += "[\n";

    for (int i = 0; i < cant; i++){
        if (!kills[i]->isAlive){
            log += "[ID#" + to_string(kills[i]->ID) + ", " + kills[i]->nombre + " " + kills[i]->apellido + ", YA ESTABA MUERTA]\n";
            continue;
        }

        log += "[ID#" + to_string(kills[i]->ID) + ", " + kills[i]->nombre + " " + kills[i]->apellido + "]\n";

        kills[i]->isAlive = false;
        kills[i]->killLog->add("Asesinado por BlackDwarf por practicar: " + deporte);

        real++;
    }

    log += "]\n";
    log += "Total de asesinatos: " + to_string(real) + "\n";
    log += "Porcentaje de asesinatos real: " + to_string(((double) real / (double) kills.size())*100.0) + "%\n";

    FileManager::saveFile(log, fileName);
}
