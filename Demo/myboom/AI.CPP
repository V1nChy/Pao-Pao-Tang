#include "StdAfx.h"
#include "AI.h"
#include"Paopao.h"

struct Block *blockHead;
extern bool begin;//开始准备状态
extern bool end;//结束状态
extern int giftMap[HEIGHT][WIDTH];
extern int map[HEIGHT][WIDTH];
extern Paopao paopao;
//AI/获取提前的爆炸信息/popo 泡泡指针头/popoExpMap 要保存到的二维数组
void AI::GetPopoExpMap(struct Role *AI,int tMap[HEIGHT][WIDTH], struct Popo *popo, int popoExpMap[HEIGHT][WIDTH])
{
	struct Popo *p = popo;

	while(p != NULL)
	{
		if(p->life > DANPOPO)
			popoExpMap[p->y][p->x] = DPOPO*100 + p->lengthOfPopo;//危险泡泡

		else
			popoExpMap[p->y][p->x] = POPO*100 + p->lengthOfPopo;//将要危险泡泡

		p = p->next;
	}
	p = popo;
	while(p != NULL)
	{
		if(popoExpMap[p->y][p->x]/100 == DPOPO)
			GetDMap(AI, tMap, popoExpMap, p->x, p->y, DEXPLOTION);//获取危险的地方

		p = p->next;
	}
	p = popo;
	while(p != NULL)
	{
		if(popoExpMap[p->y][p->x]/100 == POPO)
			GetDMap(AI, tMap, popoExpMap, p->x, p->y, WDEXPLOTION);//获取准备危险的地方

		p = p->next;
	}
}

//获取一个泡泡提前产生的爆炸信息/popoExpMap 要保存到的二维数组/x, y泡泡所在的坐标矩阵/level提前爆炸级别
void AI::GetDMap(struct Role *AI,int tMap[HEIGHT][WIDTH], int popoExpMap[HEIGHT][WIDTH], int x, int y, int level)
{
	int len = popoExpMap[y][x]%100;
	popoExpMap[y][x] = level;//。。。。。。。。。
	bool flag[4] = {true,true,true,true};
	for(int i=0; i < len; i++)
	{
		if(flag[0])
		{
			if(x+i < WIDTH)
			{
				if (CanMove(AI, RIGHT, tMap, y, x + i))
			//	if(popoExpMap[y][x+i] == SANDGROUND)
					popoExpMap[y][x+i] = level;
				else if(tMap[y][x+i] == SANDBLOCKYELLOW ||
					tMap[y][x + i] == SandTree)
					flag[0] = false;
				else if(popoExpMap[y][x+i]/100 == POPO)
				{
					popoExpMap[y][x+i] = DPOPO*100 + len;
					GetDMap(AI, tMap, popoExpMap, x + i, y, level);
				}
				
			}
			else
				flag[0] = false;
		}
		if(flag[1])
		{
			if(x-i >= 0)
			{
				if (CanMove(AI, LEFT, tMap, y, x - i))
				//if(popoExpMap[y][x-i] == SANDGROUND)
					popoExpMap[y][x-i] = level;
				else if(tMap[y][x-i] == SANDBLOCKYELLOW ||
					tMap[y][x - i] == SandTree)
					flag[1] = false;
				else if(popoExpMap[y][x-i]/100 == POPO)
				{
					popoExpMap[y][x-i] = DPOPO*100 + len;
					GetDMap(AI, tMap, popoExpMap, x - i, y, level);
				}
				
			}
			else
				flag[1] = false;
		}
		if(flag[2])
		{
			if(y+i < HEIGHT)
			{
				if (CanMove(AI, DOWN, tMap, y + i, x))
			//	if(popoExpMap[y+i][x] == SANDGROUND)
					popoExpMap[y+i][x] = level;
				else if(tMap[y+i][x] == SANDBLOCKYELLOW ||
					tMap[y + i][x] == SandTree)
					flag[2] = false;
				else if(popoExpMap[y+i][x]/100 == POPO)
				{
					popoExpMap[y+i][x] = DPOPO*100 + len;
					GetDMap(AI, tMap, popoExpMap, x, y + i, level);
				}
				
			}
			else
				flag[2] = false;
		}
		if(flag[3])
		{
			if(y-i >= 0)
			{
				if (CanMove(AI, UP, tMap, y - i, x))
			//	if(popoExpMap[y-i][x] == SANDGROUND)
					popoExpMap[y-i][x] = level;
				else if(tMap[y-i][x] == SANDBLOCKYELLOW ||
					tMap[y - i][x] == SandTree)
					flag[3] = false;
				else if(popoExpMap[y-i][x]/100 == POPO)
				{
					popoExpMap[y-i][x] = DPOPO*100 + len;
					GetDMap(AI, tMap, popoExpMap, x, y - i, level);
				}
				
			}
			else
				flag[3] = false;
		}
	}
}

