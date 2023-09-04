// Калькулятор.

#include <windows.h>
#include <Windowsx.h>
#include <tchar.h>
#include <string>
#include "resource.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Прототип функции. CALLBACK 
INT_PTR CALLBACK modalProcAas(	// Прототип функции модального диалогового окна "О программе".
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	);

INT_PTR CALLBACK Dialog_open_calculator_proc		// Прототип функции модального диалогового окна открытия калькулятора.
	(
	_In_ HWND   hwndDlg_open_calc,
	_In_ UINT   uMsg_open_calc,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	);

INT_PTR CALLBACK Dialog_nomodal_proc		// Прототип функции немодального диалогового окна Спонсорам.
(
_In_ HWND   hwndDlg_nomodal,
_In_ UINT   uMsg_nomodal,
_In_ WPARAM wParam,
_In_ LPARAM lParam
);

void CALLBACK timerProc(HWND hwnd, UINT msg_timer, UINT_PTR timer2); // Прототип функции обработки таймера 2.

// WndProc - Эта функция обрабатывает многочисленные сообщения, которые приложение получает от операционной системы.
//--------------------------------------------------------------------------------------------------------------------------------
HINSTANCE hInstance;
HWND hwnd; // HWND - дескриптор.
HWND button1; // кнопка 1.
HWND button2; // кнопка 2.
HWND button3; // кнопка 3.
HWND button4; // кнопка 4.
HWND button5; // кнопка 5.
HWND button6; // кнопка 6.
HWND button7; // кнопка 7.
HWND button8; // кнопка 8.
HWND button9; // кнопка 9.
HWND button0; // кнопка 0.
HWND button_plus; // кнопка +.
HWND button_minus; // кнопка -.
HWND button_multiplication; // кнопка *.
HWND button_division; // кнопка /.
HWND button_result; // кнопка =.
HWND button_point; // кнопка ,.
HWND buttonCancel;	// кнопка "отмена".
HWND buttonC; // кнопка "очистка дисплея".
HWND buttonAC; // кнопка "очистка памяти".
HWND button_pow; // кнопка вычисления значения х в степени y.
HWND button_sin; // кнопка вычисления значения синуса. Углы указываются в радианаx.
HWND button_cos; // кнопка вычисления значения косинуса. Углы указываются в радианаx.
HWND button_tan; // кнопка вычисления значения тангенса. Углы указываются в радианаx.
HWND button_sqrt; // кнопка вычисления положительного квадратного корня.
HWND button_negative; // кнопка отрицательной величины.
HWND edit; // Дисплей калькулятора.
HWND nomodal_Dialog; // Дескриптор немодального диалогового окна.
HMENU hMenu; // Идентификатор меню.
TCHAR Loper[10]; // Массивы для хранения левого операнда.
//TCHAR Roper[10]; // Массивы для хранения правого операнда.
TCHAR Result[10]; // Массивы для хранения результата.
TCHAR buffer[10];
//char operation; // переменная для хранения нажатой кнопки операции.
int operation = -1;		// переменная для хранения нажатой кнопки операции.
// + - 0
// - - 1
// / - 2
// * - 3
// pow - 4
// sin - 5
// cos - 6
// tan - 7
// sqrt - 8
float res = 0.0;
float rop = 0.0;
UINT_PTR timer1; // таймер 1.
UINT_PTR timer2; // таймер 2.
int tsecond = 0;
//--------------------------------------------------------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) // Точка входа в программу.
// WinMain - название точки входа в программу.
// _hInstance - уникальный код программы.
// hPrevInstance - код родительского приложения.
// PSTR - указатель на строку.
// iCmdShow - целочисленная переменная, которая содержит 

