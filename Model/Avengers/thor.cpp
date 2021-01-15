#include <Model/thanos.h>
#include <Model/dataStructures/HashMap.h>

Thor::Thor(Mundo * _mundo){
    mundo = _mundo;
}

void Thor::save(int level){
    Hashmap<int, LinkedList<Persona *>*> * niveles = mundo->arbol->niveles();

    if (!niveles->contains(level)){
        // Pasar esto al log de la app
        cout << "El nivel no existe..." << endl;
        return;
    }

    LinkedList<Persona *> * nivel = niveles->get(level);
    int cant = 0;

    for (int i = 0; i < nivel->length; i++){
        Persona * tmp = nivel->get(i);

        if (tmp->isAlive) continue;

        cout << "Salvando a: " << tmp->nombre << endl;

        tmp->isAlive = true;
        tmp->savedLog->add("Salvado por Thor por estar en el nivel: " + to_string(level));

        cant++;
    }

    double porc = ((double) cant / (double) mundo->personas->length)*100.0;

    cout << "Humanos salvados por Thor: " << cant << endl;
    cout << "Porcentaje de personas salvadas: " << porc << "%" << endl;
}

