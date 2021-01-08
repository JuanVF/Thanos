#include <Controller/mainwindow.h>

//#include <Model/jsonmanager.h>
#include <Model/thanos.h>

#include <Model/dataStructures/HashMap.h>
#include <Model/dataStructures/Tree.h>
#include <Model/mundo.h>

#include <QApplication>

int test();
int openApp(int argc, char *argv[]);
void getLevels(LinkedList<Node<Persona *>*> * list, Hashmap<int, LinkedList<Node<Persona *>*> *> * hashmap, int level);



int main(int argc, char *argv[]){

    int toRet = openApp(argc, argv);
    //int toRet = test();

    //int toRet = openApp(argc, argv);
    //int toRet = test();

    return toRet;

}

int test(){

    //int r = RangoEtario().seleccionarRangoViajes();
    //cout << r <<endl;

    // Tests de performance
    // Esto lo pueden borrar era solo para testear :P
    //mundo->printHumans();

    return 0;
}

int openApp(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


