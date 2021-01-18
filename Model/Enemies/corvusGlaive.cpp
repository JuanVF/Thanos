#include <Model/thanos.h>
#include <Model/dataStructures/Heap.h>
#include <Model/dataStructures/LinkedList.h>

CorvusGlaive::CorvusGlaive(Mundo * _mundo){
    mundo = _mundo;
    gentePorMatar = (5*mundo->getAlivePeople())/100;
    heap = new Heap(9999999, true);
    cout << mundo->getAlivePeople() << endl;
    for(int i=0; i<mundo->personas->length;i++){
        if(mundo->personas->get(i)->isAlive){
            heap->insert(mundo->personas->get(i)->acciones->cantidadPecados());
        }
    }
    cout << "For loop terminado" <<  endl;
}

Persona * CorvusGlaive::getBySins(int num){
    for (int i=0; i<mundo->personas->length; i++){
        if ((mundo->personas->get(i)->acciones->cantidadPecados() == num) and (mundo->personas->get(i)->isAlive)){
            return mundo->personas->get(i);
        }
    }
    return NULL;
}

void CorvusGlaive::kill(){
    int genteAsesinada = 0;
    string log = "Corvus Glaive: Asesinando a los pecadores!\n";
    string filename = "CorvusGlaive#"+Utils::getDate()+".txt";

    for(int i=0; i< gentePorMatar; i++){
        Persona * tmp = getBySins(heap->get());

        if (tmp == NULL) continue;

        tmp->isAlive = false;
        tmp->killLog->add("Asesinado por Corvus Glaive");

        log += "[ID#"+to_string(tmp->ID)+", "+tmp->nombre+"]\n";

        heap->deleteElement();
        genteAsesinada++;
    }

    log += "Corvus Glaive ha asesinado a un total de: " + to_string(genteAsesinada) + "personas por sus pecados\n";

    FileManager::saveFile(log, filename);
}

