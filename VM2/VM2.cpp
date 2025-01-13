#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
using namespace std;
class Matr
{
private:
    int size;
    double** mas;
    double* mas1;
public:
    Matr()
    {
        size = 0;
        mas = NULL;
        mas1 = NULL;
    }
    Matr(int l)
    {
        size = l;
        mas = new double* [l];
        for (int i = 0; i < l; i++)
            mas[i] = new double[l];
        mas1 = new double[l];
    }
    void Add()
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                cin >> mas[i][j];
        for (int i = 0; i < size; i++)
        {
            cin >> mas1[i];
        }
    }
    void Print()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << setw(4) << mas[i][j] << " ";
            }
            cout << " " << mas1[i] << endl;
        }
    }
    void Preob()
    {
        double temp = 0;
        for (int k = 0; k < size; k++)
        {
            for (int i = 0; i < size; i++)
            {
                temp = mas[i][i] * (-1);
                mas1[i] /= temp;
                for (int j = 0; j <= size; j++)
                {
                    mas[i][j] /= temp;
                }
            }
        }
        for (int i = 0; i < size; i++)
        {
            mas1[i] *= -1;
            for (int j = 0; j < size; j++)
                mas[i][i] = 0;
        }
    }
    double Pogr(double** mas, double epsilon)
    {
        double eps = 0; double sum = 0, max = 0;
        double norm1 = 0, norm2 = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < i; j++)
            {
                sum += fabs(mas[i][j]);
                if (sum > norm1) norm1 = sum;
            }
            sum = 0;
            for (int j = i + 1; j < size; j++)
            {
                sum += fabs(mas[i][j]);
                if (sum > norm2) norm2 = sum;
            }
            sum = 0;
        }
        if (norm1 >= 1 || norm2 >= 1)
        {
            cerr << "Норма матрицы больше или равна 1." << endl;
            Sleep(4000);
            exit(1);
        }
        eps = ((1 - norm1) / norm2) * epsilon;
        return eps;
    }
    void Itera(double epsilon)
    {
        double* x = new double[size];
        double* p = new double[size];
        double* a = new double[size];
        double* E = new double[size];
        double per = Pogr(mas, epsilon), max = 0;
        for (int i = 0; i < size; i++)
        {
            x[i] = mas1[i];
            p[i] = 0;
        }
        double var = 0;
        for (int i = 0; i < size; i++)
        {
            var = 0;
            for (int k = 0; k < size; k++)
                var = mas[i][k] * mas1[k];
            x[i] = var;
        }
        for (int i = 0; i < size; i++)
            p[i] = x[i] + mas1[i];
        int counter = 0;
        do
        {
            counter++;
            cout << "Итерация № " << counter << endl << endl;
            for (int i = 0; i < size; i++)
            {
                var = 0;
                for (int j = 0; j < i; j++)
                    var += (mas[i][j] * p[j]);
                for (int j = i + 1; j < size; j++)
                    var += (mas[i][j] * x[j]);
                a[i] = var;
                x[i] = mas1[i] + a[i];
            }
            max = 0;
            for (int i = 0; i < size; i++)
            {
                E[i] = fabs(x[i] - p[i]);
                if (max < E[i]) max = E[i];
                p[i] = x[i];
                cout << "x" << i + 1 << "=" << x[i] << " " << endl;
            }
            cout << endl;
            cout << "max =" << max << endl << endl;
        } while (max > per);
        cout << endl << "Результат: \n\n";
        for (int i = 0; i < size; i++)
            cout << "x" << i + 1 << "=" << x[i] << " " << endl;
        delete[] x;
        delete[] p;
        delete[] E;
        delete[] a;
    }
    ~Matr()
    {
        for (int i = 0; i < size; i++)
            delete mas[i];
        delete mas;
    }
};
int main()
{
    setlocale(LC_ALL, "rus");
    int n; double epsi;
    cout << "Введите количество уравнений:   ";
    cin >> n;
    cout << "Введите желаемую точность:   ";
    cin >> epsi;
    Matr a(n);
    cout << "Введите матрицу коэффициентов, потом столбец свободных членов:" << endl;
    a.Add();
    cout << endl << "Расширенная матрица:" << endl;
    a.Print();
    a.Preob();
    cout << endl << "Преображенная матрица" << endl;
    a.Print();
    cout << endl;
    a.Itera(epsi);
    cout << endl;
    system("pause");
    return 0;
}