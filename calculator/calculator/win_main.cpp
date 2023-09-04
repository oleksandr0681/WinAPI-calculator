// �����������.

#include <windows.h>
#include <Windowsx.h>
#include <tchar.h>
#include <string>
#include "resource.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// �������� �������. CALLBACK 
INT_PTR CALLBACK modalProcAas(	// �������� ������� ���������� ����������� ���� "� ���������".
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	);

INT_PTR CALLBACK Dialog_open_calculator_proc		// �������� ������� ���������� ����������� ���� �������� ������������.
	(
	_In_ HWND   hwndDlg_open_calc,
	_In_ UINT   uMsg_open_calc,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	);

INT_PTR CALLBACK Dialog_nomodal_proc		// �������� ������� ������������ ����������� ���� ���������.
(
_In_ HWND   hwndDlg_nomodal,
_In_ UINT   uMsg_nomodal,
_In_ WPARAM wParam,
_In_ LPARAM lParam
);

void CALLBACK timerProc(HWND hwnd, UINT msg_timer, UINT_PTR timer2); // �������� ������� ��������� ������� 2.

// WndProc - ��� ������� ������������ �������������� ���������, ������� ���������� �������� �� ������������ �������.
//--------------------------------------------------------------------------------------------------------------------------------
HINSTANCE hInstance;
HWND hwnd; // HWND - ����������.
HWND button1; // ������ 1.
HWND button2; // ������ 2.
HWND button3; // ������ 3.
HWND button4; // ������ 4.
HWND button5; // ������ 5.
HWND button6; // ������ 6.
HWND button7; // ������ 7.
HWND button8; // ������ 8.
HWND button9; // ������ 9.
HWND button0; // ������ 0.
HWND button_plus; // ������ +.
HWND button_minus; // ������ -.
HWND button_multiplication; // ������ *.
HWND button_division; // ������ /.
HWND button_result; // ������ =.
HWND button_point; // ������ ,.
HWND buttonCancel;	// ������ "������".
HWND buttonC; // ������ "������� �������".
HWND buttonAC; // ������ "������� ������".
HWND button_pow; // ������ ���������� �������� � � ������� y.
HWND button_sin; // ������ ���������� �������� ������. ���� ����������� � �������x.
HWND button_cos; // ������ ���������� �������� ��������. ���� ����������� � �������x.
HWND button_tan; // ������ ���������� �������� ��������. ���� ����������� � �������x.
HWND button_sqrt; // ������ ���������� �������������� ����������� �����.
HWND button_negative; // ������ ������������� ��������.
HWND edit; // ������� ������������.
HWND nomodal_Dialog; // ���������� ������������ ����������� ����.
HMENU hMenu; // ������������� ����.
TCHAR Loper[10]; // ������� ��� �������� ������ ��������.
//TCHAR Roper[10]; // ������� ��� �������� ������� ��������.
TCHAR Result[10]; // ������� ��� �������� ����������.
TCHAR buffer[10];
//char operation; // ���������� ��� �������� ������� ������ ��������.
int operation = -1;		// ���������� ��� �������� ������� ������ ��������.
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
UINT_PTR timer1; // ������ 1.
UINT_PTR timer2; // ������ 2.
int tsecond = 0;
//--------------------------------------------------------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) // ����� ����� � ���������.
// WinMain - �������� ����� ����� � ���������.
// _hInstance - ���������� ��� ���������.
// hPrevInstance - ��� ������������� ����������.
// PSTR - ��������� �� ������.
// iCmdShow - ������������� ����������, ������� �������� 

