#include <Controller/mainwindow.h>
#include <Model/dataStructures/HashMap.h>
#include <Model/dataStructures/Tree.h>
#include <Model/mundo.h>

#include <QApplication>

int test();
int openApp(int argc, char *argv[]);
void getLevels(LinkedList<Node<Persona *>*> * list, Hashmap<int, LinkedList<Node<Persona *>*> *> * hashmap, int level);



int main(int argc, char *argv[]){
    //int toRet = openApp(argc, argv);
    int toRet = test();

    return toRet;

}

int test(){
    // Tests de performance
    // Esto lo pueden borrar era solo para testear :P
    Mundo * mundo = new Mundo();

    float time = clock();

    mundo->generateHumans(10000);

    float since = (clock() - time)/1000.0;

    cout << "Tiempo en generar humanos: " << since << "s" << endl;

    time = clock();
    mundo->generateTree();
    since = (clock() - time)/1000.0;

    cout << "Tiempo en generar arbol: " << since << "s" << endl;

    int lastID = mundo->personas->lastNode->data->getID();
    cout << "Ultima ID: " << lastID << endl;

    time = clock();
    Node<Persona *> * tmp = mundo->personas->firstNode;

    for (int i = 0; i < mundo->personas->length; i++){
        if (tmp->data->getID() == lastID) break;

        tmp = tmp->next;
    }

    since = (clock() - time)/1000.0;

    cout << "Tiempo en buscar iterativamente: " << since << "s" << endl;
    //mundo->printHumans();

    return 0;
}

int openApp(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


