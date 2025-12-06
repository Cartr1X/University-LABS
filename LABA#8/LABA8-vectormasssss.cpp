#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <functional>
using namespace std;

// Структура для хранения результатов вычислений
struct Result {
    double x;
    double value;
    int iterations;
};

// Тип функции для вычисления
using CalcFunction = function<double(double, double, int&)>;

double Y(double x, double eps, int &k);
double S(double x, double eps, int &k);

vector<Result> calculateValues(double a, double b, double h, double eps, CalcFunction func);
void printTable(const vector<Result>& results, const string& title, double eps);

int main()
{
    double a = -1.0, b = 1.3, h = 0.1, eps = 1e-5;
    
    // Вычисление значений функции Y(x)
    vector<Result> yResults = calculateValues(a, b, h, eps, Y);
    printTable(yResults, "Таблица значений функции Y(x) = (2x*sinx - 2 + cosx)/4", eps);
    
    cout << "\n\n";
    
    // Вычисление значений разложения в ряд S(x)
    vector<Result> sResults = calculateValues(a, b, h, eps, S);
    printTable(sResults, "Таблица значений разложения в ряд S(x)", eps);
    
    return 0;
}

vector<Result> calculateValues(double a, double b, double h, double eps, CalcFunction func) {
    vector<Result> results;
    
    for (double x = a; x < b + h/2; x += h) {
        int iterations = 0;
        double value = func(x, eps, iterations);
        
        results.push_back({x, value, iterations});
    }
    
    return results;
}

void printTable(const vector<Result>& results, const string& title, double eps) {
    cout << title << endl;
    cout << "Точность E = " << eps << endl;
    cout << setw(10) << "x" << setw(20) << "Значение" << setw(12) << "Итерации" << endl;
    cout << string(42, '-') << endl;
    
    for (const auto& result : results) {
        cout << fixed << setprecision(3) << setw(10) << result.x 
             << fixed << setprecision(8) << setw(20) << result.value
             << setw(12) << result.iterations << endl;
    }
}

// Функция Y(x) = (2x*sinx - 2 + cosx)/4
double Y(double x, double eps, int &k) {
    k = 0; // Для функции Y итераций не требуется
    return (2.0 * x * sin(x) - 2.0 + cos(x)) / 4.0;
}

// Функция S(x) - разложение в ряд
double S(double x, double eps, int &k) {
    double sum = 0.0;
    double term;
    k = 2;
    
    term = pow(-1.0, k) * cos(k * x) / (k * k - 1.0);
    sum = term;
    int current_k = k;
    
    while (fabs(term) > eps) {
        current_k++;
        term = pow(-1.0, current_k) * cos(current_k * x) / (current_k * current_k - 1.0);
        sum += term;
        
        // Защита от бесконечного цикла
        if (current_k > 10000) {
            cout << "Предупреждение: превышено максимальное количество итераций" << endl;
            break;
        }
    }
    
    // Возвращаем количество выполненных итераций
    k = current_k - 1;
    return sum;
}