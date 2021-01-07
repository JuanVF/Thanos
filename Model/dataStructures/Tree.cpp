#include <Model/thanos.h>
#include <Model/dataStructures/TreeNode.h>
#include <Model/dataStructures/HashMap.h>

struct Tree{
public:
    TreeNode * raiz;

    Tree(){
        raiz = NULL;
    }

    // Constructor
    Tree(Node<Persona *> * persona){
        raiz = new TreeNode(persona);
    }

    // Funciones

    // Retorna la cantidad de nodos necesarios para un nodo completo dada una cantidad
    static int nodosNecesarios(int cant){
        // Se despeja el n de la suma geometrica con r = 2
        int n = ceil((log(abs(cant + 1)) / log(2)) - 1);

        // Se obtiene el total a partir de la suma geometrica
        int total = -1 + pow(2, n+1);

        return total;
    }

    // Retorna la cantidad de nodos que tiene el arbol
    int cantidadNodos(){
        return cantidadNodos(raiz);
    }

    // Agregamos una persona al arbol
    void insertar(Node<Persona *> * persona){
        if (persona == NULL) return;

        insertar(persona, &raiz);
    }

    // Dado un indice lo busca en el arbol y lo devuelve
    Persona * obtener(int indice){
        if (indice < 0) return NULL;

        Persona * persona = obtenerAux(indice, raiz);

        return persona;
    }

    // Devuelve un hashmap con las personas por cada nivel del arbol
    // La key es el nivel y devuelve una lista con las personas en ese nivel
    Hashmap<int, LinkedList<Persona *> *> * niveles(){
        Hashmap<int, LinkedList<Persona *> *> * hashmap = new Hashmap<int, LinkedList<Persona *> *>();

        if (raiz != NULL)
            niveles(hashmap, raiz, 0);

        return hashmap;
    }

    // Dada una lista ordenada genera un arbol completo y ordenado a partir de ella
    // Debe cumplir que la cantidad de elementos es 2**k - 1 o no sera completo
    static Tree * generateTree(LinkedList<Node<Persona *>*> * list){
        Hashmap<int, LinkedList<Node<Persona *>*> *> * levels = new Hashmap<int, LinkedList<Node<Persona *>*> *>();
        Tree * tree = new Tree();

        generateHashmap(list, levels, 0);

        int key = 0;
        bool hashesLeft = levels->contains(key);
        vector<Node<Persona *>*> tmp;

        while (hashesLeft){
            // Un vector es mas eficiente que una lista enlazada
            tmp = levels->get(key)->toVector();

            for (int i = 0; i < (int) tmp.size(); i++){
                tree->insertar(tmp[i]);
            }

            key++;
            hashesLeft = levels->contains(key);
        }

        return tree;
    }
private:
    // Dada una lista ordenada genera un hashmap con los niveles de un arbol
    // Este hashmap es uno completo y ordenado
    // Requisitos: la lista debe estar ordenada
    static void generateHashmap(LinkedList<Node<Persona *>*> * list, Hashmap<int, LinkedList<Node<Persona *>*> *> * hashmap, int level){
        // Insertamos el valor
        if (hashmap->contains(level))
            hashmap->get(level)->add(list->getMedian());
        else
            hashmap->insert(level, new LinkedList<Node<Persona *>*>(list->getMedian()));

        // Condicion de parada
        if (list->length == 1) return;

        generateHashmap(list->split(0, list->getMedianIndex()), hashmap, level + 1);
        generateHashmap(list->split(list->getMedianIndex() + 1, list->length), hashmap, level + 1);
    }

    // Auxiliar para la funcion persona
    Persona * obtenerAux(int indice, TreeNode * tmp){
        if (tmp == NULL) return NULL;

        // Caso llegamos al ultimo nivel
        if (tmp->hijosNulos()){
            return busquedaIterativa(indice, tmp, tmp->getID() <= indice);
        }

        // Caso: la persona estaba en el arbol
        if (tmp->getID() == indice) return tmp->persona->data;

        int weightRoot = Utils::abs(tmp->getID() - indice);
        int weightSon = 0;

        TreeNode * son = NULL;

        // Aqui verificamos si la ID esta entre el hijo o el nodo
        // TODO: Needs refactor
        if (tmp->hijoIzq->getID() < indice && indice < tmp->getID()){ // Hijo izquierdo
            weightSon = Utils::abs(tmp->hijoIzq->getID() - indice);
            son = tmp->hijoIzq;

            if (weightRoot < weightSon)
                return busquedaIterativa(indice, tmp, false);
            else
                return busquedaIterativa(indice, son, true);

        } else if (tmp->getID() < indice && indice < tmp->hijoDer->getID()){ // Hijo derecho
            weightSon = Utils::abs(tmp->hijoDer->getID() - indice);
            son = tmp->hijoDer;

            if (weightRoot < weightSon)
                return busquedaIterativa(indice, tmp, true);
            else
                return busquedaIterativa(indice, son, false);
        }

        // Validamos a que hijo lo mandamos
        son = (tmp->getID() > indice) ? tmp->hijoIzq : tmp->hijoDer;

        return obtenerAux(indice, son);
    }

    // Hace la busqueda iterativa en la lista enlazada
    Persona * busquedaIterativa(int indice, TreeNode * tmp, bool isRight){
        Node<Persona *> * sig = tmp->persona;

        while(sig != NULL){
            if (sig->data->getID() == indice) return sig->data;

            sig = (isRight) ? sig->next : sig->prev;
        }

        return NULL;
    }

    // Funcion auxiliar para crear el hashmap con los niveles
    void niveles(Hashmap<int, LinkedList<Persona *> *> * hashmap, TreeNode * tmp, int level){
        if (tmp == NULL) return;

        if (hashmap->contains(level)){
            LinkedList<Persona *> * personas = hashmap->get(level);

            personas->add(tmp->persona->data);
        } else {
            LinkedList<Persona *> * personas = new LinkedList<Persona *>(tmp->persona->data);

            hashmap->insert(level, personas);
        }

        niveles(hashmap, tmp->hijoIzq, level + 1);
        niveles(hashmap, tmp->hijoDer, level + 1);
    }

    // Funcion auxiliar para insertar en el arbol
    void insertar(Node<Persona *> * persona, TreeNode * * tmp){
        if ((*tmp) == NULL){
            (*tmp) = new TreeNode(persona);

            return;
        }

        if ((*tmp)->esHoja()){
            if ((*tmp)->getID() > persona->data->getID()){
                (*tmp)->hijoIzq = new TreeNode(persona);

            } else {
                (*tmp)->hijoDer = new TreeNode(persona);

            }

            return;
        }

        if ((*tmp)->getID() > persona->data->getID()){
            insertar(persona, &(*tmp)->hijoIzq);

        } else {
            insertar(persona, &(*tmp)->hijoDer);
        }
    }

    // Funcion auxiliar para obtener la cantidad de nodos
    int cantidadNodos(TreeNode * tmp){
        if (tmp == NULL) return 0;

        if (tmp->esHoja()) return 1;

        return cantidadNodos(tmp->hijoIzq) + 1 + cantidadNodos(tmp->hijoDer);
    }
};
