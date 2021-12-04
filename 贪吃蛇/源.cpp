#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#define HIGH 13
#define WIDE 20
using namespace std;

//数字0表示空白，1表示墙，2表示蛇，3表示苹果

char flag = 0x01;//0000 0000	低四位表示贪吃蛇运行的状态，依次为上，下，左，右，高四位以此表示：经典模式，无墙壁模式，与身体重合，与食物重合
vector<vector<int>> map;
vector<pair<int,int>> snake;
pair<int, int>apple = make_pair(3,3);

//第二层函数
void setApple();		//设置蛇的身体
void forEachSnake();			////给map输入蛇的坐标    判断蛇是否死去
void growUp();			//让蛇成长
void mapInit();			//初始化地图
void snakeInit();		//初始化蛇


//第一层函数
void init();
void inPut();
void upDate();
void draw();

/// <summary>
/// 第二层函数
/// </summary>

//设置苹果的位置
void setApple()
{
	int x, y;
	x = rand() % (WIDE - 1);
	y = rand() % (HIGH - 1);
	while (1)
	{
		apple = make_pair(x, y);
		for (auto i = snake.begin()+1; i != snake.end(); i++)if (apple != *i)goto speak;
	}
speak:
	{}
}
//给map输入蛇的坐标    判断蛇是否死去
void forEachSnake()
{
	//给map输入蛇的坐标    判断蛇是否死去
	for (auto i = snake.begin(); i != snake.end(); i++)
	{
		auto y = map.begin();
		if ((*i).second < HIGH - 1 && (*i).second > 0)y += (*i).second;
		else flag = 0x20;

		auto x = (*y).begin();
		if ((*i).first < WIDE - 1 && (*i).first > 0)x += (*i).first;
		else flag = 0x20;

		//判断是否咬到自己
		for (auto j = i+1; j != snake.end(); j++)if((*i)==(*j))flag = 0x20;

		//已经确定了y，只需给这个y上的x赋值即可
		(*x) = 2;

		//判断蛇是否吃到苹果
		if ((*i) == apple)
		{
			flag |= 1 << 4;
		}

	}
}
//吃到糖果之后应该做的事情
void growUp()
{
	if ((flag >> 4) & 0x01)
	{	
		setApple();
		flag &= ~(1 << 4);
		snake.push_back(*(snake.end() - 1));
		
		
	}
}
//初始化地图
void mapInit()
{
	vector<int> line = { 0 };
	for (int i = 0; i < HIGH; i++)
	{
		line.clear();
		if (i == 0 || i == WIDE - 1)
		{
			for (int j = 0; j < WIDE; j++)
			{
				line.push_back(1);
			}
		}
		else
		{
			for (int j = 0; j < WIDE; j++)
			{
				if (j == 0 || j == WIDE - 1)line.push_back(1);
				else line.push_back(0);
			}
		}
		map.push_back(line);
	}
}
//初始化蛇
void snakeInit()
{
	pair<int, int> tem = make_pair(9, 9);
	for (int i = 0; i < 5; i++)
	{
		snake.push_back(tem);
		tem.first--;
	}
}


/// <summary>
/// 第一层函数
/// </summary>
void init()
{
	//初始化地图
	mapInit();

	//蛇初始化的位置
	snakeInit();
}

void inPut()
{
	if (_kbhit())
	{
		char operate;
		operate = _getch();
		switch (operate)
		{
		case 'w':
			flag = (flag | 0x08) & 0xf8;
			break;
		case 's':
			flag = (flag | 0x04) & 0xf4;
			break;
		case 'a':
			flag = (flag | 0x02) & 0xf2;
			break;
		case 'd':
			flag = (flag | 0x01) & 0xf1;
			break;
		}
	}
}
void upDate()
{


	//清空地图上的蛇
	vector<int> line = {0,0,0};
	map.clear();
	for (int i = 0; i < HIGH; i++)
	{
		line.clear();
		if (i == 0 || i == HIGH - 1)
		{
			for (int j = 0; j < WIDE; j++)
			{
				line.push_back(1);
			}
		}
		else
		{
			for (int j = 0; j < WIDE; j++)
			{
				if (j == 0 || j == WIDE - 1)line.push_back(1);
				else line.push_back(0);
			}
		}
		map.push_back(line);
	}

	forEachSnake();

	growUp();

	//给map输入苹果的坐标
	*((*(map.begin() + apple.second)).begin() + apple.first) = 3;

	
	
	//更新蛇的坐标
	for (auto i = snake.end()-1; i != snake.begin(); i--)
	{
		(*i) = (*(i - 1));
	}
	if ((flag >> 3) & 0x01)(*snake.begin()).second--;
	if ((flag >> 2) & 0x01)(*snake.begin()).second++;
	if ((flag >> 1) & 0x01)(*snake.begin()).first--;
	if ((flag >> 0) & 0x01)(*snake.begin()).first++;

	

}
void draw()
{
	system("cls");
	for (auto y = map.begin(); y != map.end(); y++)
	{
		for (auto x = y->begin(); x != y->end(); x++)
		{
			if (*x == 1)cout << "墙";
			else if (*x == 2)cout << "〇";
			else if (*x == 3)cout << "⊙";
			else cout << "  ";
		}
		cout << endl;
	}

}

/// <summary>
/// 贪吃蛇
/// </summary>
/// <returns></returns>
int main()
{
	
	init();
	while (((flag >> 5) & 0x01) == 0)
	{
		upDate();
		draw();
		Sleep(200);
		inPut();
	}


	system("pause");
	return 0;
}