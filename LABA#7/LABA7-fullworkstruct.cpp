#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <locale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "russian");
    struct strc{ // пользовательский тип данных, который позволяет объединять переменные различных типов под одним именем
        char fio[40];
        char address[50]; 
        int otc[4];
        double sb; // средний балл
    } mstud[100]; // массив студентов

    int nst, i, j;
    cout << "Введите количество абитуриентов: " << endl;
    cin >> nst;

    for (i = 0; i < nst; i++)
    {
        cout << "Введите ФИО: ";
        cin.ignore(); // очищаем буфер ввода, чтобы удалить оставшийся символ новой строки (`\n`) после считывания ФИО, что мешает последующим вызовам getline() для чтения строк. 
        cin.getline(mstud[i].fio, 40);

        cout << "Введите адрес, включая указанный город Минск: ";
        cin.getline(mstud[i].address, 50);

        cout << "Введите 4 оценки (через пробел): " << endl;
        mstud[i].sb = 0;
        for (j = 0; j < 4; j++)
        {
            cin >> mstud[i].otc[j];
            mstud[i].sb += mstud[i].otc[j] / 4.0;
        }
        cout << endl;
    }

    // Создание массива для Минских абитуриентов со средним баллом 4,5
    strc minsk_students[100];
    int count_minsk = 0;
    for (i = 0; i < nst; i++)
    {
        // Проверяем, что адрес содержит "Минск" и средний балл >= 4.5
        if (strstr(mstud[i].address, "Минск") != NULL && mstud[i].sb >= 4.5) // != NULL означает "если результат функции НЕ равен NULL", т.е. условие будет истинным, только если "Минск" был найден в адресе
        {
            minsk_students[count_minsk] = mstud[i];
            count_minsk++;
        }
    }

    for (i = 0; i < count_minsk - 1; i++) // вывод ФИО в алфавитном порядкке (+1)
    {
        for (j = i + 1; j < count_minsk; j++)
        {
            if (strcmp(minsk_students[i].fio, minsk_students[j].fio) > 0)
            {
                strc temp = minsk_students[i];
                minsk_students[i] = minsk_students[j];
                minsk_students[j] = temp;
            }
        }
    }

    cout << "Количество абитуриентов из Минска со средним баллом не ниже 4.5: " << count_minsk << endl;
    cout << "Их фамилии в алфавитном порядке:" << endl;
    
    for (i = 0; i < count_minsk; i++)
    {
        // Извлекаем фамилию
        char surname[40];
        strcpy(surname, minsk_students[i].fio); // strcpy копирует все содержимое строки
        char* space_pos = strchr(surname, ' '); // поиск пробела в фамилии
        if (space_pos != NULL) // в случае если он есть:
        {
            *space_pos = '\0'; // обрезаем строку после фамилии
        }
        cout << surname << endl;
    }

    return 0;
}