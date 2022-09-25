#include "SeaBattle.h"

void SeaBattle::DrawAround(int y, int x)
{
	GameCell(*curField)[10] = (stepOfFirst) ? enemyField : playerField;

	bool StopCheck = false;    //���������� ��������
	switch (curField[y][x].rotation)
	{
	case Horizontal:
	{
		//���������� ����� �������� ������ � ������� �������
		int Left = 0;
		int Right = 9;
		int Up = (y == 0) ? y : y - 1;
		int Down = (y == 9) ? y : y + 1;

		//StopCheck = false; //� ��������� ��������� ����
		//�������� �����
		for (int i = x - 1; i >= 0; i--) //������� ������ ����� Killed
		{
			switch (curField[y][i].cond)
			{
			case HiddenShip: return; //������� �� ����� - ������ ��������
			case Empty: case Opened:
			{
				StopCheck = true; //��� ����
				Left = i;         //������ ������ ������ ������
			} break;
			}
			if (StopCheck) //����� �� ���� - ����� ��������
				break;
		}

		//�������� ������
		StopCheck = false;
		for (int i = x + 1; i < 10; i++) //������� ������ ����� Killed
		{
			switch (curField[y][i].cond)
			{
			case HiddenShip: return; //������� �� ����� - ������ ��������
			case Empty: case Opened:
			{
				StopCheck = true; //��� ����
				Right = i;        //������ ��������� ������ �����
			} break;
			}
			if (StopCheck) //����� �� ���� - ����� ��������
				break;
		}

		//��� �������� �� �������� - ������� �����
		//��� �� ����� ������� �� ��������
		for (int i = Up; i <= Down; i++)
			for (int j = Left; j <= Right; j++)
				switch (curField[i][j].cond)
				{
				case Empty: curField[i][j].cond = Opened; break; //���� �� ���� - �������
				//HiddenShip - �� ����� ����, ��� ������ � ������, � ��� �� ��������� ����
				//KilledShip ��� ������� ���
				//Opened ��� ������ ��������� �����
				}
	} break;

	case Vertical:
	{
		//���������� ����� �������� ������ � ������� �������
		int Left = (x == 0) ? x : x - 1;
		int Right = (x == 9) ? x : x + 1;
		int Up = 0;
		int Down = 9;

		//StopCheck = false; //� ��������� ��������� ����
		//�������� �����
		for (int i = y - 1; i >= 0; i--) //������� ������ ����� Killed
		{
			switch (curField[i][x].cond)
			{
			case HiddenShip: return; //������� �� ����� - ������ ��������
			case Empty: case Opened:
			{
				StopCheck = true; //��� ����
				Up = i;           //������ ������ ������ ����
			} break;
			}
			if (StopCheck) //����� �� ���� - ����� ��������
				break;
		}

		//�������� ������
		StopCheck = false;
		for (int i = y + 1; i < 10; i++) //������� ������ ����� Killed
		{
			switch (curField[i][x].cond)
			{
			case HiddenShip: return; //������� �� ����� - ������ ��������
			case Empty: case Opened:
			{
				StopCheck = true; //��� ����
				Down = i;         //������ ��������� ������ ����
			} break;
			}
			if (StopCheck) //����� �� ���� - ����� ��������
				break;
		}

		//��� �������� �� �������� - ������� �����
		//��� �� ����� ������� �� ��������
		for (int i = Up; i <= Down; i++)
			for (int j = Left; j <= Right; j++)
				switch (curField[i][j].cond)
				{
				case Empty: curField[i][j].cond = Opened; break; //���� �� ���� - �������
				//HiddenShip - �� ����� ����, ��� ������ � ������, � ��� �� ��������� ����
				//KilledShip ��� ������� ���
				//Opened ��� ������ ��������� �����
				}
	} break;
	} //switch;
}

bool SeaBattle::checkHit(int y, int x)
{
	GameCell(*curField)[10] = (stepOfFirst) ? enemyField : playerField;

	switch (curField[y][x].cond)
	{
	case HiddenShip: //������ � �������
	{
		curField[y][x].cond = KilledShip;
		DrawAround(y, x); //����� ����� ������� ���������
		return true;
	}
	case Empty:      //������� ������ ������
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

	//��������, ���� �� ������� ������, � ������� �� ������ �� �����
	do
	{
		x = rand() % 10;
		y = rand() % 10;
	} while (cur[y][x].cond == Opened ||
		cur[y][x].cond == KilledShip);

	char cY = 65 + y;
	cout << "��������� ��������� � " << cY << (x + 1) << endl;

	//�������� �������� �������������
	int* point = new int[2];
	point[0] = y;
	point[1] = x;
	return point;
}

int* SeaBattle::Shoot()
{
	string playerName = (stepOfFirst) ? firstName : secondName;
	cout << playerName + ", ������� ����������:" << endl;

	cout << "������� ������� (����� A � J)" << endl;
	cout << "(�� ��������� - �)" << endl;
	char cRow = 'A';
	cin >> cRow;
	int iRow = 0;
	if (cRow > 64 && cRow < 75)				//65-A, 74-J
		iRow = cRow - 65;
	else if (cRow > 96 && cRow < 107) //97-a, 106-j
		iRow = cRow - 97;
	// else iColl = 0;

	cout << "������� ������ (�� 1 �� 10)" << endl;
	cout << "(�� ��������� 1)" << endl;
	int coll = 1;
	cin >> coll;
	coll = (coll < 1 || coll > 10) ? 0 : coll - 1;

	//�������� �������� �������������
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
	cout << endl; //��� �������
	cout << playerName << endl;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i == 0 and j == 0) //������ �����
			{
				cout << "__|"; //'\t';
				continue;
			}
			if (j == 0)  //�������-�����
			{
				char c = 64 + i; //�=65, �� �������� � 1
				cout << c << " |"; //'\t';
				continue;
			}
			if (i == 0) //������-�����
			{
				cout << j << " "; //'\t';
				continue;
			}

			//������ ������ ����
			switch (curField[i - 1][j - 1].cond)
			{
			case Empty: cout << ' ' << '|'; break;
			case HiddenShip: cout << killedShip << '|'; break;
			case KilledShip: cout << 'X' << '|'; break;
			case Opened: cout << '-' << '|'; break;
			}
		} //����� ������
		cout << endl;
	} //��� ������
	cout << endl; //��� �������
}

