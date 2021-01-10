#include <Controller/mainwindow.h>
#include <Model/dataStructures/HashMap.h>
#include <Model/estado.h>
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
    /*Hashmap<int, string> * haspmap = new Hashmap<int, string>();
    haspmap->insert(1,"hola");
    haspmap->insert(2,"hola 2");
    haspmap->insert(3,"hola 3");
    cout << haspmap->get(1) << endl;
    cout << haspmap->get(2) << endl;
    return 0;
    */
    int estado = EstadoMarital().getEstado();
    cout << estado << endl;
    return 0;
}

int openApp(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
