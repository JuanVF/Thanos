#include <Model/thanos.h>
#include <Model/dataStructures/LinkedList.h>

string Nebula::filename = "";

Nebula::Nebula(Mundo * _mundo){
    mundo = _mundo;
}

// Selecciona un humano aleatoria y lo mata
void Nebula::kill(){
    bool isDead = true;
    Persona * random;

    string filename = "Nebula #" + Utils::getDate() + ".txt";
    Nebula::filename = "Nebula: Asesinando a un humano aleatoriamente y a todos sus amigos...\n";

    Nebula::filename += "DISCLAIMER: No generamos todos los nodos marcados por la inmensa cantidad de datos\n";
    Nebula::filename += "            Solo generamos los primeros. Si se trackean todos el programa tiende a crashear\n";
    Nebula::filename += "            El algoritmo de Nebula por lo general elimina al 100% de la poblacion\n";
    Nebula::filename += "            Igual se puede verificar con el kill log de cada humano.\n";

    while(isDead){
        random = mundo->arbol->obtenerRandom();

        if (random == NULL) continue;

        isDead = !random->isAlive;
    }

    Nebula::filename += "Humano seleccionado: ID#" + to_string(random->ID) + ", " + random->nombre + "\n";
    Nebula::filename += "Asesinando a sus amigos\n";

    int amount = killAux(random);
    double porc = ((double) amount / (double) mundo->personas->length) * 100;
    Nebula::filename += "Asesinados de Nebula: " + to_string(amount) + "\n";
    Nebula::filename += "Poblacion total: " + to_string(mundo->personas->length) + "\n";
    Nebula::filename += "Porcentaje de asesinatos: " + to_string(porc) + "%\n";

    if (amount == mundo->personas->length)
        Nebula::filename += "Nebula se ha marcado un EXTERMINIO! (Asesino a toda la poblacion) \n";

    FileManager::saveFile(Nebula::filename, filename);

    Nebula::filename.clear();
}

// Mata recursivamente a todos los amigos
// La condicion de parada es que si entre los amigos hay uno muerto
// corta la cadena
int Nebula::killAux(Persona * tmp){
    if (tmp == NULL) return 0;

    int amount = 0;

    vector<Persona *> amigos = tmp->amigos->toVector();

    for (int i = 0; i < (int) amigos.size(); i++){
        Persona * amigo = amigos[i];

        if (amigo->isAlive){
            amigo->killLog->add("Asesinado por Nebula");
            amigo->isAlive = false;

            // Reportar en un .log
            if (Nebula::filename.length() < 1000)
                Nebula::filename += "[ID#" + to_string(amigo->ID) + "]\n";

            amount += 1;
            amount += killAux(amigo);
        } else {
            //if (Nebula::filename.length() < 5000)
            //    Nebula::filename += "[ID#" + to_string(amigo->ID) + ", MUERTO]\n";
        }
    }

    return amount;
}
