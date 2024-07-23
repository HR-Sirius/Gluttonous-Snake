#include<graphics.h>
#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

#define WIDTH 30
#define HEIGHT 30
#define SIZE 20
//#define DELAY  150

//创建地图二维数组
int Map[HEIGHT][WIDTH] = { 0 };

//创建结构体POSITON，记录每一节蛇身的坐标
struct POSITION
{
	int x;
	int y;
};

//创建蛇身,初始化长度为1,初始化蛇身位置为{WIDTH * SIZE / 2, HEIGHT * SIZE / 2}
vector<POSITION> Snake = { {WIDTH/ 2, HEIGHT/ 2} };
//创建食物
struct POSITION Food = { 0,0 };

//分数初始化为0
int score = 0;

//判断食物生成条件
bool is_spawn = true;
//判断食物是否已被吃掉
bool is_eaten = true;
//判断蛇是否能移动
bool is_move_up = false;
bool is_move_down = false;
bool is_move_left = false;
bool is_move_right = false;

//渲染地图
void DrawMap()
{
	line(0, 0, WIDTH * SIZE, 0);
	line(0, 0, 0, HEIGHT * SIZE);
	line(0, HEIGHT * SIZE, WIDTH * SIZE, HEIGHT * SIZE);
	line(WIDTH * SIZE, 0, WIDTH * SIZE, HEIGHT * SIZE);
}

//渲染蛇身
void DrawSnake()
{
	int i = 0;
	//更改绘制颜色为绿色
	setfillcolor(GREEN);
	//遍历vector Snake,获取每一节蛇身的位置并渲染
	for (; i < Snake.size(); i++)
	{
		fillrectangle(Snake[i].x * SIZE, Snake[i].y * SIZE, (Snake[i].x + 1) * SIZE, (Snake[i].y + 1) * SIZE);
	}
}

//显示当前分数
void DrawScoreText()
{
	static TCHAR Scorestr[10];
	_stprintf_s(Scorestr, _T("当前分数为:%d"), score);

	//更改文本颜色
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, Scorestr);
}

//蛇移动
void Snakemove(bool is_eaten)
{
	setfillcolor(GREEN);
/*这种方法每移动一次要全部遍历，会浪费性能
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
	//如果此次移动未吃到食物，则移动会清除最后一节
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
	//此次移动吃到了食物，不会清除最后一节
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

//食物生成
void FoodSpawn()
{
	//先判断是否能够生成食物，若is_spawn为true，则随机生成食物，否则说明当前地图存在食物，不生成额外食物
	if (is_spawn)
	{
		//一直生成，直到不生成在蛇身上为止
		while (true)
		{
			Food.x = rand() % WIDTH;
			Food.y = rand() % HEIGHT;
			bool flag = false;
			for (int i = 0; i < Snake.size(); i++)
			{
				//食物位置与蛇身重合
				if (Food.x == Snake[i].x && Food.y == Snake[i].y)
					break;
				//不重合，结束
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

//蛇吃食物
bool Eatfood()
{
	//成功则返回true，重新调用FoodSpawn()和ScoreAdd(),否则返回false
	if (Food.x == Snake[0].x && Food.y == Snake[0].y)
	{

		is_spawn = true;
		return true;
	}
	else
		return false;
}

//分数记录
void ScoreAdd(bool is_eaten)
{
	if (is_eaten)
	{
		score += 10;
	}
}

//判断游戏是否结束
bool CheckGameOver()
{
	//判断是否触碰地图边界
	if ((Snake[0].x < 0) || (Snake[0].x > WIDTH) || (Snake[0].y < 0) || (Snake[0].y > HEIGHT))
	{
		return true;
	}
	//判断是否触碰到蛇身
	for (auto iter = Snake.begin()+1; iter != Snake.end(); iter++)
	{
		if (Snake[0].x == iter->x && Snake[0].y == iter->y)
			return true;
	}
	return false;
}

int main()
{
	//初始化游戏画面
	initgraph(WIDTH*SIZE,HEIGHT*SIZE,EX_SHOWCONSOLE);
	DrawSnake();

	//判断游戏运行条件
	bool running = true;

	ExMessage msg;

	BeginBatchDraw();

	//游戏主体循环
	while (running)
	{
		//动态延时优化
		DWORD start_time = GetTickCount();
		//信息获取
		while (peekmessage(&msg))
		{
			//获取键盘按下时按键的虚拟键码,松开按键时仍朝原方向移动，直到按下另一个方向键
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
		//信息处理
		FoodSpawn();

		Snakemove(is_eaten);
		is_eaten = Eatfood();
		ScoreAdd(is_eaten);

		DrawMap();
		DrawSnake();
		//由于游戏的每一帧可能运行的距离不同，因此直接sleep不太合适
		//Sleep(DELAY);
		DrawScoreText();

		if (CheckGameOver())
		{
			static TCHAR str[64];
			_stprintf_s(str, _T("分数为:%d"), score);
			MessageBox(GetHWnd(), str, _T("游戏结束"), MB_OK);
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