//判断指定位置的四周有没有指定值的物质/x,y坐标/value 物品对应值
bool AI::HavePoint(int tMap[HEIGHT][WIDTH], int x, int y, int value, int &point_x, int &point_y)
{
	
	if(x+1 < WIDTH && tMap[y][x+1] == value)
	{
		point_x = x+1;
		point_y = y;
		return true;
	}
	else if(x-1 >= 0 && tMap[y][x-1] == value)
	{
		point_x = x-1;
		point_y = y;
		return true;
	}
	else if(y-1 >= 0 && tMap[y-1][x] == value)
	{
		point_x = x;
		point_y = y-1;
		return true;
	}
	else if(y+1 < HEIGHT && tMap[y+1][x] == value)
	{
		point_x = x;
		point_y = y+1;
		return true;
	}

	return false;
}

//获取是否放泡泡/tMap地图信息/popoExpMap提前爆炸的信息数组/AI,enemy/popo 泡泡头指针
bool AI::GetPutPopo(int tMap[HEIGHT][WIDTH], const int popoExpMap[HEIGHT][WIDTH],struct Role *AI, struct Role *enemy, struct Popo *popo)
{
	int skew_x, skew_y, x, y, popo_x, popo_y;
	GetPutPopoXY(AI->x, AI->y, popo_x, popo_y);
	skew_x = 20;
	skew_y = SKEW_Y;
	//有道具则不放泡泡
	if(popoExpMap[(AI->y + skew_y)/40][(AI->x + skew_x)/40] != DEXPLOTION
		&& popoExpMap[(AI->y)/40][(AI->x)/40] != DEXPLOTION
		&& tMap[(AI->y + skew_y)/40][(AI->x + skew_x)/40] < EXPLOSIONCENTRE
		&& (GetDistance((AI->x + skew_x)/40, (enemy->x + skew_x)/40) <= 5
		&& GetDistance((AI->y + skew_y)/40, (enemy->y + skew_y)/40) <= 5)
		&& !GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, SANDBLOCKYELLOW, 0))
		return true;
	else if(GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, SANDBLOCKYELLOW, 0)
		&& popoExpMap[(AI->y + skew_y)/40][(AI->x + skew_x)/40] != WDEXPLOTION
		&& popoExpMap[(AI->y + skew_y)/40][(AI->x + skew_x)/40] != DEXPLOTION)
	{
		if(	(GetDistance(popo_x, x) == 0 && GetDistance(popo_y, y) == 0))
			if(popoExpMap[y][x] != WDEXPLOTION && popoExpMap[y][x] != DEXPLOTION
				&& popoExpMap[popo_y][popo_x] != DEXPLOTION)
				return true;
	}

	return false;
}

//AI的处理/AI,enemy人物指针/direction要返回的方向/putPopo是否放泡泡，返回/popo 泡泡头指针
void AI::AIDeal(int tMap[HEIGHT][WIDTH], struct Role *AI, struct Role *enemy, struct Popo *popo, int &direction, bool &putPopo)
{
	bool agreePutPopo = true;
	int popoExpMap[HEIGHT][WIDTH];
	for(int i=0; i<WIDTH; i++)
		for(int j=0; j<HEIGHT; j++)
			popoExpMap[j][i] = 0;
	//计算出地图要爆炸泡泡及对应时间
		GetPopoExpMap(AI, tMap, popo, popoExpMap);
	//获取运动方向，是否要进行泡泡的放置
	direction = GetDirection(tMap, popoExpMap, AI, enemy, popo, agreePutPopo);
	//
	if(agreePutPopo)
		putPopo = GetPutPopo(tMap, popoExpMap, AI, enemy, popo);
}

