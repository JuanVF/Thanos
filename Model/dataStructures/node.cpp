#include <Model/thanos.h>

template <typename Data>
struct Node{
	Data data;
	Node<Data> * next;
	Node<Data> * prev;
	
	// Constructores
	Node(Data _data){
		data = _data;
		next = NULL;
		prev = NULL;	
	}
	
	Node(Data _data, Node<Data> * _next){
		data = _data;
		next = _next;
		prev = NULL;
	}
	
	Node(Data _data, Node<Data> * _next, Node<Data> * _prev){
		data = _data;
		next = _next;
		prev = _prev;	
	}
	
	// Funciones
	
	void print(){
		cout << "[ " << data << " ] ";
	}

    // Permite intercambiar valores entre punteros
    void swap(Node<Data> * node){
        Data * tmp = data;
        data = node->data;
        node->data = tmp;
    }

    // Permite intercambiar dos nodos
    static void swap(Node<Data> * n1, Node<Data> * n2){
        Data tmp = n1->data;
        n1->data = n2->data;
        n2->data = tmp;
    }
};
