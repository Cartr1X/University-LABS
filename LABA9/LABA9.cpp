// пояснение: песня была сделана на более низкой частоте т.к. комп не воспроизводил половину звуков :(
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "russian");

    printf("Играем Happy Birthday!\n");

    Beep(392, 300); Sleep(30);
    Beep(392, 300); Sleep(30);
    Beep(440, 600); Sleep(30);
    Beep(392, 600); Sleep(30);
    Beep(523, 600); Sleep(30);
    Beep(494, 900);
    Sleep(100);

    Beep(392, 300); Sleep(30);
    Beep(392, 300); Sleep(30);
    Beep(440, 600); Sleep(30);
    Beep(392, 600); Sleep(30);
    Beep(587, 600); Sleep(30);
    Beep(523, 900);
    Sleep(100);

    Beep(392, 300); Sleep(30);
    Beep(392, 300); Sleep(30);
    Beep(784, 600); Sleep(30);
    Beep(658, 600); Sleep(30);
    Beep(523, 600); Sleep(30);
    Beep(494, 600); Sleep(30);
    Beep(440, 900);
    Sleep(100);

    Beep(698, 300); Sleep(30);
    Beep(698, 300); Sleep(30);
    Beep(658, 600); Sleep(30);
    Beep(523, 600); Sleep(30);
    Beep(587, 600); Sleep(30);
    Beep(523, 900);

    printf("Мелодия завершена!\n\n");

    printf("Нажмите любую клавишу для повторного проигрывания...\n");
    getchar();

    printf("Играем Happy Birthday еще раз!\n");

    Beep(392, 300); Sleep(30);
    Beep(392, 300); Sleep(30);
    Beep(440, 600); Sleep(30);
    Beep(392, 600); Sleep(30);
    Beep(523, 600); Sleep(30);
    Beep(494, 900);
    Sleep(100);

    Beep(392, 300); Sleep(30);
    Beep(392, 300); Sleep(30);
    Beep(440, 600); Sleep(30);
    Beep(392, 600); Sleep(30);
    Beep(587, 600); Sleep(30);
    Beep(523, 900);
    Sleep(100);

    Beep(392, 300); Sleep(30);
    Beep(392, 300); Sleep(30);
    Beep(784, 600); Sleep(30);
    Beep(658, 600); Sleep(30);
    Beep(523, 600); Sleep(30);
    Beep(494, 600); Sleep(30);
    Beep(440, 900);
    Sleep(100);

    Beep(698, 300); Sleep(30);
    Beep(698, 300); Sleep(30);
    Beep(658, 600); Sleep(30);
    Beep(523, 600); Sleep(30);
    Beep(587, 600); Sleep(30);
    Beep(523, 900);

    printf("Мелодия завершена!\n");

    return 0;
}