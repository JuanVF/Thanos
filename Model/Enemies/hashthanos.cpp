#include <Model/thanos.h>
#include <Model/dataStructures/HashMap.h>

hashthanos::hashthanos(Mundo * _mundo){
    mundo = _mundo;
    thanos = NULL;
}

void hashthanos::generateHashtable(){
    Hashmap<int, LinkedList<Persona *> *> * personas = mundo->getByYears();
    Hashmap<int, LinkedList<Persona *> *> * kills = new Hashmap<int, LinkedList<Persona *> *>();

    string filename = "thanos_tabla.txt";
    string log = "Thanos: Generando la tabla de dispersion\n";

    // Generamos la tabla de dispersion
    for (int i = 1935; i <= 2020; i++){
        if (!personas->contains(i)) continue;
        log += "Anio: " + to_string(i) + " : [ ";

        LinkedList<Persona *> * y = generateByYear(personas->get(i)->toVector());

        for (int i = 0; i < y->length; i++){
            log += y->get(i)->nombre + ", ";
        }

        log += " ]\n";

        kills->insert(i, y);
    }

    FileManager::saveFile(log, filename);

    thanos = kills;
}

LinkedList<Persona *> * hashthanos::generateByYear(vector<Persona *> _personas){
    LinkedList<Persona *> * kills = new LinkedList<Persona *>();

    for (int i = 0; i < (int) _personas.size(); i++){
        Persona * p = _personas[i];

        // Si es 0 mas puntos para ser eliminado tiene
        // Entre mas ejercicio haga menos prob de ser eliminado tiene
        p->puntosThanos += Utils::abs(7 - p->deporte->cantidad) * 10;

        // Entre menos paises haya visitado, mas prob tiene de ser eliminado
        p->puntosThanos += Utils::abs(100 - p->turismo.size());

        // Entre mas pecados tenga mas prob de ser eliminado tiene
        p->puntosThanos += p->acciones->cantidadPecados();

        // Entre mas buenas acciones tenga menos prob de ser eliminado tiene
        p->puntosThanos -= p->acciones->cantidadVirtudes();

        // Entre mas amigos tenga, mas prob de ser eliminado tiene
        p->puntosThanos += p->amigos->length;

        Node<Persona *> * tmp = kills->firstNode;

        if (kills->length == 0)
            kills->add(p);
        else for (int i = 0; i < kills->length; i++){
            if (tmp->data->puntosThanos > p->puntosThanos){
                kills->add(p, i);
                break;
            }

            tmp = tmp->next;
        }
    }

    int end = kills->length;
    int start = kills->length - 10;
    start = (start < 0) ? 0 : start;

    LinkedList<Persona *> * x = kills->split(start, end);

    return x;
}

void hashthanos::killByLevel(int level){
    if (thanos == NULL) return;

    string filename = "Thanos Nivel#" + Utils::getDate() + ".txt";
    string log = "Thanos: asesinando por nivel\n";
    log += "Nivel: " + to_string(level) + "\n";

    for (int i = 1935; i < 2020; i++){
        if (!thanos->contains(i)) continue;

        if (level > (int) thanos->get(i)->length) continue;
        if (thanos->get(i)->get(level - 1) == NULL) continue;
        if (!thanos->get(i)->get(level - 1)->isAlive) continue;

        Persona * persona = thanos->get(i)->get(level - 1);

        persona->isAlive = false;
        persona->killLog->add("Asesinado por Thanos, por estar en el nivel: " + to_string(level));

        log += "[ID#" + to_string(persona->ID) + ", " + persona->nombre + " ]\n";
    }

    FileManager::saveFile(log, filename);
}

void hashthanos::killByYear(int year){
    if (thanos == NULL) return;

    if (!thanos->contains(year)) return;

    string filename = "Thanos Anio#" + Utils::getDate() + ".txt";
    string log = "Thanos: asesinando por anio\n";
    log += "Anio: " + to_string(year) + "\n";

    int amount = 0;

    for (int i = 0; i < (int) thanos->get(year)->length; i++){
        if (thanos->get(year)->get(i) == NULL) continue;
        if (!thanos->get(year)->get(i)->isAlive) continue;

        Persona * persona = thanos->get(year)->get(i);

        persona->isAlive = false;
        persona->killLog->add("Asesinado por Thanos, por estar en el anio: " + to_string(year));
        log += "[ID#" + to_string(persona->ID) + ", " + persona->nombre + " ]\n";

        amount++;
    }

    log += "Personas asesinadas: " + to_string(amount) + "\n";

    FileManager::saveFile(log, filename);
}

void hashthanos::killByLevelAndYear(int year, int level){
    if (thanos == NULL) return;

    if (!thanos->contains(year)) return;

    if (level > (int) thanos->get(year)->length) return;
    if (!thanos->get(year)->get(level - 1)->isAlive) return;

    Persona * persona = thanos->get(year)->get(level - 1);

    string filename = "Thanos #" + Utils::getDate() + ".txt";
    string log = "Thanos: asesinando por nivel y anio\n";
    log += "Nivel: " + to_string(level) + ", Anio: " + to_string(year) + "\n";

    log += "Seleccionado: ID#" + to_string(persona->ID) + ", " + persona->nombre + "\n";

    persona->isAlive = false;
    string logMsg = "Asesinado por Thanos, por estar en el nivel: " + to_string(level) + ", y anio: " + to_string(year);
    persona->killLog->add(logMsg);

    log += logMsg;

    FileManager::saveFile(log, filename);
}
