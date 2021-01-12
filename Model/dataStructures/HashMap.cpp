#include <Model/thanos.h>
#include <Model/dataStructures/LinkedList.h>

// Es la estructura llave valor para el hashmap
template <typename Key, typename Value>
struct Pairs{
    Key key;
    Value value;

    Pairs(Key _key, Value _value){
        key = _key;
        value = _value;
    }
};

// Esta estructura tiene una alta dependencia de la LinkedList por eficiencia
// Cualquier cambio a esa estructura hay que validar que no afecte al Hashmap
template <typename Key, typename Value>
struct Hashmap{
public:
    int groups;
    vector<LinkedList<Pairs<Key, Value> *> *> list;

    // Esta funcion recibe una linked list y retorna el valor
    Value getValue(LinkedList<Pairs<Key, Value> *> * item, Key key){
        Node<Pairs<Key, Value> *> * tmp = item->firstNode;

        for (int i = 0; i < item->length; i++){
            if (tmp->data->key == key) return tmp->data->value;

            tmp = tmp->next;
        }

        return NULL;
    }

    // Funcion auxiliar para desconectar un nodo (funcion del remove)
    void removeNode(LinkedList<Pairs<Key, Value> *> * tmpList, Node<Pairs<Key, Value> *> * tmp){
        if (tmp->prev != NULL)
            tmp->prev->next = tmp->next;
        else
            tmpList->firstNode = tmp->next;

        if (tmp->next != NULL)
            tmp->next->prev = tmp->prev;
        else
            tmpList->lastNode = tmp->prev;

        tmp->next = NULL;
        tmp->prev = NULL;

    }
    // Crea un hashmap de 1000 grupos
    Hashmap(){
        groups = 1000;

        list.resize(groups);
        list.assign(groups, NULL);
    }

    // Crea un hashmap de 10 ** n grupos
    // Si n es menor que cero le asigna el default
    Hashmap(int n){
        groups = (n < 0) ? 1000 : n;

        list.resize(groups);
        list.assign(groups, NULL);
    }

    // Inserta un valor en el hashmap
    void insert(Key key, Value value){
        int hashKey = hashFunction(key);

        if (list[hashKey] == NULL)
            list[hashKey] = new LinkedList<Pairs<Key, Value> *>(new Pairs<Key, Value>(key, value));
        else
            list[hashKey]->add(new Pairs<Key, Value>(key, value));
    }

    // Obtiene el valor por su llave
    Value get(Key key){
        int hashKey = hashFunction(key);

        // No existe
        if (list[hashKey] == NULL) return NULL;

        return getValue(list[hashKey], key);
    }

    // Permite settear el valor de una llave
    // Si no existe, la crea y retorna nulo (indicando que no existia)
    Value set(Key key, Value value){
        int hashKey = hashFunction(key);

        Value val = NULL;

        if (list[hashKey] == NULL){
            list[hashKey] = new LinkedList<Pairs<Key, Value> *>(new Pairs<Key, Value>(key, value));

        } else {
            Node<Pairs<Key, Value> *> * tmp = list[hashKey]->firstNode;

            for (int i = 0; i < list[hashKey]->length; i++){
                if (key == tmp->data->key){
                    val = tmp->data->value;

                    tmp->data->value = value;

                    break;
                }
            }
        }

        return val;
    }

    // Retorna true si contiene a la llave
    bool contains(Key key){
        return get(key) != NULL;
    }

    // Permite aumentar la cantidad de llaves disponibles
    // No permite disminuir la cantidad de llaves
    bool resize(int n){
        if (n <= groups | n < 0) return false;

        groups = n;
        list.resize(n);

        return true;
    }

    // Remueve un valor del hashmap
    Value remove(Key key){
        int hashKey = hashFunction(key);

        Node<Pairs<Key, Value> *> * tmp = list[hashKey]->firstNode;

        // Hago el recorrido aqui por eficiencia
        // La LinkedList recorre todo para buscar y eliminar
        // Entonces haria un double for para cada accion
        // Aqui hago ambas al mismo tiempo :)
        for (int i = 0; i < list[hashKey]->length; i++){
            if (tmp->data->key == key){
                Value * val = tmp->data->value;

                removeNode(list[hashKey], tmp);

                return val;
            }

            tmp = tmp->next;
        }

        return NULL;
    }

    // Aplica una funcion hash al hashmap
    int hashFunction(Key key){
        int rst = hash<Key>{}(key);

        rst = (rst < 0) ? rst * -1 : rst;

        return rst % groups;
    }

    // Funcion de debug
    void print(){
        for (int i = 0; i < list.size(); i++){
            if (list[i] == NULL) continue;

            cout << "Hash code: " << i << endl;

            list[i]->print();
        }
    }
};
