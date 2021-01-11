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

    eGenero genero = (probGen > 50) ? HOMBRE : MUJER;
    string nombre = (genero == HOMBRE) ? nombresMasc[in] : nombresFem[in];
    string creencia = creencias[Utils::getRandom(0, creencias.size() - 1)];
    string profesion = profesiones[Utils::getRandom(0, profesiones.size() - 1)];
    Ubicacion * ubicacion = paises[Utils::getRandom(0, paises.size() - 1)];

    return new Persona(ID, genero, nombre, creencia, profesion, ubicacion);
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

// Genera los amigos en el arbol
void Mundo::generateFriends(){
    Node<Persona *> * nodo = personas->firstNode;

    for (int i = 0; i < personas->length; i++){
        nodo->data->generarAmigos(personas);

        nodo = nodo->next;
    }
}

// Retorna una persona por su ID
Persona * Mundo::getById(int ID){
    return arbol->obtener(ID);
}

// Retorna la lista de amigos de una persona por su ID
vector<Persona *> Mundo::getFriendsById(int ID){
    Persona * persona = getById(ID);

    return persona->amigos->toVector();
}

void Mundo::printHumans(){
    if (personas == NULL) return;

    int last = -1;

    cout << "Lista de humanos: " << endl << endl;
    Node<Persona*> * tmp = personas->firstNode;

    for (int i = 0; i < personas->length; i++){
        int current = tmp->data->getID();
        cout << "ID#" << current << ", Nombre: " <<tmp->data->nombre << endl;
        cout << "Creencia: " << tmp->data->creencia << endl;
        cout << "Profesion: " << tmp->data->profesion << endl;
        cout << "Pais: " << tmp->data->ubicacion->pais << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Amigos: " << endl;

        for (int j = 0; j < tmp->data->amigos->length; j++){
            cout << "ID#" << tmp->data->amigos->get(j)->ID << ", Nombre: " <<tmp->data->amigos->get(j)->nombre << endl;
        }

        cout << "--------------------------------------------------" << endl << endl;

        last = current;
        tmp = tmp->next;
    }
}
