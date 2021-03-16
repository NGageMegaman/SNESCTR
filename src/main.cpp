#include "cpu.h"
#include "ppu.h"
using namespace std;

CPU *cpu;
PPU *ppu;

const char g_szClassName[] = "SNES CTR";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern "C" {
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
        WNDCLASSEX wc;
        HWND hwnd;
        MSG Msg = {0};

        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = 0;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = g_szClassName;
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wc)) {
            MessageBox(NULL, (const char*) "Window Registration Failed!", (const char*)"Error!", MB_ICONEXCLAMATION | MB_OK);
            return 0;
        }

        hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            g_szClassName,
            (const char*) "SNES CTR Emulator",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 256, 224,
            NULL, NULL, hInstance, NULL);

        if (hwnd == NULL) {
            MessageBox(NULL, (const char*)"Window Creation Failed!", (const char*)"Error!", MB_ICONEXCLAMATION | MB_OK);
            return 0;
        }

        ShowWindow(hwnd, nCmdShow);
        UpdateWindow(hwnd);

        while (GetMessage(&Msg, NULL, 0, 0) > 0) {
            TranslateMessage(&Msg);
            if (Msg.message != 96) DispatchMessage(&Msg);
        }
        return Msg.wParam;
    }
}

int tick = 0;
COLORREF *arr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    //TEXT can be STATIC, BUTTON or TEXT
    //if (tick == 20) {
        //CreateWindow(TEXT("STATIC"), TEXT(tick1), 
            //WS_VISIBLE | WS_CHILD, 
            //10, 10, 100, 25,
            //hwnd, (HMENU) NULL, NULL, NULL);
    //}
    //tick++;
    switch(msg) {
        case WM_CREATE:
            cpu = CPU::getInstance();
            ppu = PPU::getInstance();
            arr = (COLORREF *) malloc(256*224 * sizeof(COLORREF));
            SetTimer(hwnd, 1, USER_TIMER_MINIMUM, NULL);
            break;
        case WM_TIMER: {
            tick++;
            int cnt = 0;
            int line = 0;
            while (line != 300) {
                cpu->executeInstruction();
                if (cnt % 400 == 0) {
                    if (line < 225) {
                        Scanline scanline = ppu->HBlank(line);
                        Pixel *pixels = scanline.getPixels();
                        for (int i = 0; i<256; ++i) {
                            arr[i + line*256] = pixels[i].getRGBColor();
                        }
                    }
                    line++;
                }
                cnt++;
            }
            cpu->NMI();
            HDC hdc = GetDC(hwnd);
            HBITMAP map = CreateBitmap(256, 224, 1, 8*4, (void *) arr);
            HDC src = CreateCompatibleDC(hdc);
            SelectObject(src, map);
            BitBlt(hdc, 0, 0, 256, 224, src, 0, 0, SRCCOPY);
            DeleteObject(map);
            DeleteDC(src);
            ReleaseDC(NULL, hdc);
            //free(arr);
            break;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            free(arr);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            free(arr);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
