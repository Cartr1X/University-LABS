#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Student
{
    std::string fio;
    std::string adress;
    std::vector<int> grades;
    double average_score;
};

int main()
{
    setlocale(LC_ALL, "russian");
    int nst;

    std::cout << "Enter students count: ";
    std::cin >> nst;
    std::cin.ignore();

    std::vector<Student> stud;
    stud.reserve(nst);

    for (int i = 0; i < nst; i++)
    {
        Student student;
        std::cout << "Enter student fio: ";
        std::getline(std::cin, student.fio);

        std::cout << "Enter adress: ";
        std::getline(std::cin, student.adress);

        std::cout << "Enter 4 grades: ";
        student.average_score = 0;
        student.grades.resize(4);

        for (int j = 0; j < 4; j++)
        {
            std::cin >> student.grades[j];
            student.average_score += student.grades[j];
        }
        student.average_score /= 4.0;
        std::cin.ignore();
        stud.push_back(student);
    }

    std::vector<std::string> minsk_students;

    for (const auto& student : stud)
    {
        if (student.adress == "Минск" != std::string::npos && student.average_score >= 4.5)
        {
            minsk_students.push_back(student.fio);
        }
    }

    std::sort(minsk_students.begin(), minsk_students.end());

    std::cout << "Number of students who live in Minsk and have average score not less than 4.5: "
        << minsk_students.size() << "\n";

    if (!minsk_students.empty())
    {
        for (const auto& fio : minsk_students)
        {
            std::cout << fio << "\n";
        }
    }

    return 0;
}