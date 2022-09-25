#include "SeaBattle.h"

void SeaBattle::DrawAround(int y, int x)
{
	GameCell(*curField)[10] = (stepOfFirst) ? enemyField : playerField;

	bool StopCheck = false;    //остановить проверку
	switch (curField[y][x].rotation)
	{
	case Horizontal:
	{
		//интереснее сразу получить ячейки в области обводки
		int Left = 0;
		int Right = 9;
		int Up = (y == 0) ? y : y - 1;
		int Down = (y == 9) ? y : y + 1;

		//StopCheck = false; //в начальном состоянии ложь
		//Проверка влево
		for (int i = x - 1; i >= 0; i--) //текущая ячейка точно Killed
		{
			switch (curField[y][i].cond)
			{
			case HiddenShip: return; //корабль не добит - нечего обводить
			case Empty: case Opened:
			{
				StopCheck = true; //это край
				Left = i;         //значит первая палуба правее
			} break;
			}
			if (StopCheck) //дошли до края - можно обводить
				break;
		}

		//Проверка вправо
		StopCheck = false;
		for (int i = x + 1; i < 10; i++) //текущая ячейка точно Killed
		{
			switch (curField[y][i].cond)
			{
			case HiddenShip: return; //корабль не добит - нечего обводить
			case Empty: case Opened:
			{
				StopCheck = true; //это край
				Right = i;        //значит последняя палуба левее
			} break;
			}
			if (StopCheck) //дошли до края - можно обводить
				break;
		}

		//Обе проверки не выкинули - корабль добит
		//Тут же имеем границы за кораблем
		for (int i = Up; i <= Down; i++)
			for (int j = Left; j <= Right; j++)
				switch (curField[i][j].cond)
				{
				case Empty: curField[i][j].cond = Opened; break; //если он пуст - открыть
				//HiddenShip - не может быть, ибо нельзя в притык, а сам он полностью убит
				//KilledShip уже открыты все
				//Opened нет смысла открывать снова
				}
	} break;

	case Vertical:
	{
		//интереснее сразу получить ячейки в области обводки
		int Left = (x == 0) ? x : x - 1;
		int Right = (x == 9) ? x : x + 1;
		int Up = 0;
		int Down = 9;

		//StopCheck = false; //в начальном состоянии ложь
		//Проверка вверх
		for (int i = y - 1; i >= 0; i--) //текущая ячейка точно Killed
		{
			switch (curField[i][x].cond)
			{
			case HiddenShip: return; //корабль не добит - нечего обводить
			case Empty: case Opened:
			{
				StopCheck = true; //это край
				Up = i;           //значит первая палуба ниже
			} break;
			}
			if (StopCheck) //дошли до края - можно обводить
				break;
		}

		//Проверка вправо
		StopCheck = false;
		for (int i = y + 1; i < 10; i++) //текущая ячейка точно Killed
		{
			switch (curField[i][x].cond)
			{
			case HiddenShip: return; //корабль не добит - нечего обводить
			case Empty: case Opened:
			{
				StopCheck = true; //это край
				Down = i;         //значит последняя палуба выше
			} break;
			}
			if (StopCheck) //дошли до края - можно обводить
				break;
		}

		//Обе проверки не выкинули - корабль добит
		//Тут же имеем границы за кораблем
		for (int i = Up; i <= Down; i++)
			for (int j = Left; j <= Right; j++)
				switch (curField[i][j].cond)
				{
				case Empty: curField[i][j].cond = Opened; break; //если он пуст - открыть
				//HiddenShip - не может быть, ибо нельзя в притык, а сам он полностью убит
				//KilledShip уже открыты все
				//Opened нет смысла открывать снова
				}
	} break;
	} //switch;
}

bool SeaBattle::checkHit(int y, int x)
{
	GameCell(*curField)[10] = (stepOfFirst) ? enemyField : playerField;

	switch (curField[y][x].cond)
	{
	case HiddenShip: //попали в корабль
	{
		curField[y][x].cond = KilledShip;
		DrawAround(y, x); //могли убить корабль полностью
		return true;
	}
	case Empty:      //открыть пустую ячейку
	{
		curField[y][x].cond = Opened;
		return false;
	}
	default: return false;
	}
}