Ship SeaBattle::GetShip(bool isFirst, int size)
{
	Ship newShip;
	int maximumX = 10;
	char maximumY = 'J'; //64 + 10;
	string playerName = (isFirst) ? firstName : secondName;

	Draw(isFirst, 'O');
	cout << playerName << ", ������� ������� ��� ���������� ������� ������ " << size << endl;

	//Orientation
	cout << playerName << ", ������� ����������� �������, ���:" << endl;
	cout << "������������� - 0, H, h" << endl;
	cout << "����������� - 1, V, v" << endl;
	cout << "(���� ������� ����� ��������� �� �������������� �����������)" << endl;
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
	cout << playerName << ", ������� ���������� Y ����� ������� ������ (�� A �� " << maximumY << ")" << endl;
	cout << "(�� �������� � ����������� �������! ��� ������ �� ������� �� ��������� - 1)" << endl;
	cin >> cY;
	if (cY > 64 && cY < 75)        //65-A, 74-J
		newShip.y = cY - 65;
	else if (cY > 96 && cY < 107) //97-a, 106-j
		newShip.y = cY - 97;
	else newShip.y = 0;
	newShip.y = (newShip.y < 1 || newShip.y > maximumY) ? 0 : (newShip.y - 1) % maximumY; //��� �������

	//X
	cout << playerName << ", ������� ���������� � ����� ����� ������ (�� 1 �� " << maximumX << ")" << endl;
	cout << "(�� �������� � ����������� �������! ��� ������ �� ������� �� ��������� - 1)" << endl;
	cin >> newShip.x;
	newShip.x = (newShip.x < 1 || newShip.x > maximumX) ? 0 : (newShip.x - 1) % maximumX; //��� �������

	return newShip;
}

Ship SeaBattle::RandomShip(int size)
{
	Ship randomShip;
	int maximumX = 9, maximumY = 9; //����� ������ � ����������� ����?

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

	randomShip.x = rand() % maximumX; //����� �������� �������� ���������� ��� �����
	randomShip.y = rand() % maximumY;
	return randomShip;
}

void SeaBattle::BuildField(bool isFirst, bool isMan)
{
	//������������ �����
	if (isFirst)
		cout << firstName << ", ���������� �������!" << endl;
	else
	{
		if (isMan)
			cout << secondName << ", ���������� �������!" << endl;
		else
			cout << "��������� ����������� �������!" << endl;
	}
	//������������ �����

	for (int size = 4; size > 0; size--)        //N-��������
		for (int count = 5 - size; count > 0; count--)  //5-N ���
		{
			bool isAdded = false;    //���� ����, ��� ������� �������� �������
			while (!isAdded)
			{
				Ship newShip = (isMan) ? GetShip(isFirst, size) : RandomShip(size);
				//Ship newShip = RandomShip(size); ��� ������������
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
		//������ ��������� ����
		//������� ����� �� ����� �� ������
		int Left = (ship.x == 0) ? 0 : ship.x - 1;
		int Right = (ship.x == 9) ? 9 : ship.x + 1;
		int Up = (ship.y == 0) ? 0 : ship.y - 1;
		int Down = (ship.y + size == 9) ? 9 : ship.y + size + 1;

		for (int x = Left; x <= Right; x++)
			for (int y = Up; y <= Down; y++)
				if (curField[y][x].cond == HiddenShip) //�������� ��� ������ Empty 
					return false;

		for (int y = ship.y; y < ship.y + size; y++)
		{
			curField[y][ship.x].cond = HiddenShip;
			curField[y][ship.x].rotation = Vertical;
		}
	} break; 

	case Horizontal:
	{
		//������ ��������� ����
		//������� ����� �� ����� �� ������
		int Left = (ship.x == 0) ? 0 : ship.x - 1;
		int Right = (ship.x + size == 9) ? 9 : ship.x + size + 1;
		int Up = (ship.y == 0) ? 0 : ship.y - 1;
		int Down = (ship.y == 9) ? 9 : ship.y + 1;

		for (int x = Left; x <= Right; x++)
			for (int y = Up; y <= Down; y++)
				if (curField[y][x].cond == HiddenShip) //�������� ��� ������ Empty 
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

