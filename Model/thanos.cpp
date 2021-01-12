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
#include <Model/genero.h>

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


/*template <typename Data>
class Accion{
private:
    Data data;
    int cant;
public:
    Accion(Data _data){
        data = _data;
        cant = 0;        
    }
    Accion(){
        data = NULL;
        cant = 0;
    }
    void setCantidad(int _cant){
        cant = _cant;
    }
    void setData(Data _data){
        data = _data;
    }
};*/

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
class PaisesVisitados;

class EmailSender;
template <typename Data> class Accion;

/*
    Nota: Traten de definir sus clases aqui... esto para evitar problemas de importacion y declaracion
          Con definir me refiero a solo las variables y funciones que tienen... el codigo y la logica
          cada una de las clases va a tener su propio archivo.
*/


class Persona{
public:
    int ID;
    string apellido;
    string nombre;
    string creencia;
    string profesion;
    string * experiencias;
    LinkedList<Persona *> * amigos;
    Ubicacion * ubicacion;
    // Ejercicio * salud;
    // Familia * familia;
    // eEstadoMarital estado;
    // RangoEtario * edad;
    // Acciones * acciones;
    eGenero genero;

    void generarPecados();
    void generarBuenasAcciones();
    Persona(int _ID, eGenero _genero, string nombre);

    void generarAmigos(LinkedList<Persona *> * personas);
    void generarAcciones();

    int getID();
    static int getID(Persona * persona);
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
    vector<Ubicacion *> paises;
    vector<int> selectedIDs;

    Mundo();

    void reLoad(int _nombres, int _apellidos, int _creencias, int _profesiones, int _paises);
    void loadData();
    void generateHumans(int amount);
    Persona * generateHuman(int ID);
    void generateTree();
    void printHumans();
    // El resto de funcionas las generaremos cuando el arbol este listo
};

class Utils{
public:
    Utils();
    static float getRandom(int min, int max);
    static int getUnitRandom(int min, int max);
    static int abs(int num);
    static int len(int num);
};

class Ubicacion{
private:
    string * continente;
    string * pais;
public:
    Ubicacion();
    Ubicacion(string _pais, string _continente);
};

class Ejercicio{
private:
    int cantidad;
    LinkedList<string*> *deportes;
public:
    Ejercicio();
};

class Familia{
private:
    Persona conyugue;
    LinkedList<Persona*> *hijos;
public:
    Familia();
    void generarConyugue();
    void generarHijos();
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

class EmailSender{
    const string email = "prograthanos@gmail.com";
    const string password = "laprograthanos";
public:
    EmailSender(){}

    bool sendEmail(string name, string toName, string to, string subject, string body);
};

//////////////////////////Codigo de Maximo/////////////////////////
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
    infantil ,
    preescolar,
    escolar,
    pubertad,
    adolescencia,
    joven,
    adultoJoven,
    adultoMaduro,
    adultoMayor
};

/////////////Clases////////
class Acciones{
private:   
    Hashmap<string ,int > *listaPecados;
    Hashmap<string,int > *listaVirtudes;
public:
    Acciones();
    //Estas funciones le suman un int a los pecados que ya tenian
    void agregarPecados(int num, string sin);
    void agregarBuenasAcciones(int num, string virtue);
    //Estas en vez de sumar definen la cantidad de una vez
    void setPecado(int num, string sin);
    void setVirtud(int num, string virtue);
};


class RangoEtario{
public:
    enum RangosEtarios rango;
    int  edad;    
    string rango_etario;

    //fechaDeNacimiento es un array en donde
    //[0] = dia
    //[1] = mes
    //[2] = año
    int fechaDeNacimiento[3];

    bool isLeap(int num);    
    void generarFecha();
    void setEdad(int num);
    void asignarRango();

    //  Nota.
    //  Esta funcion se encargara de cambiar la edad en caso de que se quiera una etapa especifica al formar la familia
    //  Las etapas son: bisabuelo, abuelo, padre, hijo

    void setEdadEtapa(string etapa);

};

class PaisesVisitados{
private:
    LinkedList<Ubicacion *> * listaPaisesVisitados;
    //string listaPaisesVisitados[50];
public:
    int seleccionarRangoViajes();
    void seleccionarPaisesRandom();
    void generarPaises();

};



