#include <Model/thanos.h>
#include <Model/dataStructures/TreeNode.h>

IronMan::IronMan(Mundo * _mundo){
    mundo = _mundo;
}

void IronMan::save(){
    TreeNode * raiz = mundo->arbol->raiz;

    FileManager::saveFile("IronMan: empezando a detonar en el arbol\n", "IronMan.txt");
    saveAux(raiz);
}

void IronMan::saveAux(TreeNode *tmp){
    if (tmp == NULL)
        return;

    int aProb[] = {40, 60};
    int fProb = aProb[Utils::getUnitRandom(0, 1)];

    if (Utils::getRandom(0, 100) < fProb){
        Persona * persona = tmp->persona->data;
        FileManager::appendFile("[ID#"+to_string(persona->ID)+", "+persona->nombre+"] ", "IronMan.txt");
        FileManager::appendFile("Salvando familia "+persona->apellido+"\n", "IronMan.txt");
        saveFamilies(tmp->persona->data);
    }

    saveAux(tmp->hijoIzq);
    saveAux(tmp->hijoDer);
}

void IronMan::saveFamilies(Persona * persona){
    if (persona == NULL)
        return;

    for (int i = 0; i < persona->familia->hijos->length; i++){
        Persona * hijo = persona->familia->hijos->get(i);

        hijo->savedLog->add("Salvado por Iron Man por ser de la familia: " + hijo->apellido);

        saveFamilies(hijo);
    }
}
