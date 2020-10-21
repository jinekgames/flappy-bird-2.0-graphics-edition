#pragma once

//#include "ScoreIO.h"

//�������, ����������� ��� ������� ����

//����� ����� �������� ����
#define WALLTIME 400
//�������� �������� �����������
#define WALLSPEED 2.0
//������ ���� � �����
#define WINWALL 200.0
//������� �����
#define WALLSIZE 50.0
//��������� ���������� �������
#define G_ACCELERATION 5.81
//������ �������� �������
#define MAIN_OBJ_SIZE 20.0
//�������� ����� ����� ������
#define JUMP_SPEED 50.0
//������ ����� ������ ���� � �����
#define WINWALL_DOWNSPACE 300.0

class GameProc {
	//������� ������ ����
	bool game_run = false;
	//���������� ������������ ������
	int tim = 0;

	//������� ����
	double Y = 800, X = 600;
	//�����, ������� �������� ����� ����� ������� � ���
	const double t = 0.2;

	//��������
	double v = 0.0;

	//������ �������� �������
	double y = 0.0;
	//��������� �������� �������
	double x = 10;

	//���������� X �����
	double xwall;
	//��������� ���� � �����
	double ywall = 0;

	//��������� ����
	int score = 0;
	//����������� �����������
	bool wallScored = true;


	//������������ � �����������//
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

	//���������� ������ ������//
private:

	//������� ���������� ������ �������� �������
	double height(double vv, double yy);
	//������� �������� �������� �������
	double speed(double vv, double yy);
	//�������
	void rule();
	//����� ����� ��� � WALLSTEP ������
	void wall();


	//��� ������������//
public:

	//���������� �������� �������
	POINT objectCoords();
	//���������� �����
	POINT wallCoords();
	//��������� ������
	void jump();
	//������� ������ ����� (���������� ��������� ����)
	bool proc();
	//��������� (���������� ��������� ����)
	bool restart();
	//��������� ��������� �����
	int getScore();
	//��������� ������� �� �����
	//int getRecord();
};
