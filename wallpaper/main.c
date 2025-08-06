#include <windows.h>

float ballX = 0, ballY = 0;
float speed = 0.1f;

// Cria uma janela atrás dos ícones do desktop
HWND CreateDesktopLayerWindow(HINSTANCE hInstance);

// Funções auxiliares
void DrawBall(HWND hwnd) {
    HDC hdc = GetDC(hwnd);
    RECT rect;
    GetClientRect(hwnd, &rect);

    // Limpa o fundo com transparência
    HBRUSH bg = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdc, &rect, bg);
    DeleteObject(bg);

    // Desenha a bolinha vermelha
    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hdc, brush);
    Ellipse(hdc, (int)(ballX - 10), (int)(ballY - 10), (int)(ballX + 10), (int)(ballY + 10));
    DeleteObject(brush);

    ReleaseDC(hwnd, hdc);
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

// Cria uma janela de fundo real (atrás dos ícones)
HWND CreateDesktopLayerWindow(HINSTANCE hInstance) {
    // Envia mensagem para criar WorkerW
    HWND progman = FindWindow("Progman", NULL);
    SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, NULL);

    // Acha o WorkerW com SHELLDLL_DefView
    HWND workerw = NULL;
    HWND defview = NULL;

    do {
        workerw = FindWindowEx(NULL, workerw, "WorkerW", NULL);
        defview = FindWindowEx(workerw, NULL, "SHELLDLL_DefView", NULL);
    } while (workerw && !defview);

    // A janela certa é a que NÃO contém o SHELLDLL_DefView
    HWND target = NULL;
    if (workerw)
        target = workerw;
    else
        target = progman;

    // Registra a classe da janela
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "DesktopBallClass";
    wc.hbrBackground = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_TRANSPARENT,
        "DesktopBallClass", NULL,
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL
    );

    // Torna a cor preta transparente
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    // Coloca como filho do WorkerW
    SetParent(hwnd, target);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    return hwnd;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hwnd = CreateDesktopLayerWindow(hInstance);

    // Posição inicial
    POINT p;
    GetCursorPos(&p);
    ballX = p.x;
    ballY = p.y;

    SetTimer(hwnd, 1, 16, NULL); // 60 FPS

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}