#include <Model/thanos.h>
#include <Model/dataStructures/Heap.h>
#include <Model/dataStructures/LinkedList.h>

Midnight::Midnight(Mundo * _mundo){
    mundo = _mundo;
    gentePorMatar = (5*mundo->getAlivePeople())/100;
    heap = new Heap(9999999, false);
    for(int i=0; i<mundo->personas->length;i++){
        if(mundo->personas->get(i)->isAlive){
            heap->insert(mundo->personas->get(i)->acciones->cantidadVirtudes());
        }
    }
}

Persona * Midnight::getByVirtues(int num){
    for (int i=0; i< mundo->personas->length; i++){
        if ((mundo->personas->get(i)->acciones->cantidadVirtudes() == num) and (mundo->personas->get(i)->isAlive)){
            return mundo->personas->get(i);
        }
    }
    return NULL;
}

void Midnight::kill(){
    int genteAsesinada = 0;
    string log = "Midnight: Asesinando a las buenas personas!\n";
    string filename = "Midnight#"+Utils::getDate()+".txt";

    for(int i=0; i< gentePorMatar; i++){
        Persona * tmp = getByVirtues(heap->get());

        if (tmp == NULL) continue;

        tmp->isAlive = false;
        tmp->killLog->add("Fue asesinado por MidNight");

        log += "[ID#"+to_string(tmp->ID)+", "+tmp->nombre+"]\n";

        heap->deleteElement();
        genteAsesinada++;
    }

    log += "Corvus Glaive ha asesinado a un total de: " + to_string(genteAsesinada) + "personas por sus pecados\n";

    FileManager::saveFile(log, filename);
}
