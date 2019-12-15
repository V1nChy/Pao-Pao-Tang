#include"StdAfx.h"
#include"Paopao.h"

extern int map[HEIGHT][WIDTH];
extern int giftMap[HEIGHT][WIDTH];
extern struct Role *role1, *role2;

//确定泡泡所在的位置
void Paopao::AddRealPopo(struct Role *&trole)
{
	int temp_x, temp_y;
	temp_x = trole->x / 40;
	temp_y = trole->y / 40;
	if (trole->x - temp_x * 40 <= 20 && trole->y - temp_y * 40 <= 10)//左上
		AddPopo(trole->lengthOfPopo, POPOLIFE, temp_x, temp_y, trole->roleId, trole);
	else if (trole->x - temp_x * 40 > 20 && trole->y - temp_y * 40 <= 10)//右上
		AddPopo(trole->lengthOfPopo, POPOLIFE, temp_x + 1, temp_y, trole->roleId, trole);
	else if (trole->x - temp_x * 40 <= 20 && trole->y - temp_y * 40 > 10)//左下
		AddPopo(trole->lengthOfPopo, POPOLIFE, temp_x, temp_y + 1, trole->roleId, trole);
	else                                                //右下
		AddPopo(trole->lengthOfPopo, POPOLIFE, temp_x + 1, temp_y + 1, trole->roleId, trole);

}

//增加一个泡泡，lengthOfPopo为泡泡长，life为泡泡生命周期  x，y表示泡泡所在的矩阵
void Paopao::AddPopo(int lengthOfPopo, int life, int x, int y, int roleId, struct Role *trole)
{
	if (map[y][x] == POPO)
		return;
	else if (map[y][x] == SANDBLOCKYELLOW)
		return;
	trole->putPopo++;
	if (map[y][x] != SandTent)
			map[y][x] = POPO;
	struct Popo *temp = new struct Popo[1];
	struct Popo *p;

	//还没泡泡直接等
	if (popo == NULL)
	{
		popo = temp;
		popo->next = NULL;
		//	temp = popo;
	}
	//根据y，x排序先后
	else
	{
		p = popo;
		if (y < p->y || (y == p->y && x > p->x))
		{
			temp->next = popo;
			popo = temp;
		}
		else
		{
			while (p->next != NULL)
			{
				if (y < p->next->y || (y == p->next->y && x > p->next->x))
					break;
				else
					p = p->next;
			}
			temp->next = p->next;
			p->next = temp;
		}
	}

	temp->lengthOfPopo = lengthOfPopo;
	temp->life = 1;
	temp->x = x;
	temp->y = y;
	temp->roleId = roleId;
}

//找到指定泡泡结点
struct Popo * Paopao::GetPopo(int x, int y)
{
	struct Popo *temp = popo;

	if (temp->x == x && temp->y == y)
	{
		return temp;
	}

	while (temp->next != NULL)
	{
		temp = temp->next;
		if (temp->x == x && temp->y == y)
		{
			//使用了全局变量role1，role2...not good
			/*		if(temp->roleId == role1->roleId)
			role1->numOfPopo--;
			else
			role2->numOfPopo--;
			*/
			return temp;
		}
	}
	return NULL;
}

//找到指定泡泡坐标
void Paopao::GetPutPopoXY(int x, int y, int &popo_x, int &popo_y)
{
	int temp_x, temp_y;
	temp_x = x / 40;
	temp_y = y / 40;
	if (x - temp_x * 40 <= 20 && y - temp_y * 40 <= 10)//偏左上
	{
		popo_x = temp_x;
		popo_y = temp_y;
	}

	else if (x - temp_x * 40 > 20 && y - temp_y * 40 <= 10)//偏右上
	{
		popo_x = temp_x + 1;
		popo_y = temp_y;
	}
	else if (x - temp_x * 40 <= 20 && y - temp_y * 40 > 10)//偏左下
	{
		popo_x = temp_x;
		popo_y = temp_y + 1;
	}
	else
	{
		popo_x = temp_x + 1;
		popo_y = temp_y + 1;
	}
}

