#include <Controller/mainwindow.h>
#include <Model/dataStructures/HashMap.h>
#include <Model/dataStructures/Tree.h>
#include <Model/Mundo/mundo.h>

#include <QApplication>

int test();
int openApp(int argc, char *argv[]);

int main(int argc, char *argv[]){
    //int toRet = openApp(argc, argv);
    int toRet = test();

    return toRet;

}

int test(){
    Mundo * mundo = new Mundo();
    float time = clock();
    mundo->generateHumans(10000);
    float since = (clock() - time)/1000.0;

    cout << "Tiempo en generar humanos: " << since << "s" << endl;
    mundo->generateTree();

    /*time = clock();
    mundo->generateFriends();
    since = (clock() - time)/1000.0;
    cout << "Tiempo en generar amigos: " << since << "s" << endl;*/

    time = clock();
    mundo->generateFamilies();
    since = (clock() - time)/1000.0;
    cout << "Tiempo en generar familia: " << since << "s" << endl;

    mundo->printHumans();

    return 0;
}

int openApp(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


