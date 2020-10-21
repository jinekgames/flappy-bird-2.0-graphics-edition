#include <windows.h>

#include "GameMain.h"
#include <math.h>

//������� ���������� ������ �������� �������
double GameProc::height(double vv, double yy) {
	yy = yy + vv * t + G_ACCELERATION * t * t / 2;
	return yy;
}

//������� �������� �������� �������
double GameProc::speed(double vv, double yy) {
	vv = vv + G_ACCELERATION * t;
	return vv;
}

//�������
void GameProc::rule() {
	if (x - xwall + MAIN_OBJ_SIZE >= 0 && x - xwall <= WALLSIZE && (y < ywall || y + MAIN_OBJ_SIZE >= ywall + WINWALL))	//���������� ���� ��� ������������ �� ������
		game_run = false;

	else if (/*xwall - x <= WALLSIZE*/x > xwall && !wallScored)	//������������ ����
	{
		score++;
		wallScored = true;
	}

	if (y < 0)	//����������� ������ ������� �������� ����
	{
		y = 0;
		v = 0;
	}

	if (y >= Y - MAIN_OBJ_SIZE) //������ ������� �� ������ �������
	{
		v = -v;
	}
}

//����� ����� ��� � WALLSTEP ������
void GameProc::wall() {
	//if (tim % (int)((double)WALLTIME / 600.0 * X) == 0 and tim > 0) {
	if (xwall < -WALLSIZE - 20 && tim > 0) {
		xwall = X;								//�� ������ ���� ����
		ywall = rand() % (int)(Y - WINWALL - WINWALL_DOWNSPACE); //� ����� � ��������� �����
		wallScored = false;
	}
}



//���������� �������� �������
POINT GameProc::objectCoords() {
	POINT res = { x, y };
	return res;
}

//���������� �����
POINT GameProc::wallCoords() {
	POINT res = { xwall, ywall };
	return res;
}

//��������� ������
void GameProc::jump() {
	v = - JUMP_SPEED;
}

//������� ������ �����  (���������� ��������� ����)
bool GameProc::proc() {
	rule();
	wall();	
	xwall -= WALLSPEED;
	y = height(v, y);
	v = speed(v, y);
	tim++; //���������� �������� ������

	//if (!game_run) {
	//	int rec = inputScore();
	//	if (rec < score) {
	//		outputScore(score);
	//	}
	//}

	return game_run;
}

//��������� (���������� ��������� ����)
bool GameProc::restart() {
	y = 0.0;					//����������� �������
	tim = 0;					//��������� �������� ������
	xwall = -(WALLSIZE + 1);	//����������� ����� �� �������� �������
	game_run = true;			//������� ���������� ������ ���� �������� ���
	score = 0;					//��������� �����
	wallScored = true;			//���� ���������
	
	return game_run;
}

//��������� ��������� �����
int GameProc::getScore() {
	return score;
}

////��������� ������� �� �����
//int GameProc::getRecord() {
//	return inputScore();
//}