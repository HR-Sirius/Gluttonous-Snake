#include<graphics.h>
#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

#define WIDTH 30
#define HEIGHT 30
#define SIZE 20
//#define DELAY  150

//������ͼ��ά����
int Map[HEIGHT][WIDTH] = { 0 };

//�����ṹ��POSITON����¼ÿһ�����������
struct POSITION
{
	int x;
	int y;
};

//��������,��ʼ������Ϊ1,��ʼ������λ��Ϊ{WIDTH * SIZE / 2, HEIGHT * SIZE / 2}
vector<POSITION> Snake = { {WIDTH/ 2, HEIGHT/ 2} };
//����ʳ��
struct POSITION Food = { 0,0 };

//������ʼ��Ϊ0
int score = 0;

//�ж�ʳ����������
bool is_spawn = true;
//�ж�ʳ���Ƿ��ѱ��Ե�
bool is_eaten = true;
//�ж����Ƿ����ƶ�
bool is_move_up = false;
bool is_move_down = false;
bool is_move_left = false;
bool is_move_right = false;

//��Ⱦ��ͼ
void DrawMap()
{
	line(0, 0, WIDTH * SIZE, 0);
	line(0, 0, 0, HEIGHT * SIZE);
	line(0, HEIGHT * SIZE, WIDTH * SIZE, HEIGHT * SIZE);
	line(WIDTH * SIZE, 0, WIDTH * SIZE, HEIGHT * SIZE);
}

//��Ⱦ����
void DrawSnake()
{
	int i = 0;
	//���Ļ�����ɫΪ��ɫ
	setfillcolor(GREEN);
	//����vector Snake,��ȡÿһ�������λ�ò���Ⱦ
	for (; i < Snake.size(); i++)
	{
		fillrectangle(Snake[i].x * SIZE, Snake[i].y * SIZE, (Snake[i].x + 1) * SIZE, (Snake[i].y + 1) * SIZE);
	}
}

//��ʾ��ǰ����
void DrawScoreText()
{
	static TCHAR Scorestr[10];
	_stprintf_s(Scorestr, _T("��ǰ����Ϊ:%d"), score);

	//�����ı���ɫ
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, Scorestr);
}

//���ƶ�
void Snakemove(bool is_eaten)
{
	setfillcolor(GREEN);
/*���ַ���ÿ�ƶ�һ��Ҫȫ�����������˷�����
	if (is_move_up)
	{
		for (int i = 0; i < Snake.size()-1; i++)
		{
			Snake[i + 1] = Snake[i];
		}
		Snake[0].y = Snake[0].y - 1;
	}
	if (is_move_down)
	{
		for (int i = 0; i < Snake.size() - 1; i++)
		{
			Snake[i + 1] = Snake[i];
		}
		Snake[0].y = Snake[0].y + 1;
	}
	if (is_move_right)
	{
		for (int i = 0; i < Snake.size() - 1; i++)
		{
			Snake[i + 1] = Snake[i];
		}
		Snake[0].x =Snake[0].x + 1;
	}
	if (is_move_left)
	{
		for (int i = 0; i < Snake.size() - 1; i++)
		{
			Snake[i + 1] = Snake[i];
		}
		Snake[0].x = Snake[0].x - 1;
	}*/
	//����˴��ƶ�δ�Ե�ʳ����ƶ���������һ��
	if (!is_eaten)
	{
		if (is_move_up)
		{
			Snake.insert(Snake.begin(), { Snake[0].x,Snake[0].y - 1 });
			fillrectangle(Snake[0].x * SIZE, Snake[0].y * SIZE, (Snake[0].x + 1) * SIZE, (Snake[0].y + 1) * SIZE);
			clearrectangle(Snake[Snake.size() - 1].x * SIZE, Snake[Snake.size() - 1].y * SIZE, (Snake[Snake.size() - 1].x + 1) * SIZE, (Snake[Snake.size() - 1].y + 1) * SIZE);
			Snake.pop_back();
		}
		if (is_move_down)
		{
			Snake.insert(Snake.begin(), { Snake[0].x,Snake[0].y + 1 });
			fillrectangle(Snake[0].x * SIZE, Snake[0].y * SIZE, (Snake[0].x + 1) * SIZE, (Snake[0].y + 1) * SIZE);
			clearrectangle(Snake[Snake.size() - 1].x * SIZE, Snake[Snake.size() - 1].y * SIZE, (Snake[Snake.size() - 1].x + 1) * SIZE, (Snake[Snake.size() - 1].y + 1) * SIZE);
			Snake.pop_back();
		}
		if (is_move_right)
		{
			Snake.insert(Snake.begin(), { Snake[0].x + 1,Snake[0].y });
			fillrectangle(Snake[0].x * SIZE, Snake[0].y * SIZE, (Snake[0].x + 1) * SIZE, (Snake[0].y + 1) * SIZE);
			clearrectangle(Snake[Snake.size() - 1].x * SIZE, Snake[Snake.size() - 1].y * SIZE, (Snake[Snake.size() - 1].x + 1) * SIZE, (Snake[Snake.size() - 1].y + 1) * SIZE);
			Snake.pop_back();
		}
		if (is_move_left)
		{
			Snake.insert(Snake.begin(), { Snake[0].x - 1,Snake[0].y });
			fillrectangle(Snake[0].x * SIZE, Snake[0].y * SIZE, (Snake[0].x + 1) * SIZE, (Snake[0].y + 1) * SIZE);
			clearrectangle(Snake[Snake.size() - 1].x * SIZE, Snake[Snake.size() - 1].y * SIZE, (Snake[Snake.size() - 1].x + 1) * SIZE, (Snake[Snake.size() - 1].y + 1) * SIZE);
			Snake.pop_back();
		}
	}
	//�˴��ƶ��Ե���ʳ�����������һ��
	else
	{
		if (is_move_up)
		{
			Snake.insert(Snake.begin(), { Snake[0].x,Snake[0].y - 1 });
			fillrectangle(Snake[0].x * SIZE, Snake[0].y * SIZE, (Snake[0].x + 1) * SIZE, (Snake[0].y + 1) * SIZE);
		}
		if (is_move_down)
		{
			Snake.insert(Snake.begin(), { Snake[0].x,Snake[0].y + 1 });
			fillrectangle(Snake[0].x * SIZE, Snake[0].y * SIZE, (Snake[0].x + 1) * SIZE, (Snake[0].y + 1) * SIZE);
		}
		if (is_move_right)
		{
			Snake.insert(Snake.begin(), { Snake[0].x + 1,Snake[0].y });
			fillrectangle(Snake[0].x * SIZE, Snake[0].y * SIZE, (Snake[0].x + 1) * SIZE, (Snake[0].y + 1) * SIZE);
		}
		if (is_move_left)
		{
			Snake.insert(Snake.begin(), { Snake[0].x - 1,Snake[0].y });
			fillrectangle(Snake[0].x * SIZE, Snake[0].y * SIZE, (Snake[0].x + 1) * SIZE, (Snake[0].y + 1) * SIZE);
		}
	}
}

