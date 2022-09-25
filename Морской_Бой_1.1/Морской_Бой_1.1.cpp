#include <iostream>
#include "SeaBattle.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "");

	int countPlayers = 1;
	cout << "Введите количество игроков: " << endl;
	cin >> countPlayers;
	countPlayers = countPlayers % 2 + 1;

	/*int hardMode = 0;
	cout << "Введите положительное число для сложного режима" << endl;
	cin >> hardMode;*/

	char autoMap = 'Y';
	cout << "Введите 0 для автоматической генерации поля" << endl;
	cin >> autoMap;

	//С этими настройками запустим игру
	bool multiplayer = countPlayers == 2;
	//bool hardAI = hardMode > 0;
	bool autoField = autoMap == '0';
	SeaBattle game = SeaBattle(multiplayer,/* hardAI,*/ autoField);
	cout << game.Start();
}

