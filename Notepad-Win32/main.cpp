#include <windows.h>

LRESULT CALLBACK WindowsProcedure(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInst , HINSTANCE hPrevInst, LPSTR args,int ncmdshow)         //
{
    WNDCLASSW wc = {0};     //Class wc de Windows Class

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW ;      //configuração Background
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);        //configuração Cursor
    wc.hInstance = hInst;                           //configuração instancia
    wc.lpszClassName = L"WindowClass";              //
    wc.lpfnWndProc = WindowsProcedure;              //

    if (!RegisterClassW(&wc))                       //
        return -1;

    CreateWindowW(L"WindowClass", L"Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 600,300,1000,600,NULL,NULL,NULL,NULL);

    MSG msg = {0};

    while(GetMessage(&msg,NULL,NULL,NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    return 0;
}   //fim main

LRESULT CALLBACK WindowsProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd,msg,wp,lp);
    }
}   //fim WindowsProcesure
