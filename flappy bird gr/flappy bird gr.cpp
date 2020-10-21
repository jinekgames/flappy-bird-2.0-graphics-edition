﻿// flappy bird gr.cpp : Defines the entry point for the application.
//

#pragma warning(disable : 4996)

#define WIN32_LEAN_AND_MEAN	//Чтобы юзать именно Windows SDK

#include "framework.h"
#include "GameMain.h"
#include "resource.h"

#define SLEEP_TIMEOUT 8

#define WINDOWS_CLASS_NAME L"JNK_PROG"

#define WINDOW_SIZE_X 450
#define WINDOW_SIZE_Y 800

#define RAND_MSG_SPAWN_SPEED 1

#define PHONK_PLAY TRUE

//Инициализация класса для вычислений игры
GameProc game(WINDOW_SIZE_X, WINDOW_SIZE_Y);
//Запуск программы
bool onStart = true;
//Состояние игры
bool gameState = false;
//Пауза
bool pause = false;

//Стостояние клавиши пробела
bool spaceKeyDown = false;
//Стостояние клавиши Esc
bool escKeyDown = false;

//Счетчик числа вызовов WM_PAINT
int drawCallNum = 0;

//Счетчик главного цикла
int winCycleNum = 0;

//Текущие размеры окна
int windowCurSizeX = WINDOW_SIZE_X, windowCurSizeY = WINDOW_SIZE_Y;

//Положение курсора
POINT cursorCoords;
//Положение окна
POINT windowCoords;

//Триггер проигрывания фонка
bool phonkPlay = PHONK_PLAY;

HINSTANCE hinstance_app;


