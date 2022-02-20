#include <windows.h>
#include <stdio.h>

//#define FILE_MENU_NOVO 1
//#define FILE_MENU_ABRIR 2
//#define FILE_MENU_SAIR 3
#define OPEN_FILE_BUTTON 1
#define SAVE_FILE_BUTTON 2

LRESULT CALLBACK WindowsProcedure(HWND,UINT,WPARAM,LPARAM);

//void AddMenus(HWND);            //declaração função adicionar menus
void AddControls(HWND);         //declaração função adicionar controlos

//HMENU hMenu;
HWND hMainWindow,hEdit;

//---- Função principal ----

int WINAPI WinMain(HINSTANCE hInst , HINSTANCE hPrevInst, LPSTR args,int ncmdshow)         //função principal
{
    WNDCLASSW wc = {0};                             //Declaração Class. wc de Windows Class.

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW ;      //configuração Background
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);        //configuração Cursor
    wc.hInstance = hInst;                           //configuração instancia
    wc.lpszClassName = L"WindowClass";              //String de identificação a class windows
    wc.lpfnWndProc = WindowsProcedure;              //Ponteiro para a função definida WindowsProcedure

    if (!RegisterClassW(&wc))                       //Registar Class
        return -1;

    hMainWindow = CreateWindowW(L"WindowClass", L"Notepad do Faria", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 600,300,1000,600,NULL,NULL,NULL,NULL);

    MSG msg = {0};

    while(GetMessage(&msg,NULL,NULL,NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }   //fim while
    return 0;
}   //fim main

void display_file(char* path)
{
    FILE *file;
    file = fopen(path,"rb");
    fseek(file,0,SEEK_END);
    int _size = ftell(file);
    rewind(file);
    char *data = new char[_size+1];
    fread(data,_size,1,file);
    data[_size] = '\0';

    SetWindowText(hEdit,data);

    fclose(file);
}

void open_file(HWND hWnd)
{
    OPENFILENAME ofn;

    char file_name[100];

    ZeroMemory(&ofn,sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile [0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    //ofn.lpstrFile = "All Files\0*.*\0Source Files\0*.CPP\0Python Files\0*.PY\0Text Files\0*.TXT\0";

    ofn.nFilterIndex = 1;

    GetOpenFileName(&ofn);

    display_file(ofn.lpstrFile);
}

void write_file(char* path)
{
    FILE *file;
    file = fopen(path,"w");             //"w" modo escrita

    int _size = GetWindowTextLength(hEdit);        //retorna o tamanho do texto na EditBox
    char *data = new char[_size+1];
    GetWindowText(hEdit, data,_size+1);

    fwrite(data,_size+1,1,file);
    fclose(file);
}

void save_file(HWND hWnd)
{
    OPENFILENAME ofn;

    char file_name[100];

    ZeroMemory(&ofn,sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile [0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    //ofn.lpstrFile = "All Files\0*.*\0Source Files\0*.CPP\0Python Files\0*.PY\0Text Files\0*.TXT\0";

    ofn.nFilterIndex = 1;

    GetSaveFileName(&ofn);

    write_file(ofn.lpstrFile);
}

LRESULT CALLBACK WindowsProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        {
            switch(wp)
            {
            case OPEN_FILE_BUTTON:
                open_file(hWnd);
                break;
            case SAVE_FILE_BUTTON:
                save_file(hWnd);
                break;
            }   //fim switch(wp)
        }

        break;

    case WM_CREATE:
        AddControls(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hWnd,msg,wp,lp);
    }   //fim switch(msg)
}   //fim WindowsProcesure

/*
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
*/

void AddControls(HWND hWnd)          //Função para adicionar controlos
{
    CreateWindowW(L"Button",L"Abrir Ficheiro", WS_VISIBLE | WS_CHILD,10,10,150,36,hWnd,(HMENU)OPEN_FILE_BUTTON,NULL,NULL);

    CreateWindowW(L"Button",L"Guardar Ficheiro", WS_VISIBLE | WS_CHILD,170,10,150,36,hWnd,(HMENU)SAVE_FILE_BUTTON,NULL,NULL);

    hEdit = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | WS_VSCROLL | WS_HSCROLL,
                          10,50,400,300,hWnd,NULL,NULL,NULL);
}

