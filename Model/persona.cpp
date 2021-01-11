#include <Model/thanos.h>
#include <Model/dataStructures/LinkedList.h>
#include <Model/utils.h>

Persona::Persona(int _ID, eGenero _genero, string _nombre){
    ID = _ID;
    nombre = _nombre;
    genero = _genero;
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

void Persona::generarAmigos(LinkedList<Persona *> * personas){
    int cant = Utils::getRandom(0, 50);

}