//ʳ������
void FoodSpawn()
{
	//���ж��Ƿ��ܹ�����ʳ���is_spawnΪtrue�����������ʳ�����˵����ǰ��ͼ����ʳ������ɶ���ʳ��
	if (is_spawn)
	{
		//һֱ���ɣ�ֱ����������������Ϊֹ
		while (true)
		{
			Food.x = rand() % WIDTH;
			Food.y = rand() % HEIGHT;
			bool flag = false;
			for (int i = 0; i < Snake.size(); i++)
			{
				//ʳ��λ���������غ�
				if (Food.x == Snake[i].x && Food.y == Snake[i].y)
					break;
				//���غϣ�����
				else
				{
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
		setfillcolor(RED);
		fillrectangle(Food.x * SIZE, Food.y * SIZE, (Food.x + 1) * SIZE, (Food.y + 1) * SIZE);
		is_spawn = false;
	}
}

//�߳�ʳ��
bool Eatfood()
{
	//�ɹ��򷵻�true�����µ���FoodSpawn()��ScoreAdd(),���򷵻�false
	if (Food.x == Snake[0].x && Food.y == Snake[0].y)
	{

		is_spawn = true;
		return true;
	}
	else
		return false;
}

//������¼
void ScoreAdd(bool is_eaten)
{
	if (is_eaten)
	{
		score += 10;
	}
}

//�ж���Ϸ�Ƿ����
bool CheckGameOver()
{
	//�ж��Ƿ�����ͼ�߽�
	if ((Snake[0].x < 0) || (Snake[0].x > WIDTH) || (Snake[0].y < 0) || (Snake[0].y > HEIGHT))
	{
		return true;
	}
	//�ж��Ƿ���������
	for (auto iter = Snake.begin()+1; iter != Snake.end(); iter++)
	{
		if (Snake[0].x == iter->x && Snake[0].y == iter->y)
			return true;
	}
	return false;
}

int main()
{
	//��ʼ����Ϸ����
	initgraph(WIDTH*SIZE,HEIGHT*SIZE,EX_SHOWCONSOLE);
	DrawSnake();

	//�ж���Ϸ��������
	bool running = true;

	ExMessage msg;

	BeginBatchDraw();

	//��Ϸ����ѭ��
	while (running)
	{
		//��̬��ʱ�Ż�
		DWORD start_time = GetTickCount();
		//��Ϣ��ȡ
		while (peekmessage(&msg))
		{
			//��ȡ���̰���ʱ�������������,�ɿ�����ʱ�Գ�ԭ�����ƶ���ֱ��������һ�������
			if (msg.message == WM_KEYDOWN)
			{
				switch (msg.vkcode)
				{
				case 0x57:
					if (!is_move_down)
					{
						is_move_up = true;
						is_move_left = false;
						is_move_right = false;
					}
					break;
				case 0x53:
					if (!is_move_up)
					{
						is_move_down = true;
						is_move_left = false;
						is_move_right = false;
					}
					break;
				case 0x41:
					if (!is_move_right)
					{
						is_move_left = true;
						is_move_up = false;
						is_move_down = false;
					}
					break;
				case 0x44:
					if (!is_move_left)
					{
						is_move_right = true;
						is_move_up = false;
						is_move_down = false;
					}
					break;
				}
			}
		}
		//��Ϣ����
		FoodSpawn();

		Snakemove(is_eaten);
		is_eaten = Eatfood();
		ScoreAdd(is_eaten);

		DrawMap();
		DrawSnake();
		//������Ϸ��ÿһ֡�������еľ��벻ͬ�����ֱ��sleep��̫����
		//Sleep(DELAY);
		DrawScoreText();

		if (CheckGameOver())
		{
			static TCHAR str[64];
			_stprintf_s(str, _T("����Ϊ:%d"), score);
			MessageBox(GetHWnd(), str, _T("��Ϸ����"), MB_OK);
			running = false;
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 10)
		{
			Sleep(1000 / 10 - delta_time);
		}
	}

	EndBatchDraw();

	closegraph();

	return 0;
}