//Обработчик событий окна
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps; //Для WM_PAINT
	HDC hdc;		//Дескриптор контекста устройства

	//Обработка
	switch (msg)
	{
	case WM_CREATE:	//Инициализация
	{
		if (phonkPlay) {
			PlaySound(MAKEINTRESOURCE(WAV_PHONK), hinstance_app, SND_ASYNC | SND_LOOP | SND_RESOURCE);
		}
		return 0;
	} break;
	case WM_MOVE:
	{
		windowCoords.x = LOWORD(lparam);
		windowCoords.y = HIWORD(lparam);
		return 0;
	} break;
	case WM_SIZE:
	{
		windowCurSizeX = LOWORD(lparam);
		windowCurSizeY = HIWORD(lparam);
		return 0;
	} break;
	case WM_MOUSEMOVE:
	{
		cursorCoords.x = LOWORD(lparam);
		cursorCoords.y = HIWORD(lparam);
		return 0;
	} break;
	case WM_KEYDOWN:
	{
		switch (wparam)
		{
			case VK_SPACE:
			{
				if (!spaceKeyDown) {
					spaceKeyDown = TRUE;
					if (gameState) {
						game.jump();
					} else {
						onStart = FALSE;
						gameState = game.restart();
						pause = FALSE;
					}
				}
			} break;
			case VK_ESCAPE:
			{
				if (!escKeyDown) {
					escKeyDown = TRUE;
					if (!pause && gameState) {
						pause = TRUE;
					} else {
						pause = FALSE;
					}
				}
			} break;
		}
		return 0;
	} break;
	case WM_KEYUP:
	{
		switch (wparam)
		{
			case VK_SPACE:
			{
				spaceKeyDown = FALSE;
			} break;
			case VK_ESCAPE:
			{
				escKeyDown = FALSE;
			} break;
		}
		return 0;
	} break;
	case WM_PAINT:	//Обновление
	{
		drawCallNum++;

		//Объявление всего окна недействительным
		InvalidateRect(hwnd, NULL, TRUE);


		hdc = BeginPaint(hwnd, &ps);

		//перерисовка окна

		//отрисовка движущихся объектов игры
		if (gameState) {
			//отрисовка главного объекта
			POINT mainObj = game.objectCoords();
			HBRUSH red_brush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, red_brush);
			Ellipse(hdc, mainObj.x, mainObj.y, mainObj.x + MAIN_OBJ_SIZE, mainObj.y + MAIN_OBJ_SIZE);
			DeleteObject(red_brush);

			//открисовка препятствия
			POINT wallObj = game.wallCoords();
			HBRUSH blue_brush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, blue_brush);
			Rectangle(hdc, wallObj.x, -1, wallObj.x + WALLSIZE, wallObj.y);
			Rectangle(hdc, wallObj.x, wallObj.y + WINWALL, wallObj.x + WALLSIZE, WINDOW_SIZE_Y);
			DeleteObject(blue_brush);
		}

		//Отрисовка надписи при запуске игры
		if (onStart) {
			HFONT hFont = CreateFont(60, 23, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
			SelectObject(hdc, hFont);

			RECT rect = { windowCurSizeX / 6, windowCurSizeY / 6, windowCurSizeX * 5 / 6, windowCurSizeY };
			SetTextColor(hdc, RGB(0, 0, 255));
			DrawText(hdc, TEXT("press SPACE\nto Start"), -1, &rect, DT_NOCLIP | DT_CENTER);
			DeleteObject(hFont);
		}

		//Отрисовка надписи при проигрыше
		else if (!gameState) {
			HFONT hFont = CreateFont(60, 23, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
			SelectObject(hdc, hFont);

			RECT rect = { windowCurSizeX / 6, windowCurSizeY / 6, windowCurSizeX * 5 / 6, windowCurSizeY };
			SetTextColor(hdc, RGB(0, 0, 255));
			DrawText(hdc, TEXT("GAME OVER"), -1, &rect, DT_NOCLIP | DT_CENTER);
			DeleteObject(hFont);
		}

		//Отрисовка надписи при паузе
		else if (pause) {
			HFONT hFont = CreateFont(90, 42, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
			SelectObject(hdc, hFont);

			RECT rect = { windowCurSizeX / 6, windowCurSizeY / 6, windowCurSizeX * 5 / 6, windowCurSizeY };
			SetTextColor(hdc, RGB(0, 0, 255));
			DrawText(hdc, TEXT("PAUSE"), -1, &rect, DT_NOCLIP | DT_CENTER);
			DeleteObject(hFont);
		}

		//Открисовка очков
		if (!pause && !onStart) {
			HFONT hFont = CreateFont(72, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
			SelectObject(hdc, hFont);

			RECT rect = { windowCurSizeX / 6, 25, windowCurSizeX * 5 / 6, windowCurSizeY };
			SetTextColor(hdc, RGB(0, 0, 255));
			char buf[11];
			SetBkMode(hdc, TRANSPARENT);
			DrawTextA(hdc, itoa(game.getScore(), buf, 10), -1, &rect, DT_NOCLIP | DT_CENTER);
			DeleteObject(hFont);
		}

		EndPaint(hwnd, &ps);

		return 0;
	} break;
	case WM_DESTROY:	//Закрытие
	{
		PlaySound(NULL, hinstance_app, SND_PURGE);
		PostQuitMessage(0);
		return 0;
	} break;
	case WM_COMMAND:
	{
		switch LOWORD(wparam)
		{
			case MENU_PHONK:
			{
				phonkPlay = !phonkPlay;
				PlaySound((phonkPlay) ? MAKEINTRESOURCE(WAV_PHONK) : NULL, hinstance_app, (phonkPlay) ? SND_ASYNC | SND_LOOP | SND_RESOURCE : NULL);

			} break;
			default:
				break;
		}
	} break;
	case WM_CLOSE:
	{
		//Подтверждение выхода
		if (MessageBox(hwnd, L"До связи бро", L" ", MB_YESNO) == IDYES) {
			//Воспроизведение приятного звука закрытия программы
			PlaySound(MAKEINTRESOURCE(WAV_APP_CLOSE), hinstance_app, SND_ASYNC | SND_RESOURCE);
			//Выведение рандомных пикселей на экран
			for (int i = 0; i < 100; i++) {
				const int rad = 100;
				int pixelX = rand() % windowCurSizeX / rad * rad,
					pixelY = rand() % windowCurSizeY / rad * rad;
				COLORREF pixelCol = RGB(rand() % 256, rand() % 256, rand() % 256);
				RECT rect = { pixelX, pixelY, pixelX + rad, pixelY + rad };
				HDC hdc1 = GetDC(hwnd);
				FillRect(hdc1, &rect, CreateSolidBrush(pixelCol));
				ReleaseDC(hwnd, hdc1);
				Sleep(20);
			}
			//Вызов обработчика по умолчанию
			return SendMessage(hwnd, WM_DESTROY, 0, 0);
		} else {
			return 0;
		}
	} break;
	default:
		break;
	}

	return(DefWindowProc(hwnd, msg, wparam, lparam));	//Для обработки останого
}

int GameMain(HINSTANCE hinstance, HWND hwnd) {
	WCHAR start[256];

	//ФИЗИКА
	if (gameState && !pause) {
		gameState = game.proc();
	}


	//ГРАФИКА
	//отправление вызова WM_PAINT в очередь
	SendMessage(hwnd, WM_PAINT, 0, 0);
	
	//Синхронизация до ~60 фпс ( 1000 мс / 60 = 16.6(6) мс )
	Sleep(SLEEP_TIMEOUT);

	return 0;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	srand(time(0));

	//eбашу окно
	WNDCLASSEX winclass = {
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS,
		WinProc,
		0,
		0,
		hinstance,
		LoadIcon(hinstance, MAKEINTRESOURCE(ICO_MYICON)),
		LoadCursor(hinstance, MAKEINTRESOURCE(CUR_MYCUR)),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		MAKEINTRESOURCE(MAIN_MENU),
		WINDOWS_CLASS_NAME,
		LoadIcon(hinstance, MAKEINTRESOURCE(ICO_MYICON))
	};

	//Дескриптор окна
	HWND hwnd;
	MSG msg;

	hinstance_app = hinstance;	//Сохранение дескриптора процесса в глобальной переменной для использования в WinProc()

	RegisterClassEx(&winclass);

	if (!(hwnd = CreateWindowEx(NULL,
		WINDOWS_CLASS_NAME,
		L"jinek_games Flappy_Bird 2.0",
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX | WS_VISIBLE,
		1000, 100, WINDOW_SIZE_X, WINDOW_SIZE_Y,
		NULL, NULL,
		hinstance, NULL
	))) return 0;


	while (true)
	{
		winCycleNum++;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)	break;	//Проверка сообщения о выходе
			TranslateMessage(&msg);	//Преобразование клавиатурного ввода
			DispatchMessage(&msg);	//Пересылка сообщения WinProc
		}

		//Выполнение игры
		GameMain(hinstance, hwnd);
	}

	return msg.wParam;
}