{
	HINSTANCE hInstance = _hInstance; // hInstance 
	MSG msg;	// msg - структура, которая описывает сообщение конечному звену.
	WNDCLASSEX wndclass;	// wndclass - класс (структура) окна.
	wndclass.cbSize = sizeof(wndclass);		// cbSize 
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	// CS_HREDRAW, CS_VREDRAW
	wndclass.lpfnWndProc = WndProc;		// lpfnWndProc - указатель на функцию CALLBACK WndProc.
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance; // Передаём уникальный код приложения в класс, который описывает наше приложение.
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// hIcon - иконка.
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);		// курсор.
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// цвет фона приложения.
	wndclass.lpszMenuName = NULL;	// Длинный указатель на главное меню.
	wndclass.lpszClassName = L"znoReg";		// znoReg уникальное название класса.
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);		// маленькая иконка.

	if (!RegisterClassEx(&wndclass))	// Функция производит регистрацию класса (структуры).
	{
		MessageBox(hwnd, L"Не удалось зарегестрировать класс окна", L"Ошибка регистрации класса окна", MB_OK);
		return 0;
	}
	//инициализация класса окна------------------------------------------------------------------------------------------------end
	hwnd = CreateWindow(	// Функция создаёт всё (не только окно, но и кнопки и т.д.). //CreateWindowEX
		// CreateWindowA, CreateWindowW
		// hwnd - уникальный дескриптор (описатель) приложения.
		wndclass.lpszClassName,
		L"Калькулятор",	// Имя окна. L - Использование Unicode.
		WS_OVERLAPPEDWINDOW^WS_THICKFRAME | WS_MAXIMIZEBOX | WS_SYSMENU, // WS_OVERLAPPEDWINDOW - минимальные настройки.
		// ^WS_THICKFRAME исключает WS_THICKFRAME из WS_OVERLAPPEDWINDOW.
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		345,
		300,
		NULL,
		NULL, // указатель на меню.
		hInstance, // Уникальный идентификатор приложения.
		NULL	// plParam -
		);
	if (!hwnd)
	{
		MessageBox(hwnd, L"Не удалось создать экземпляр окна", L"Ошибка создания экземпляра окна", MB_OK);
		return 0;
	}
	ShowWindow(hwnd, iCmdShow);		// Показать окно.

	UpdateWindow(hwnd);		// Перерисовать окно.
	while (GetMessage(&msg, NULL, 0, 0))	// Получение сообщения.
	{
		TranslateMessage(&msg);		// 
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)	// hwnd - дескриптор приложения.
// iMsg - код события. wParam, lParam - параметры.
{
	switch (iMsg)
	{
	case WM_CREATE: { // Создание окна.
						//MessageBox(NULL, L"Калькулятор уже создан, но не показан на экране.", L"", NULL);
						//DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_open_calculator), hwnd, Dialog_open_calculator_proc);
						// Edit Control почему-то не работает.
						hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));	// Инициализация меню.
						SetMenu(hwnd, hMenu);
						CheckMenuItem(hMenu, ID_standard, MF_CHECKED);
						//CheckMenuItem();
						edit = CreateWindow(L"Edit", L" ", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 20, 20, 290, 30, hwnd, NULL, hInstance, NULL);
						//SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)L"Вася"); // (LPARAM) - явное приведение типа.
						// WM_SETTEXT Sets the text of a window. wParam - This parameter is not used. lParam - A pointer to a null-terminated string that is the window text. 
						button1 = CreateWindow(L"Button", L"1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 70, 50, 30, hwnd, NULL, hInstance, NULL);
						button2 = CreateWindow(L"Button", L"2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 80, 70, 50, 30, hwnd, NULL, hInstance, NULL);
						button3 = CreateWindow(L"Button", L"3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 140, 70, 50, 30, hwnd, NULL, hInstance, NULL);
						button4 = CreateWindow(L"Button", L"4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 70, 50, 30, hwnd, NULL, hInstance, NULL);
						button5 = CreateWindow(L"Button", L"5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 260, 70, 50, 30, hwnd, NULL, hInstance, NULL);
						button6 = CreateWindow(L"Button", L"6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 110, 50, 30, hwnd, NULL, hInstance, NULL);
						button7 = CreateWindow(L"Button", L"7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 80, 110, 50, 30, hwnd, NULL, hInstance, NULL);
						button8 = CreateWindow(L"Button", L"8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 140, 110, 50, 30, hwnd, NULL, hInstance, NULL);
						button9 = CreateWindow(L"Button", L"9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 110, 50, 30, hwnd, NULL, hInstance, NULL);
						button0 = CreateWindow(L"Button", L"0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 260, 110, 50, 30, hwnd, NULL, hInstance, NULL);
						button_point = CreateWindow(L"Button", L",", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 150, 50, 30, hwnd, NULL, hInstance, NULL);
						button_minus = CreateWindow(L"Button", L"-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 80, 150, 50, 30, hwnd, NULL, hInstance, NULL);
						button_multiplication = CreateWindow(L"Button", L"*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 140, 150, 50, 30, hwnd, NULL, hInstance, NULL);
						button_division = CreateWindow(L"Button", L"/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 150, 50, 30, hwnd, NULL, hInstance, NULL);
						button_plus = CreateWindow(L"Button", L"+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 260, 150, 50, 30, hwnd, NULL, hInstance, NULL);
						button_negative = CreateWindow(L"Button", L"( - )", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 190, 50, 30, hwnd, NULL, hInstance, NULL);
						button_sqrt = CreateWindow(L"Button", L"sqrt", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 80, 190, 50, 30, hwnd, NULL, hInstance, NULL);
						buttonC = CreateWindow(L"Button", L"C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 140, 190, 50, 30, hwnd, NULL, hInstance, NULL);
						button_result = CreateWindow(L"Button", L"=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 190, 110, 30, hwnd, NULL, hInstance, NULL);
						button_pow = CreateWindow(L"Button", L"pow", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 340, 70, 50, 30, hwnd, NULL, hInstance, NULL);
						button_sin = CreateWindow(L"Button", L"sin", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 70, 50, 30, hwnd, NULL, hInstance, NULL);
						button_cos = CreateWindow(L"Button", L"cos", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 340, 110, 50, 30, hwnd, NULL, hInstance, NULL);
						button_tan = CreateWindow(L"Button", L"tan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 110, 50, 30, hwnd, NULL, hInstance, NULL);
						SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // очистка дисплея (чтобы кнопка отрицательной величины работала сразу после включения калькулятора).
						// buttonCancel = CreateWindow(L"Button", L"Cancel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 10, 100, 30, hwnd, NULL, hInstance, NULL);
						//ShowWindow(hwnd, SW_HIDE);
						SetTimer(hwnd, timer1, 5000, NULL); // Запуск таймера. Таймер всё время работает с момента запуска программы.
						break;
	}
	case WM_TIMER:	// Обработка таймера.
	{
					 if (wParam == timer1)
					 {
						 tsecond++;
						 //MessageBox(NULL, L"5 секунд", L"", NULL);
						 if (tsecond >= 6)
						 {
							 KillTimer(hwnd, timer1); // Первый вариант.
							 //SetTimer(hwnd, timer2, 1000, timerProc);		// Второй вариант. Запуск таймера. Таймер всё время работает с момента запуска программы.
							 MessageBox(NULL, L"Прошло 30 секунд", L"", NULL);
						 }
						 break;
					 }
	}
	case WM_COMMAND: // 
	{
						 if (HIWORD(wParam) == BN_CLICKED)	// Обработка щелчка.
						 {
							 if (LOWORD(wParam) == ID_exit) // Выбран пункт меню "Выход".
							 {
								 DestroyWindow(hwnd);
							 }

							 if (LOWORD(wParam) == ID_standard) // Выбран пункт меню "обычный".
							 {
								 //MessageBox(NULL, L"Выбран пункт меню обычный.", L"", NULL);
								 CheckMenuItem(hMenu, ID_standard, MF_CHECKED);
								 CheckMenuItem(hMenu, ID_engineer, MF_UNCHECKED);
								 SetWindowPos(hwnd, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, 345, 300, SWP_NOMOVE | SWP_DRAWFRAME);
								 // SetWindowPos Изменяет размер, положения и z-порядок дочернего элемента, контекстного меню
								 // и окна верхнего уровня.
								 DestroyWindow(edit);
								 edit = CreateWindow(L"Edit", L" ", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 20, 20, 290, 30, hwnd, NULL, hInstance, NULL);
								 // Для изменения размеров дисплея можно использовать SetWindowPos вместо DestroyWindow и CreateWindow.
								 //SetWindowPos(edit, HWND_TOP, 20, 20, 290, 30, SWP_NOMOVE);
							 }

							 if (LOWORD(wParam) == ID_engineer) // Выбран пункт меню "инженерный".
							 {
								 //MessageBox(NULL, L"Выбран пункт меню инженерный.", L"", NULL);
								 CheckMenuItem(hMenu, ID_standard, MF_UNCHECKED);
								 CheckMenuItem(hMenu, ID_engineer, MF_CHECKED);
								 SetWindowPos(hwnd, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, 485, 300, SWP_NOMOVE | SWP_DRAWFRAME);
								 // SetWindowPos Изменяет размер, положения и z-порядок дочернего элемента, контекстного меню
								 // и окна верхнего уровня.
								 //DestroyWindow(edit);
								 //edit = CreateWindow(L"Edit", L" ", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 20, 20, 430, 30, hwnd, NULL, hInstance, NULL);
								 // Для изменения размеров дисплея можно использовать DestroyWindow и CreateWindow вместо SetWindowPos.
								 SetWindowPos(edit, HWND_TOP, 20, 20, 430, 30, SWP_NOMOVE);
							 }

							 if (LOWORD(wParam) == ID_about_us) // Выбран пункт меню "О нас".
							 {
								 DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_About_program), hwnd, modalProcAas);
								 // Функция DialogBox создаёт модальное диалоговое окно.
								// MessageBox(NULL, L"Выбран пункт меню О нас.", L"", NULL);
							 }

							 if (LOWORD(wParam) == ID_sponsor) // Выбран пункт меню "Спонсорам".
							 {
								 //MessageBox(NULL, L"Выбран пункт меню Спонсорам.", L"", NULL);
								 nomodal_Dialog = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG_nomodal), hwnd, Dialog_nomodal_proc);
								 //ShowWindow(nomodal_Dialog, SW_SHOW);
								 ShowWindow(nomodal_Dialog, SW_SHOWNORMAL);
								 //ShowWindow(nomodal_Dialog, SW_HIDE);
							 }
							 //MessageBox(NULL, L"Щелчок", L"", NULL);
							 //if (lParam == (LPARAM)buttonOK) // (LPARAM) - Явное приведение buttonOK к LPARAM.
							 //{
							 //	 MessageBox(NULL, L"Вы нажали OK", L"", NULL);
							 // }
							 //if (lParam == (LPARAM)buttonCancel) // (LPARAM) - Явное приведение buttonCancel к LPARAM.
							 //{
							 //MessageBox(NULL, L"Вы нажали Cancel", L"", NULL);
							 //SendMessage(buttonCancel, BM_SETSTATE, TRUE, NULL);
							 //}
							 if (lParam == (LPARAM)button1)		// Нажата кнопка 1.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 // Функция SendMessage посылает синхронное сообщение указанному окну или нескольким окнам.
								 // edit - дескриптор окна-получателя.
								 // WM_GETTEXT - код сообщения. Copies the text that corresponds to a window into a buffer provided by the caller. 
								 // 10 - первый параметр сообщения. The maximum number of characters to be copied, including the terminating null character. 
								 // (LPARAM)buffer - второй параметр сообщения. A pointer to the buffer that is to receive the text. 
								 // Параметры wParam и lParam содержат дополнительную информацию, интерпретация которой
								 // зависит от кода сообщения.
								 if (wcschr(buffer, '.') == NULL)
									 // wcschr Находит символ в строке, используя текущий языковой стандарт или указанную
									 // категорию состояния преобразования LC_CTYPE.
									 // buffer - Исходная строка, завершающаяся символом NULL.
									 // , - Символ, который нужно найти.
								 {
									 if (wcslen(buffer) < 8)
										 // wcslen Получает длину строки, используя текущий или указанный языковой стандарт.
									 {
										 wcscpy(Loper, buffer);
										 // wcscpy Копирует строку.
										 // Loper - Конечная строка.
										 // buffer - Исходная строка, завершающаяся символом NULL.
										 wcscat(Loper, L"1");
										 // wcscat Дополняет строку (Appends a string).
										 // Loper - Null-terminated destination string.
										 // 1 - Null-terminated source string.
										 // L - Использование Unicode.
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"1");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }

							 }

							 if (lParam == (LPARAM)button2)		// Нажата кнопка 2.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"2");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"2");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button3)		// Нажата кнопка 3.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"3");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"3");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button4)		// Нажата кнопка 4.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"4");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"4");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button5)		// Нажата кнопка 5.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"5");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"5");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button6)		// Нажата кнопка 6.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"6");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"6");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button7)		// Нажата кнопка 7.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"7");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"7");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button8)		// Нажата кнопка 8.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"8");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"8");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button9)		// Нажата кнопка 9.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"9");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"9");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button0)		// Нажата кнопка 0.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"0");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
								 else
								 {
									 if (wcslen(buffer) < 9)
									 {
										 wcscpy(Loper, buffer);
										 wcscat(Loper, L"0");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button_point) // Нажата кнопка ,.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 // wcscpy Копирует строку.
										 wcscat(Loper, L".");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button_negative) // Нажата кнопка отрицательной величины.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcscmp(buffer, L"") == 0) // Если дисплей калькулятора пустой.
									 // wcscmp сравнивает строки расширенных символов. 0 - строки идентичны.
								 {
									 wcscpy(Loper, buffer);
									 // wcscpy Копирует строку.
									 wcscat(Loper, L"-");
									 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
								 }
								 if (wcscmp(buffer, L"-") == 0) // Если на дисплее только "-".
									 // wcscmp сравнивает строки расширенных символов. 0 - строки идентичны.
								 {
									 wcscpy(buffer, L"");
									 // wcscpy Копирует строку.
									 // buffer - Конечная строка.
									 // "" - Исходная строка, завершающаяся символом NULL.
									 // L - Использование Unicode.
									 wcscpy(Loper, buffer);
									 // wcscpy Копирует строку.
									 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
								 }
							 }

							 if (lParam == (LPARAM)buttonC)		// Нажата кнопка "очистка дисплея".
							 {
								 wcscpy(buffer, L"");
								 // wcscpy Копирует строку.
								 // buffer - Конечная строка.
								 // "" - Исходная строка, завершающаяся символом NULL.
								 // L - Использование Unicode.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)buffer);
							 }

							 if (lParam == (LPARAM)button_plus)		// Нажата кнопка +.
							 {
								 // operation = '+';
								 operation = 0;
								 wcscpy(Result, Loper);
								 // wcscpy Копирует строку.
								 // Result - Конечная строка.
								 // Loper - Исходная строка, завершающаяся символом NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // очистка дисплея.
							 }

							 if (lParam == (LPARAM)button_minus)	// Нажата кнопка -.
							 {
								 operation = 1;
								 wcscpy(Result, Loper);
								 // wcscpy Копирует строку.
								 // Result - Конечная строка.
								 // Loper - Исходная строка, завершающаяся символом NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // очистка дисплея.
							 }

							 if (lParam == (LPARAM)button_multiplication) // Нажата кнопка *.
							 {
								 operation = 3;
								 wcscpy(Result, Loper);
								 // wcscpy Копирует строку.
								 // Result - Конечная строка.
								 // Loper - Исходная строка, завершающаяся символом NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // очистка дисплея.
							 }

							 if (lParam == (LPARAM)button_division)		// Нажата кнопка /.
							 {
								 operation = 2;
								 wcscpy(Result, Loper);
								 // wcscpy Копирует строку.
								 // Result - Конечная строка.
								 // Loper - Исходная строка, завершающаяся символом NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // очистка дисплея.
							 }

							 if (lParam == (LPARAM)button_pow)	// Нажата кнопка вычисления значения х в степени y.
							 {
								 operation = 4;
								 wcscpy(Result, Loper);
								 // wcscpy Копирует строку.
								 // Result - Конечная строка.
								 // Loper - Исходная строка, завершающаяся символом NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // очистка дисплея.
							 }

							 if (lParam == (LPARAM)button_sin)	// Нажата кнопка вычисления значения синуса.
							 {
								 operation = 5;
								 //wcscpy(Result, Loper);
								 // wcscpy Копирует строку.
								 // Result - Конечная строка.
								 // Loper - Исходная строка, завершающаяся символом NULL.
								 rop = _wtof(Loper);
								 //res = _wtof(Result);
								 res = sin((double)rop);
								 wstring fres = std::to_wstring(res);
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
							 }

							 if (lParam == (LPARAM)button_cos)	// Нажата кнопка вычисления значения косинуса.
							 {
								 operation = 6;
								 rop = _wtof(Loper);
								 res = cos((double)rop);
								 wstring fres = std::to_wstring(res);
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
							 }

							 if (lParam == (LPARAM)button_tan)	// Нажата кнопка вычисления значения тангенса.
							 {
								 operation = 7;
								 rop = _wtof(Loper);
								 res = tan((double)rop);
								 wstring fres = std::to_wstring(res);
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
							 }

							 if (lParam == (LPARAM)button_sqrt)		// // Нажата кнопка вычисления положительного квадратного корня.
							 {
								 operation = 8;
								 rop = _wtof(Loper);
								 res = sqrt((double)rop);
								 wstring fres = std::to_wstring(res);
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
							 }

							 if (lParam == (LPARAM)button_result)	// Нажата кнопка =.
							 {
								 int count = 0;		// Количество нулей.
								 //for (int i = 10; i >= 0; i--)
								 //{
								 // if ('0' == Result[i - 1])
								 // {
								 //	 // count++;
								 //	 Result[i - 1] = NULL;
								 // }
								 // else
								 // {
								 //	 break;
								 // }
								 //}
								 //TCHAR* str = new TCHAR[10-count+1];
								 switch (operation)
								 {
									 //case '+':
								 case 0:		// +
									{
													res = _wtof(Result);
													rop = _wtof(Loper);
													//rop = _wtof(buffer);
													res += rop;
													wstring fres = std::to_wstring(res);
													//for (int i = 9; i > 0; i--)
													//{
														//if (L'0' == fres[i - 1]) // Нули почему-то не считаются.
														//if (L'0' == fres[i])
														//if ('0' == fres[i])
														//if (fres.c_str()[i - 1] == L'0')
														//if (fres.c_str()[i - 1] == '0')
														//if (fres.c_str()[i] == '0')
														//if (fres.c_str()[i] == L'0')
														//{
															//count++;
															//wstring nulls = std::to_wstring(count);
															//TCHAR * number_nulls = L"Количество нулей: ";
															//wcscat(number_nulls, nulls.c_str());
															//MessageBox(NULL, number_nulls, L"", NULL);
															//fres[i - 1] = NULL;
														//}
														//else
														//{
															//break;
														//}
													//}
													//TCHAR* line_result = new TCHAR[10 - count + 1];
													//for (int i = 0; i < (10 - count); i++)
													//for (int i = 0; i < (10 - count - 1); i++)
													//{
														//line_result[i] = fres.c_str()[i];
													//}
													//line_result[10 - count] = NULL;
													SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
													//wcscpy(line_result, fres.c_str());
													//SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)line_result);
													//delete[] line_result;
													//line_result = nullptr;
													// Вызов оператора delete для нулевого указателя пройдёт совершенно безболезненно для программы.
													// Лишние нули почему-то не убираются.
													break;
									}

								 case 1:		// -
									{
													res = _wtof(Result);
													rop = _wtof(Loper);
													//rop = _wtof(buffer);
													res -= rop;
													wstring fres = std::to_wstring(res);
													SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
													break;
									}

								 case 2:		// /
									{
													res = _wtof(Result);
													rop = _wtof(Loper);
													//rop = _wtof(buffer);
													res /= rop;
													wstring fres = std::to_wstring(res);
													SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
													break;
									}
								 case 3:		// *
									{
													res = _wtof(Result);
													rop = _wtof(Loper);
													//rop = _wtof(buffer);
													res *= rop;
													wstring fres = std::to_wstring(res);
													SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
													break;
									}
								 case 4:	// pow
									{
										res = _wtof(Result);
										rop = _wtof(Loper);
										res = pow((double)res, (double)rop);
										wstring fres = std::to_wstring(res);
										SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
										break;
									}
								 case 5:	// sin
									{
										//res = _wtof(Result);
										//res = sin((double)res);
										//wstring fres = std::to_wstring(res);
										//SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
										break;
									}
								 case 6:	// cos
									{
										break;
									}
								 case 7:	// tan
									{
										break;
									}
								 case 8:	// sqrt
									{
										break;
									}
								 default:
									 break;
								 }
							 }
						 }


						 break;
	}
	case WM_CLOSE:
	{
					 if (MessageBox(hwnd, L"Вы действительно хотите выйти?", L"Выход", MB_OKCANCEL) == IDCANCEL)
						 // Если пользователь отказался закрыть окно (нажал "отмена").
					 {
						 return false;
					 }
					 //MessageBox(hwnd, L"Вы действительно хотите выйти?", L"Выход", MB_OKCANCEL);
					 break;
	}
	case WM_DESTROY:	// Сообщение о том, что пользователь хочет закрыть приложение.
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

INT_PTR CALLBACK modalProcAas(
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	){

	switch (uMsg)
	{
	case WM_COMMAND:
	{
		if (HIWORD(wParam) == BN_CLICKED)	// Обработка щелчка.
		{
			//MessageBox(NULL, L"Произошёл щелчок в диалоговом окне", L"", NULL);
			if (LOWORD(wParam) == (LPARAM)IDOK) // Нажата кнопка ОК.
			{
				//MessageBox(NULL, L"Вы нажали OK", L"", NULL);
				EndDialog(hwndDlg, true);	// Функция закрывает модальное диалоговое окно.
			}
		}
	}
	case WM_CLOSE:
	{
		EndDialog(hwndDlg, true);	// Функция закрывает модальное диалоговое окно.
	}
	default:
		break;
	}

	return false;
}

INT_PTR CALLBACK Dialog_open_calculator_proc		// Обработка событий модального диалогового окна открытия калькулятора.
(
_In_ HWND   hwndDlg_open_calc,
_In_ UINT   uMsg_open_calc,
_In_ WPARAM wParam,
_In_ LPARAM lParam
)
{
	switch (uMsg_open_calc)
	{
	case WM_COMMAND:
	{
					   if (HIWORD(wParam) == BN_CLICKED)	// Обработка щелчка.
					   {
						   //MessageBox(NULL, L"Произошёл щелчок в диалоговом окне", L"", NULL);
						   if (LOWORD(wParam) == (LPARAM)IDOK) // Нажата кнопка ОК.
						   {
							   //MessageBox(NULL, L"Вы нажали OK", L"", NULL);
							   EndDialog(hwndDlg_open_calc, true);	// Функция закрывает модальное диалоговое окно.
						   }
						   else
						   {
							   return false;
						   }
					   }
	}
	case WM_CLOSE:
	{
					 EndDialog(hwndDlg_open_calc, true);	// Функция закрывает модальное диалоговое окно.
	}
	default:
		break;
	}
	return false;
}

INT_PTR CALLBACK Dialog_nomodal_proc		// Обработка событий немодального диалогового окна Спонсорам.
(
_In_ HWND   hwndDlg_nomodal,
_In_ UINT   uMsg_nomodal,
_In_ WPARAM wParam,
_In_ LPARAM lParam
)
{
	switch (uMsg_nomodal)
	{
	case WM_COMMAND:
	{
					   if (HIWORD(wParam) == BN_CLICKED)	// Обработка щелчка.
					   {
						   //MessageBox(NULL, L"Произошёл щелчок в диалоговом окне", L"", NULL);
						   if (LOWORD(wParam) == (LPARAM)IDOK) // Нажата кнопка ОК.
						   {
							   //MessageBox(NULL, L"Вы нажали OK", L"", NULL);
							   EndDialog(hwndDlg_nomodal, true);	// Функция закрывает модальное диалоговое окно.
						   }
					   }
	}
	case WM_CLOSE:
	{
					 EndDialog(hwndDlg_nomodal, true);	// Функция закрывает модальное диалоговое окно.
	}
	default:
		break;
	}
	return false;
}