//获取方向/tMap地图/AI 智能电脑/enemy AI对手
int AI::GetDirection(int tMap[HEIGHT][WIDTH], const int popoExpMap[HEIGHT][WIDTH],
				 struct Role *AI, struct Role *enemy, struct Popo *popo, bool &agreePutPopo)
{

	int x, y, direction = -1;
	int block_x, block_y;
	int popo_x, popo_y;
	int skew_x, skew_y;
	skew_x = 20;
	skew_y = SKEW_Y+10;
	
	//像素坐标转换为15*13的数组坐标
	GetPutPopoXY(AI->x, AI->y, popo_x, popo_y);

//	GetPoint(tMap, popoExpMap, popo_x, popo_y, block_x, block_y, SANDBLOCKYELLOW);//获取可炸方块的位置
	//AI电脑正站在计算危险的地方，马上无条件转移，优先级最高	
	if(popoExpMap[(AI->y + skew_y)/40][(AI->x + skew_x)/40] == DEXPLOTION)//不安全
	{
		//获取距离本身最近的安全的地方，SANDGROUND为安全值. x, y为获取到的安全地点
		GetPoint(tMap, popoExpMap, (AI->x + skew_x)/40, (AI->y + skew_y)/40, x, y, SANDGROUND, 1);

		//算出移动目标地点当前最近的方向
		direction = MoveToPoint(AI, tMap, (AI->x + skew_x) / 40, (AI->y + skew_y) / 40, x, y);
		switch(direction)
		{
		case UP:
			//如果要移动方向的下一格为爆炸区，则direction = -1,即不移动
			if( tMap[(AI->y - AI->speed + skew_y)/40][(AI->x + skew_x)/40] >= EXPLOSIONCENTRE)
				direction = -1;
		case DOWN:
			if( tMap[(AI->y + AI->speed + skew_y)/40][(AI->x + skew_x)/40] >= EXPLOSIONCENTRE)
				direction = -1;
		case LEFT:
			if( tMap[(AI->y + skew_y)/40][(AI->x  - AI->speed+ skew_x)/40] >= EXPLOSIONCENTRE)
				direction = -1;
		case RIGHT:
			if( tMap[(AI->y + skew_y)/40][(AI->x  + AI->speed+ skew_x)/40] >= EXPLOSIONCENTRE)
				direction = -1;
		}
		return direction;
	}
	//获取道具坐标
	else if(GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, GIFT4, 1)
		||GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, GIFT5, 1)
		||GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, GIFT1, 1)
		||GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, GIFT2, 1)
		||GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, GIFT3, 1)
		|| GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, GIFT6, 1)
		|| GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, GIFT7, 1)
		|| GetPoint(tMap, popoExpMap, popo_x, popo_y, x, y, GIFT8, 1))
	{
		//如果道具所在的地方为危险区则放弃
		if(popoExpMap[y][x] < DEXPLOTION)
			direction = MoveToPoint(AI, tMap, popo_x, popo_y,
				x, y);
		//拾取道具过程不放泡泡
		agreePutPopo = false;
	}
	//获取周围最近的可炸的方块
	else if(GetPoint(tMap, popoExpMap, popo_x, popo_y, block_x, block_y, SANDBLOCKYELLOW, 0))
	{
		if(popoExpMap[block_y][block_x] != WDEXPLOTION && popoExpMap[block_y][block_x] != DEXPLOTION && 
			!HavePoint(tMap, popo_x, popo_y, SANDBLOCKYELLOW, block_x, block_y) )//有可炸方块且本身没到达
			//算出移动到方块处最短距离所要移动的方向
			direction = MoveToPoint(AI, tMap, popo_x, popo_y,
				block_x, block_y);
	}
	//AI开始攻击玩家

	//如果与玩家X方向或Y方向的距离超过5，移动而不放泡泡
	else if((GetDistance((AI->x + skew_x)/40, (enemy->x + skew_x)/40) >= 5
		|| GetDistance((AI->y + skew_y)/40, (enemy->y + skew_y)/40) >= 5))
	{
		//移动
		direction = MoveToPoint(AI, tMap, (AI->x + skew_x) / 40, (AI->y + skew_y) / 40,
			(enemy->x + skew_x)/40, (enemy->y + skew_y)/40);
	}
	//1.x方向或y方向距离小于5
	//2.x方向距离小于y方向距离
	//3.距离大于1
	//往x方向移动并放泡泡达到攻击的效果
	else if(GetDistance((AI->x + skew_x)/40, (enemy->x + skew_x)/40) <= 
		GetDistance((AI->y + skew_y)/40, (enemy->y + skew_y)/40)
		&& GetDistance((AI->x )/40 , (enemy->x)/40) > 1)
		direction = MoveToPoint(AI, tMap, (AI->x + skew_x) / 40, (AI->y + skew_y) / 40,
			(enemy->x + skew_x)/40, (AI->y + skew_y)/40);
	//与上面类似，往y方向移动并不断放泡泡攻击
	else if(GetDistance((AI->x + skew_x)/40, (enemy->x + skew_x)/40) > 
	    GetDistance((AI->y + skew_y)/40, (enemy->y + skew_y)/40)
		&& GetDistance((AI->y)/40 , (enemy->y)/40 ) > 1)
		direction = MoveToPoint(AI, tMap, (AI->x + skew_x) / 40, (AI->y + skew_y) / 40,
			(AI->x + skew_x)/40, (enemy->y + skew_y)/40);
	
	else if(AI->x < enemy->x - AI->speed && GetDistance((AI->x )/40 , (enemy->x)/40) <= 1
		&& tMap[AI->y/40][(AI->x + AI->speed)/40] == SANDGROUND && tMap[AI->y/40 + 1][(AI->x + AI->speed)/40] == SANDGROUND)
			direction = RIGHT;
	else if(AI->x > enemy->x + AI->speed && GetDistance((AI->x )/40 , (enemy->x)/40) <= 1
		&& tMap[AI->y/40][(AI->x - AI->speed)/40] == SANDGROUND && tMap[AI->y/40 + 1][(AI->x- AI->speed)/40] == SANDGROUND)
			direction = LEFT;
	else if(AI->y < enemy->y - AI->speed && GetDistance((AI->y)/40 , (enemy->y)/40 ) <= 1
		&& tMap[(AI->y + AI->speed)/40][(AI->x)/40] == SANDGROUND && tMap[(AI->y + AI->speed)/40][(AI->x)/40+1] == SANDGROUND)
			direction = DOWN;
	else if(AI->y > enemy->y + AI->speed && GetDistance((AI->y)/40 , (enemy->y)/40 ) <= 1
		&& tMap[(AI->y - AI->speed)/40][(AI->x)/40] == SANDGROUND && tMap[(AI->y - AI->speed)/40][(AI->x)/40+1] == SANDGROUND)
			direction = UP;

	//在最后确定攻击敌方所移动的方向是否危险，危险则不移动
	switch(direction)
	{
	case UP:
		if(popoExpMap[(AI->y - AI->speed + skew_y)/40][(AI->x + skew_x)/40] == DEXPLOTION
			|| tMap[(AI->y - AI->speed + skew_y)/40][(AI->x + skew_x)/40] >= EXPLOSIONCENTRE)
			direction = -1;
	case DOWN:
		if(popoExpMap[(AI->y + AI->speed + skew_y)/40][(AI->x + skew_x)/40] == DEXPLOTION
		    || tMap[(AI->y + AI->speed + skew_y)/40][(AI->x + skew_x)/40] >= EXPLOSIONCENTRE)
			direction = -1;
	case LEFT:
		if(popoExpMap[(AI->y + skew_y)/40][(AI->x - AI->speed + skew_x)/40] == DEXPLOTION
			|| tMap[(AI->y + skew_y)/40][(AI->x  - AI->speed+ skew_x)/40] >= EXPLOSIONCENTRE)
			direction = -1;
	case RIGHT:
		if(popoExpMap[(AI->y + skew_y)/40][(AI->x + AI->speed + skew_x)/40] == DEXPLOTION
			|| tMap[(AI->y + skew_y)/40][(AI->x  + AI->speed+ skew_x)/40] >= EXPLOSIONCENTRE)
			direction = -1;
	}

	return direction;
}

