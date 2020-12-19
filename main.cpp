#include <Controller/mainwindow.h>
#include <Model/jsonmanager.h>

#include <QApplication>

int test();
int openApp(int argc, char *argv[]);

int main(int argc, char *argv[]){
    //int toRet = openApp(argc, argv);
    int toRet = test();
    return toRet;
}

int test(){
    return 0;
}

int openApp(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
