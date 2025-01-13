#include <iostream>
#include <math.h>

using namespace std;

class Smth {
private:
    double a, b, c;
public:
    Smth() {
        a = 0;
        b = 0;
        c = 0;
    }
    Smth(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    Smth(const Smth& other) {
        a = other.a;
        b = other.c;
        c = other.c;
    }
    double Angles(Smth x)
    {
        double r;
        const double pi = acos(-1.0);
        double y;
        y = ((x.b * x.b + x.c * x.c) - x.a * x.a) / (2 * x.c * x.b);
        r = acos(y) * 180 / pi;
        return r;
    }
    ~Smth() {}
};

int main()
{
    system("color F0");
    setlocale(LC_ALL, "Rus");
    double a, b, c;
    Smth B;
    cin >> a;
    cin >> b;
    cin >> c;
    if ((a > 0) && (b > 0) && (c > 0)) {
        Smth A(a, b, c);
        cout << A.Angles(A) << endl;
        Smth B(b, a, c);
        cout << A.Angles(B) << endl;
        Smth C(c, b, a);
        cout << A.Angles(C) << endl;
    }
    else {
        cout << "Error!" << endl;
    }
    Smth C = B;
    return 0;
}
