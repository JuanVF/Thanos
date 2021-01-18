#include <Controller/mainwindow.h>
#include <QApplication>

#include <Model/thanos.h>
#include <Model/Enemies/corvusGlaive.h>

int test();
int openApp(int argc, char *argv[]);

int main(int argc, char *argv[]){
    //int toRet = openApp(argc, argv);
    int toRet = test();

    return toRet;

}

int test(){
    Mundo * mundo = new Mundo();

    mundo->generateHumans(10000);
    cout << "Humanos generados" << endl;
    mundo->generateTree();
    cout << "Arbol generado" << endl;
    mundo->generateFamilies();
    cout << "Familia generadad" << endl;
    mundo->generateFriends();
    cout << "Amigos generados" << endl;

    CorvusGlaive * cv = new CorvusGlaive(mundo);

    cout << "Empezando asesinatos" << endl;
    cv->kill();

    return 0;
}

int openApp(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


