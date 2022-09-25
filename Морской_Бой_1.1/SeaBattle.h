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

	GameCell playerField[10][10]; //Поле игрока
	GameCell enemyField[10][10];  //Поле компьютера

	bool stepOfFirst;             //Флаг активного игрока, true=>playerField
	bool isPlaying;               //Флаг окончания игры
	bool pvp;                     //Второй игрок - человек
	bool hardMode;                //Режим умного AI
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
		//Случайный игрок начинает
		srand(time(0));
		stepOfFirst = (rand() % 2) == 0;

		//а вот не инициализируется нулями(
		for (int y = 0; y < 10; y++)
			for (int x = 0; x < 10; x++)
			{
				playerField[y][x].cond = Empty;
				playerField[y][x].rotation = Undefined;
				enemyField[y][x].cond = Empty;
				enemyField[y][x].rotation = Undefined;
			}

		//Флажки
		isPlaying = true;
		this->pvp = pvp;
		this->hardMode = hardMode;

		//Построить карты
		if (pvp)
		{
			firstName = "Первый игрок";
			secondName = "Второй игрок";
			BuildField(true, !autoMap);
			system("cls");
			BuildField(false, !autoMap);
			system("cls");
		}
		else
		{
			firstName = "Игрок";
			secondName = "Компьютер";
			BuildField(true, !autoMap);
			BuildField(false, false);
		}
	}
	string Start()
	{
		while (isPlaying)
		{
			//Нарисуем карту
			cout << string(30, '-') << endl;
			if (!pvp) //Режим против компьютера
			{
				Draw(true, 'O');         //игрок видит свои корабли
				Draw(false, ' ');        //корабли компьютера скрыты
				//Draw(false, 'O');        //тестирование
			}
			else
				Draw(!stepOfFirst, ' '); //рисуем карту соперника, скрыв его корабли

			//Логика игры
			//в пвп всегда стреляют люди. в пве только первый игрок
			int* target = (pvp or stepOfFirst) ? Shoot() : AIShoot();
			//int* target = AIShoot(); //тестирование

			if (checkHit(target[0], target[1])) //стреляем в эти координаты
				isPlaying = !checkWin();        //если попали, проверяем что осталось
			else                                //не попал
				stepOfFirst = !stepOfFirst;     //меняем атакующего
		}

		string result = (stepOfFirst) ? firstName : secondName;
		return result + " победил!";
	}
};

