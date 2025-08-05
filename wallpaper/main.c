#include <windows.h>

// Variáveis globais
int mouseX = 0, mouseY = 0;

// Prototipação
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Desenha a bolinha na tela
void DrawBall(HWND hwnd) {
    HDC hdc = GetDC(hwnd);

    RECT rect;
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW)); // limpa fundo

    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // cor da bolinha
    Ellipse(hdc, mouseX - 10, mouseY - 10, mouseX + 10, mouseY + 10); // desenha
    DeleteObject(brush);

    ReleaseDC(hwnd, hdc);
}

// Define a janela como plano de fundo
void SetAsDesktopBackground(HWND hwnd) {
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
    // Definir classe da janela
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MouseFollower";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    // Criar janela invisível ao clique, sem bordas e transparente
    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT,
        "MouseFollower", NULL,
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL);

    // Torna a janela transparente visualmente
    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);

    // Enviar a janela para o desktop
    SetAsDesktopBackground(hwnd);

    // Exibir janela
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Loop de mensagens
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// Tratamento da janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg) {
        case WM_CREATE:
            SetTimer(hwnd, 1, 16, NULL); // 60 FPS
            break;
        case WM_TIMER:
            {
                POINT p;
                GetCursorPos(&p);
                mouseX = p.x;
                mouseY = p.y;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                DrawBall(hwnd);
                EndPaint(hwnd, &ps);
            }
            break;
        case WM_DESTROY:
            KillTimer(hwnd, 1);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}
