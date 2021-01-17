#include <Model/thanos.h>
#include <Model/Mundo/ejercicio.h>
#include <Model/Mundo/paisesvisitados.h>
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
    apellidos.resize(100);
    deportes.resize(63);

    loadData();
}

// Esta funcion se encarga de iniciar los datos...
// Si el mundo ya fue iniciado y se vuelve a llamar esta funcion
// borra TODOS los datos previamente cargados
void Mundo::reLoad(int _nombres, int _apellidos, int _creencias, int _profesiones, int _paises, int _deportes){
    paises.resize(_paises);
    creencias.resize(_creencias);
    profesiones.resize(_profesiones);
    deportes.resize(_deportes);

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
    apellidos = (json.getByString(json.apellidosPath, apellidos.size()))->toVector();
    deportes = (json.getByString(json.deportesPath, deportes.size()))->toVector();
}

// Genera los humanos del mundo
// TODO: Muchas cosas
void Mundo::generateHumans(int amount){
    int generated = 0;

    LinkedList<Persona *> * tmp = new LinkedList<Persona *>();

    int limit = 9999999;
    int randNum = Utils::getRandom(0, limit);
    int prev = randNum;

    string localLogFile = FileManager::readFile(FileManager::logFile);
    localLogFile += "Generando " + to_string(amount) + " humanos...\n";

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

    localLogFile += "Humanos generados...\n";
    FileManager::saveFile(localLogFile, FileManager::logFile);
}

// Genera una persona con datos aleatorios
Persona * Mundo::generateHuman(int ID){

    int probGen = Utils::getRandom(0, 100);
    int in = Utils::getRandom(0, 199);

    eGenero genero = (probGen > 50) ? hombre : mujer;
    string nombre = (genero == hombre) ? nombresMasc[in] : nombresFem[in];
    string apellido = apellidos[Utils::getRandom(0, apellidos.size() - 1)];
    string creencia = creencias[Utils::getRandom(0, creencias.size() - 1)];
    string profesion = profesiones[Utils::getRandom(0, profesiones.size() - 1)];
    Ubicacion * ubicacion = paises[Utils::getRandom(0, paises.size() - 1)];

    Persona * persona = new Persona(ID, genero, nombre, apellido, creencia, profesion, ubicacion);
    persona->deporte->generarDeportes(deportes);
    persona->turismo = PaisesVisitados::generarPaises(paises);

    return persona;
}

// Esta funcion genera el arbol del mundo
void Mundo::generateTree(){
    string localLogFile = FileManager::readFile(FileManager::logFile);
    localLogFile += "Generando el arbol del mundo\n";

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

    localLogFile += "Arbol generado...\n";
    FileManager::saveFile(localLogFile, FileManager::logFile);
}

// Genera los amigos en el arbol
void Mundo::generateFriends(){
    string localLogFile = FileManager::readFile(FileManager::logFile);
    localLogFile += "Generando amigos\n";

    vector<Persona *> vPersonas = personas->toVector();

    for (int i = 0; i < (int) vPersonas.size(); i++){
        vPersonas[i]->generarAmigos(vPersonas);
    }

    localLogFile += "Amigos generados...\n";
    FileManager::saveFile(localLogFile, FileManager::logFile);
}

void Mundo::generateFamilies(){
    string localLogFile = FileManager::readFile(FileManager::logFile);
    localLogFile += "Generando familia\n";

    vector<Persona *> tmp = personas->toVector();

    int amount = 0;
    for (int i = 0; i < (int) tmp.size(); i++){
        tmp[i]->familia->generarConyugue(tmp);
        tmp[i]->familia->generarHijos(tmp);

        if (tmp[i]->familia->hijos->length > 0) amount++;
    }

    localLogFile += "Personas con mas de un hijo: " + to_string(amount) + "\n";
    localLogFile += "Familia generada...\n";
    FileManager::saveFile(localLogFile, FileManager::logFile);
}

// Retorna una persona por su ID
Persona * Mundo::getById(int ID){
    string localLogFile = FileManager::readFile(FileManager::logFile);
    localLogFile += "Se consulto la ID#" + to_string(ID) + "\n";

    Persona * tmp = arbol->obtener(ID);

    if (tmp == NULL)
        localLogFile += "La ID es nula...\n";

    FileManager::saveFile(localLogFile, FileManager::logFile);

    return tmp;
}

vector<Persona *> Mundo::getFamilyById(int ID){
    Persona * tmp = getById(ID);
    Persona * _raiz = Familia::obtenerRaizFamiliar(tmp);

    return _raiz->familia->hijos->toVector();
}

// Retorna la lista de amigos de una persona por su ID
vector<Persona *> Mundo::getFriendsById(int ID){
    Persona * persona = getById(ID);

    return persona->amigos->toVector();
}

