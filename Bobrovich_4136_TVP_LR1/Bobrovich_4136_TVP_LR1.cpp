#include <iostream>

using namespace std;

// Итеративная функция
int f1(int x) {
    return 2 * x;
}

//Рекурсивная функция
double f2(int x) {
    if (x == 0) {
        return 0; //нулевая функция
    }
    return 2 + f2(x - 1); //функция следования
}

int main() {
    int x = 4;
    cout << "f(" << x << ") = \n" << "Iterative method: " << f1(x) << "\nRecursive method: " << f2(x) << endl;
    return 0;
}
