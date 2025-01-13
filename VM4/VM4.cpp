#include <iostream>
#include <cmath>

using namespace std;

double f(double x)
{
    return (tan(pow (x, 2)))/(x + 1);
}

int main()
{
    double a, b, h;
    int n;
    double INTGRL = 0.0;

    cout << "Vvedite a= ";
    cin >> a;

    cout << "Vvedite b= ";
    cin >> b;

    cout << "Vvedite n= ";
    cin >> n;

    h = ((b - a) / n);

    for (double x = a; x < b; x += h)
        INTGRL += f(x + h / 2);
    INTGRL *= h;

    cout << "Shag = " << h << endl;
    cout << endl;
    cout << "S = " << INTGRL;
    return 0;
}
