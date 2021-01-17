#include <Model/thanos.h>

string FileManager::logFile = "gameLog.txt";
string FileManager::avengersFile = "avengersLog.txt";
string FileManager::enemiesFile = "enemiesLog.txt";

// Lee un archivo
string FileManager::readFile(string path){
    path = APP_LOGS_DIR + path;

    QFile file(QString("").append(path.c_str()));
    QString text;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);

        text = text.append(in.readAll());

        file.close();
    }

    return text.toStdString();
}

// Guarda sobre un archivo
bool FileManager::saveFile(string data, string path){
    path = APP_LOGS_DIR + path;

    QFile file(QString("").append(path.c_str()));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

    QTextStream out(&file);

    out << QByteArray(data.c_str());

    file.close();

    return true;
}

// Guarda sobre un archivo
bool FileManager::appendFile(string data, string path){
    path = APP_LOGS_DIR + path;

    QFile file(QString("").append(path.c_str()));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) return false;

    QTextStream out(&file);

    out << QByteArray(data.c_str());

    file.close();

    return true;
}
