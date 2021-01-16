#include <Model/thanos.h>
#include <Model/dataStructures/LinkedList.h>

Ebony::Ebony(Mundo * _mundo){
    mundo = _mundo;
}

void Ebony::kill(int ID){
    Persona * persona = mundo->arbol->obtener(ID);

    if (persona == NULL){
        cout << "Esa ID no existe..." << endl;
        return;
    }

    cout << "Exterminando a la familia: " << persona->apellido << endl;

    Persona * raiz = Familia::obtenerRaizFamiliar(persona);

    if (raiz == NULL)
        cout << "La raiz es nula..." << endl;

    int amount = 0;

    if (raiz->isAlive){
        raiz->isAlive = false;
        amount++;
    }

    amount += killAux(raiz);

    double porc = ((double) amount / (double) mundo->personas->length) * 100;

    cout << "Asesinatos de Ebony: " << amount << endl;
    cout << "Poblacion total: " << mundo->personas->length << endl;
    cout << "Porcentaje de asesinatos: " << porc << "%" <<endl;

    if (amount == mundo->personas->length)
        cout << "Ebony se ha marcado un EXTERMINIO!" << endl;
}

int Ebony::killAux(Persona * tmp){
    if (tmp == NULL)
        return 0;

    int amount = 0;

    for (int i = 0; i < tmp->familia->hijos->length; i++){
        Persona * curr = tmp->familia->hijos->get(i);

        if (curr->isAlive){
            curr->isAlive = false;
            amount++;
        }

        amount += killAux(tmp->familia->hijos->get(i));
    }

    return amount;
}
