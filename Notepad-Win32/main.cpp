#include <windows.h>

#define FILE_MENU_NOVO 1
#define FILE_MENU_ABRIR 2
#define FILE_MENU_SAIR 3
LRESULT CALLBACK WindowsProcedure(HWND,UINT,WPARAM,LPARAM);

void AddMenus(HWND);     //declaração função adicionar menus

HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst , HINSTANCE hPrevInst, LPSTR args,int ncmdshow)         //função principal
{
    WNDCLASSW wc = {0};     //Class wc de Windows Class

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW ;      //configuração Background
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);        //configuração Cursor
    wc.hInstance = hInst;                           //configuração instancia
    wc.lpszClassName = L"WindowClass";              //
    wc.lpfnWndProc = WindowsProcedure;              //

    if (!RegisterClassW(&wc))                       //
        return -1;

    CreateWindowW(L"WindowClass", L"Notepad do Faria", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 600,300,1000,600,NULL,NULL,NULL,NULL);

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
    case WM_COMMAND:
        switch(wp)
        {
        case FILE_MENU_SAIR:
            DestroyWindow(hWnd);        //Se alguem clicar "Sair" a janela fecha e a aplicação encerra
            break;
        case FILE_MENU_NOVO:
            break;
        case FILE_MENU_ABRIR:
            break;
        }


        break;
    case WM_CREATE:
        AddMenus(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd,msg,wp,lp);
    }
}   //fim WindowsProcesure


void AddMenus(HWND hWnd)         //Função criar menu "taskbar"
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();         //Criar Menu
    HMENU hSubMenu = CreateMenu();          //Criar SubMenu

    AppendMenu(hSubMenu,MF_STRING,NULL,"SubMenu");

    AppendMenu(hFileMenu,MF_STRING,FILE_MENU_NOVO,"Novo");          //SubMenu de File -> Menu NOVO
    AppendMenu(hFileMenu,MF_POPUP,(UINT_PTR)hSubMenu,"Abrir");      //SubMenu de File -> Menu Abrir -> com submenu SubMenu
    AppendMenu(hFileMenu,MF_SEPARATOR,NULL,NULL);                   //SubMenu de File -> Separador de divisão so submenu de File
    AppendMenu(hFileMenu,MF_STRING,FILE_MENU_SAIR,"Sair");          //SubMenu de File -> Menu Sair //fecha o programa

    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileMenu,"Ficheiro");
    AppendMenu(hMenu,MF_POPUP,NULL,"Editar");
    AppendMenu(hMenu,MF_POPUP,NULL,"Formatar");
    AppendMenu(hMenu,MF_POPUP,NULL,"Ver");
    AppendMenu(hMenu,MF_POPUP,NULL,"Ajuda");

    SetMenu(hWnd, hMenu);
}




