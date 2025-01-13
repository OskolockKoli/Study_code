#include <iostream>
#include <exception>
#include <math.h>

#define n 5 //13

using namespace std;

void err1(int*, int);
void err2(int*, int);

int sum(int* arr, int all) {
    int s, i;
    s = 0;
    for (i = 0; i < all; i++) {
        if (arr[i] > 0) {
            s += arr[i];
        }
    }
    return s;
}

int f1(int* arr, int all) {
    int p, i, min, max, mini, maxi;
    mini = 0;
    maxi = 0;
    p = 1;
    min = 100000;
    max = 0;
    for (i = 0; i < all; i++) {
        if (abs(arr[i]) < abs(min)) {
            min = arr[i];
            mini = i;
        }
        if (abs(arr[i]) > abs(max)) {
            max = arr[i];
            maxi = i;
        }
    }
    if ((maxi == mini) || (maxi == mini - 1) || (mini == maxi - 1)) {
        p = 0;
        return p;
    }
    if (mini < maxi) {
        for (i = mini + 1; i < maxi; i++) {
            p *= arr[i];
        }
        return p;
    }
    if (maxi < mini) {
        for (i = maxi + 1; i < mini; i++) {
            p *= arr[i];
        }
        return p;
    }
}

void f2(int* arr, int all) {
    int i, j, temp;
    for (i = 0; i < all; i++) {
        for (j = 0; j < all - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < all; i++) {
        cout << arr[i] << endl;
    }
}

int main()
{
    system("color F0");
    setlocale(0, "Rus");

    int i;
    int* a = new int[n];
    cout << "Введите элементы массива с первого: " << endl;
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }
    try {
        err1(a, n);
    }
    catch (const exception& err1) {
        cout << endl;
        cout << "Ошибка, нет отрицательных чисел!" << endl;
        cout << endl;
    }
    try {
        err2(a, n);
    }
    catch (const exception& err1) {
        cout << endl;
        cout << "Ошибка, нет нулей!" << endl;
        cout << endl;
    }
    cout << "Сумма положительных элементов массива: ";
    cout << sum(a, n) << endl;
    cout << "Произведение элементов массива, расположенных между максимальным по модулю и минимальным по модулю элементами: ";
    cout << f1(a, n) << endl;
    cout << "Упорядоченный массив: " << endl;
    f2(a, n);
    return 0;
}

void err1(int* arr, int all)
{
    int i, count;
    count = 0;
    for (i = 0; i < all; i++) {
        if (arr[i] < 0) {
            count++;
        }
    }
    if (count == 0) {
        throw exception();
    }
}

void err2(int* arr, int all)
{
    int i, count;
    count = 0;
    for (i = 0; i < all; i++) {
        if (arr[i] == 0) {
            count++;
        }
    }
    if (count == 0) {
        throw exception();
    }
}
