#include <Controller/mainwindow.h>
#include <Model/dataStructures/HashMap.h>
#include <Model/dataStructures/Tree.h>
#include <Model/Mundo/mundo.h>
#include <Model/Enemies/Nebula.h>
#include <Model/Enemies/ebony.h>
#include <Model/Enemies/blackdwarf.h>
#include <Model/Enemies/hashthanos.h>
#include <Model/Avengers/thor.h>
#include <Model/Avengers/antman.h>
#include <Model/Avengers/ironman.h>
#include <Model/Avengers/spiderman.h>
#include <Model/filemanager.h>

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

    Nebula * nebula = new Nebula(mundo);
    Ebony * ebony = new Ebony(mundo);
    BlackDwarf * bd = new BlackDwarf(mundo);
    hashthanos * thanos = new hashthanos(mundo);

    Thor * thor = new Thor(mundo);
    Antman * antman = new Antman(mundo);
    IronMan * ironman = new IronMan(mundo);
    SpiderMan * spider = new SpiderMan(mundo);

    cout << "Generando humanos" << endl;
    mundo->generateHumans(10000);
    cout << "Generando arbol" << endl;
    mundo->generateTree();
    cout << "Generando amigos" << endl;
    mundo->generateFriends();
    cout << "Generando familia" << endl;
    mundo->generateFamilies();

    int randID = mundo->arbol->obtenerRandom()->ID;

    ebony->kill(randID);
    bd->kill("Parapente");
    thanos->generateHashtable();

    thanos->killByLevel(0);
    thanos->killByYear(2020);
    thanos->killByLevelAndYear(2019, 5);

    nebula->kill();

    antman->save(10);

    ironman->save();

    spider->save();

    thor->save(5);

    return 0;
}

int openApp(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


