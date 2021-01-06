#include <Model/thanos.h>
#include <Model/ubicacion.h>
#include <Model/dataStructures/LinkedList.h>
#include <Model/utils.h>

// Recibe un string a un .json y lo guarda en el jsonObject pasado por parametro
void JsonManager::readJson(string path, QJsonObject * obj){
    QFile file((APP_FILES_DIR + path).c_str());
    QJsonDocument doc;
    QByteArray data;

    // El archivo existe
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        data = file.readAll();
        doc = doc.fromJson(data);
        (*obj) = doc.object();
    }
}

// Recibe un string a un .json en una lista y lo guarda en el jsonArray pasado por parametro
void JsonManager::readJsonArray(string path, QJsonArray *objs){
    QFile file((APP_FILES_DIR + path).c_str());
    QJsonDocument doc;
    QByteArray data;

    // El archivo existe
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        data = file.readAll();
        doc = doc.fromJson(data);
        (*objs) = doc.array();
    }
}

// Esto lee un array de strings .json y lo retorna en una lista enlazada
LinkedList<string> * JsonManager::getByString(string path){
    LinkedList<string> * data = new LinkedList<string>();

    QJsonArray json;
    readJsonArray(path, &json);

    for (int i = 0; i < json.size(); i++){
        string current = json[i].toString().toStdString();

        data->add(current);
    }

    return data;
}

// Retorna una lista de nombres asociados a genero
LinkedList<string> * JsonManager::getNames(eGenero genero){
    LinkedList<string> * nombres = new LinkedList<string>();

    string path = (genero == HOMBRE) ? nombresMascPath : nombresFemPath;

    QJsonArray nombresJson;
    readJsonArray(path, &nombresJson);

    for (int i = 0; i < nombresJson.size(); i++){
        QJsonObject json = nombresJson[i].toObject();

        string nombre = json["Nombre"].toString().toStdString();

        if (nombre.empty()) continue;

        nombres->add(nombre);
    }

    return nombres;
}

// Esto lee el paises.json y lo retorna en una lista enlazada
LinkedList<Ubicacion *> * JsonManager::getPaises(){
    LinkedList<Ubicacion *> * paises = new LinkedList<Ubicacion *>();

    QJsonArray paisesJson;
    readJsonArray(paisesPath, &paisesJson);

    for (int i = 0; i < paisesJson.size(); i++){
        QJsonObject json = paisesJson[i].toObject();

        string strPais = json["country"].toString().toStdString();
        string strCont = json["continent"].toString().toStdString();

        Ubicacion * pais = new Ubicacion(strPais, strCont);

        paises->add(pais);
    }

    return paises;
}

// Esto lee un array de strings .json y lo retorna en una lista enlazada
LinkedList<string> * JsonManager::getByString(string path, int n){

    LinkedList<string> * data = new LinkedList<string>();

    QJsonArray json;
    readJsonArray(path, &json);

    n = (n >= json.size()) ? json.size() - 1 : n;

    int init = (new Utils())->getRandom(0, json.size() - n);

    for (int i = init; i < init + n; i++){
        string current = json[i].toString().toStdString();

        data->add(current);
    }

    return data;
}

// Esto lee el paises.json y lo retorna en una lista enlazada pero aleatoria de n paises
LinkedList<Ubicacion *> * JsonManager::getPaises(int n){
    LinkedList<Ubicacion *> * paises = new LinkedList<Ubicacion *>();

    QJsonArray paisesJson;
    readJsonArray(paisesPath, &paisesJson);

    n = (n >= paisesJson.size()) ? paisesJson.size() - 1 : n;

    int init = (new Utils())->getRandom(0, paisesJson.size() - n);

    for (int i = init; i < init + n; i++){
        QJsonObject json = paisesJson[i].toObject();

        string strPais = json["country"].toString().toStdString();
        string strCont = json["continent"].toString().toStdString();

        Ubicacion * pais = new Ubicacion(strPais, strCont);

        paises->add(pais);
    }

    return paises;
}
