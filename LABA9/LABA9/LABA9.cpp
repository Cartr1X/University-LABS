#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

// Проверяем, поддерживается ли частота Beep()
int isFrequencySupported(int freq) {
    // Beep() обычно поддерживает частоты от 37 до 32767 Гц
    // Но на практике лучше ограничить диапазон 100-5000 Гц
    return (freq >= 100 && freq <= 5000);
}

// Безопасное воспроизведение ноты
void safeBeep(int freq, int duration) {
    if (freq <= 0) {
        Sleep(duration);
        return;
    }

    if (!isFrequencySupported(freq)) {
        // Если частота вне диапазона, используем ближайшую поддерживаемую
        if (freq < 100) freq = 100;
        if (freq > 5000) freq = 5000;
        printf("[Частота скорректирована: %d -> %d Гц]\n", freq, freq);
    }

    Beep(freq, duration);
}

void playHappyBirthday() {
    printf("Играем Happy Birthday!\n");

    // Исправленные частоты - все в поддерживаемом диапазоне
    int melody[][2] = {
        {392, 300}, {392, 300}, {440, 600}, {392, 600}, {523, 600}, {494, 900},
        {0, 100},
        {392, 300}, {392, 300}, {440, 600}, {392, 600}, {587, 600}, {523, 900},
        {0, 100},
        // Исправляем слишком высокие ноты (784 Гц может быть проблемной)
        {392, 300}, {392, 300}, {659, 600}, {587, 600}, {523, 600}, {494, 600}, {440, 900},
        {0, 100},
        {587, 300}, {587, 300}, {523, 600}, {440, 600}, {494, 600}, {440, 900}
    };

    int notesCount = sizeof(melody) / sizeof(melody[0]);

    for (int i = 0; i < notesCount; i++) {
        safeBeep(melody[i][0], melody[i][1]);

        if (i < notesCount - 1 && melody[i][0] > 0) {
            Sleep(30);
        }
    }

    printf("Мелодия завершена!\n\n");
}

void playDemo() {
    printf("Демо-мелодия (проверка диапазона частот)...\n");

    // Тестируем разные частоты
    int testFreqs[] = { 100, 200, 300, 400, 500, 600, 800, 1000, 1500, 2000, 3000, 4000 };
    int testCount = sizeof(testFreqs) / sizeof(testFreqs[0]);

    for (int i = 0; i < testCount; i++) {
        printf("%d Гц: ", testFreqs[i]);
        if (isFrequencySupported(testFreqs[i])) {
            Beep(testFreqs[i], 150);
            printf("OK\n");
        }
        else {
            printf("Не поддерживается\n");
        }
        Sleep(100);
    }

    printf("Демо завершена!\n");
}

void testPianoRange() {
    printf("\n=== Тест диапазона пианино ===\n");

    // Стандартные частоты для октавы
    int pianoNotes[] = { 262, 294, 330, 349, 392, 440, 494, 523 };
    const char* noteNames[] = { "До", "Ре", "Ми", "Фа", "Соль", "Ля", "Си", "До+" };

    for (int i = 0; i < 8; i++) {
        printf("%s (%d Гц): ", noteNames[i], pianoNotes[i]);
        if (isFrequencySupported(pianoNotes[i])) {
            Beep(pianoNotes[i], 200);
            printf("✓\n");
        }
        else {
            printf("✗ (не поддерживается)\n");
        }
        Sleep(50);
    }
}

int main() {
    setlocale(LC_ALL, "russian");

    printf("=== Консольное пианино с поддержкой частот ===\n");

    // Сначала тестируем диапазон
    testPianoRange();

    printf("\n");
    playHappyBirthday();

    printf("Управление:\n");
    printf("a-s-d-f-g-h-j - ноты от До до Си\n");
    printf("1-8 - тестовые частоты (100-4000 Гц)\n");
    printf("h - проиграть Happy Birthday\n");
    printf("r - демо-мелодия\n");
    printf("t - тест диапазона\n");
    printf("q - выход\n\n");

    char key;
    while (1) {
        if (_kbhit()) {
            key = _getch();

            if (key == 'q') {
                printf("Выход\n");
                break;
            }

            if (key == 'h') {
                playHappyBirthday();
                continue;
            }

            if (key == 'r') {
                playDemo();
                continue;
            }

            if (key == 't') {
                testPianoRange();
                continue;
            }

            // Тестовые частоты
            if (key >= '1' && key <= '8') {
                int testFreqs[] = { 100, 200, 400, 600, 800, 1000, 1500, 2000 };
                int idx = key - '1';
                if (idx >= 0 && idx < 8) {
                    printf("Тест: %d Гц\n", testFreqs[idx]);
                    safeBeep(testFreqs[idx], 300);
                }
                continue;
            }

            int freq = 0;
            const char* note = "";

            switch (key) {
            case 'a': freq = 262; note = "До"; break;
            case 's': freq = 294; note = "Ре"; break;
            case 'd': freq = 330; note = "Ми"; break;
            case 'f': freq = 349; note = "Фа"; break;
            case 'g': freq = 392; note = "Соль"; break;
            case 'h': freq = 440; note = "Ля"; break;
            case 'j': freq = 494; note = "Си"; break;
            default: continue;
            }

            printf("Ноть: %s (%d Гц)\n", note, freq);
            safeBeep(freq, 300);
            Sleep(30);
        }
    }

    return 0;
}