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

template <typename Data> 
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
};

class Mundo;
class Persona;
class Acciones;
class Familia;
class Ubicacion;
class RangoEtario;
class Ejercicio;
class Utils;
class JsonManager;


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
    // Ubicacion * ubicacion;
    // Ejercicio * salud;
    // Familia * familia;
    // eEstadoMarital estado;
    // RangoEtario * edad;
    // Acciones * acciones;
    // eGenero genero;

    void generarPecados();
    void generarBuenasAcciones();

public:
    Persona();

    void generarAmigos(CircularList<Persona *> personas);
    void generarAcciones();
};

class Mundo{
private:
    CircularList<Persona *> * personas;
    // Arbol

    // Estos son los arreglos de datos que se van a cargar
    string * apellidos;
    string * nombres;
    string * paises;
    string * creencias;
    string * profesiones;

public:
    Mundo();
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
    LinkedList<string> * getPaises();
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

///////////////////////////Clases///////////////////
class Acciones{
private:
    enum Pecados pecados;
    enum Virtudes virtudes;    
    LinkedList<Accion<Pecados*> > *listaPecados;
    LinkedList<Accion<Virtudes*> > *listaVirtudes;
    
public:
    //Preguntar si ya con hacerlo asi quedan hechas las listas.
    void agregarPecados(int num, string sin);
    void agregarBuenasAcciones(int num, string virtue);
    void inicializar();
};


class RangoEtario{
public:
    enum RangosEtarios rango;
    int  edad;
    int fechaDeNacimiento[3];
    int seleccionarRangoViajes();
    string rango_etario;

    bool isLeap(int num);    
    void generarFecha();
    void asignarRango();


    
};
///////////////////////////////////////////////////
