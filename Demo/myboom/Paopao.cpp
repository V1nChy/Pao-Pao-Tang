#include"StdAfx.h"
#include"Paopao.h"

extern int map[HEIGHT][WIDTH];
extern int giftMap[HEIGHT][WIDTH];
extern struct Role *role1, *role2;

//ȷ���������ڵ�λ��
void Paopao::AddRealPopo(struct Role *&trole)
{
	int temp_x, temp_y;
	temp_x = trole->x / 40;
	temp_y = trole->y / 40;
	if (trole->x - temp_x * 40 <= 20 && trole->y - temp_y * 40 <= 10)//����
		AddPopo(trole->lengthOfPopo, POPOLIFE, temp_x, temp_y, trole->roleId, trole);
	else if (trole->x - temp_x * 40 > 20 && trole->y - temp_y * 40 <= 10)//����
		AddPopo(trole->lengthOfPopo, POPOLIFE, temp_x + 1, temp_y, trole->roleId, trole);
	else if (trole->x - temp_x * 40 <= 20 && trole->y - temp_y * 40 > 10)//����
		AddPopo(trole->lengthOfPopo, POPOLIFE, temp_x, temp_y + 1, trole->roleId, trole);
	else                                                //����
		AddPopo(trole->lengthOfPopo, POPOLIFE, temp_x + 1, temp_y + 1, trole->roleId, trole);

}

//����һ�����ݣ�lengthOfPopoΪ���ݳ���lifeΪ������������  x��y��ʾ�������ڵľ���
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

	//��û����ֱ�ӵ�
	if (popo == NULL)
	{
		popo = temp;
		popo->next = NULL;
		//	temp = popo;
	}
	//����y��x�����Ⱥ�
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

//�ҵ�ָ�����ݽ��
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
			//ʹ����ȫ�ֱ���role1��role2...not good
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

//�ҵ�ָ����������
void Paopao::GetPutPopoXY(int x, int y, int &popo_x, int &popo_y)
{
	int temp_x, temp_y;
	temp_x = x / 40;
	temp_y = y / 40;
	if (x - temp_x * 40 <= 20 && y - temp_y * 40 <= 10)//ƫ����
	{
		popo_x = temp_x;
		popo_y = temp_y;
	}

	else if (x - temp_x * 40 > 20 && y - temp_y * 40 <= 10)//ƫ����
	{
		popo_x = temp_x + 1;
		popo_y = temp_y;
	}
	else if (x - temp_x * 40 <= 20 && y - temp_y * 40 > 10)//ƫ����
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

//ɾ��ָ�����ݽ��
void Paopao::DeletePopo(struct Popo *p)
{
	//ͷ
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
	//ɾ������
	while (p != NULL)
	{
		popo = popo->next;
		delete p;
		p = popo;
	}
}

//����Ҫ�������ݣ�x, y��ʾҪ��ը���������ڵľ���
void Paopao::DealExPopo(int x, int y)
{
	struct Popo *p = GetPopo(x, y);
	//ʹ����ȫ�ֱ���role1��role2...not good
	if (p->roleId == role1->roleId)
		role1->putPopo--;
	else
		role2->putPopo--;

	if (map[y][x] != SandTent)
			map[y][x] = EXPLOSIONCENTRE;

	//��ը��Χ
	//��
	for (int i = 1; i<p->lengthOfPopo; i++)
	{
		if (y - i >= 0)
		{
			if (map[y - i][x] == POPO)
				DealExPopo(x, y - i);
			else if (map[y - i][x] >= SANDGROUND && map[y - i][x] <= GIFT8)
				map[y - i][x] = EXPLOSIONUP;
			else if (map[y - i][x] == SANDBLOCKYELLOW)//ը�����Ӿ�ֹͣ��
			{
				map[y - i][x] = giftMap[y - i][x];
				break;
			}
			else if (map[y - i][x] == SandTree || map[y - i][x] == SandOasisAni)//ը��ǽֹͣ
				break;
		}
		else//Խ��
			break;
	}
	for (int i = 1; i<p->lengthOfPopo; i++)//��
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
	for (int i = 1; i<p->lengthOfPopo; i++)//��
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
	
	for (int i = 1; i<p->lengthOfPopo; i++)//��
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