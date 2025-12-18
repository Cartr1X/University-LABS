#include <windows.h>
#include <stdio.h>
#include <math.h>

int main() {
    double A = 50.0;      // Амплитуда
    double x_start = 0.0; // Начало диапазона по X
    double x_end = 10.0;  // Конец диапазона по X
    double step = 0.1;    // Шаг по X
    
    // Получаем контекст устройства для консоли
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);
    
    // Создаем перо для рисования графика
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    HPEN old_pen = (HPEN)SelectObject(device_context, pen);
    
    // Настройки для отображения (масштаб и смещение)
    int x_offset = 50;    // Смещение по X
    int y_offset = 200;   // Смещение по Y (центр графика)
    double x_scale = 20.0; // Масштаб по X
    double y_scale = A;    // Масштаб по Y
    
    // Рисуем оси координат
    HPEN axis_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(device_context, axis_pen);
    
    // Ось X
    MoveToEx(device_context, 0, y_offset, NULL);
    LineTo(device_context, 600, y_offset);
    
    // Ось Y
    MoveToEx(device_context, x_offset, 0, NULL);
    LineTo(device_context, x_offset, 400);
    
    // Возвращаем перо для графика
    SelectObject(device_context, pen);
    
    // Переменные для координат
    double x, y;
    int screen_x, screen_y;
    
    // Начинаем рисовать график
    x = x_start;
    y = A * sin(x);
    
    // Преобразуем математические координаты в экранные
    screen_x = (int)(x_offset + x * x_scale);
    screen_y = (int)(y_offset - y * y_scale);
    
    // Устанавливаем начальную точку
    MoveToEx(device_context, screen_x, screen_y, NULL);
    
    // Рисуем график с помощью цикла
    for (x = x_start + step; x <= x_end; x += step) {
        y = A * sin(x); // Вычисляем значение функции
        
        // Преобразуем математические координаты в экранные
        screen_x = (int)(x_offset + x * x_scale);
        screen_y = (int)(y_offset - y * y_scale);
        
        // Рисуем линию к следующей точке
        LineTo(device_context, screen_x, screen_y);
    }
    
    // Подписи на графике
    SetTextColor(device_context, RGB(0, 0, 255));
    SetBkMode(device_context, TRANSPARENT);
    TextOut(device_context, 10, 10, L"График функции y = A * sin(x)", 30);
    
    char amplitude_text[50];
    sprintf(amplitude_text, "A = %.1f", A);
    TextOutA(device_context, 10, 30, amplitude_text, strlen(amplitude_text));
    
    char range_text[50];
    sprintf(range_text, "x in [%.1f, %.1f]", x_start, x_end);
    TextOutA(device_context, 10, 50, range_text, strlen(range_text));
    
    // Восстанавливаем старое перо и освобождаем ресурсы
    SelectObject(device_context, old_pen);
    DeleteObject(pen);
    DeleteObject(axis_pen);
    ReleaseDC(console_handle, device_context);
    
    printf("График функции y = %.1f * sin(x) нарисован!\n", A);
    printf("Диапазон: x от %.1f до %.1f\n", x_start, x_end);
    printf("Нажмите Enter для выхода...");
    
    getchar();
    return 0;
}