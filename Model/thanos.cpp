#ifndef COMMONS
#define COMMONS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <random>

using namespace std;
#endif

/*
    Aqui vamos a declarar las clases y estructuras que se van a utilizar en toda la progra
*/

template <typename Data> struct CircularList;
template <typename Data> struct LinkedList;
template <typename Data> struct Node;
template <typename Data> struct Queue;

class Mundo;
class Persona;
class Acciones;
template <typename Data> class Accion;
class Familia;
class Ubicacion;
class RangoEtario;
class Ejercicio;
class Utils;

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
