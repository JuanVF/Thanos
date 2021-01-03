#include <Model/thanos.h>
#include <Model/persona.h>

struct TreeNode{
    Persona * persona;

    TreeNode * hijoIzq, * hijoDer;

    // Constructores
    TreeNode(Persona * _persona){
        persona = _persona;
    }

    TreeNode(Persona * _persona, TreeNode * _hijoIzq){
        persona = _persona;
        hijoIzq = _hijoIzq;
    }

    TreeNode(Persona * _persona, TreeNode * _hijoIzq, TreeNode * _hijoDer){
        persona = _persona;
        hijoIzq = _hijoIzq;
        hijoDer = _hijoDer;
    }

    // Funciones

    // Retorna la ID del nodo
    int getID(){
        return persona->getID();
    }
};
