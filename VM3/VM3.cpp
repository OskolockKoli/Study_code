#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

class newton
{
    double* x;
    double* y;
    int n;

public:
    newton()
    {
        cout << "\nCreating an object...\n\n";

        cout << "Number of dots: ";
        for (;;)
        {
            cin >> n;
            if (n < 1)
                cout << "N must be more than 1, enter it again: ";
            else break;
        }
        cout << endl;

        x = new double[n];
        y = new double[n];

        for (int i = 0; i < n; i++)
        {
            cout << "X[" << i + 1 << "]=";
            cin >> x[i];
            cout << "Y[" << i + 1 << "]=";
            cin >> y[i];
        }
    }

    void show()
    {
        cout << "\nThe Table:\n\n";
        for (int i = 0; i < n; i++)
        {
            cout << x[i] << "\t";
            cout << y[i] << "\n";
        }
    }

    ~newton()
    {
        delete[] x;
        delete[] y;
    }

    double* coeffs()
    {

        double* k = new double[n];
        k[0] = y[0];
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < n - j; i++)
            {
                y[i] = (y[i + 1] - y[i]) / (x[i + j] - x[i]);
                //cout << y[i] << endl;
                k[j] = y[0];

            }
            cout << k[j] << endl;
        }
        return k;
    }

    double calc(double* k, double argx)
    {

        double S = k[0], p = 1;
        S += k[1] * (argx - x[1]) + k[2] * (argx - x[1]) * (argx - x[2]) + k[3] * (argx - x[1]) * (argx - x[2]) * (argx - x[3]) + k[4] * (argx - x[1]) * (argx - x[2]) * (argx - x[3]) * (argx - x[4]);
        //cout << "S = " << S << endl;
        return S;
    }


};


int main()
{
    cout << "\nClass Newton\n";
    cout << "Input values: X[n] and Y[n] - The Table\n";
    cout << "Then choose another x to calc f(x)\n";

    int n;
    double h = 0.79;
    newton first;
    first.show();
    double* k = first.coeffs();
    for (int i = 0; i < 5; i++) {
        cout << "\nWant to calc another x[i]? X=";
        double xtocalc;
        cin >> xtocalc;
        double res = first.calc(k, xtocalc + h);
        cout << res << endl;
    }
    return 0;
}
