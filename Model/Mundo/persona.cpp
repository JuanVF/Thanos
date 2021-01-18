#include <Model/thanos.h>
#include <Model/utils.h>
#include <Model/dataStructures/LinkedList.h>
#include <Model/Mundo/RangoEtario.h>
#include <Model/Mundo/familia.h>
#include <Model/Mundo/Acciones.h>

Persona::Persona(int _ID, eGenero _genero, string _nombre, string _apellido, string _creencia, string _profesion, Ubicacion * ub){
    ID = _ID;
    nombre = _nombre;
    apellido = _apellido;
    genero = _genero;
    creencia = _creencia;
    profesion = _profesion;
    ubicacion = ub;

    amigos = new LinkedList<Persona *>();
    killLog = new LinkedList<string>();
    savedLog = new LinkedList<string>();
    edad = new RangoEtario();
    familia = new Familia(this);

    edad->generarFecha();
    edad->asignarRango();

    generarEstado();

    isAlive = true;

    deporte = new Ejercicio();
    acciones = new Acciones();

    puntosThanos = 0;
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

// Retorna la ID de una persona
int Persona::getPoints(Persona * persona){
    return (persona == NULL) ? 0: persona->getPoints();
}

// Retorna la ID de una persona
int Persona::getPoints(){
    return puntosThanos;
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
            if (tmp->data->ID == ID){
                return true;
            }
            tmp = tmp->next;
        }

        nodo = nodo->next;
    }

    return false;
}

// Genera los amigos de las personas
void Persona::generarAmigos(vector<Persona *> vPersonas){
    int cant = Utils::getRandom(0, 50);

    if (cant == 0) return;

    int start = Utils::getRandom(0, vPersonas.size() - 1);

    for (int i = start; i < (int) vPersonas.size(); i++){
        if (amigos->length >= cant) break;

        if (vPersonas[i]->ubicacion->pais == ubicacion->pais){
            amigos->add(vPersonas[i]);

        } else if (Utils::getRandom(0, 100) <= 40){
            amigos->add(vPersonas[i]);

        } else if (Utils::getRandom(0, 100) <= 70 && amigosComun(vPersonas[i])){
            amigos->add(vPersonas[i]);
            vPersonas[i]->amigos->add(this);
        }
    }
}

string Persona::getInfo(){
    string estaVivo = (isAlive) ? "Esta vivo" : "Esta muerto";

    string anio = to_string(edad->fechaDeNacimiento[2]);
    string mes = to_string(edad->fechaDeNacimiento[1]);
    string dia = to_string(edad->fechaDeNacimiento[0]);

    string conyugue = (familia->conyugue == NULL) ? "N/A" : familia->conyugue->nombre + ", ID#" + to_string(familia->conyugue->ID);

    string info = "Persona: " + nombre + " " + apellido + "\n";
    info += "ID#" + to_string(ID) + "\n";
    info += "Vivo: " + estaVivo + "\n";
    info += "Creencia: " + creencia + "\n";
    info += "Profesion: " + profesion + "\n";
    info += "Continente: " + ubicacion->continente + ", Pais: " + ubicacion->pais + "\n";
    info += "Fecha de nacimiento: " + anio + "/" + mes + "/" + dia + "\n";
    info += "Conyugue: " + conyugue + "\n";
    info += "----------------------------------------------\n";
    info += "Deportes: \n";
    info += "Cantidad de veces por semana: " + to_string(deporte->cantidad) + "\n";
    info += "Lista: \n";

    for (int i = 0; i < (int) deporte->vDeportes.size(); i++){
        info += deporte->vDeportes[i] + " ";
    }

    info += "\n";
    info += "----------------------------------------------\n";


    return info;
}
