#include <Model/thanos.h>
#include <Model/dataStructures/TreeNode.h>

Antman::Antman(Mundo * _mundo){
    mundo = _mundo;
}

void Antman::save(int amount){
    if (amount < 3){
        cout << "Se necesitan minimo dos hormigas" << endl;
        return;
    }

    string filename = "Antman #" + Utils::getDate() + ".txt";
    string log = "AntMan, va a salvar con #" + to_string(amount) + " de hormigas\n";

    vector<LinkedList<Node<Persona *> *> *> recorridos;
    recorridos.resize(amount);

    for (int i = 0; i < amount; i++){
        recorridos[i] = new LinkedList<Node<Persona *> *>();

        saveAux(mundo->arbol->raiz, recorridos[i]);
    }

    // Agregamos al log los recorridos...
    for (int i = 0; i < (int) recorridos.size(); i++){
        log += "Recorrido #" + to_string(i + 1) + "\n";
        for (int j = 0; j < recorridos[i]->length; j++){
            Persona * persona = recorridos[i]->get(j)->data;

            log += "[ID#" + to_string(persona->ID) + ", " + persona->nombre + "] ->";
        }
        log += "\n";
    }

    int firstID = recorridos[0]->get(recorridos[0]->length-1)->data->ID;
    int lastID = recorridos[1]->get(recorridos[1]->length-1)->data->ID;

    Node<Persona *> * first = (firstID > lastID) ? recorridos[1]->get(recorridos[1]->length-1) : recorridos[0]->get(recorridos[0]->length-1);

    int goal = (firstID > lastID) ? firstID : lastID;

    log += "Personas rescatadas por AntMan: \n [\n";
    while (first != NULL && first->data->ID != goal){
        Persona * persona = first->data;
        persona->savedLog->add("Rescatado por antman");

        log += "[ID#" + to_string(persona->ID) + ", " + persona->nombre + "]\n";

        first = first->next;
    }

    log += "]\n";

    FileManager::saveFile(log, filename);
}

void Antman::saveAux(TreeNode * tmp, LinkedList<Node<Persona *> *> * recorrido){
    if (tmp == NULL || tmp->hijosNulos())
        return;

    // Agregar en un archivo esto
    recorrido->add(tmp->persona);

    // Caso hijo derecho
    if (Utils::getRandom(0, 100) < 50){
        saveAux(tmp->hijoDer, recorrido);
    } else {
        saveAux(tmp->hijoIzq, recorrido);

    }
}
