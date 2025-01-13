#include <iostream>

using namespace std;

int r() {
    int num = rand() % (2);
    return num;
}

void generatem(int* arr[], int n) {
    int i, j, k;
    k = 0;
    for (i = k; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                arr[i][j] = 0;
            }
            else {
                arr[i][j] = r();
                arr[j][i] = arr[i][j];
            }
        }
        k++;
    }
}

void MS(int* arr[], int n) {
    int i, j;
    cout << "Матрица смежности:" << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int f1(int* arr[], int n) {
    int i, j, count;
    count = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (arr[i][j] == 1) {
                count++;
            }
        }
    }
    cout << endl << "Количество рёбер: " << count / 2 << endl;
    return count / 2;
}

void MI(int* arr[], int* brr[], int row, int col) {
    int i, j, k;
    k = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            brr[i][j] = 0;
        }
    }
    cout << "Матрица инциндентности:" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = i + 1; j < row; j++) {
            if (arr[i][j] == 1) {
                brr[i][k] = 1;
                brr[j][k++] = 1;
            }
        }
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            cout << brr[i][j] << " ";
        }
        cout << endl;
    }
}

void MF(int* arr[], int n) {
    int i, j, k, p;
    int* a = new int[n];
    for (i = 0; i < n; i++) {
        a[i] = 1;
    }
    int* b = new int[n];
    for (i = 0; i < n; i++) {
        b[i] = 0;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a[i] = arr[i][j];
            if (i == j) {
                a[i] = 2;
            }
            p = j;
            k = i;
            //cout << a[i] << " " << p << endl;
            if (a[i] == 0) {
                for (int i = 0; i < n; i++) {
                    b[i] = arr[p][i];
                    //cout << b[i];
                }
                for (int i = 0; i < n; i++) {
                    for (int i = 0; i < n; i++) {
                        a[i] = arr[k][i];
                        //cout << a[i];
                    }
                    if ((a[i] == 1) && (b[i] == 1)) {
                        arr[p][k] = 1;
                        arr[k][p] = 1;
                        //cout << "!";
                    }
                    else {
                        //cout << "#";
                    }
                }
            }
        }
    }
    cout << "Конечная матрица: " << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int rez(int* arr[], int n) {
    int i, j, count;
    count = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (arr[i][j] == 0) {
                count++;
            }
        }
    }
    if (count == n) {
        return 1;
    }
    else {
        return 0;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int n, i, j, m, flag, k;
    flag = 0;
    cout << "Введите количество людей: " << endl;
    cin >> n;
    cout << endl;
    int** a = new int* [n];
    for (i = 0; i < n; ++i) {
        a[i] = new int[n];
    }
    //generatem(a, n);
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            if (i == j) {
                a[i][j] = 0;
            }
            else {
                cout << "Элемент на позиции [" << i << "] [" << j << "] равен ";
                cin >> a[i][j];
                a[j][i] = a[i][j];
            }
        }
    }
    MS(a, n);
    m = f1(a, n);
    int** b = new int* [n];
    for (i = 0; i < n; ++i) {
        b[i] = new int[m];
    }
    cout << endl;
    //MI(a, b, n, m);
    //cout << endl;
    MF(a, n);
    f1(a, n);
    cout << endl;
    k = rez(a, n);
    if (k == 1) {
        cout << "Всех перезнакомить получилось!" << endl;
    }
    else {
        MF(a, n);
        f1(a, n);
        if (k == 1) {
            cout << "Всех перезнакомить получилось!" << endl;
        }
        else {
            cout << "Всех перезнакомить не получилось!" << endl;
        }
    }
    return 0;
}