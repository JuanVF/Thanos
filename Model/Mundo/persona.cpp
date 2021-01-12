#include <Model/thanos.h>
#include <Model/utils.h>
#include <Model/dataStructures/LinkedList.h>
#include <Model/Mundo/RangoEtario.h>
#include <Model/Mundo/familia.h>

Persona::Persona(int _ID, eGenero _genero, string _nombre, string _apellido, string _creencia, string _profesion, Ubicacion * ub){
    ID = _ID;
    nombre = _nombre;
    apellido = _apellido;
    genero = _genero;
    creencia = _creencia;
    profesion = _profesion;
    ubicacion = ub;

    amigos = new LinkedList<Persona *>();
    edad = new RangoEtario();
    familia = new Familia(this);

    edad->generarFecha();
    edad->asignarRango();

    generarEstado();
}

void Persona::generarEstado(){
    int probEstado = Utils::getRandom(0, 100);

    if (probEstado < 10 || RangoEtario::esMenor(edad->rango)){
        estado = soltero;
    } else if (probEstado < 20){
        estado = divorciado;
    } else {
        estado = casado;
    }
}

// Retorna la ID de una persona
int Persona::getID(){
    return ID;
}

// Dada una persona retorna su ID (se usa para el algoritmo de ordenamiento)
// Si es nulo retorna 0
int Persona::getID(Persona * persona){
    return (persona == NULL) ? 0 : persona->getID();
}

void Persona::generarAcciones(){

}

// Retorna true si tienen algun amigo en comun
bool Persona::amigosComun(Persona * persona){
    Node<Persona *> * nodo = persona->amigos->firstNode;

    for (int i = 0; i < (int) persona->amigos->length; i++){
        Persona * comun = nodo->data;

        Node<Persona *> * tmp = comun->amigos->firstNode;

        for (int j = 0; j < comun->amigos->length; j++){
            if (tmp->data->ID == ID) return true;

            tmp = tmp->next;
        }

        nodo = nodo->next;
    }

    return false;
}

// Genera los amigos de las personas
void Persona::generarAmigos(LinkedList<Persona *> * personas){
    int cant = Utils::getRandom(0, 50);
    int start = Utils::getRandom(0, personas->length - 1);

    vector<Persona *> vPersonas = personas->toVector();

    for (int i = start; i < (int) vPersonas.size(); i++){
        if (amigos->length >= cant) break;

        if (vPersonas[i]->ubicacion->pais == ubicacion->pais){
            amigos->add(vPersonas[i]);

        } else if (Utils::getRandom(0, 100) <= 40){
            amigos->add(vPersonas[i]);

        } else if (amigosComun(vPersonas[i]) & Utils::getRandom(0, 100) <= 70){
            amigos->add(vPersonas[i]);
        }
    }
}