//查找指定value值的地方/popoExpMap 提前爆炸的信息/AIx,AIy AI所在坐标/x,y返回的安全地方的坐标
//value 查找最近值为value的地方/没找到则x，y=-1/prior是否是返回找到它时它的之前一个块
bool AI::GetPoint(int tMap[HEIGHT][WIDTH], const int popoExpMap[HEIGHT][WIDTH],
			 int AIx, int AIy , int &x, int &y, int value, int prior)
{
	int i=0, j=0;
	int Amap[HEIGHT][WIDTH];//2标记则为已经寻过，1则表示已经删除
	blockHead = new struct Block[1];
	blockHead->next = NULL;
	struct Block *p = blockHead;
	InitBlock(blockHead, AIx, AIy, 0, 0, 1);
	Amap[p->y][p->x] = 1;
//	x = -1;
//	y = -1;
	while(p != NULL)
	{
		if(p->x+1 < WIDTH && Amap[p->y][p->x+1] != 1)
		{
			if(popoExpMap[p->y][p->x+1] != DEXPLOTION && tMap[p->y][p->x+1] == value)
			{
				x = p->x+1*prior;
				y = p->y;
				DeleteAll(blockHead);
				return true;
			}
			else if(tMap[p->y][p->x+1] != SANDBLOCKYELLOW &&
				tMap[p->y][p->x + 1] != SandTree && tMap[p->y][p->x + 1] != POPO
				 && tMap[p->y][p->x+1] < EXPLOSIONCENTRE)
			{
				AddBlock(p->x+1, p->y, 0, 0, p->total+1);
				Amap[p->y][p->x+1] = 1;
			}
		}
		
		if(p->x-1 >=0 && Amap[p->y][p->x-1] != 1)
		{
			if(popoExpMap[p->y][p->x-1] != DEXPLOTION && tMap[p->y][p->x-1] == value)
			{
				x = p->x-1*prior;
				y = p->y;
				DeleteAll(blockHead);
				return true;
			}
			else if(tMap[p->y][p->x-1] != SANDBLOCKYELLOW &&
				tMap[p->y][p->x - 1] != SandTree && tMap[p->y][p->x - 1] != POPO
				 && tMap[p->y][p->x-1] < EXPLOSIONCENTRE)
			{
				AddBlock(p->x-1, p->y, 0, 0, p->total+1);
				Amap[p->y][p->x-1] = 1;
			}
		}
		
		if(p->y+1 < HEIGHT && Amap[p->y+1][p->x] != 1)
		{
			if(popoExpMap[p->y+1][p->x] != DEXPLOTION && tMap[p->y+1][p->x] == value)
			{
				x = p->x;
				y = p->y+1*prior;
				DeleteAll(blockHead);
				return true;
			}
			else if(tMap[p->y+1][p->x] != SANDBLOCKYELLOW &&
				tMap[p->y + 1][p->x] != SandTree && tMap[p->y + 1][p->x] != POPO
				 && tMap[p->y+1][p->x] < EXPLOSIONCENTRE)
			{
				AddBlock(p->x, p->y+1, 0, 0, p->total+1);
				Amap[p->y+1][p->x] = 1;
			}
		}
		
		if(p->y-1 >= 0 && Amap[p->y-1][p->x] != 1)
		{
			if(popoExpMap[p->y-1][p->x] != DEXPLOTION && tMap[p->y-1][p->x] == value)
			{
				x = p->x;
				y = p->y-1*prior;
				DeleteAll(blockHead);
				return true;
			}
			else if(tMap[p->y-1][p->x] != SANDBLOCKYELLOW &&
				tMap[p->y - 1][p->x] != SandTree && tMap[p->y - 1][p->x] != POPO
				 && tMap[p->y-1][p->x] < EXPLOSIONCENTRE)
			{
				AddBlock(p->x, p->y-1, 0, 0, p->total+1);
				Amap[p->y-1][p->x] = 1;
			}
		}
		p = blockHead->next;
		delete blockHead;
		blockHead = p;
	}
	DeleteAll(blockHead);
	return false;
}

