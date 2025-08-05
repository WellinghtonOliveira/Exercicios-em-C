#include <windows.h>

float ballX = 0, ballY = 0;
float speed = 0.1f;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void DrawBall(HWND hwnd) {
    HDC hdc = GetDC(hwnd);

    RECT rect;
    GetClientRect(hwnd, &rect);

    // Fundo transparente (cor-chave)
    HBRUSH brushBack = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdc, &rect, brushBack);
    DeleteObject(brushBack);

    // Bolinha vermelha
    HBRUSH brushBall = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hdc, brushBall);
    Ellipse(hdc, (int)(ballX - 10), (int)(ballY - 10), (int)(ballX + 10), (int)(ballY + 10));
    DeleteObject(brushBall);

    ReleaseDC(hwnd, hdc);
}

// Mover a janela para plano de fundo, atrás dos ícones
void SetAsWallpaper(HWND hwnd) {
    HWND progman = FindWindow("Progman", NULL);
    SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, NULL);

    HWND workerw = NULL;
    HWND defview = NULL;

    do {
        workerw = FindWindowEx(NULL, workerw, "WorkerW", NULL);
        defview = FindWindowEx(workerw, NULL, "SHELLDLL_DefView", NULL);
    } while (workerw != NULL && defview == NULL);

    if (workerw != NULL) {
        SetParent(hwnd, workerw);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WallpaperBall";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT,
        "WallpaperBall", NULL,
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL);

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    // Chama a função para colocar a janela atrás dos ícones
    SetAsWallpaper(hwnd);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    POINT p;
    GetCursorPos(&p);
    ballX = p.x;
    ballY = p.y;

    SetTimer(hwnd, 1, 16, NULL);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg) {
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
