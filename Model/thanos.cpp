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
#include <time.h>

using namespace std;

#include <Model/dataStructures/datastructures.h>

#endif

/////////////////////////Enums////////////////////////////////////

enum Pecados{
    Lujuria,
    Gula,
    Avaricia,
    Pereza,
    Ira,
    Envidia,
    Soberbia
};

enum Virtudes{
    Castidad,
    Ayuno,
    Donacion,
    Diligencia,
    Calma,
    Solidaridad,
    Humildad
};

enum RangosEtarios{
    infantil = 0,
    preescolar,
    escolar,
    pubertad,
    adolescencia,
    joven,
    adultoJoven,
    adultoMaduro,
    adultoMayor
};

enum eGenero{
    hombre,
    mujer,
};

enum eEstadoMarital{
    soltero,
    casado,
    divorciado,
};

/*
    Constantes
*/
const string APP_FILES_DIR = QDir::homePath().toStdString() + "/documents/thanos/";
const string APP_LOGS_DIR = QDir::homePath().toStdString() + "/documents/thanos/logs/";

/*
    Aqui vamos a declarar las clases y estructuras que se van a utilizar en toda la progra
*/
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

/*
    Nota: Traten de definir sus clases aqui... esto para evitar problemas de importacion y declaracion
          Con definir me refiero a solo las variables y funciones que tienen... el codigo y la logica
          cada una de las clases va a tener su propio archivo.
*/


class Persona{
public:
    int ID;
    int puntosThanos;

    string apellido;
    string nombre;
    string creencia;
    string profesion;
    string * experiencias;

    eGenero genero;
    eEstadoMarital estado;
    Acciones * acciones;
    Ejercicio * deporte;
    Familia * familia;
    RangoEtario * edad;
    Ubicacion * ubicacion;
    vector<Ubicacion *> turismo;
    LinkedList<Persona *> * amigos;
    LinkedList<string> * killLog;
    LinkedList<string> * savedLog;
    bool isAlive;

    void generarPecados();
    void generarBuenasAcciones();
    Persona(int _ID, eGenero _genero, string _nombre, string _apellido, string _creencia, string _profesion, Ubicacion * ub);
    bool amigosComun(Persona * persona);

    void generarAmigos(vector<Persona *> vPersonas);
    void generarAcciones();
    void generarEstado();

    int getID();
    int getPoints();
    static int getID(Persona * persona);
    static int getPoints(Persona * persona);
};

class Mundo{
public:
    Tree * arbol;
    LinkedList<Persona *> * personas;
    // Estos son los arreglos de datos que se van a cargar
    vector<string> nombresMasc;
    vector<string> nombresFem;
    vector<string> apellidos;
    vector<string> creencias;
    vector<string> profesiones;
    vector<string> deportes;
    vector<Ubicacion *> paises;
    vector<int> selectedIDs;

    Mundo();

    void reLoad(int _nombres, int _apellidos, int _creencias, int _profesiones, int _paises, int _deportes);
    void loadData();
    void generateHumans(int amount);
    Persona * generateHuman(int ID);
    void generateTree();
    void printHumans();
    void generateFriends();
    void generateFamilies();

    // Consultas al mundo
    Persona * getById(int ID);
    vector<Persona *> getFamilyById(int ID);
    vector<Persona *> getFriendsById(int ID);
    vector<Persona *> getBySport(string sport);

    int getAlivePeople();
    int getDeathPeople();
    int getSavedPeople();

    Hashmap<int, LinkedList<Persona *> *> * getByYears();
};

class Utils{
public:
    Utils();
    static float getRandom(int min, int max);
    static int getUnitRandom(int min, int max);
    static int abs(int num);
    static int len(int num);
    static string getDate();
};

class Ubicacion{
public:
    string continente;
    string pais;
    Ubicacion();
    Ubicacion(string _pais, string _continente);
};

class Ejercicio{
public:
    vector<string> vDeportes;
    Hashmap<string, bool> * deportes;
    int cantidad;

    Ejercicio();
    void generarDeportes(vector<string> deportes);
};

class JsonManager{

public:
    const string paisesPath = "paises.json"; // Este es el unico que se lee con readJsonArray (pais-ubicacion)
    const string apellidosPath = "apellidos.json";
    const string nombresMascPath = "nombres_h.json";
    const string nombresFemPath = "nombres_m.json";
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
    LinkedList<string> * getNames(eGenero genero);
    LinkedList<string> * getNames(eGenero genero, int n);
};

class FileManager{
public:
    static string logFile;
    static string avengersFile;
    static string enemiesFile;

    static string readFile(string path);
    static bool saveFile(string data, string path);
    static bool appendFile(string data, string path);
};

