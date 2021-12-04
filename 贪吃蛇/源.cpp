#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#define HIGH 13
#define WIDE 20
using namespace std;

//����0��ʾ�հף�1��ʾǽ��2��ʾ�ߣ�3��ʾƻ��

char flag = 0x01;//0000 0000	����λ��ʾ̰�������е�״̬������Ϊ�ϣ��£����ң�����λ�Դ˱�ʾ������ģʽ����ǽ��ģʽ���������غϣ���ʳ���غ�
vector<vector<int>> map;
vector<pair<int,int>> snake;
pair<int, int>apple = make_pair(3,3);

//�ڶ��㺯��
void setApple();		//�����ߵ�����
void forEachSnake();			////��map�����ߵ�����    �ж����Ƿ���ȥ
void growUp();			//���߳ɳ�
void mapInit();			//��ʼ����ͼ
void snakeInit();		//��ʼ����


//��һ�㺯��
void init();
void inPut();
void upDate();
void draw();

/// <summary>
/// �ڶ��㺯��
/// </summary>

//����ƻ����λ��
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
//��map�����ߵ�����    �ж����Ƿ���ȥ
void forEachSnake()
{
	//��map�����ߵ�����    �ж����Ƿ���ȥ
	for (auto i = snake.begin(); i != snake.end(); i++)
	{
		auto y = map.begin();
		if ((*i).second < HIGH - 1 && (*i).second > 0)y += (*i).second;
		else flag = 0x20;

		auto x = (*y).begin();
		if ((*i).first < WIDE - 1 && (*i).first > 0)x += (*i).first;
		else flag = 0x20;

		//�ж��Ƿ�ҧ���Լ�
		for (auto j = i+1; j != snake.end(); j++)if((*i)==(*j))flag = 0x20;

		//�Ѿ�ȷ����y��ֻ������y�ϵ�x��ֵ����
		(*x) = 2;

		//�ж����Ƿ�Ե�ƻ��
		if ((*i) == apple)
		{
			flag |= 1 << 4;
		}

	}
}
//�Ե��ǹ�֮��Ӧ����������
void growUp()
{
	if ((flag >> 4) & 0x01)
	{	
		setApple();
		flag &= ~(1 << 4);
		snake.push_back(*(snake.end() - 1));
		
		
	}
}
//��ʼ����ͼ
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
//��ʼ����
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
/// ��һ�㺯��
/// </summary>
void init()
{
	//��ʼ����ͼ
	mapInit();

	//�߳�ʼ����λ��
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


	//��յ�ͼ�ϵ���
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

	//��map����ƻ��������
	*((*(map.begin() + apple.second)).begin() + apple.first) = 3;

	
	
	//�����ߵ�����
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
			if (*x == 1)cout << "ǽ";
			else if (*x == 2)cout << "��";
			else if (*x == 3)cout << "��";
			else cout << "  ";
		}
		cout << endl;
	}

}

/// <summary>
/// ̰����
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