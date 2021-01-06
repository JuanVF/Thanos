#include <Model/thanos.h>
#include <Model/dataStructures/node.h>

template <typename Data>
struct LinkedList{
	Node<Data> * firstNode;
	Node<Data> * lastNode;
	
	int length;
	
	// Constructores
	LinkedList(){
		firstNode = NULL;
		lastNode = NULL;
		length = 0;
	}
	
	LinkedList(Data data){
		firstNode = lastNode = new Node<Data>(data);
		
		length = 1;
	}
	
	// Funciones
	
	// Returna true si la lista esta vacia
	bool isEmpty(){
		return length == 0;
	}
	
	// Inserta en la ultima posicion
	void add(Data data){
		Node<Data> * temp = new Node<Data>(data);
		
		temp->prev = lastNode;
		
		if (!isEmpty()){
			lastNode->next = temp;
			lastNode = temp;
		
		}else{
			firstNode = lastNode = temp;
		}
		
		length++;
	}
	
	// Inserta en la primera posicion
	void addFirst(Data data){
		Node<Data> * temp = new Node<Data>(data);
		
		if (!isEmpty()){
			temp->next = firstNode;
			firstNode->prev = temp;
		
		} else {
			lastNode = temp;
		}
		
		firstNode = temp;
		
		length++;
	}
	
	// Inserta en la posicion n
	void add(Data data, int n){
		if (n >= length || isEmpty()){
			add(data);
			
		} else if (n <= 0){
			addFirst(data);
		
		} else {
			
			Node<Data> * newNode = new Node<Data>(data);
			Node<Data> * temp = firstNode;
			
			for (int i = 0; i < (n-1); i++){
				temp = temp->next;
			}
			
			newNode->next = temp->next;
			newNode->prev = temp;
			
			temp->next->prev = newNode;
			temp->next = newNode;
			
			length++;	
		}
	}
	
	// Cambia el valor del nodo n
	void set(Data data, int n){
		// Restricciones para tener todo en la misma funcion
		if (n < 0) n = 0;
		if (n >= length) n = length - 1;
		
		if (isEmpty()) return;
		
		Node<Data> * temp = firstNode;
		
		for (int i = 0; i < n; i++){
			temp = temp->next;
		}
		
		temp->data = data;
	}
	
	// Remueve el de la ultima posicion y retorna su valor
	Data remove(){
		if (isEmpty()) return NULL;
		
		Node<Data> * removed = lastNode;
		
		lastNode = removed->prev;
		
		if (length != 1){
			lastNode->next = NULL;
			removed->prev = NULL;
		}
		
		length--;
		
		return removed->data;
	}
	
	// Remueve el primero de la lista
	Data removeFirst(){
		if (isEmpty()) return NULL;
		
		Node<Data> * removed = firstNode;
		
		firstNode = removed->next;
		
		if (length != 1){
			firstNode->prev = NULL;
			removed->next = NULL;
		}
		
		length--;
		
		return removed->data;
	}
	
	// Remueve el nodo de una posicion n
	Data remove(int n){
		if (n <= 0){
			return removeFirst();
		
		} else if (n >= (length-1)){
			return remove();
		
		}
		
		Node<Data> * removed = firstNode;
			
		for (int i = 0; i < n; i++){
			removed = removed->next;
		}
		
		removed->prev->next = removed->next;
		removed->next->prev = removed->prev;
		
		removed->next = NULL;
		removed->prev = NULL;
		
		length--;
		
		return removed->data;
	}
	
	// Retorna el ultimo de la lista
	Data get(){
		if (isEmpty()) return NULL;
		
		return lastNode->data;
	}
	
	// Retorna el primero de la lista
	Data getFirst(){
		if (isEmpty()) return NULL;
		
		return firstNode->data;
	}
	
	// Retorna el de una posicion n
	Data get(int n){
		if (n <= 0) return getFirst();
		
		if (n >= length - 1) return get();
		
		Node<Data> * temp = firstNode;
		
		for (int i = 0; i < n; i++){
			temp = temp->next;
		}
		
		return temp->data;
	}
	
	// Retorna la lista al reves
	LinkedList<Data> * reverse(){
		LinkedList<Data> * rev = new LinkedList<Data>();
		Node<Data> * temp = lastNode;
		
		for (int i = 0; i < length; i++){
			rev->add(temp->data);
			temp = temp->prev;
		}
		
		return rev;
	}

    // Convierte una lista enlazada a un vector (array)
    vector<Data> toVector(){
        vector<Data> vec;

        vec.resize(length);

        Node<Data> * tmp = firstNode;

        for (int i = 0; i < length; i++){
            vec[i] = tmp->data;

            tmp = tmp->next;
        }

        return vec;
    }

    // Convierte una lista enlazada a un vector de nodos (array)
    vector<Node<Data> *> toNodeVector(){
        vector<Node<Data> *> vec;

        vec.resize(length);

        Node<Data> * tmp = firstNode;

        for (int i = 0; i < length; i++){
            vec[i] = tmp;

            tmp = tmp->next;
        }

        return vec;
    }

    // Parte la lista entre los indices dados
    LinkedList<Data> * split(int min, int max){
        // Evitamos que el minimo sea mayor que el maximo
        min = (min > max) ? max : min;
        // Evitamos indices negativos (de momento 8) )
        min = (min < 0) ? 0 : min;

        max = (min == max) ? max + 1 : max;

        LinkedList<Data> * list = new LinkedList<Data>();

        for (int i = min; i < max; i++){
            list->add(this->get(i));
        }

        return list;
    }

    // Retorna el dato que esta a la mitad de la lista
    Data getMedian(){
        return this->get(getMedianIndex());
    }

    // Retorna el indice que corresponde a la mediana
    int getMedianIndex(){
        int index = (length % 2 == 0) ? length / 2 : round(length / 2.0);
        return index - 1;
    }
	
	// Imprime la lista
	void print(){
		Node <Data> * temp = firstNode;
		
		cout << "[ ";
		
		for (int i = 0; i < length; i++){
			temp->print();
			temp = temp->next;
		}	
		
		cout << "]" << endl;
    }

    // Permite concatenar otra linkedlist
    void concat(LinkedList<Data> * list){
        Node<Data> * tmp = list->firstNode;

        for (int i = 0; i < list->length; i++){
            add(tmp->data);

            tmp = tmp->next;
        }
    }

    // Esta funcion permite ordenar una LinkedList con una funcion por parametro
    // Data DEBE TENER UN INTEGER que lo identifique como ID en la lista
    // La funcion DEBE RETORNAR ese integer
    void sort(int (*getter)(Data data)){
        vector<Node<Data> *> arr = this->toNodeVector();

        sortAux(arr, 0, length-1, getter);
    }

private:
    // Algoritmo recursivo de quick sort
    void sortAux(vector<Node<Data> *> arr, int low, int high, int (*getter)(Data data)){
        if (low < high){
            int partIndex = partition(arr, low, high, getter);

            sortAux(arr, low, partIndex - 1, getter);
            sortAux(arr, partIndex + 1, high, getter);
        }
    }

    // Esta funcion permite obtener el indice de particion y hacer los swaps de ordenamiento
    int partition(vector<Node<Data> *> arr, int low, int high, int (*getter)(Data data)){
        int pivot = arr[high]->data->getID();
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++){
            if ((*getter)(arr[j]->data) <= pivot){
                i++;
                Node<Data>::swap(arr[j], arr[i]);
            }
        }

        Node<Data>::swap(arr[i+1], arr[high]);

        return i + 1;
    }
};
