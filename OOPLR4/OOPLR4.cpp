#include <iostream>
#include <math.h>

using namespace std;

class Points
{
public:
    double x1, x2, x3, x4, y1, y2, y3, y4, S, a, b;
    void show();
    void assign();
    Points() {}
    Points(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4, double S, double a, double b) {
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
        this->x4 = x4;
        this->y1 = y1;
        this->y2 = y2;
        this->y3 = y3;
        this->y4 = y4;
        this->S = S;
        this->a = b;
        this->a = b;
    }
    ~Points() {}
};

void Points::show()
{
    cout << "x1= " << x1 << endl << "y1= " << y1 << endl << "x2= " << x2 << endl << "y2= " << y2 << endl << "x3= " << x3 << endl << "y3= " << y3 << endl << "x4= " << x4 << endl << "y4= " << y4 << endl << endl;
}
void Points::assign()
{
    cout << "Введите координаты: " << endl;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    cout << endl;
}

class Quadrilateral : public Points {
public:
    Quadrilateral operator/(Points t) {
        Quadrilateral vivel;
        vivel.S = sqrt((x1 - x2) * (x1 - x2) + (y1 - y3) * (y1 - y3));
        vivel.a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        vivel.b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
        if ((vivel.S != vivel.a) && (vivel.S != vivel.b)) {
            return vivel;
        }
        else {
            cout << "Неправильный четырёхугольник!" << endl;
            return vivel;
        }
    }
    Quadrilateral operator*(Points t) {
        Quadrilateral vivel;
        vivel.S = sqrt((x3 - x4) * (x3 - x4) + (y1 - y4) * (y1 - y4));
        vivel.a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        vivel.b = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
        if ((vivel.S != vivel.a) && (vivel.S != vivel.b)) {
            return vivel;
        }
        else {
            cout << "Неправильный четырёхугольник!" << endl;
            return vivel;
        }
    }
    /*Quadrilateral operator+(Points t) {
        Quadrilateral vivel;
        vivel.S = (abs((x1 - x2)*(y1 + y2) + (x2 - x3)*(y2 + y3) + (x3 - x4)*(y3+y4) + (x4 - x1)*(y4 + y1))) / 2;
        return vivel;
    }*/
    void showS()
    {
        cout << S << endl;
    }
};

int main()
{
    system("color F0");
    setlocale(0, "Rus");
    Quadrilateral a, b, c;
    a.assign();
    b.assign();
    c = a / b;
    cout << "Первая диагональ первого четырёхугольника: ";
    c.showS();
    cout << endl;
    c = a * b;
    cout << "Второая диагональ первого четырёхугольника: ";
    c.showS();
    cout << endl;
    c = b / a;
    cout << "Первая диагональ второго четырёхугольника: ";
    c.showS();
    cout << endl;
    c = b * a;
    cout << "Второая диагональ второго четырёхугольника: ";
    c.showS();
    cout << endl;
    return 0;
}