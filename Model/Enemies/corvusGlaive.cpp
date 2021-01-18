#include <Model/thanos.h>
#include <Model/dataStructures/Heap.h>
#include <Model/dataStructures/LinkedList.h>

CorvusGlaive::CorvusGlaive(Mundo * _mundo){
    mundo = _mundo;
    gentePorMatar = (5*mundo->getAlivePeople())/100;
    heap = new Heap(9999999, true);

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
    for(int i=0; i<gentePorMatar;i++){
        cout<<"Corvus Glaive ha asesinado a: "<< mundo->personas->get(i) <<"por su cantidad de pecados"<<endl;
        getBySins(heap->get())->isAlive = false;;
        heap->deleteElement();
        genteAsesinada++;
    }
    cout<<"Corvus Glaive ha asesinado a un total de: "<< genteAsesinada <<"personas por sus pecados"<<endl;
}