//A 寻路算法/移动到某点/tMap地图/AI 智能电脑/d_x,d_y目标坐标
int AI::MoveToPoint(struct Role *AI,int tMap[HEIGHT][WIDTH], int AIx, int AIy, int d_x, int d_y)
{
	int disX, disY, direction = -1;
	int x, y, use;
	int Amap[HEIGHT][WIDTH];//2标记则为已经寻过，1则表示已经删除
	//初始化。。。。。
	for(int i=0; i<WIDTH; i++)
		for(int j=0; j<HEIGHT; j++)
			Amap[j][i] = 0;
	//获取x方向距离
	disX = GetDistance(AIx, d_x);
	//Y方向距离
	disY = GetDistance(AIy, d_y);
	blockHead = new struct Block[1];
	blockHead->next = NULL;
	struct Block *p;
	InitBlock(blockHead, d_x, d_y, disX+disY, 0, disX+disY);
	Amap[blockHead->y][blockHead->x] = 1;
	while(blockHead != NULL)
	{	
		x = blockHead->x;
		y = blockHead->y;
		use = blockHead->use;
		//删除头
		p = blockHead->next;
		delete blockHead;
		blockHead = p;
		
		if(x-1 >= 0 && Amap[y][x-1] != 1)
		{
			if(y == AIy && x-1 == AIx && tMap[d_y][d_x] < EXPLOSIONCENTRE)
			{
				direction = RIGHT;
				break;
			}
			else if (CanMove(AI, LEFT, tMap, y, x - 1) && tMap[y][x - 1] < CANMOVE)
		//	else if(tMap[p->y][p->x-1] == SANDGROUND)
			{
				disX = GetDistance(AIx, x-1);
				disY = GetDistance(AIy, y);
				AddBlock(x-1, y, disX+disY, use+1, disX+disY+use+1);
			}
			Amap[y][x-1] = 1;
		}

		if(x+1 < WIDTH && Amap[y][x+1] != 1)
		{
			if(y == AIy && x+1 == AIx && tMap[d_y][d_x] < EXPLOSIONCENTRE)
			{
				direction = LEFT;
				break;
			}
			else if (CanMove(AI, RIGHT, tMap, y, x + 1) && tMap[y][x + 1] < CANMOVE)
			//else if(tMap[p->y][p->x+1] == SANDGROUND)
			{
				disX = GetDistance(AIx, x+1);
				disY = GetDistance(AIy, y);
				AddBlock(x+1, y, disX+disY, use+1, disX+disY+use+1);
			}
			Amap[y][x+1] = 1;
		}

		
		if(y+1 < HEIGHT && Amap[y+1][x] != 1)
		{
			if(y+1 == AIy && x == AIx && tMap[d_y][d_x] < EXPLOSIONCENTRE)
			{
				direction = UP;
				break;
			}
			else if (CanMove(AI, DOWN, tMap, y + 1, x) && tMap[y + 1][x] < CANMOVE)
		//	else if(tMap[p->y+1][p->x] == SANDGROUND)
			{
				disX = GetDistance(AIx, x);
				disY = GetDistance(AIy, y+1);
				AddBlock(x, y+1, disX+disY, use+1, disX+disY+use+1);
			}
			Amap[y+1][x] = 1;
		}

		if(y-1 >= 0 && Amap[y-1][x] != 1)
		{
			if(y-1 == AIy && x == AIx && tMap[d_y][d_x] < EXPLOSIONCENTRE)
			{
				direction = DOWN;
				break;
			}
			else if (CanMove(AI, UP, tMap, y - 1, x) && tMap[y - 1][x] < CANMOVE)
		//	else if(tMap[p->y-1][p->x] == SANDGROUND )
			{
				disX = GetDistance(AIx, x);
				disY = GetDistance(AIy, y-1);
				AddBlock(x, y-1, disX+disY, use+1, disX+disY+use+1);
			}
			Amap[y-1][x] = 1;
		}
	}
	DeleteAll(blockHead);
	return direction;
}

