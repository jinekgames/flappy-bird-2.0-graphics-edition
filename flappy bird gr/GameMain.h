#pragma once

//#include "ScoreIO.h"

//функция, необходимые для функции игры

//Время между спавнами стен
#define WALLTIME 400
//Скорость движения препятствия
#define WALLSPEED 2.0
//Высота окна в стене
#define WINWALL 200.0
//Толщина стены
#define WALLSIZE 50.0
//Ускорение свободного падения
#define G_ACCELERATION 5.81
//Размер главного объекта
#define MAIN_OBJ_SIZE 20.0
//Скорость сразу после прыжка
#define JUMP_SPEED 50.0
//Отступ снизу спавна окна в стене
#define WINWALL_DOWNSPACE 300.0

class GameProc {
	//условие работы игры
	bool game_run = false;
	//Количество отрисованных кадров
	int tim = 0;

	//Размеры поля
	double Y = 800, X = 600;
	//Время, которое проходит между двумя кадрами в сек
	const double t = 0.2;

	//Скорость
	double v = 0.0;

	//Высота главного объекта
	double y = 0.0;
	//Положение главного объекта
	double x = 10;

	//Координата X стены
	double xwall;
	//Положение окна в стене
	double ywall = 0;

	//Набранные очки
	int score = 0;
	//Прохождение препятствия
	bool wallScored = true;


	//Конструкторы и деструкторы//
public:

	GameProc() {
		xwall = -(WALLSIZE + 1);
		//getDirectory();
	}
	GameProc(double xGameZoneSize, double yGameZoneSize) {
		X = xGameZoneSize;
		Y = yGameZoneSize;
		xwall = -(WALLSIZE + 1);
		//getDirectory();
	}

	//Вунтренние методы класса//
private:

	//Функция координаты высоты главного объекта
	double height(double vv, double yy);
	//Функция скорости главного объекта
	double speed(double vv, double yy);
	//Правила
	void rule();
	//Спавн стены раз в WALLSTEP кадров
	void wall();


	//Для пользователя//
public:

	//Координаты главного объекта
	POINT objectCoords();
	//Координаты стены
	POINT wallCoords();
	//Обработка прыжка
	void jump();
	//Просчет вообще всего (возвращает состояние игры)
	bool proc();
	//Обнуление (возвращает состояние игры)
	bool restart();
	//Получение набранных очков
	int getScore();
	//Получение рекорда из файла
	//int getRecord();
};
