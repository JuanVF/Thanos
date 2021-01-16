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
    /*Mundo * mundo = new Mundo();

    Nebula * nebula = new Nebula(mundo);
    Ebony * ebony = new Ebony(mundo);
    BlackDwarf * bd = new BlackDwarf(mundo);
    hashthanos * thanos = new hashthanos(mundo);

    Thor * thor = new Thor(mundo);
    Antman * antman = new Antman(mundo);
    IronMan * ironman = new IronMan(mundo);
    SpiderMan * spider = new SpiderMan(mundo);

    float time = clock();
    mundo->generateHumans(10000);
    float since = (clock() - time)/1000.0;

    cout << "Tiempo en generar humanos: " << since << "s" << endl;
    mundo->generateTree();

    time = clock();
    mundo->generateFriends();
    since = (clock() - time)/1000.0;
    cout << "Tiempo en generar amigos: " << since << "s" << endl;

    time = clock();
    mundo->generateFamilies();
    since = (clock() - time)/1000.0;
    cout << "Tiempo en generar familia: " << since << "s" << endl;

    time = clock();
    nebula->kill();
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Nebula de hacer kills: " << since << "s" << endl;


    int randID = mundo->arbol->obtenerRandom()->ID;

    time = clock();
    ebony->kill(randID);
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Ebony de hacer kills: " << since << "s" << endl;

    time = clock();
    bd->kill("Parapente");
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Black dwarf de hacer kills: " << since << "s" << endl;

    time = clock();
    thanos->generateHashtable();
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Thanos en generar tabla: " << since << "s" << endl;

    time = clock();
    thanos->killByLevel(0);
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Thanos en asesinar un nivel: " << since << "s" << endl;

    time = clock();
    thanos->killByYear(2020);
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Thanos en asesinar un anio: " << since << "s" << endl;

    time = clock();
    thanos->killByLevelAndYear(2019, 5);
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Thanos en asesinar un nivel y anio: " << since << "s" << endl;

    time = clock();
    thor->save(5);
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Thor en salvar un nivel: " << since << "s" << endl;

    time = clock();
    antman->save(10);
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Antman en salvar: " << since << "s" << endl;

    time = clock();
    ironman->save();
    since = (clock() - time)/1000.0;
    cout << "Tiempo de IronMan en salvar personas: " << since << "s" << endl;

    time = clock();
    spider->save();
    since = (clock() - time)/1000.0;
    cout << "Tiempo de Spiderman en salvar: " << since << "s" << endl;

    //mundo->printHumans();*/

    return 0;
}

int openApp(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


