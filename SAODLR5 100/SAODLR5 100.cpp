#include <iostream>

using namespace std;

int gcount = 0;
const int n = 10;

int r(int min, int max)
{
    int num = min + rand() % (max - min + 1);
    return num;
}

void f1(int a, int* arr, const int n)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == a) {
            cout << "Элемент равный " << arr[i] << " находится на позиции " << i + 1 << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "Элемента с таким значением нет." << endl;
    }
}

void f2(int a, int* arr, const int n)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (i == a) {
            cout << "Элемент равный " << arr[i] << " находится на позиции " << i << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "Элемента с такой позицией нет." << endl;
    }
}

void sortch(int* arr, const int n)
{
    int i, j, k, count;
    count = 1;
    int* brr = new int[n];
    for (i = 0; i < n; i++) {
        k = 0;
        for (j = 0; j < n; j++) {
            if ((arr[j] < arr[i]) || ((arr[j] == arr[i]) && (j < i))) {
                k++;
                gcount++;
            }
        }
        brr[k] = arr[i];
    }
    for (i = 0; i < n; i++) {
        arr[i] = brr[i];
    }
    i = 1;
    while (i < n) {
        if (arr[i] == arr[i - 1]) {
            count++;
            i++;
            gcount++;
        }
        else {
            cout << arr[i - 1] << " встречается " << count << " раз ";
            count = 1;
            i++;
            gcount++;
        }
    }
    cout << arr[i - 1] << " встречается " << count << " раз";
}

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    int n, m, k, l, i, x;
    cout << "Введите количество элементов в массиве: ";
    cin >> n;
    int* a = new int[n];
    cout << "Введите элементы массива, начиная с первого: ";
    for (i = 0; i < n; i++) {
        cin >> x;
        a[i] = x;
    }

    cout << endl;
    cout << "Если хотите узнать позицию элемента по его значению, нажмите 1.\nЕсли хотите узнать номер элемента по позиции, нажмите 2.\nЕсли ничего не хотите, нажмите 0.\n";
    cin >> m;
    if ((m != 1) && (m != 2) && (m != 0)) {
        cout << "Error" << endl;
    }
    if (m == 1) {
        cin >> k;
        f1(k, a, n);
    }
    if (m == 2) {
        cin >> k;
        f2(k, a, n);
    }
    if (m == 0) {
        cout << "Thanks" << endl;
    }

    sortch(a, n);

    cout << endl;
    cout << "Если хотите добавить элемент, нажмите 1.\nЕсли удалить элемент, нажмите 2.\nЕсли ничего не хотите, нажмите 0.\n";
    cin >> m;
    if ((m != 1) && (m != 2) && (m != 0)) {
        cout << "Error" << endl;
    }
    if (m == 1) {
        n++;
        cout << "Введите значение элемента: " << endl;
        cin >> l;
            a[n - 1] = l;
            sortch(a, n);
    }
    if (m == 2) {
        cout << "Введите позицию элемента: " << endl;
        cin >> l;
        if (0 <= l < n) {
            for (i = l; i < n; i++) {
                a[i - 1] = a[i];
            }
            n--;
            sortch(a, n);
        }
        else {
            cout << "Не попадает в количество элементов!" << endl;
        }
    }
    if (m == 0) {
        cout << "Thanks" << endl;
    }

    cout << endl;
    cout << "Общее количество сравнений и перестановок, при осуществлении сортировки " << gcount << endl;

    return 0;
}