//一个方块的数据结构的赋值/temp block指针/x,y方块坐标/need到目的所要的计数
//use已经使用的计数/total总共需要的路程
void AI::InitBlock(struct Block *temp, int x, int y, int need, int use, int total)
{
	temp->x = x;
	temp->y = y;
	temp->need = need;
	temp->use = use;
	temp->total = total;
}

//增加一个方块
void AI::AddBlock(int x, int y, int need, int use, int total)
{
	struct Block *temp = new struct Block[1];
	InitBlock(temp, x, y, need, use, total);

	if(blockHead == NULL)
	{
		blockHead = temp;
		blockHead->next = NULL;
		return;
	}
	else
	{
		//头
		if(total < blockHead->total)
		{
			temp->next = blockHead;
			blockHead = temp;
			return;
		}

		struct Block *p = blockHead;
		while(p->next != NULL)
		{
			if(total < p->next->total)
			{
				temp->next = p->next;
				p->next = temp;
				return;
			}
			p = p->next;
		}

		p->next = temp;
		temp->next = NULL;
	}
}

//删除所有方块
void AI::DeleteAll(struct Block *head)
{
	struct Block *p = head;
	while(head != NULL)
	{
		p = head;
		head = head->next;
		delete p;
	}
}

//获取两点的距离
int AI::GetDistance(int x1, int x2)
{
	if(x1 >= x2)
	{
		return x1 - x2;
	}
	else
	{
		return x2 - x1;
	}
}

