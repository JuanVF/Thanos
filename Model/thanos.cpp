#ifndef COMMONS
#define COMMONS

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <random>
#include <string>
#include <windows.h>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QFile>

using namespace std;
#endif

/*
    Constantes
*/
QDir dir;
const string APP_FILES_DIR = dir.homePath().toStdString() + "/documents/thanos/";

/*
    Aqui vamos a declarar las clases y estructuras que se van a utilizar en toda la progra
*/
template <typename Data> struct CircularList;
template <typename Data> struct LinkedList;
template <typename Data> struct Node;
template <typename Data> struct Queue;
template <typename Key, typename Value> struct Hashmap;
template <typename Key, typename Value> struct Pairs;
struct TreeNode;
struct Tree;
class Mundo;
class Persona;
class Acciones;
class Familia;
class Ubicacion;
class RangoEtario;
class Ejercicio;
class Utils;
class JsonManager;
class EmailSender;
template <typename Data> class Accion;

/*
    Nota: Traten de definir sus clases aqui... esto para evitar problemas de importacion y declaracion
          Con definir me refiero a solo las variables y funciones que tienen... el codigo y la logica
          cada una de las clases va a tener su propio archivo.
*/

class Persona{
private:
    int ID;
    string apellido;
    string nombre;
    string creencia;
    string profesion;
    string * experiencias;
    CircularList<Persona *> * amigos;
    Ubicacion * ubicacion;
    // Ejercicio * salud;
    // Familia * familia;
    // eEstadoMarital estado;
    // RangoEtario * edad;
    // Acciones * acciones;
    // eGenero genero;

    void generarPecados();
    void generarBuenasAcciones();

public:
    Persona(){}

    void generarAmigos(CircularList<Persona *> * personas);
    void generarAcciones();

    int getID();
};

class Mundo{
private:
    CircularList<Persona *> * personas;
    // Arbol

    // Estos son los arreglos de datos que se van a cargar
    vector<string> nombres;
    vector<string> apellidos;
    vector<string> creencias;
    vector<string> profesiones;
    vector<Ubicacion *> paises;
public:
    Mundo();

    void reLoad(int _nombres, int _apellidos, int _creencias, int _profesiones, int _paises);
    void loadData();
    // El resto de funcionas las generaremos cuando el arbol este listo
};

class Utils{
public:
    Utils();
    float getRandom(int min, int max);
    int getUnitRandom(int min, int max);
    int abs(int num);
    int len(int num);
};

class JsonManager{
public:
    const string paisesPath = "paises.json"; // Este es el unico que se lee con readJsonArray (pais-ubicacion)
    const string apellidosPath = "apellidos.json";
    const string nombresPath = "nombres.json";
    const string profesionesPath = "profesiones.json";
    const string deportesPath = "deportes.json";
    const string creenciasPath = "creencias.json";

    JsonManager(){};

    void readJson(string path, QJsonObject * obj);
    void readJsonArray(string path, QJsonArray * objs);
    LinkedList<string> * getByString(string path);
    LinkedList<string> * getByString(string path, int n);

    LinkedList<Ubicacion *> * getPaises();
    LinkedList<Ubicacion *> * getPaises(int n);
};

class EmailSender{
    const string email = "prograthanos@gmail.com";
    const string password = "laprograthanos";
public:
    EmailSender(){}

    bool sendEmail(string name, string toName, string to, string subject, string body);
};

class Ubicacion{
public:
    string pais;
    string continente;

    Ubicacion(string _pais, string _continente);
};
