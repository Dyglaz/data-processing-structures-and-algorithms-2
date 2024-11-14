#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int rooms [49] [49]; // Отметить информацию о стене комнаты
int color [49] [49]; // пометить посещение комнаты
int maxRoomArea = 0; // Площадь наибольшей связанной области
int roomArea = 0; // текущее подключение к поиску
int roomNum; // Количество соединенных комнат

void DFS(int i, int j)
{
	if (color[i][j])
		return;
	roomArea++;
	color[i][j] = roomNum; // отметить текущую точку, которую посетили
	if ((rooms[i][j] & 1)== 0)
	{
		 DFS (i, j-1); // На западной стороне нет стены, глубоко обыщите западную сторону
	}
	if ((rooms[i][j] & 2) == 0)
	{
		 DFS (i-1, j); // Нет стены на севере, глубокий поиск на север
	}
	if ((rooms[i][j] & 4)== 0)
	{
		 DFS (i, j + 1); // Нет стены на востоке, глубокий поиск на востоке
	}
	if ((rooms[i][j] & 8)== 0)
	{
		 DFS (i + 1, j); // Нет стены на юге, глубокий поиск на юге
	}
}
 
int main()
{
    cout << "Практическая работа №7. Алгоритмические стратегии. Киселёв Максим. ИКБО-08-21. Вариант №14." << endl;
    cout << "Введите количество клеток по вертикале: ";
	int row, col;
	cin >> row;
    cout << "Введите количество клеток по горизонтале: ";
    cin >> col;
    cout << "Введите значения ячеек замка, которые отвечают за стены ячеек: " << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> rooms[i][j];
		}
	}
	memset(color, 0, sizeof(color));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (!color[i][j])
			{
				roomNum++;
				roomArea = 0;
				DFS(i, j);
				maxRoomArea = max(roomArea, maxRoomArea);
			}
 
		}
	}
	cout << "Количество комнат в замке: " << roomNum << endl;
	cout << "Площадь наибольшей комнаты : " <<  maxRoomArea << endl;
}