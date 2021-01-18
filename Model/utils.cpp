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
        int random = (int) (rand() / pow(10, 2)) % 10;

        unit = random % 10;

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
    if (min > max){
        int tmp = max;
        max = min;
        min = tmp;
    }

    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed1 * getUnitRandom(1, 9) * 7); // seed the generator
    uniform_int_distribution<> distr(min, max); // define the range

    int rst = (int) distr(gen);

    return rst;
}

string Utils::getDate(){
    return to_string(time(0));
}
