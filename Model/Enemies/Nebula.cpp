#include <Model/thanos.h>
#include <Model/dataStructures/LinkedList.h>

Nebula::Nebula(Mundo * _mundo){
    mundo = _mundo;
}

// Selecciona un humano aleatoria y lo mata
void Nebula::kill(){
    bool isDead = true;
    Persona * random;

    while(isDead){
        random = mundo->arbol->obtenerRandom();

        if (random == NULL) continue;

        isDead = !random->isAlive;
    }

    int amount = killAux(random);
    double porc = ((double) amount / (double) mundo->personas->length) * 100;

    cout << "Asesinados de Nebula: " << amount << endl;
    cout << "Poblacion total: " << mundo->personas->length << endl;
    cout << "Porcentaje de asesinatos: " << porc << "%" <<endl;
    if (amount == mundo->personas->length)
        cout << "Nebula se ha marcado un EXTERMINIO!" << endl;
}

// Mata recursivamente a todos los amigos
// La condicion de parada es que si entre los amigos hay uno muerto
// corta la cadena
int Nebula::killAux(Persona * tmp){
    if (tmp == NULL) return 0;

    vector<Persona *> amigos = tmp->amigos->toVector();
    int amount = 0;

    for (int i = 0; i < (int) amigos.size(); i++){
        if (amigos[i]->isAlive){
            amigos[i]->killLog->add("Asesinado por Nebula");
            amigos[i]->isAlive = false;

            // Reportar en un .log
            amount += 1;
            amount += killAux(amigos[i]);
        }
    }

    return amount;
}
