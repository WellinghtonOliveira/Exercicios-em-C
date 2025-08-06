#include <windows.h>

float ballX = 0, ballY = 0;
float speed = 0.1f;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void DrawBall(HWND hwnd) {
    HDC hdc = GetDC(hwnd);

    RECT rect;
    GetClientRect(hwnd, &rect);

    // Apaga o fundo com cor transparente
    HBRUSH brushBack = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdc, &rect, brushBack);
    DeleteObject(brushBack);

    // Desenha a bolinha vermelha
    HBRUSH brushBall = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hdc, brushBall);
    Ellipse(hdc, (int)(ballX - 10), (int)(ballY - 10), (int)(ballX + 10), (int)(ballY + 10));
    DeleteObject(brushBall);

    ReleaseDC(hwnd, hdc);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "BolaMouseClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW,
        "BolaMouseClass", NULL,
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL
    );

    // Define a cor preta como transparente
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Inicializa posição da bolinha
    POINT p;
    GetCursorPos(&p);
    ballX = p.x;
    ballY = p.y;

    SetTimer(hwnd, 1, 16, NULL);  // ~60 FPS

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_TIMER: {
            POINT p;
            GetCursorPos(&p);
            ballX += (p.x - ballX) * speed;
            ballY += (p.y - ballY) * speed;
            InvalidateRect(hwnd, NULL, FALSE);
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            DrawBall(hwnd);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
            KillTimer(hwnd, 1);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
