#include <iostream>

using namespace std;

const int n = 10;

int r(int min, int max)
{
	int num = min + rand() % (max - min + 1);
	return num;
}

void f1(int a[n])
{
	for (int i = 0; i < n; i++) {
		if (a[i] % 2 == 0) {
			a[i] = a[i] / 2;
		}
	}
}

int f2(int count)
{
	return count;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int count, m, n;
	count = 0;
	cout << "Введите количество элементов массива ";
	cin >> n;
	int *a = new int [n];
	cout << "Исходный массив: " << endl;
	for (int i = 0; i < n; i++) {
		a[i] = r(-((n / 2) - 1), (n / 2));
		if (a[i] < 0) {
			count++;
		}
		cout << a[i] << endl;
	}
	cout << "Если хотите все четные значения элементов уменьшить в два раза, то нажмите 1. \nЕсли хотите подсчитать количество элементов с отрицательными значениями, то нажмите 2. \nЕсли ничего не хотите, нажмите 0." << endl;
	cin >> m;
	cout << endl;
	if ((m != 1) && (m != 2) && (m != 0)) {
		cout << "Error" << endl;
	}
	if (m == 1) {
		f1(a);
		for (int i = 0; i < n; i++) {
			cout << a[i] << endl;
		}
	}
	if (m == 2) {
		cout << f2(count) << endl;
	}
	if (m == 0) {
		cout << "Thanks" << endl;
	}

	return 0;
}
