#include <Model/thanos.h>
#include <Model/dataStructures/TreeNode.h>

struct Tree{
    TreeNode * raiz;

    // Constructor
    Tree(TreeNode * _raiz){
        raiz = _raiz;
    }

    // Funciones

    // Retorna la cantidad de nodos necesarios para un nodo completo dada una cantidad
    int nodosNecesarios(int cant){
        // Se despeja el n de la suma geometrica con r = 2
        int n = ceil((log(abs(cant + 1)) / log(2)) - 1);

        // Se obtiene el total a partir de la suma geometrica
        int total = -1 + pow(2, n+1);

        return total;
    }

    // Agregamos una persona al arbol
    void insertar(Persona * persona){

    }
};
