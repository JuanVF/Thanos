#include <Model/thanos.h>

#include <Model/dataStructures/LinkedList.h>
#include <Model/dataStructures/TreeNode.h>

SpiderMan::SpiderMan(Mundo * _mundo){
    mundo = _mundo;
}

void SpiderMan::save(){
    string filename = "spiderman.txt";
    string log = "Spiderman, salvando personas\n";

    FileManager::saveFile(log, filename);

    TreeNode * raiz = mundo->arbol->raiz;
    LinkedList<Persona *> * recorrido = new LinkedList<Persona *>();

    saveAux(raiz, recorrido);

    log = FileManager::readFile(filename);
    log += "Recorrido de la telarania: \n[\n";
    for (int i = 0; i < recorrido->length; i++){
        Persona * persona = recorrido->get(i);

        log += "[ID#"+to_string(persona->ID)+", "+persona->nombre+"]->";
    }
    log += "]\n";

    FileManager::saveFile(log, filename);
}

void SpiderMan::saveAux(TreeNode *tmp, LinkedList<Persona *> *recorrido){
    if (tmp == NULL)
        return;

    if (tmp->hijosNulos()){
        saveLeafs(tmp->persona, recorrido->length);

        return;
    }

    Persona * persona = tmp->persona->data;

    if (Utils::getRandom(0, 100) < 20 && !persona->isAlive){
        recorrido->add(persona);

        cout << "Spiderman ha salvado a: " << persona->nombre << endl;
        persona->isAlive = true;
        persona->savedLog->add("Salvado por SpiderMan en el arbol");
    }

    saveAux(tmp->hijoIzq, recorrido);
    saveAux(tmp->hijoDer, recorrido);
}

void SpiderMan::saveLeafs(Node<Persona *> * tmp, int amount){
    string filename = "spiderman.txt";
    string log = FileManager::readFile(filename);

    log += "Salvando en la lista por la hoja:"+to_string(tmp->data->ID)+"\n";

    for (int i = 0; i < amount; i++){
        if (tmp == NULL) break;

        Persona * persona = tmp->data;

        if (!persona->isAlive){
            //cout << "Spiderman ha salvado en la lista a: " << persona->nombre << endl;

            persona->isAlive = true;
            persona->savedLog->add("Salvado por SpiderMan en la lista");
            log += "[ID#"+to_string(persona->ID)+", "+persona->nombre+"]\n";
        }

        tmp = tmp->next;
    }

    FileManager::saveFile(log, filename);
}
