#include <Model/thanos.h>
#include <Model/jsonmanager.h>
#include <Model/dataStructures/Tree.h>
#include <Model/utils.h>

Mundo::Mundo(){
    arbol = new Tree();
    personas = new LinkedList<Persona *>();

    selectedIDs.resize(9999999);
    selectedIDs.clear();

    JsonManager json;

    paises.resize(100);
    creencias.resize(10);
    profesiones.resize(50);

    nombresMasc.resize(200);
    nombresFem.resize(200);

    loadData();
}

// Esta funcion se encarga de iniciar los datos...
// Si el mundo ya fue iniciado y se vuelve a llamar esta funcion
// borra TODOS los datos previamente cargados
void Mundo::reLoad(int _nombres, int _apellidos, int _creencias, int _profesiones, int _paises){
    paises.resize(_paises);
    creencias.resize(_creencias);
    profesiones.resize(_profesiones);

    loadData();
}

// Esta funcion carga los datos de los .json
void Mundo::loadData(){
    JsonManager json;

    paises = (json.getPaises(paises.size()))->toVector();
    creencias = (json.getByString(json.creenciasPath, creencias.size()))->toVector();
    profesiones = (json.getByString(json.profesionesPath, profesiones.size()))->toVector();

    nombresMasc = (json.getNames(hombre))->toVector();
    nombresFem = (json.getNames(mujer))->toVector();
}

// Genera los humanos del mundo
// TODO: Muchas cosas
void Mundo::generateHumans(int amount){
    int generated = 0;

    LinkedList<Persona *> * tmp = new LinkedList<Persona *>();

    int limit = 9999999;
    int randNum = Utils::getRandom(0, limit);
    int prev = randNum;

    while (generated < amount){
        // Esto se hace por eficiencia (hacer un while para obtener un aleatorio que
        // no este en la lista es algoritmicamente pesado, con esto evitamos que pase menos y sea
        // mucho mas rapido. (sin esto generar 10k humanos toma 10s-20s aprox y con esto dura a lo mas 1s).
        int errL = Utils::abs(prev-0);
        int errH = Utils::abs(limit-prev);

        int lower = (errL > errH) ? 0 : prev + 1;
        int higher = (errL > errH) ? prev - 1 : limit;

        do{
            randNum = Utils::getRandom(lower, higher);
        }while (selectedIDs[randNum] != 0);

        prev = randNum;
        selectedIDs[randNum] = 1;

        tmp->add(generateHuman(randNum));
        generated++;
    }

    // La lista debe estar ordenada para que el algoritmo de generar un arbol funcione
    // de otra manera el algoritmo no generara un arbol ordenado
    personas->concat(tmp);
    personas->sort(Persona::getID);
}

// Genera una persona con datos aleatorios
Persona * Mundo::generateHuman(int ID){
    int probGen = Utils::getRandom(0, 100);
    int in = Utils::getRandom(0, 199);

    eGenero genero = (probGen > 50) ? hombre : mujer;
    string nombre = (genero == hombre) ? nombresMasc[in] : nombresFem[in];

    return new Persona(ID, genero, nombre);
}

// Esta funcion genera el arbol del mundo
void Mundo::generateTree(){
    vector<Node<Persona*>*> vec = personas->toNodeVector();
    LinkedList<Node<Persona*>*> * lista = new LinkedList<Node<Persona*>*>();

    int porcentaje = personas->length * 0.01;
    porcentaje = Tree::nodosNecesarios(porcentaje);

    int distance = (personas->length) / (porcentaje);

    Node<Persona*> * tmp;

    int total = 0;
    for (int i = 0; i < (int) vec.size(); i += distance){
        if (total >= porcentaje) break;

        tmp = vec[i];

        lista->add(tmp);

        tmp = tmp->next;
        total++;
    }

    arbol = Tree::generateTree(lista);
}

void Mundo::printHumans(){
    if (personas == NULL) return;

    int last = -1;

    Node<Persona*> * tmp = personas->firstNode;
    for (int i = 0; i < personas->length; i++){
        int current = tmp->data->getID();
        cout << "ID#" << current << ", Nombre: " <<tmp->data->nombre << endl;

        last = current;
        tmp = tmp->next;
    }
}
