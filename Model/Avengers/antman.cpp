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

    vector<LinkedList<Node<Persona *> *> *> recorridos;
    recorridos.resize(amount);

    for (int i = 0; i < amount; i++){
        recorridos[i] = new LinkedList<Node<Persona *> *>();

        saveAux(mundo->arbol->raiz, recorridos[i]);
    }

    int firstID = recorridos[0]->get(recorridos[0]->length-1)->data->ID;
    int lastID = recorridos[1]->get(recorridos[1]->length-1)->data->ID;

    Node<Persona *> * first = (firstID > lastID) ? recorridos[1]->get(recorridos[1]->length-1) : recorridos[0]->get(recorridos[0]->length-1);

    int goal = (firstID > lastID) ? firstID : lastID;

    cout << "Empezando a rescatar..." << endl;
    cout << "Empieza en la ID: " << first->data->ID << endl;
    cout << "Termina en la ID: " << goal << endl;
    while (first != NULL && first->data->ID != goal){
        first->data->savedLog->add("Rescatado por antman");

        first = first->next;
    }

    // TODO: Agregar archivos
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
