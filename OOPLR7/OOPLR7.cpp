#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>

using namespace std;

template <class Smth>
void show(Smth first, Smth last) {
    for (; first != last; ++first) {
        cout << *first << endl;
    }
}

class Smth {
public:
    vector<int> v;
    void f1(int n, int m1, int m2);
};

void Smth::f1(int n, int m1, int m2) {
    vector<int> v;

    v.resize(n);
    generate(v.begin(), v.end(), [&m1, &m2]() { return rand() % abs(m1 - m2 + 1) + m1; });
    show(v.begin(), v.end());
    cout << endl;
    cout << "Элемент с макс абс знач: " << *max_element(v.begin(), v.end(), [](int a, int b) { return abs(a) < abs(b); }) << endl;
    cout << endl;
    replace_if(v.begin(), v.end(), [](int a) { return a < 0; }, 0);
    show(v.begin(), v.end());
    cout << endl;
    set<int> uv(v.begin(), v.end());
    v = vector<int>(uv.begin(), uv.end());
    show(v.begin(), v.end());
}

int main()
{
    system("color F0");
    setlocale(0, "Rus");
    srand(time(0));

    int n, m1, m2;
    Smth a;
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите нижнюю границу диапазона чисел: ";
    cin >> m1;
    cout << "Введите нижнюю границу диапазона чисел: ";
    cin >> m2;
    cout << endl;
    a.f1(n, m1, m2);
    return 0;
}