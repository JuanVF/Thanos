#include <Model/thanos.h>
#include <Model/dataStructures/LinkedList.h>

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

// Esto lee el paises.json y lo retorna en una lista enlazada
// ToDo: que sea una lista de ubicaciones
LinkedList<string> * JsonManager::getPaises(){
    LinkedList<string> * paises = new LinkedList<string>();

    QJsonArray paisesJson;
    readJsonArray(paisesPath, &paisesJson);

    for (int i = 0; i < paisesJson.size(); i++){
        QJsonObject pais = paisesJson[i].toObject();

        paises->add(pais["country"].toString().toStdString());
    }

    return paises;
}