class EmailSender{
    const string email = "prograthanos@gmail.com";
    const string password = "laprograthanos";
public:
    EmailSender(){}

    bool sendEmail(string name, string toName, string to, string subject, string body);
};

class Acciones{
private:
    Hashmap<Pecados, int > *listaPecados;
    Hashmap<Virtudes, int > *listaVirtudes;
public:
    Acciones();
    //Estas funciones le suman un int a los pecados que ya tenian
    void agregarPecados(int num, Pecados sin);
    void agregarBuenasAcciones(int num, Virtudes virtue);
    //Estas en vez de sumar definen la cantidad de una vez
    void setPecado(int num, Pecados sin);
    void setVirtud(int num, Virtudes virtue);

    int cantidadPecados();
    int cantidadVirtudes();
};


class RangoEtario{
public:
    RangosEtarios rango;
    int edad;
    int fechaDeNacimiento[3];
    int seleccionarRangoViajes();
    string rango_etario;

    RangoEtario(){};
    bool isLeap(int num);    
    void generarFecha();
    void asignarRango();

    static bool esMenor(RangosEtarios rango);
    static bool puedeSerHijo(RangosEtarios padre, RangosEtarios hijo);
};

class Familia{
public:
    Persona * persona;
    Persona * conyugue;
    Persona * padre;
    LinkedList<Persona*> * hijos;

    Familia(Persona * _persona);
    void generarConyugue(vector<Persona *> personas);
    void generarHijos(vector<Persona *> personas);
    static bool estaEnSusHijos(int ID, Persona * persona);
    static Persona * obtenerRaizFamiliar(Persona * persona);
};


struct Tree{
    TreeNode * raiz;
    static Hashmap<int, Persona*> * cache;

    Tree();
    Tree(Node<Persona *> * persona);

    // Funciones
    static int nodosNecesarios(int cant);
    static Tree * generateTree(LinkedList<Node<Persona *>*> * list);
    static void generateHashmap(LinkedList<Node<Persona *>*> * list, Hashmap<int, LinkedList<Node<Persona *>*> *> * hashmap, int level);

    int cantidadNodos();
    int cantidadNodos(TreeNode * tmp);
    Hashmap<int, LinkedList<Persona *> *> * niveles();Persona * obtenerAux(int indice, TreeNode * tmp);

    void niveles(Hashmap<int, LinkedList<Persona *> *> * hashmap, TreeNode * tmp, int level);
    void insertar(Node<Persona *> * persona, TreeNode * * tmp);
    void insertar(Node<Persona *> * persona);

    Persona * busquedaIterativa(int indice, TreeNode * tmp, bool isRight);
    Persona * obtener(int indice);
    Persona * obtenerRandom();
    Persona * obtenerRandomAux(TreeNode * tmp);
    Persona * busquedaRandIterativa(TreeNode * tmp, bool isRight);
};

class PaisesVisitados{
public:
    static int seleccionarRangoViajes();
    static void seleccionarPaisesRandom();
    static vector<Ubicacion *> generarPaises(vector<Ubicacion *> paises);
};

class Nebula{
private:
    Mundo * mundo;
public:
    static string filename;

    Nebula(Mundo * _mundo);

    void kill();
    int killAux(Persona * tmp);
};

class Ebony{
private:
    Mundo * mundo;
public:
    Ebony(Mundo * _mundo);

    void kill(int ID);
    int killAux(Persona * tmp, string * log);
};

class BlackDwarf{
private:
    Mundo * mundo;
public:
    BlackDwarf(Mundo * mundo);

    void kill(string deporte);
};

class hashthanos{
private:
    Mundo * mundo;
    Hashmap<int, LinkedList<Persona *> *> * thanos;
public:
    hashthanos(Mundo * _mundo);

    void generateHashtable();
    LinkedList<Persona *> * generateByYear(vector<Persona *> _personas);

    void killByYear(int year);
    void killByLevel(int level);
    void killByLevelAndYear(int year, int level);
};

class Thor{
private:
    Mundo * mundo;
public:
    Thor(Mundo * _mundo);

    void save(int level);
};

class Antman{
private:
    Mundo * mundo;
public:
    Antman(Mundo * _mundo);

    void save(int amount);

    void saveAux(TreeNode * tmp, LinkedList<Node<Persona *> *> * recorrido);
};

class IronMan{
private:
    Mundo * mundo;
public:
    IronMan(Mundo * _mundo);

    void save();
    void saveAux(TreeNode * tmp);
    void saveFamilies(Persona * persona);
};


class SpiderMan{
private:
    Mundo * mundo;
public:

    SpiderMan(Mundo * _mundo);

    void save();
    void saveAux(TreeNode * tmp, LinkedList<Persona *> * recorrido);
    void saveLeafs(Node<Persona *> * tmp, int amount);
};
