#include <iostream>
#include <math.h>

using namespace std;

class praymoyg
{
private:
    int a;
public:
    int x1, x2, x3, x4, y1, y2, y3, y4, n, P;
    praymoyg operator*(praymoyg t);
    praymoyg operator|(praymoyg t);//первый периметр
    praymoyg operator==(praymoyg t);//второй периметр
    praymoyg operator/(praymoyg t);//сравнение периметров
    praymoyg operator+(praymoyg t);
    friend int operator-(praymoyg t, int a);
    void show();
    void showP();
    void assign();
    praymoyg () {}
    praymoyg (int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, int n, int P) {
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
        this->x4 = x4;
        this->y1 = y1;
        this->y2 = y2;
        this->y3 = y3;
        this->y4 = y4;
        this->n = n;
        this->P = P;
    }
    ~praymoyg() {}
};

praymoyg praymoyg:: operator*(praymoyg t)
{
    praymoyg yvel;
    yvel.x1 = x1 * n;
    yvel.x2 = x2 * n;
    yvel.x3 = x3 * n;
    yvel.x4 = x4 * n;
    yvel.y1 = y1 * n;
    yvel.y2 = y2 * n;
    yvel.y3 = y3 * n;
    yvel.y4 = y4 * n;
    return yvel;
}
praymoyg praymoyg:: operator+(praymoyg t)
{
    praymoyg yvel;
    yvel.x1 = x1 + t.x1;
    yvel.x2 = x2 + t.x2;
    yvel.x3 = x3 + t.x3;
    yvel.x4 = x4 + t.x4;
    yvel.y1 = y1 + t.y1;
    yvel.y2 = y2 + t.y2;
    yvel.y3 = y3 + t.y3;
    yvel.y4 = y4 + t.y4;
    return yvel;
}
praymoyg praymoyg:: operator|(praymoyg t)
{
    praymoyg vivel;
    vivel.P = (abs(x4) - abs(x1) + abs(y2) - abs(y1)) * 2;
    return vivel;
}
praymoyg praymoyg::operator==(praymoyg t)
{
    praymoyg yvel;
    yvel.P = (abs(t.x4) - abs(t.x1) + abs(t.y2) - abs(t.y1)) * 2;
    return yvel;
}
praymoyg praymoyg::operator/(praymoyg t)//если равны, то выводит первый, если нет, то второй 
{
    praymoyg yvel, vivel;
    vivel.P = (abs(x4) - abs(x1) + abs(y2) - abs(y1)) * 2;
    yvel.P = (abs(t.x4) - abs(t.x1) + abs(t.y2) - abs(t.y1)) * 2;
    if (vivel.P == yvel.P) {
        return yvel;
    }
    else {
        return vivel;
    }
}
void praymoyg::show()
{
    cout << "x1= " << x1 << endl << "y1= " << y1 << endl << "x2= " << x2 << endl << "y2= " << y2 << endl << "x3= " << x3 << endl << "y3= " << y3 << endl << "x4= " << x4 << endl << "y4= " << y4 << endl << endl;
}
void praymoyg::showP()
{
    cout << "P = " << P << endl ;
}
void praymoyg::assign()
{
        cout << "Введите координаты: " << endl;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        cout << "Введите коэффициент n: " << endl;
        cin >> n;
        cout << endl;
}
int operator-(praymoyg t, int a)
{
    praymoyg yvel;
    yvel.P += a;
    return a;
}

int main()
{
    system("color F0");
    setlocale(0, "Rus");
    praymoyg a, b, c;
    int k = 1;
    int P;
    a.assign();
    b.assign();
    c = a;
    c = a * b;
    c.show();
    c = b * a;
    c.show();
    c = a + b;
    c.show();
    c = a | b;
    c.showP();
    c = a == b;
    c.showP();
    c = a / b;
    c.showP();
    P = a - k;
    cout << P << endl;
    return 0;
}