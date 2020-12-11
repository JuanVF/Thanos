#include <Model/thanos.h>

Utils::Utils(){}

// Retorna el valor absoluto de un numero
int Utils::abs(int num){
    return (num >= 0) ? num : num * -1;
}

// Retorna la cantidad de digitos de un numero
int Utils::len(int num){
    int quantity = 1;

    num = abs(num);

    while (num / 10 > 0){
        num = num / 10;

        quantity++;
    }

    return quantity;
}

// Genera un numero aleatorio entre min y max
// sin embargo, solo genera un digito
// min y max deben estar entre 0 y 9
int Utils::getUnitRandom(int min, int max){
    min = abs(min);
    max = abs(max);

    // Evitamos que entren numeros mayores a 9
    min = (min > 9) ? min % 10 : min;
    max = (max > 9) ? max % 10 : max;

    if (min == max) return max;

    int unit = 0;

    int i = 0;

    // Generamos la semilla
    srand(time(0) * 7 + rand());

    do{
        int random = (int) (rand() / pow(10, rand() % 1000)) % 10;

        unit = rand() % 10;

        if (i >= 7){
            srand(time(0) * 8 + rand());
            i = 0;
        }

        i++;
    } while(unit < min || max < unit);

    return unit;
}

// Genera un random entre min y max
// si min > max o viceversa se ajustan
float Utils::getRandom(int min, int max){
    float rst = 0;

    // Evitamos que el minimo sea mayor al maximo
    min = (min > max) ? max : min;

    // Generamos numeros aleatorios menores a la base del max
    int a = min % 10, b = max % 10;

    int length = len(max);
    int minB = min, maxB = max;

    for (int i = 0; i < length - 1; i++){
        a = minB % 10;
        b = maxB % 10;

        rst += getUnitRandom(0, 9) * pow(10, i);

        minB = minB / 10;
        maxB = maxB / 10;
    }

    a = minB % 10;
    b = maxB % 10;

    rst += pow(10, length - 1) * getUnitRandom(a, b);

    rst = (rst < min) ? min : rst;
    rst = (rst > max) ? max : rst;

    return rst;
}