vector<Persona *> Mundo::getBySport(string sport){
    vector<Persona *> _personas = personas->toVector();
    LinkedList<Persona *> * lKills = new LinkedList<Persona *>();

    for (int i = 0; i < (int) _personas.size(); i++){
        if (_personas[i]->deporte->deportes->contains(sport)){
            lKills->add(_personas[i]);
        }
    }

    return lKills->toVector();
}

int Mundo::getAlivePeople(){
    vector<Persona *> _personas = personas->toVector();
    int cant = 0;

    for (int i = 0; i < (int) _personas.size(); i++){
        cant += _personas[i]->savedLog->length;
    }

    return cant;
}

int Mundo::getDeathPeople(){
    vector<Persona *> _personas = personas->toVector();
    int cant = 0;

    for (int i = 0; i < (int) _personas.size(); i++){
        cant += _personas[i]->killLog->length;
    }

    return cant;
}

int Mundo::getSavedPeople(){
    vector<Persona *> _personas = personas->toVector();
    int cant = 0;

    for (int i = 0; i < (int) _personas.size(); i++){
        cant = (_personas[i]->savedLog->length > 0) ? cant + 1 : cant;
    }

    return cant;
}

Hashmap<int, LinkedList<Persona *> *> * Mundo::getByYears(){
    Hashmap<int, LinkedList<Persona *> *> * _personas = new Hashmap<int, LinkedList<Persona *> *>();
    vector<Persona *> vPersonas = personas->toVector();

    for (int i = 0; i < (int) vPersonas.size(); i++){
        int year = vPersonas[i]->edad->fechaDeNacimiento[2];

        if (_personas->contains(year))
            _personas->get(year)->add(vPersonas[i]);
        else
            _personas->insert(year, new LinkedList<Persona *>(vPersonas[i]));
    }

    return _personas;
}

void Mundo::printHumans(){
    if (personas == NULL) return;

    int last = -1;

    cout << "Lista de humanos: " << endl << endl;
    Node<Persona*> * tmp = personas->firstNode;

    for (int i = 0; i < personas->length; i++){
        int current = tmp->data->getID();

        int anio = tmp->data->edad->fechaDeNacimiento[2];
        int mes = tmp->data->edad->fechaDeNacimiento[1];
        int dia = tmp->data->edad->fechaDeNacimiento[0];

        Persona * cong = tmp->data->familia->conyugue;

        string conyugue = (cong == NULL) ? "N/A" : cong->nombre + " " + cong->apellido;
        string vivo = (tmp->data->isAlive) ? "Esta vivo" : "Esta muerto";

        int IDCong = (cong == NULL) ? 0 : cong->ID;

        cout << "ID#" << current << ", Nombre: " <<tmp->data->nombre << " " << tmp->data->apellido << endl;
        cout << "Vivo: " << vivo << endl;
        cout << "Creencia: " << tmp->data->creencia << endl;
        cout << "Profesion: " << tmp->data->profesion << endl;
        cout << "Pais: " << tmp->data->ubicacion->pais << endl;
        cout << "Fecha nacimiento: " << anio << "/" << mes << "/" << dia << endl;
        cout << "Conyugue: " << conyugue << ", ID: " << IDCong << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Deportes: " << endl;
        cout << "Cantidad de veces: " << tmp->data->deporte->cantidad << endl;
        cout << "Lista: " << endl;

        for (int i = 0; i < (int) tmp->data->deporte->vDeportes.size(); i++)
            cout << tmp->data->deporte->vDeportes[i] << " ";
        cout << endl;

        cout << "--------------------------------------------------" << endl;
        cout << "Paises visitados: " << endl;

        for (int i = 0; i < tmp->data->turismo.size(); i++)
            if (tmp->data->turismo[i] != NULL)
            if (!tmp->data->turismo[i]->pais.empty())
                cout << tmp->data->turismo[i]->pais << " ";
        cout << endl;

        cout << "--------------------------------------------------" << endl;
        cout << "Amigos: " << endl;

        for (int j = 0; j < tmp->data->amigos->length; j++){
            cout << "ID#" << tmp->data->amigos->get(j)->ID << ", Nombre: " <<tmp->data->amigos->get(j)->nombre << endl;
        }

        cout << "--------------------------------------------------" << endl;
        cout << "Hijos: " << endl;


        for (int j = 0; j < tmp->data->familia->hijos->length; j++){
            cout << "ID#" << tmp->data->familia->hijos->get(j)->ID << ", Nombre: " <<tmp->data->familia->hijos->get(j)->nombre << endl;
        }
        cout << "--------------------------------------------------" << endl << endl;

        last = current;
        tmp = tmp->next;
    }
}
