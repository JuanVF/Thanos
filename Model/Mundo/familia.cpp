#include <Model/thanos.h>

#include <Model/dataStructures/LinkedList.h>
#include <Model/dataStructures/Tree.h>

Familia::Familia(Persona * _persona){
    conyugue = NULL;
    padre = NULL;
    persona = _persona;
    hijos = new LinkedList<Persona *>();
}

void Familia::generarConyugue(vector<Persona *> personas){
    if (persona->estado == soltero) return;

    int start = Utils::getRandom(0, (int) personas.size() - 100);
    Persona * cong = NULL;

    for (int i = start; i < (int) personas.size(); i++){
        cong = personas[i];

        if (cong->ID != persona->ID && cong->familia->conyugue == NULL){
            conyugue = cong;
            cong->familia->conyugue = persona;
            return;
        }
    }

    persona->estado = soltero;
}

void Familia::generarHijos(vector<Persona *> personas){
    int amount = Utils::getRandom(0, 4);

    if (amount == 0) return;

    for (int i = 0; i < (int) personas.size(); i++){
        if (hijos->length >= amount) break;

        Persona * hijo = personas[i];

        if (hijo->familia->padre != NULL) continue;

        if (hijo->ID != persona->ID && RangoEtario::puedeSerHijo(persona->edad->rango, hijo->edad->rango)){
            if (hijo->apellido == persona->apellido && !estaEnSusHijos(persona->ID, hijo)){
                hijos->add(hijo);
                hijo->familia->padre = persona;
            }
        }
    }
}

bool Familia::estaEnSusHijos(int ID, Persona * persona){
    if (persona == NULL) return false;

    if (persona->familia->hijos->length == 0) return false;

    if (persona->ID == ID){
        return true;
    }

    vector<Persona *> vHijos = persona->familia->hijos->toVector();

    for (int i = 0; i < persona->familia->hijos->length; i++){
        bool esta = estaEnSusHijos(ID, vHijos[i]);

        if (esta) return true;
    }

    return false;
}

// Obtiene el tataratatarata...abuelo (la raiz de la familia)
Persona * Familia::obtenerRaizFamiliar(Persona * _persona){
    if (_persona->familia->padre == NULL)
        return _persona;

    return obtenerRaizFamiliar(_persona->familia->padre);
}
