#pragma warning (disable: 4996)

#include "ScoreIO.h"

#include <fstream>
#include <windows.h>

using namespace std;

//������ � ����� �� ����� � �����������
TCHAR* path;

//������� ��� ������������ ������ � ������ ������ (��� �������, ��� ����� �������, ����� ����� ����)
void concat(TCHAR* main, TCHAR* add, int& pos)
{
	for (int k = 0; main[pos] = add[k]; pos++, k++);
}

//�������, ������������ ���� � ����� � �����������
void getDirectory() {
//
}

void outputScore(int score) {
	ofstream fout(path);
	if (!fout)	return;
	fout << score << endl;
	fout.close();
}

void inputScore(int& score) {
	char res[11];
	int valid = 1;

	ifstream fin(path);
	if (!fin)	return;
	fin >> res;
	fin.close();

	for (int i = 0; res[i] && i < 11; i++) {
		if (res[i] < '0' || res[i] >'9') {
			valid = false;
			break;
		}
	}

	score = (valid) ? atoi(res) : 0;
}

int inputScore() {
	int res;
	inputScore(res);
	return res;
}