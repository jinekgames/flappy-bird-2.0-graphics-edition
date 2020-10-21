#include <windows.h>

#include "GameMain.h"
#include <math.h>

//Функция координаты высоты главного объекта
double GameProc::height(double vv, double yy) {
	yy = yy + vv * t + G_ACCELERATION * t * t / 2;
	return yy;
}

//Функция скорости главного объекта
double GameProc::speed(double vv, double yy) {
	vv = vv + G_ACCELERATION * t;
	return vv;
}

//Правила
void GameProc::rule() {
	if (x - xwall + MAIN_OBJ_SIZE >= 0 && x - xwall <= WALLSIZE && (y < ywall || y + MAIN_OBJ_SIZE >= ywall + WINWALL))	//Завершение игры при столкновении со стеной
		game_run = false;

	else if (x > xwall + WALLSIZE && !wallScored)	//Засчитывание очка
	{
		score++;
		wallScored = true;
	}

	if (y < 0)	//Ограничение высоты верхней границей поля
	{
		y = 0;
		v = 0;
	}

	if (y > Y - MAIN_OBJ_SIZE) //Отскок объекта от нижней границы
	{
		v = v * (-1) * ( rand() % 65 + 35 );
		v /= 100;
		y = Y - MAIN_OBJ_SIZE;
	}
}

//Спавн стены раз в WALLSTEP кадров
void GameProc::wall() {
	if (xwall < -WALLSIZE - 20 && tim > 0) {
		xwall = X;								//на правом крае поля
		ywall = rand() % (int)(Y - WINWALL - WINWALL_DOWNSPACE); //с окном в рандомном месте
		wallScored = false;
	}
}



//Координаты главного объекта
POINT GameProc::objectCoords() {
	POINT res = { x, y };
	return res;
}

//Координаты стены
POINT GameProc::wallCoords() {
	POINT res = { xwall, ywall };
	return res;
}

//Обработка прыжка
void GameProc::jump() {
	v = - JUMP_SPEED;
}

//Просчет вообще всего  (возвращает состояние игры)
bool GameProc::proc() {
	rule();
	wall();	
	xwall -= WALLSPEED;
	y = height(v, y);
	v = speed(v, y);
	tim++; //Обновление счетчика кадров

	//if (!game_run) {
	//	int rec = inputScore();
	//	if (rec < score) {
	//		outputScore(score);
	//	}
	//}

	return game_run;
}

//Обнуление (возвращает состояние игры)
bool GameProc::restart() {
	y = 0.0;					//Возвращение объекта
	tim = 0;					//Обнуление счетчика кадров
	xwall = -(WALLSIZE + 1);	//Возвращение стены на исходную позицию
	game_run = true;			//Задание переменной начала игры значания НЕТ
	score = 0;					//Обнуление очков
	wallScored = true;			//тоже обнуление
	
	return game_run;
}

//Получение набранных очков
int GameProc::getScore() {
	return score;
}

////Получение рекорда из файла
//int GameProc::getRecord() {
//	return inputScore();
//}