int* SeaBattle::AIShoot()
{
	int x = 0, y = 0;
	GameCell(*cur)[10] = (stepOfFirst) ? enemyField : playerField;

	//Стреляем, пока не выберем клетку, о которой мы ничего не знаем
	do
	{
		x = rand() % 10;
		y = rand() % 10;
	} while (cur[y][x].cond == Opened ||
		cur[y][x].cond == KilledShip);

	char cY = 65 + y;
	cout << "Компьютер выстрелил в " << cY << (x + 1) << endl;

	//Странные проблемы совместимости
	int* point = new int[2];
	point[0] = y;
	point[1] = x;
	return point;
}

int* SeaBattle::Shoot()
{
	string playerName = (stepOfFirst) ? firstName : secondName;
	cout << playerName + ", укажите координаты:" << endl;

	cout << "Укажите столбец (между A и J)" << endl;
	cout << "(По умолчанию - А)" << endl;
	char cRow = 'A';
	cin >> cRow;
	int iRow = 0;
	if (cRow > 64 && cRow < 75)				//65-A, 74-J
		iRow = cRow - 65;
	else if (cRow > 96 && cRow < 107) //97-a, 106-j
		iRow = cRow - 97;
	// else iColl = 0;

	cout << "Укажите строку (от 1 до 10)" << endl;
	cout << "(По умолчанию 1)" << endl;
	int coll = 1;
	cin >> coll;
	coll = (coll < 1 || coll > 10) ? 0 : coll - 1;

	//Странные проблемы совместимости
	int* point = new int[2];
	point[1] = coll;
	point[0] = iRow;
	return point;
}

bool SeaBattle::checkWin()
{
	GameCell(*curField)[10] = (stepOfFirst) ? enemyField : playerField;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (curField[i][j].cond == HiddenShip)
				return false;
	return true;
}

void SeaBattle::Draw(bool isFirst, char killedShip)
{
	GameCell(*curField)[10] = (isFirst) ? playerField : enemyField;
	string playerName = (isFirst) ? firstName : secondName;
	cout << endl; //для красоты
	cout << playerName << endl;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i == 0 and j == 0) //уголок карты
			{
				cout << "__|"; //'\t';
				continue;
			}
			if (j == 0)  //столбцы-буквы
			{
				char c = 64 + i; //А=65, но начинаем с 1
				cout << c << " |"; //'\t';
				continue;
			}
			if (i == 0) //строки-цифры
			{
				cout << j << " "; //'\t';
				continue;
			}

			//ячейки самого поля
			switch (curField[i - 1][j - 1].cond)
			{
			case Empty: cout << ' ' << '|'; break;
			case HiddenShip: cout << killedShip << '|'; break;
			case KilledShip: cout << 'X' << '|'; break;
			case Opened: cout << '-' << '|'; break;
			}
		} //конец строки
		cout << endl;
	} //все строки
	cout << endl; //для красоты
}

Ship SeaBattle::GetShip(bool isFirst, int size)
{
	Ship newShip;
	int maximumX = 10;
	char maximumY = 'J'; //64 + 10;
	string playerName = (isFirst) ? firstName : secondName;

	Draw(isFirst, 'O');
	cout << playerName << ", укажите условия для добавления корабля длиной " << size << endl;

	//Orientation
	cout << playerName << ", введите направление корабля, где:" << endl;
	cout << "Горизонтально - 0, H, h" << endl;
	cout << "Вертикально - 1, V, v" << endl;
	cout << "(Иные символы будут считаться за горизонтальное направление)" << endl;
	char orientation;
	cin >> orientation;
	switch (orientation)
	{
	case '1': case 'V': case 'v':
	{
		newShip.rotation = Vertical;
		maximumY -= size;
	} break;
	default:
	{
		newShip.rotation = Horizontal;
		maximumX = 11 - size;
	}
	};

	//Y
	char cY = 'A';
	cout << playerName << ", введите координату Y самой верхней палубы (от A до " << maximumY << ")" << endl;
	cout << "(Не забудьте о размерности корабля! При выходе за границы по умолчанию - 1)" << endl;
	cin >> cY;
	if (cY > 64 && cY < 75)        //65-A, 74-J
		newShip.y = cY - 65;
	else if (cY > 96 && cY < 107) //97-a, 106-j
		newShip.y = cY - 97;
	else newShip.y = 0;
	newShip.y = (newShip.y < 1 || newShip.y > maximumY) ? 0 : (newShip.y - 1) % maximumY; //для массива

	//X
	cout << playerName << ", введите координату Х самой левой палубы (от 1 до " << maximumX << ")" << endl;
	cout << "(Не забудьте о размерности корабля! При выходе за границы по умолчанию - 1)" << endl;
	cin >> newShip.x;
	newShip.x = (newShip.x < 1 || newShip.x > maximumX) ? 0 : (newShip.x - 1) % maximumX; //для массива

	return newShip;
}

