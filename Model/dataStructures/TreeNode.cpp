#include <Model/thanos.h>
#include <Model/persona.h>
#include <Model/dataStructures/node.h>

struct TreeNode{
    Node<Persona *> * persona;

    TreeNode * hijoIzq, * hijoDer;

    // Constructores
    TreeNode(Node<Persona *> * _persona){
        persona = _persona;
        hijoDer = NULL;
        hijoIzq = NULL;
    }

    TreeNode(Node<Persona *> * _persona, TreeNode * _hijoIzq){
        persona = _persona;
        hijoIzq = _hijoIzq;
        hijoDer = NULL;
    }

    TreeNode(Node<Persona *> * _persona, TreeNode * _hijoIzq, TreeNode * _hijoDer){
        persona = _persona;
        hijoIzq = _hijoIzq;
        hijoDer = _hijoDer;
    }

    // Funciones

    // Retorna la ID del nodo
    int getID(){
        return persona->data->getID();
    }

    // Retorna true si es una hoja
    bool esHoja(){
        return hijoIzq == NULL && hijoDer == NULL;
    }

    bool hijosNulos(){
        return hijoIzq == NULL || hijoDer == NULL;
    }
};
