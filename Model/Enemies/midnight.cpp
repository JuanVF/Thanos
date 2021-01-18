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
    for (int i=0; i<mundo->personas->length; i++){
        if ((mundo->personas->get(i)->acciones->cantidadVirtudes() == num) and (mundo->personas->get(i)->isAlive)){
            return mundo->personas->get(i);
        }
    }
    return NULL;
}


void Midnight::kill(){
    int genteAsesinada =0;
    for(int i=0; i<gentePorMatar;i++){
        cout<<"Midnight ha asesinado a: "<< mundo->personas->get(i) <<"por su cantidad de virtudes"<<endl;
        getByVirtues(heap->get())->isAlive = false;;
        heap->deleteElement();
        genteAsesinada++;
    }
    cout<<"Midnight ha asesinado a un total de: "<< genteAsesinada <<"personas por sus virtudes"<<endl;

}
