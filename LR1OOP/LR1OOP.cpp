#include <iostream>

using namespace std;

class gp {
private:
    double r;
    //int z;
public:
    void Elementi(double x, double y, int z)
    {
        r = x * pow(y, z);
    }
    int print()
    {
        return r;
    }
};

int main()
{
    system("color F0");
    setlocale(LC_ALL, "Rus");
    gp smth;
    double a, q;
    int n;
    cout << "Введите первый элемент геометрической прогрессии: ";
    cin >> a;
    cout << "Введите коэффициент геометрической прогрессии: ";
    cin >> q;
    cout << "Введите номер элемента геометрической прогрессии: ";
    cin >> n;
    smth.Elementi(a, q, n);
    cout << "a = " << smth.print();
    return 0;
}