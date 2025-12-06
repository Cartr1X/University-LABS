#define _CRT_SECURE_NO_WARNINGS;
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

typedef double (*uf)(double, double, int &); // объявляет uf как указатель на функцию, которая возвращает значение типа double.

void tabl(double, double, double, double, uf); // список параметров
double Y(double, double, int &);
double S(double, double, int &);

int main()
{
    double a = -1.0, b = 1.3, h = 0.1, eps = 1e-5;
    
    cout << "Таблица значений функции Y(x) = (2x*sinx - 2 + cosx)/4" << endl;
    cout << "Точность E = " << eps << endl;
    cout << setw(10) << "x" << setw(20) << "Y(x)" << setw(12) << "Итерации" << endl; // ширина вывода
    cout << string(42, '-') << endl;
    tabl(a, b, h, eps, Y);
    
    cout << "\n\nТаблица значений разложения в ряд S(x)" << endl;
    cout << "Точность E = " << eps << endl;
    cout << setw(10) << "x" << setw(20) << "S(x)" << setw(12) << "Итерации" << endl;
    cout << string(42, '-') << endl;
    tabl(a, b, h, eps, S);
    
    return 0;
}

void tabl(double a, double b, double h, double eps, uf fun)
{
    int k = 0;
    double sum;
    for (double x = a; x < b + h/2; x += h)
    {
        sum = fun(x, eps, k);
        cout << fixed << setprecision(3) << setw(10) << x // setpression устанавливает точность вывода для чисел с плавающей запятой
             << fixed << setprecision(8) << setw(20) << sum
             << setw(12) << k << endl;
    }
}

// Функция Y(x) = (2x*sinx - 2 + cosx)/4
double Y(double x, double eps, int &k)
{
    k = 0; // Для функции Y итераций не требуется
    return (2.0 * x * sin(x) - 2.0 + cos(x)) / 4.0;
}

// Функция S(x) - разложение в ряд
double S(double x, double eps, int &k)
{
    double term, sum = 0.0;
    k = 2;
    term = pow(-1.0, k) * cos(k * x) / (k * k - 1.0);
    sum = term;
    
    while (fabs(term) > eps)
    {
        k++;
        term = pow(-1.0, k) * cos(k * x) / (k * k - 1.0);
        sum += term;
        
        // Защита от бесконечного цикла
        if (k > 10000) {
            cout << "Предупреждение: превышено максимальное количество итераций" << endl;
            break;
        }
    }
    
    return sum;
}