#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream> // stingstream новая фигня для работы со строками как с потоком, позволяет считывать слова, в нашем случае ss(text)
#include <locale>
#include <cctype>

using namespace std;

int main()
{ 
    setlocale(LC_ALL, "russian");
    string text;
    cout << "Введите строку на английском языке: ";
    getline(cin, text); // используем функцию getline, cчитываем всю строку, включая пробелы
    stringstream ss(text);
    string word;
    vector<string> words;

    while (ss >> word) // короче (ss >> word) нужна для того чтобы извлекать из потока слова, читая данные из него (я над этой фигней думал 25 минут)
    { 
        words.push_back(word); // нулевой объект в конце
    }
    // функция sort: сортирует диапазон элементов в массиве (без учета верхнего регистра)
    sort(words.begin(), words.end(), [](const string& a, const string& b)
    {
        string aLower, bLower; // Преобразуем строки в нижний регистр для сравнения
        aLower.reserve(a.length());
        bLower.reserve(b.length());
        
        for (char c : a) aLower += tolower(c);
        for (char c : b) bLower += tolower(c);
        
        return aLower < bLower;
    });

    cout << "Вывод слов в порядке латинского алфавита: ";
    for (const string& sorted_word : words) { // for (const string& ) - итерация 
        cout << sorted_word << " ";
    }
    cout << endl;

    return 0;
}