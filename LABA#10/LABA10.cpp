#include <windows.h>
#include <math.h>

int main() {
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    
    double A = 50.0, start = 0.0, end = 10.0, step = 0.05;
    int ox = 50, oy = 200, sx = 30, sy = A;
    
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    SelectObject(hdc, pen);
    
    MoveToEx(hdc, ox, oy - A, NULL);
    for (double x = start; x <= end; x += step) {
        double y = A * sin(x);
        LineTo(hdc, ox + x * sx, oy - y);
        MoveToEx(hdc, ox + x * sx, oy - y, NULL);
    }
    
    ReleaseDC(hwnd, hdc);
    DeleteObject(pen);
    
    getchar();
    return 0;
}