{
	HINSTANCE hInstance = _hInstance; // hInstance 
	MSG msg;	// msg - ���������, ������� ��������� ��������� ��������� �����.
	WNDCLASSEX wndclass;	// wndclass - ����� (���������) ����.
	wndclass.cbSize = sizeof(wndclass);		// cbSize 
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	// CS_HREDRAW, CS_VREDRAW
	wndclass.lpfnWndProc = WndProc;		// lpfnWndProc - ��������� �� ������� CALLBACK WndProc.
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance; // ������� ���������� ��� ���������� � �����, ������� ��������� ���� ����������.
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// hIcon - ������.
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);		// ������.
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ���� ���� ����������.
	wndclass.lpszMenuName = NULL;	// ������� ��������� �� ������� ����.
	wndclass.lpszClassName = L"znoReg";		// znoReg ���������� �������� ������.
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);		// ��������� ������.

	if (!RegisterClassEx(&wndclass))	// ������� ���������� ����������� ������ (���������).
	{
		MessageBox(hwnd, L"�� ������� ���������������� ����� ����", L"������ ����������� ������ ����", MB_OK);
		return 0;
	}
	//������������� ������ ����------------------------------------------------------------------------------------------------end
	hwnd = CreateWindow(	// ������� ������ �� (�� ������ ����, �� � ������ � �.�.). //CreateWindowEX
		// CreateWindowA, CreateWindowW
		// hwnd - ���������� ���������� (���������) ����������.
		wndclass.lpszClassName,
		L"�����������",	// ��� ����. L - ������������� Unicode.
		WS_OVERLAPPEDWINDOW^WS_THICKFRAME | WS_MAXIMIZEBOX | WS_SYSMENU, // WS_OVERLAPPEDWINDOW - ����������� ���������.
		// ^WS_THICKFRAME ��������� WS_THICKFRAME �� WS_OVERLAPPEDWINDOW.
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		345,
		300,
		NULL,
		NULL, // ��������� �� ����.
		hInstance, // ���������� ������������� ����������.
		NULL	// plParam -
		);
	if (!hwnd)
	{
		MessageBox(hwnd, L"�� ������� ������� ��������� ����", L"������ �������� ���������� ����", MB_OK);
		return 0;
	}
	ShowWindow(hwnd, iCmdShow);		// �������� ����.

	UpdateWindow(hwnd);		// ������������ ����.
	while (GetMessage(&msg, NULL, 0, 0))	// ��������� ���������.
	{
		TranslateMessage(&msg);		// 
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)	// hwnd - ���������� ����������.
// iMsg - ��� �������. wParam, lParam - ���������.
{
	switch (iMsg)
	{
	case WM_CREATE: { // �������� ����.
						//MessageBox(NULL, L"����������� ��� ������, �� �� ������� �� ������.", L"", NULL);
						//DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_open_calculator), hwnd, Dialog_open_calculator_proc);
						// Edit Control ������-�� �� ��������.
						hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));	// ������������� ����.
						SetMenu(hwnd, hMenu);
						CheckMenuItem(hMenu, ID_standard, MF_CHECKED);
						//CheckMenuItem();
						edit = CreateWindow(L"Edit", L" ", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 20, 20, 290, 30, hwnd, NULL, hInstance, NULL);
						//SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)L"����"); // (LPARAM) - ����� ���������� ����.
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
						SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // ������� ������� (����� ������ ������������� �������� �������� ����� ����� ��������� ������������).
						// buttonCancel = CreateWindow(L"Button", L"Cancel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 10, 100, 30, hwnd, NULL, hInstance, NULL);
						//ShowWindow(hwnd, SW_HIDE);
						SetTimer(hwnd, timer1, 5000, NULL); // ������ �������. ������ �� ����� �������� � ������� ������� ���������.
						break;
	}
	case WM_TIMER:	// ��������� �������.
	{
					 if (wParam == timer1)
					 {
						 tsecond++;
						 //MessageBox(NULL, L"5 ������", L"", NULL);
						 if (tsecond >= 6)
						 {
							 KillTimer(hwnd, timer1); // ������ �������.
							 //SetTimer(hwnd, timer2, 1000, timerProc);		// ������ �������. ������ �������. ������ �� ����� �������� � ������� ������� ���������.
							 MessageBox(NULL, L"������ 30 ������", L"", NULL);
						 }
						 break;
					 }
	}
	case WM_COMMAND: // 
	{
						 if (HIWORD(wParam) == BN_CLICKED)	// ��������� ������.
						 {
							 if (LOWORD(wParam) == ID_exit) // ������ ����� ���� "�����".
							 {
								 DestroyWindow(hwnd);
							 }

							 if (LOWORD(wParam) == ID_standard) // ������ ����� ���� "�������".
							 {
								 //MessageBox(NULL, L"������ ����� ���� �������.", L"", NULL);
								 CheckMenuItem(hMenu, ID_standard, MF_CHECKED);
								 CheckMenuItem(hMenu, ID_engineer, MF_UNCHECKED);
								 SetWindowPos(hwnd, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, 345, 300, SWP_NOMOVE | SWP_DRAWFRAME);
								 // SetWindowPos �������� ������, ��������� � z-������� ��������� ��������, ������������ ����
								 // � ���� �������� ������.
								 DestroyWindow(edit);
								 edit = CreateWindow(L"Edit", L" ", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 20, 20, 290, 30, hwnd, NULL, hInstance, NULL);
								 // ��� ��������� �������� ������� ����� ������������ SetWindowPos ������ DestroyWindow � CreateWindow.
								 //SetWindowPos(edit, HWND_TOP, 20, 20, 290, 30, SWP_NOMOVE);
							 }

							 if (LOWORD(wParam) == ID_engineer) // ������ ����� ���� "����������".
							 {
								 //MessageBox(NULL, L"������ ����� ���� ����������.", L"", NULL);
								 CheckMenuItem(hMenu, ID_standard, MF_UNCHECKED);
								 CheckMenuItem(hMenu, ID_engineer, MF_CHECKED);
								 SetWindowPos(hwnd, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, 485, 300, SWP_NOMOVE | SWP_DRAWFRAME);
								 // SetWindowPos �������� ������, ��������� � z-������� ��������� ��������, ������������ ����
								 // � ���� �������� ������.
								 //DestroyWindow(edit);
								 //edit = CreateWindow(L"Edit", L" ", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 20, 20, 430, 30, hwnd, NULL, hInstance, NULL);
								 // ��� ��������� �������� ������� ����� ������������ DestroyWindow � CreateWindow ������ SetWindowPos.
								 SetWindowPos(edit, HWND_TOP, 20, 20, 430, 30, SWP_NOMOVE);
							 }

							 if (LOWORD(wParam) == ID_about_us) // ������ ����� ���� "� ���".
							 {
								 DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_About_program), hwnd, modalProcAas);
								 // ������� DialogBox ������ ��������� ���������� ����.
								// MessageBox(NULL, L"������ ����� ���� � ���.", L"", NULL);
							 }

							 if (LOWORD(wParam) == ID_sponsor) // ������ ����� ���� "���������".
							 {
								 //MessageBox(NULL, L"������ ����� ���� ���������.", L"", NULL);
								 nomodal_Dialog = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG_nomodal), hwnd, Dialog_nomodal_proc);
								 //ShowWindow(nomodal_Dialog, SW_SHOW);
								 ShowWindow(nomodal_Dialog, SW_SHOWNORMAL);
								 //ShowWindow(nomodal_Dialog, SW_HIDE);
							 }
							 //MessageBox(NULL, L"������", L"", NULL);
							 //if (lParam == (LPARAM)buttonOK) // (LPARAM) - ����� ���������� buttonOK � LPARAM.
							 //{
							 //	 MessageBox(NULL, L"�� ������ OK", L"", NULL);
							 // }
							 //if (lParam == (LPARAM)buttonCancel) // (LPARAM) - ����� ���������� buttonCancel � LPARAM.
							 //{
							 //MessageBox(NULL, L"�� ������ Cancel", L"", NULL);
							 //SendMessage(buttonCancel, BM_SETSTATE, TRUE, NULL);
							 //}
							 if (lParam == (LPARAM)button1)		// ������ ������ 1.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 // ������� SendMessage �������� ���������� ��������� ���������� ���� ��� ���������� �����.
								 // edit - ���������� ����-����������.
								 // WM_GETTEXT - ��� ���������. Copies the text that corresponds to a window into a buffer provided by the caller. 
								 // 10 - ������ �������� ���������. The maximum number of characters to be copied, including the terminating null character. 
								 // (LPARAM)buffer - ������ �������� ���������. A pointer to the buffer that is to receive the text. 
								 // ��������� wParam � lParam �������� �������������� ����������, ������������� �������
								 // ������� �� ���� ���������.
								 if (wcschr(buffer, '.') == NULL)
									 // wcschr ������� ������ � ������, ��������� ������� �������� �������� ��� ���������
									 // ��������� ��������� �������������� LC_CTYPE.
									 // buffer - �������� ������, ������������� �������� NULL.
									 // , - ������, ������� ����� �����.
								 {
									 if (wcslen(buffer) < 8)
										 // wcslen �������� ����� ������, ��������� ������� ��� ��������� �������� ��������.
									 {
										 wcscpy(Loper, buffer);
										 // wcscpy �������� ������.
										 // Loper - �������� ������.
										 // buffer - �������� ������, ������������� �������� NULL.
										 wcscat(Loper, L"1");
										 // wcscat ��������� ������ (Appends a string).
										 // Loper - Null-terminated destination string.
										 // 1 - Null-terminated source string.
										 // L - ������������� Unicode.
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

							 if (lParam == (LPARAM)button2)		// ������ ������ 2.
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

							 if (lParam == (LPARAM)button3)		// ������ ������ 3.
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

							 if (lParam == (LPARAM)button4)		// ������ ������ 4.
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

							 if (lParam == (LPARAM)button5)		// ������ ������ 5.
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

							 if (lParam == (LPARAM)button6)		// ������ ������ 6.
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

							 if (lParam == (LPARAM)button7)		// ������ ������ 7.
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

							 if (lParam == (LPARAM)button8)		// ������ ������ 8.
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

							 if (lParam == (LPARAM)button9)		// ������ ������ 9.
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

							 if (lParam == (LPARAM)button0)		// ������ ������ 0.
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

							 if (lParam == (LPARAM)button_point) // ������ ������ ,.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcschr(buffer, '.') == NULL)
								 {
									 if (wcslen(buffer) < 8)
									 {
										 wcscpy(Loper, buffer);
										 // wcscpy �������� ������.
										 wcscat(Loper, L".");
										 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
									 }
								 }
							 }

							 if (lParam == (LPARAM)button_negative) // ������ ������ ������������� ��������.
							 {
								 SendMessage(edit, WM_GETTEXT, 10, (LPARAM)buffer);
								 if (wcscmp(buffer, L"") == 0) // ���� ������� ������������ ������.
									 // wcscmp ���������� ������ ����������� ��������. 0 - ������ ���������.
								 {
									 wcscpy(Loper, buffer);
									 // wcscpy �������� ������.
									 wcscat(Loper, L"-");
									 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
								 }
								 if (wcscmp(buffer, L"-") == 0) // ���� �� ������� ������ "-".
									 // wcscmp ���������� ������ ����������� ��������. 0 - ������ ���������.
								 {
									 wcscpy(buffer, L"");
									 // wcscpy �������� ������.
									 // buffer - �������� ������.
									 // "" - �������� ������, ������������� �������� NULL.
									 // L - ������������� Unicode.
									 wcscpy(Loper, buffer);
									 // wcscpy �������� ������.
									 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)Loper);
								 }
							 }

							 if (lParam == (LPARAM)buttonC)		// ������ ������ "������� �������".
							 {
								 wcscpy(buffer, L"");
								 // wcscpy �������� ������.
								 // buffer - �������� ������.
								 // "" - �������� ������, ������������� �������� NULL.
								 // L - ������������� Unicode.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)buffer);
							 }

							 if (lParam == (LPARAM)button_plus)		// ������ ������ +.
							 {
								 // operation = '+';
								 operation = 0;
								 wcscpy(Result, Loper);
								 // wcscpy �������� ������.
								 // Result - �������� ������.
								 // Loper - �������� ������, ������������� �������� NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // ������� �������.
							 }

							 if (lParam == (LPARAM)button_minus)	// ������ ������ -.
							 {
								 operation = 1;
								 wcscpy(Result, Loper);
								 // wcscpy �������� ������.
								 // Result - �������� ������.
								 // Loper - �������� ������, ������������� �������� NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // ������� �������.
							 }

							 if (lParam == (LPARAM)button_multiplication) // ������ ������ *.
							 {
								 operation = 3;
								 wcscpy(Result, Loper);
								 // wcscpy �������� ������.
								 // Result - �������� ������.
								 // Loper - �������� ������, ������������� �������� NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // ������� �������.
							 }

							 if (lParam == (LPARAM)button_division)		// ������ ������ /.
							 {
								 operation = 2;
								 wcscpy(Result, Loper);
								 // wcscpy �������� ������.
								 // Result - �������� ������.
								 // Loper - �������� ������, ������������� �������� NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // ������� �������.
							 }

							 if (lParam == (LPARAM)button_pow)	// ������ ������ ���������� �������� � � ������� y.
							 {
								 operation = 4;
								 wcscpy(Result, Loper);
								 // wcscpy �������� ������.
								 // Result - �������� ������.
								 // Loper - �������� ������, ������������� �������� NULL.
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)""); // ������� �������.
							 }

							 if (lParam == (LPARAM)button_sin)	// ������ ������ ���������� �������� ������.
							 {
								 operation = 5;
								 //wcscpy(Result, Loper);
								 // wcscpy �������� ������.
								 // Result - �������� ������.
								 // Loper - �������� ������, ������������� �������� NULL.
								 rop = _wtof(Loper);
								 //res = _wtof(Result);
								 res = sin((double)rop);
								 wstring fres = std::to_wstring(res);
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
							 }

							 if (lParam == (LPARAM)button_cos)	// ������ ������ ���������� �������� ��������.
							 {
								 operation = 6;
								 rop = _wtof(Loper);
								 res = cos((double)rop);
								 wstring fres = std::to_wstring(res);
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
							 }

							 if (lParam == (LPARAM)button_tan)	// ������ ������ ���������� �������� ��������.
							 {
								 operation = 7;
								 rop = _wtof(Loper);
								 res = tan((double)rop);
								 wstring fres = std::to_wstring(res);
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
							 }

							 if (lParam == (LPARAM)button_sqrt)		// // ������ ������ ���������� �������������� ����������� �����.
							 {
								 operation = 8;
								 rop = _wtof(Loper);
								 res = sqrt((double)rop);
								 wstring fres = std::to_wstring(res);
								 SendMessage(edit, WM_SETTEXT, NULL, (LPARAM)fres.c_str());
							 }

							 if (lParam == (LPARAM)button_result)	// ������ ������ =.
							 {
								 int count = 0;		// ���������� �����.
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
														//if (L'0' == fres[i - 1]) // ���� ������-�� �� ���������.
														//if (L'0' == fres[i])
														//if ('0' == fres[i])
														//if (fres.c_str()[i - 1] == L'0')
														//if (fres.c_str()[i - 1] == '0')
														//if (fres.c_str()[i] == '0')
														//if (fres.c_str()[i] == L'0')
														//{
															//count++;
															//wstring nulls = std::to_wstring(count);
															//TCHAR * number_nulls = L"���������� �����: ";
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
													// ����� ��������� delete ��� �������� ��������� ������ ���������� ������������� ��� ���������.
													// ������ ���� ������-�� �� ���������.
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
					 if (MessageBox(hwnd, L"�� ������������� ������ �����?", L"�����", MB_OKCANCEL) == IDCANCEL)
						 // ���� ������������ ��������� ������� ���� (����� "������").
					 {
						 return false;
					 }
					 //MessageBox(hwnd, L"�� ������������� ������ �����?", L"�����", MB_OKCANCEL);
					 break;
	}
	case WM_DESTROY:	// ��������� � ���, ��� ������������ ����� ������� ����������.
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
		if (HIWORD(wParam) == BN_CLICKED)	// ��������� ������.
		{
			//MessageBox(NULL, L"��������� ������ � ���������� ����", L"", NULL);
			if (LOWORD(wParam) == (LPARAM)IDOK) // ������ ������ ��.
			{
				//MessageBox(NULL, L"�� ������ OK", L"", NULL);
				EndDialog(hwndDlg, true);	// ������� ��������� ��������� ���������� ����.
			}
		}
	}
	case WM_CLOSE:
	{
		EndDialog(hwndDlg, true);	// ������� ��������� ��������� ���������� ����.
	}
	default:
		break;
	}

	return false;
}

