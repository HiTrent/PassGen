#include <windows.h>
#include <commctrl.h>
#include <time.h>
#include <stdio.h>
#include "resources.h"

/* Функция обработки сообщений */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
		case WM_COMMAND: {
			if(LOWORD(wParam) == GENBTN) {
				char str[1024] = {};
				GetDlgItemText(hWnd, NUMEDIT, (LPSTR)str, 1024);
				
				int n = 0, j = 1;
				for(int i = 1023; i >= 0; i--) {
					if(str[i] >= '0' && str[i] <= '9') {
						n += (str[i]-'0') * j;
						j *= 10;
					}
				}
				
				memset(str, 0, sizeof(str));				
				for(int i = 0; i < n; i++) switch(rand() % 3 + 1) {
					case 1: str[i] = rand() % 10 + '0'; break; //012345...
					case 2: str[i] = rand() % 26 + 'A'; break; //ABCDEF...
					case 3: str[i] = rand() % 26 + 'a'; break; //abcdef...
        			}

				SetDlgItemText(hWnd, PASSEDIT, (LPSTR)str);
			}

			else if(LOWORD(wParam) == RESETBTN) {
				SetDlgItemText(hWnd, NUMEDIT, "");
				SetDlgItemText(hWnd, PASSEDIT, "");
			}

		} break;		

		case WM_CTLCOLORSTATIC: {
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, RGB(10, 80, 10));
			return (LRESULT)GetStockObject (NULL_BRUSH);
		} break;

		case WM_DESTROY: PostQuitMessage(0); break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/* Функция регистрации класса окон */
ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName) {
	WNDCLASS wc = {0};
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInst;
	wc.lpszClassName = lpzClassName;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
	return RegisterClass(&wc);
}

/* Функция вхождений программы WinMain */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	FreeConsole();
	srand(time(0));
	InitCommonControls();
	LPCTSTR lpzClass = "Window";
	if(!RegMyWindowClass(hInstance, lpzClass)) return 1;
	
	/* Вычисление координат центра экрана */
	RECT screen;
	GetWindowRect(GetDesktopWindow(), &screen);
	int width = 500;
	int height = 300;
	int x = (screen.right - width)/2;
	int y = (screen.bottom - height)/2;
    
	/* Создание окна */
	HWND hWnd = CreateWindow(
		lpzClass,
		"PassGen",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		x, y,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	
	/* Создание кнопки "Сгенерировать" */
	HWND GenBtn = CreateWindow(
		"Button",
		"Generate",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		165, 200,
		75, 23,
		hWnd,
		(HMENU)GENBTN,
		hInstance,
		NULL
	);

	/* Создание кнопки "Очистить" */
	HWND ResetBtn = CreateWindow(
		"Button",
		"Reset",
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		260, 200,
		75, 23,
		hWnd,
		(HMENU)RESETBTN,
		hInstance,
		NULL
	);
	
	/* Создание метки "N" */
	HWND NumLabel = CreateWindowEx(
		WM_CTLCOLORSTATIC,
		"Static",
		"N",
		WS_CHILD | WS_VISIBLE,
		110, 54,
		60, 24,
		hWnd,
		(HMENU)NUMLABEL,
		NULL,
		NULL
	);

	/* Создание первого текстового поля */
	HWND NumEdit = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"Edit",
		"",
		WS_CHILD | WS_VISIBLE,
		125, 50,
		250, 23,
		hWnd,
		(HMENU)NUMEDIT,
		hInstance,
		NULL
	);

	/* Создание метки "Пароль" */
	HWND PassLabel = CreateWindowEx(
		WM_CTLCOLORSTATIC,
		"Static",
		"Password",
		WS_CHILD | WS_VISIBLE,
		70, 104,
		60, 24,
		hWnd,
		(HMENU)PASSLABEL,
		NULL,
		NULL
	);

	/* Создание второго текстового поля */
	HWND PassEdit = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"Edit",
		"",
		WS_CHILD | WS_VISIBLE,
		125, 100,
		250, 23,
		hWnd,
		(HMENU)PASSEDIT,
		hInstance,
		NULL
	);
	
	HFONT font = CreateFont(
		14, 0, 0, 0,
		FW_DONTCARE,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		"Segoe UI"
	);

	SendMessage(GenBtn, WM_SETFONT, (WPARAM)font, TRUE);
	SendMessage(ResetBtn, WM_SETFONT, (WPARAM)font, TRUE);
	SendMessage(NumLabel, WM_SETFONT, (WPARAM)font, TRUE);	
	SendMessage(NumEdit, WM_SETFONT, (WPARAM)font, TRUE);
	SendMessage(PassLabel, WM_SETFONT, (WPARAM)font, TRUE);	
	SendMessage(PassEdit, WM_SETFONT, (WPARAM)font, TRUE);

	MSG msg = {0};
	int state = 0;
	while((state = GetMessage(&msg, NULL, 0, 0 )) != 0)   
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}
