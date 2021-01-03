#include <Model/thanos.h>
#include <Model/jsonmanager.h>

Mundo::Mundo(){
    JsonManager json;

    paises.resize(100);
    creencias.resize(10);
    profesiones.resize(50);

    loadData();
}

// Esta funcion se encarga de iniciar los datos...
// Si el mundo ya fue iniciado y se vuelve a llamar esta funcion
// borra TODOS los datos previamente cargados
void Mundo::reLoad(int _nombres, int _apellidos, int _creencias, int _profesiones, int _paises){
    paises.resize(_paises);
    creencias.resize(_creencias);
    profesiones.resize(_profesiones);

    loadData();
}

// Esta funcion carga los datos de los .json
void Mundo::loadData(){
    JsonManager json;

    paises = (json.getPaises(paises.size()))->toVector();
    creencias = (json.getByString(json.creenciasPath, creencias.size()))->toVector();
    profesiones = (json.getByString(json.profesionesPath, profesiones.size()))->toVector();
}
