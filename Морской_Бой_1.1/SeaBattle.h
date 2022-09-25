#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>

using namespace std;
enum Cell
{
	Empty,
	HiddenShip,
	KilledShip,
	Opened
};

enum Orientation
{
	Undefined,
	Horizontal,
	Vertical
};

struct Ship
{
public:
	int x;
	int y;
	Orientation rotation;
};

struct GameCell
{
	Cell cond;
	Orientation rotation;
};

class SeaBattle
{

	string firstName;
	string secondName;

	GameCell playerField[10][10]; //���� ������
	GameCell enemyField[10][10];  //���� ����������

	bool stepOfFirst;             //���� ��������� ������, true=>playerField
	bool isPlaying;               //���� ��������� ����
	bool pvp;                     //������ ����� - �������
	bool hardMode;                //����� ������ AI
	void DrawAround(int y, int x);
	bool checkHit(int y, int x);
	int* AIShoot();
	int* Shoot();
	bool checkWin();
	void Draw(bool isFirst, char killedShip);
	Ship GetShip(bool isFirst, int size);
	Ship RandomShip(int size);
	void BuildField(bool isFirst, bool isMan);
	bool TryAddShip(bool isFirst, Ship ship, int size);
	

public:
	
	SeaBattle(bool pvp, /*bool hardMode*/ bool autoMap)
	{
		//��������� ����� ��������
		srand(time(0));
		stepOfFirst = (rand() % 2) == 0;

		//� ��� �� ���������������� ������(
		for (int y = 0; y < 10; y++)
			for (int x = 0; x < 10; x++)
			{
				playerField[y][x].cond = Empty;
				playerField[y][x].rotation = Undefined;
				enemyField[y][x].cond = Empty;
				enemyField[y][x].rotation = Undefined;
			}

		//������
		isPlaying = true;
		this->pvp = pvp;
		this->hardMode = hardMode;

		//��������� �����
		if (pvp)
		{
			firstName = "������ �����";
			secondName = "������ �����";
			BuildField(true, !autoMap);
			system("cls");
			BuildField(false, !autoMap);
			system("cls");
		}
		else
		{
			firstName = "�����";
			secondName = "���������";
			BuildField(true, !autoMap);
			BuildField(false, false);
		}
	}
	string Start()
	{
		while (isPlaying)
		{
			//�������� �����
			cout << string(30, '-') << endl;
			if (!pvp) //����� ������ ����������
			{
				Draw(true, 'O');         //����� ����� ���� �������
				Draw(false, ' ');        //������� ���������� ������
				//Draw(false, 'O');        //������������
			}
			else
				Draw(!stepOfFirst, ' '); //������ ����� ���������, ����� ��� �������

			//������ ����
			//� ��� ������ �������� ����. � ��� ������ ������ �����
			int* target = (pvp or stepOfFirst) ? Shoot() : AIShoot();
			//int* target = AIShoot(); //������������

			if (checkHit(target[0], target[1])) //�������� � ��� ����������
				isPlaying = !checkWin();        //���� ������, ��������� ��� ��������
			else                                //�� �����
				stepOfFirst = !stepOfFirst;     //������ ����������
		}

		string result = (stepOfFirst) ? firstName : secondName;
		return result + " �������!";
	}
};

