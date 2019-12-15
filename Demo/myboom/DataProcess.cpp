#include"stdAfx.h"
#include"AI.h"
#include"DataProcess.h"
#include"Paopao.h"

extern bool begin;//开始准备状态
extern bool end;//结束状态
extern int giftMap[HEIGHT][WIDTH];
extern int map[HEIGHT][WIDTH];
extern Paopao paopao;
extern struct Role *role1, *role2;
extern int GameStytle;
//获得道具，移动，角色改变，放泡泡
void DataProcess::DealRole(int tMap[HEIGHT][WIDTH], struct Role *&trole, bool tstate)
{

	if (trole->state > DEATH)//没死,begin,end状态限制移动
	{
		int x=0, y=0;//角色坐标位置可获得的道具坐标
		if (trole->ride == GIFT6)
			tMap[x][y] = SANDGROUND;
		else
			paopao.GetPutPopoXY(trole->x, trole->y, x, y);
		switch (tMap[y][x] )//获得道具
		{
			case GIFT1:
				if (trole->numOfPopo < MAXPOPO)
					trole->numOfPopo++;
				tMap[y][x] = SANDGROUND;
			break;
			case GIFT2:
				if (trole->speed < MAXSPEED)
					trole->speed++;
				tMap[y][x] = SANDGROUND;
			break;
			case GIFT3:
				if (trole->lengthOfPopo < MAXLENGOFPOPO)
					trole->lengthOfPopo++;
				tMap[y][x] = SANDGROUND;
			break;
			case GIFT4:
				trole->lengthOfPopo = MAXLENGOFPOPO;
				tMap[y][x] = SANDGROUND;
			break;
			case GIFT5:
				trole->speed = MAXSPEED;
				tMap[y][x] = SANDGROUND;
			break;
			case GIFT6:
				trole->ride = GIFT6;
				tMap[y][x] = SANDGROUND;
				break;
			case GIFT7:
				trole->ride = GIFT7;
				tMap[y][x] = SANDGROUND;
				break;
			case GIFT8:
				trole->ride = GIFT8;
				tMap[y][x] = SANDGROUND;
				break;
		}



		if (trole->keyState[UP])
		{
			if (MoveJudge(trole, UP, trole->x, trole->y, trole->speed))
				trole->y -= trole->speed;
		}
		else if (trole->keyState[DOWN])
		{
			if (MoveJudge(trole, DOWN, trole->x, trole->y, trole->speed))
				trole->y += trole->speed;
		}
		else if (trole->keyState[LEFT])
		{
			if (MoveJudge(trole, LEFT, trole->x, trole->y, trole->speed))
				trole->x -= trole->speed;
		}
		else if (trole->keyState[RIGHT])
		{
			if (MoveJudge(trole, RIGHT, trole->x, trole->y, trole->speed))
				trole->x += trole->speed;
		}



		if (tstate == true)
		{
			trole->state = (trole->state + 1) % 12;//状态
		}
		else
			trole->state = 0;



		if (trole->addPopo == true )
		{
			if (trole->putPopo < trole->numOfPopo)
				paopao.AddRealPopo(trole);
			trole->addPopo = false;
		}



		if (!JudgeDead(trole->x, trole->y) && trole->x != trole->immunex && trole->y!=trole->immuney) //死
		{

			if (trole->ride)
			{
				trole->immunex = trole->x;
				trole->immuney = trole->y;
				trole->ride=0;
			}
			else
			{
				trole->state = DEATH;

			}
		}
	}
	else if (trole->state <= DEATH)//死，死亡泡泡的爆炸时间
	{
		trole->state--;
		if (trole->state < DEATH - HELPTIME - 25)
		{
			end = true;//
			delete trole;//删除
			trole = NULL;
		}
	}

}

//玩家初始化，x:出生在x坐标。
void DataProcess::InitRole(struct Role *&trole, int x, int y, int roleId)
{

	trole = new struct Role[1];

	trole->state = BEGINSTATE;
	trole->x = 40 * x;
	trole->y = 40 * y;

	trole->ride = BEGINRIDE;
	trole->speed = BEGINSPEED;
	trole->lengthOfPopo = BEGINLENGTHOFPOPO;
	trole->numOfPopo = BEGINNUMOFPOPO;


	trole->putPopo = 0;
	trole->roleId = roleId;
	trole->direction = DOWN;
	trole->addPopo = false;
	trole->keyState[0] = false;
	trole->keyState[1] = false;
	trole->keyState[2] = false;
	trole->keyState[3] = false;
	trole->ride = 0;
	trole->Active_keystate = false;//右玩家按键状态
	trole->immunex = -1;
	trole->immuney = -1;
}

//游戏数据的初始化，map,gift
void DataProcess::InitDate()
{
	//PlaySound("..\\Debug\\sound\\back.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	int x, limitgift4 = 0, limitgift5 = 0, limitgift6 = 0, limitgift7 = 0, limitgift8 = 0;
	FILE *fp;//文件句柄
	srand((unsigned)time(NULL));
	if ((fp = fopen("ini.ini", "rb")) == NULL)//返回有效指针
		return;
	for (int i = 0; i<HEIGHT; i++)
	for (int j = 0; j<WIDTH; j++)
	{
		giftMap[i][j] = 0;
		fscanf(fp, "%d", &map[i][j]);
		if (map[i][j] == 7)
		{
			map[i][j] = SandTree;
		}
		else if (map[i][j] == 8)
		{
			map[i][j] = SandOasisAni;
		}
		else if (map[i][j] == 9)
		{
			map[i][j] = SandTent;
		}
		else if (map[i][j] == 1)//地图随机
		{
			x = rand() % 112;
			map[i][j] = 0;
			if (x <= 100)
			{
				map[i][j] = SANDBLOCKYELLOW;
				if (x >= 0 && x <= 7)
					giftMap[i][j] = GIFT1;
				else if (x <= 15)
					giftMap[i][j] = GIFT2;
				else if (x <= 26)
					giftMap[i][j] = GIFT3;
				else if (x == 27 && limitgift4 < Limit_gift4)
				{
					giftMap[i][j] = GIFT4;
					limitgift4++;
				}
				else if (x == 30 && limitgift5 < Limit_gift5)
				{
					giftMap[i][j] = GIFT5;//红牛
					limitgift5++;
				}
				else if (x <= 32 && limitgift6 < Limit_ride)
				{
					giftMap[i][j] = GIFT6;
					limitgift6++;
				}
				else if (x <= 34 && limitgift7 < Limit_ride)
				{
					giftMap[i][j] = GIFT7;
					limitgift7++;
				}
				else if (x <= 36 && limitgift8 < Limit_ride)
				{
					giftMap[i][j] = GIFT8;
					limitgift8++;
				}
			}
		}
	}

	fclose(fp);

}

//游戏初始化
void DataProcess::GameStart()
{
	//int x, y;
	//删除泡泡
	paopao.Deleteall();
	//PlaySound("..\\Debug\\sound\\start.wav", NULL, SND_FILENAME);
	InitDate();

	InitRole(role2, 14, 12, ROLE2);

	InitRole(role1, 3, 2, ROLE1);

	if (GameStytle == 1)
	{
		role1->Auto = false;
		role2->Auto = true;
	}
	else if (GameStytle == 2)
	{
		role1->Auto = false;
		role2->Auto = false;
	}

}