INT_PTR CALLBACK Dialog_open_calculator_proc		// ��������� ������� ���������� ����������� ���� �������� ������������.
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
					   if (HIWORD(wParam) == BN_CLICKED)	// ��������� ������.
					   {
						   //MessageBox(NULL, L"��������� ������ � ���������� ����", L"", NULL);
						   if (LOWORD(wParam) == (LPARAM)IDOK) // ������ ������ ��.
						   {
							   //MessageBox(NULL, L"�� ������ OK", L"", NULL);
							   EndDialog(hwndDlg_open_calc, true);	// ������� ��������� ��������� ���������� ����.
						   }
						   else
						   {
							   return false;
						   }
					   }
	}
	case WM_CLOSE:
	{
					 EndDialog(hwndDlg_open_calc, true);	// ������� ��������� ��������� ���������� ����.
	}
	default:
		break;
	}
	return false;
}

INT_PTR CALLBACK Dialog_nomodal_proc		// ��������� ������� ������������ ����������� ���� ���������.
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
					   if (HIWORD(wParam) == BN_CLICKED)	// ��������� ������.
					   {
						   //MessageBox(NULL, L"��������� ������ � ���������� ����", L"", NULL);
						   if (LOWORD(wParam) == (LPARAM)IDOK) // ������ ������ ��.
						   {
							   //MessageBox(NULL, L"�� ������ OK", L"", NULL);
							   EndDialog(hwndDlg_nomodal, true);	// ������� ��������� ��������� ���������� ����.
						   }
					   }
	}
	case WM_CLOSE:
	{
					 EndDialog(hwndDlg_nomodal, true);	// ������� ��������� ��������� ���������� ����.
	}
	default:
		break;
	}
	return false;
}