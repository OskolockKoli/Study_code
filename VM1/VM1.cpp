#include <iostream>
#include <cmath>
#include <conio.h>

using namespace std;

double f(double a, double b, double c, double x) {
    return tan(a * x + b) + c * pow(x, 2);
}

double fp(double a, double b, double c, double x) {
    return (a / (pow(cos(a * x + b), 2))) - 2*x;
}

int main()
{
    double a, b, c, x0, x1, e, count, temp, xmin, xmax;
    //a = 3.01;
    //b = 4;
    //c = -1;
    //e = 0.001;
    count = 1;

    cout << "PR1 Bobrovich 4136" << endl;
    cout << "3 var:\ntg(ax+b)+cx2=0\nNewton's method\na = 3.01; b = 4; c = -1; e = 0.001\n" << endl;
    cout << endl;
    cout << "Press any key to continue." << endl;
    _getch();
    system("cls");

    cout << "Please, enter a: ";
    cin >> a;
    cout << "Please, enter b: ";
    cin >> b;
    cout << "Please, enter c: ";
    cin >> c;
    cout << "Please, enter e: ";
    cin >> e;

    cout << "Please, enter lower bound: ";
    cin >> xmin;
    cout << "Please, enter upper bound: ";
    cin >> xmax;

    x0 = (xmin + xmax) / 2;

    cout << "Step number: " << count << endl;
    count++;
    cout << "X: " << x0 << endl;
    cout << endl;

    while (fabs(f(a, b, c, x0)) > e) {
        temp = ((-1) * f(a, b, c, x0)) / fp(a, b, c, x0);
        x1 = temp + x0;
        if (f(a, b, c, x1) == 0) {
            break;
        }
        x0 = x1;
        cout << "Step number: " << count << endl;
        count++;
        cout << "f(X): " << f(a, b, c, x0) << endl;
        cout << "X: " << x0 << endl;
        cout << endl;
    }
    if ((f(a, b, c, x0) < 0.001) && (f(a, b, c, x0) > -0.001)) {
        cout << "Verification passed!" << endl;
    }
    cout << "Thank you for using this beautifull thing!" << endl;
    return 0;
}