Ship SeaBattle::RandomShip(int size)
{
	Ship randomShip;
	int maximumX = 9, maximumY = 9; //смысл делать в читабельном виде?

	//Orintation
	int r = rand() % 2;
	if (r == 1)
	{
		randomShip.rotation = Vertical;
		maximumY = 10 - size;
	}
	else
	{
		randomShip.rotation = Horizontal;
		maximumX = 10 - size;
	}

	randomShip.x = rand() % maximumX; //после алгоритм проверит координаты все равно
	randomShip.y = rand() % maximumY;
	return randomShip;
}

void SeaBattle::BuildField(bool isFirst, bool isMan)
{
	//Интерфейсная часть
	if (isFirst)
		cout << firstName << ", расставьте корабли!" << endl;
	else
	{
		if (isMan)
			cout << secondName << ", расставьте корабли!" << endl;
		else
			cout << "Компьютер расставляет корабли!" << endl;
	}
	//Интерфейсная часть

	for (int size = 4; size > 0; size--)        //N-палубник
		for (int count = 5 - size; count > 0; count--)  //5-N раз
		{
			bool isAdded = false;    //флаг того, что корабль добавлен успешно
			while (!isAdded)
			{
				Ship newShip = (isMan) ? GetShip(isFirst, size) : RandomShip(size);
				//Ship newShip = RandomShip(size); Для тестирования
				isAdded = TryAddShip(isFirst, newShip, size);
			} 


		} 
}

bool SeaBattle::TryAddShip(bool isFirst, Ship ship, int size)
{
	GameCell(*curField)[10];
	if (isFirst)
		curField = playerField;
	else
		curField = enemyField;

	switch (ship.rotation)
	{
	case Vertical:
	{
		//каемку проверить надо
		//корабли точно не уйдут за стенки
		int Left = (ship.x == 0) ? 0 : ship.x - 1;
		int Right = (ship.x == 9) ? 9 : ship.x + 1;
		int Up = (ship.y == 0) ? 0 : ship.y - 1;
		int Down = (ship.y + size == 9) ? 9 : ship.y + size + 1;

		for (int x = Left; x <= Right; x++)
			for (int y = Up; y <= Down; y++)
				if (curField[y][x].cond == HiddenShip) //Возможно еще только Empty 
					return false;

		for (int y = ship.y; y < ship.y + size; y++)
		{
			curField[y][ship.x].cond = HiddenShip;
			curField[y][ship.x].rotation = Vertical;
		}
	} break; 

	case Horizontal:
	{
		//каемку проверить надо
		//корабли точно не уйдут за стенки
		int Left = (ship.x == 0) ? 0 : ship.x - 1;
		int Right = (ship.x + size == 9) ? 9 : ship.x + size + 1;
		int Up = (ship.y == 0) ? 0 : ship.y - 1;
		int Down = (ship.y == 9) ? 9 : ship.y + 1;

		for (int x = Left; x <= Right; x++)
			for (int y = Up; y <= Down; y++)
				if (curField[y][x].cond == HiddenShip) //Возможно еще только Empty 
					return false;

		for (int x = ship.x; x < ship.x + size; x++)
		{
			curField[ship.y][x].cond = HiddenShip;
			curField[ship.y][x].rotation = Horizontal;
		}
	} break;

	default: return false;
	}

	return true;
}

