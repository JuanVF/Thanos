#include <Model/thanos.h>
#include <Model/dataStructures/LinkedList.h>

Ebony::Ebony(Mundo * _mundo){
    mundo = _mundo;
}

void Ebony::kill(int ID){
    string fileName = "Ebony Mau #" + Utils::getDate() + ".txt";
    string log = "Ebony Maw: Asesinando al humano: ID#" + to_string(ID) + "\n";

    Persona * persona = mundo->arbol->obtener(ID);

    if (persona == NULL){
        string log = "La ID#" + to_string(ID) + " no existe...\n";
        FileManager::saveFile(log, fileName);
        return;
    }

    log += "Exterminando a la familia: " + persona->apellido + "\n";

    Persona * raiz = Familia::obtenerRaizFamiliar(persona);

    if (raiz == NULL)
        cout << "La raiz es nula..." << endl;

    int amount = 0;

    if (raiz->isAlive){
        raiz->isAlive = false;
    }

    amount += killAux(raiz, &log);

    double porc = ((double) amount / (double) mundo->personas->length) * 100;

    log += "Asesinatos de Ebony: " + to_string(amount) + "\n";
    log += "Poblacion total: " + to_string(mundo->personas->length) + "\n";
    log += "Porcentaje de asesinatos: " + to_string(porc) + "%\n";

    FileManager::saveFile(log, fileName);
}

int Ebony::killAux(Persona * tmp, string * log){
    if (tmp == NULL)
        return 0;

    int amount = 0;

    for (int i = 0; i < tmp->familia->hijos->length; i++){
        Persona * curr = tmp->familia->hijos->get(i);

        if (curr->isAlive){
            curr->isAlive = false;
            amount++;
            (*log) += "[ID#" + to_string(curr->ID) + ", " + curr->nombre + " " + curr->apellido + "]\n";

        } else {
            (*log) += "[ID#" + to_string(curr->ID) + ", " + curr->nombre + " " + curr->apellido + ", YA ESTABA MUERTO]\n";
        }

        amount += killAux(tmp->familia->hijos->get(i), log);
    }

    return amount;
}