void AI::GetPutPopoXY(int x, int y, int &popo_x, int &popo_y)
{
	int temp_x, temp_y;
	temp_x = x / 40;
	temp_y = y / 40;
	if(x - temp_x*40 <= 20 && y - temp_y*40 <= 10)//偏左上
	{
		popo_x = temp_x;
		popo_y = temp_y;
	}

	else if(x - temp_x*40 > 20 && y - temp_y*40 <= 10)//偏右上
	{
		popo_x = temp_x+1;
		popo_y = temp_y;
	}
	else if(x - temp_x*40 <= 20 && y - temp_y*40 > 10)//偏左下
	{
		popo_x = temp_x;
		popo_y = temp_y+1;
	}
	else
	{
		popo_x = temp_x+1;
		popo_y = temp_y+1;
	}
}

//bool AI::CanMove(int tMap[HEIGHT][WIDTH], int y, int x)
//{
//	if (tMap[y][x] >= CANMOVE)
//		return true;
//
//	switch (tMap[y][x])
//	{
//	case SANDGROUND:
//	case GIFT1:
//	case GIFT2:
//	case GIFT3:
//	case GIFT4:
//	case GIFT5:
//		return true;
//	default:
//		return false;
//	}
//	return false;
//}

void AI::AutoProcess(Role *role2, Role *role1)
{
	if (role2->state <= DEATH || end || begin)
		return;
	role2->Active_keystate = true;
	bool cdirection = false;
	bool putPopo = false;
	int direction;
	//人工智能电脑运算
	//获取运动方向以及是否能放泡泡
	AIDeal(map, role2, role1, paopao.get_popo(), direction, putPopo);
	//方向值为-1表示不移动
	if (direction == -1)
	{
		role2->Active_keystate = false;
		for (int i = 0; i<4; i++)
			role2->keyState[i] = false;

		role2->state = 0;
	}
	else if (role2->keyState[direction] != true)
	{
		role2->Active_keystate = false;
		role2->direction = direction;
		for (int i = 0; i<4; i++)
			role2->keyState[i] = false;
		role2->keyState[direction] = true;
		role2->state = 0;
	}
	//能否放泡泡
	if (putPopo)
		role2->addPopo = true;

}