//删除指定泡泡结点
void Paopao::DeletePopo(struct Popo *p)
{
	//头
	if (popo == p)
	{
		popo = p->next;
		delete p;
		return;
	}

	struct Popo *temp = popo;
	while (temp->next != p)
		temp = temp->next;

	temp->next = p->next;
	delete p;
}

void Paopao::Deleteall()
{
	struct Popo *p = popo;
	//删除泡泡
	while (p != NULL)
	{
		popo = popo->next;
		delete p;
		p = popo;
	}
}

//处理要爆的泡泡，x, y表示要爆炸的泡泡所在的矩阵
void Paopao::DealExPopo(int x, int y)
{
	struct Popo *p = GetPopo(x, y);
	//使用了全局变量role1，role2...not good
	if (p->roleId == role1->roleId)
		role1->putPopo--;
	else
		role2->putPopo--;

	if (map[y][x] != SandTent)
			map[y][x] = EXPLOSIONCENTRE;

	//爆炸范围
	//上
	for (int i = 1; i<p->lengthOfPopo; i++)
	{
		if (y - i >= 0)
		{
			if (map[y - i][x] == POPO)
				DealExPopo(x, y - i);
			else if (map[y - i][x] >= SANDGROUND && map[y - i][x] <= GIFT8)
				map[y - i][x] = EXPLOSIONUP;
			else if (map[y - i][x] == SANDBLOCKYELLOW)//炸到箱子就停止了
			{
				map[y - i][x] = giftMap[y - i][x];
				break;
			}
			else if (map[y - i][x] == SandTree || map[y - i][x] == SandOasisAni)//炸到墙停止
				break;
		}
		else//越界
			break;
	}
	for (int i = 1; i<p->lengthOfPopo; i++)//下
	{
		if (y + i < HEIGHT)
		{
			if (map[y + i][x] == POPO)
				DealExPopo(x, y + i);
			else if (map[y + i][x] >= SANDGROUND && map[y + i][x] <= GIFT8)
				map[y + i][x] = EXPLOSIONDOWN;
			else if (map[y + i][x] == SANDBLOCKYELLOW)
			{
				map[y + i][x] = giftMap[y + i][x];
				break;
			}
			else if (map[y + i][x] == SandTree || map[y + i][x] == SandOasisAni)
				break;

		}
		else
			break;
	}
	//LEFT
	for (int i = 1; i<p->lengthOfPopo; i++)//左
	{
		if (x - i >= 0)
		{
			if (map[y][x] == SandTent)
				break;
			if (map[y][x - i] == POPO)
				DealExPopo(x - i, y);
			else if (map[y][x - i] >= SANDGROUND && map[y][x - i] <= GIFT8)
				map[y][x - i] = EXPLOSIONLEFT;

			else if (map[y][x - i] == SANDBLOCKYELLOW)
			{
				map[y][x - i] = giftMap[y][x - i];
				break;
			}
			else if (map[y][x - i] == SandTree || map[y][x - i] == SandOasisAni || map[y][x - i] == SandTent )
				break;

		}
		else
			break;
	}
	
	for (int i = 1; i<p->lengthOfPopo; i++)//右
	{
		if (x + i < WIDTH)
		{
			if (map[y][x] == SandTent)
				break;
			if (map[y][x + i] == POPO)
				DealExPopo(x + i, y);
			else if (map[y][x + i] >= SANDGROUND && map[y][x + i] <= GIFT8)
				map[y][x + i] = EXPLOSIONRIGHT;
			else if (map[y][x + i] == SANDBLOCKYELLOW)
			{
				map[y][x + i] = giftMap[y][x + i];
				break;
			}
			else if (map[y][x + i] == SandTree || map[y][x + i] == SandOasisAni || map[y][x + i] == SandTent)
				break;

		}
		else
			break;
	}
	DeletePopo(p);
}