#include"stdAfx.h"
#include"Judge.h"
extern int map[HEIGHT][WIDTH];
//�ж�ָ��λ���Ƿ���ͨ��
bool Judge::CanMove(struct Role *&trole,int derect, int tMap[HEIGHT][WIDTH], int y, int x)
{
	if (trole->ride == GIFT6 && tMap[y][x] == SANDBLOCKYELLOW)
		return true;
	if (tMap[y][x] >= CANMOVE)
		return true;
	if (tMap[y][x] == SandTent)
	{
		if (derect == UP || derect == DOWN)
			return true;
		else
			return false;
	}
	if (derect == RIGHT)
	{
		if (tMap[y][x - 1] == SandTent)
			return false;
	}
	else if (derect == LEFT)
	{
		if (tMap[y][x + 1] == SandTent)
			return false;
	}
	switch (tMap[y][x])
	{
	case SANDGROUND:
	case GIFT1:
	case GIFT2:
	case GIFT3:
	case GIFT4:
	case GIFT5:
	case GIFT6:
	case GIFT7:
	case GIFT8:
		return true;
	default:
		return false;
	}
	return false;
}

//�ж������Ƿ����ƶ�,���򷵻�true ������role��x���꣬y���꣬role�ٶ�
bool Judge::MoveJudge(struct Role *&trole,int derect, int &x, int &y, int speed)
{
	switch (derect)
	{
	case UP:
	{
			   if (y - speed < 0)
			   {
				   y = 0;
				   return false;
			   }
			   if ((y - speed) / 40 != y / 40)
			   {
				   //�Ƿ�ռ��������
				   if (x != x / 40 * 40)//��
				   {
					   if (CanMove(trole, derect, map, (y - speed) / 40, x / 40) && CanMove(trole, derect, map, (y - speed) / 40, x / 40 + 1))
						   return true;
					   else if ((!CanMove(trole, derect, map, (y - speed) / 40, x / 40)) && (!CanMove(trole, derect, map, (y - speed) / 40, x / 40 + 1)))
					   {
						   y = y / 40 * 40;//�ƶ�
						   return false;
					   }
					   else if (y == y / 40 * 40)//һ�������ͨ���ڶ���
					   {
						   if (CanMove(trole, derect, map, (y - speed) / 40, x / 40))
						   {
							   if (x - x / 40 * 40 <= SKEW)
							   {
								   if (x - speed >= x / 40 * 40)
									   x = x - speed;
								   else
									   x = x / 40 * 40;
							   }
						   }
						   else //���Ͽ�ͨ
						   {
							   if ((x / 40 + 1) * 40 - x <= SKEW)
							   {
								   if (x + speed <= (x / 40 + 1) * 40)
									   x = x + speed;
								   else
									   x = (x / 40 + 1) * 40;
							   }
						   }
					   }
					   else
					   {
						   y = y / 40 * 40;
					   }
				   }
				   else
				   {
					   if (CanMove(trole, derect, map, (y - speed) / 40, x / 40))
						   return true;
					   else
					   {
						   y = y / 40 * 40;
					   }
				   }
			   }
			   else
				   return true;
	}
		break;
	case DOWN:
	{
				 if (y + 40 + speed > 520)
				 {
					 y = 480;
					 return false;
				 }

				 if ((y + speed - 1) / 40 != (y - 1) / 40 || y == 0) //��1�ܹؼ�,0�Ĵ���Ҳ�ܹؼ�
				 {
					 //�Ƿ�ռ��������
					 if (x != x / 40 * 40)//��
					 {
						 if (CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40) && CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40 + 1))
							 //	if((map[(y+speed-1)/40+1][x/40] == SANDGROUND ||map[(y+speed-1)/40+1][x/40] >= CANMOVE) && 
							 //		(map[(y+speed-1)/40+1][x/40+1] == SANDGROUND || map[(y+speed-1)/40+1][x/40+1] >= CANMOVE))//��ͨ
							 return true;
						 else if (!CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40) && !CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40 + 1))
							 //	else if(map[(y+speed-1)/40+1][x/40] > SANDGROUND && map[(y+speed-1)/40+1][x/40+1] > SANDGROUND
							 //		&&(map[(y+speed-1)/40+1][x/40] < CANMOVE && map[(y+speed-1)/40+1][x/40+1] < CANMOVE))//����ͨ
						 {
							 if (y != 0)
								 y = (y - 1) / 40 * 40 + 40;//�ƶ�

							 return false;
						 }
						 else if (y == y / 40 * 40)//һ�������ͨ���ڶ���
						 {
							 if (CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40))
								 //	if(map[(y+speed-1)/40+1][x/40] == SANDGROUND
								 //		|| map[(y+speed-1)/40+1][x/40] >= CANMOVE)//���¿�ͨ
							 {
								 if (x - x / 40 * 40 <= SKEW)
								 {
									 if (x - speed >= x / 40 * 40)
										 x = x - speed;
									 else
										 x = x / 40 * 40;
								 }
							 }
							 else //���Ͽ�ͨ
							 {
								 if ((x / 40 + 1) * 40 - x <= SKEW)
								 {
									 if (x + speed <= (x / 40 + 1) * 40)
										 x = x + speed;
									 else
										 x = (x / 40 + 1) * 40;
								 }
							 }
						 }
						 else
						 {
							 if (y != 0)
								 y = (y - 1) / 40 * 40 + 40;
						 }
					 }
					 else
					 {
						 if (CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40))
							 //	if(map[(y+speed-1)/40+1][x/40] == SANDGROUND
							 //		|| map[(y+speed-1)/40+1][x/40] >= CANMOVE)
							 return true;
						 else
						 {
							 if (y != 0)
								 y = (y - 1) / 40 * 40 + 40;
						 }
					 }
				 }
				 else
					 return true;
	}
		break;
	case LEFT:
	{
				 if (x - speed < 0)
				 {
					 x = 0;
					 return false;
				 }
				 if ((x - speed) / 40 != x / 40)
				 {
					 //�Ƿ�ռ��������
					 if (y != y / 40 * 40)//��
					 {
						 if (CanMove(trole, derect, map, y / 40, (x - speed) / 40) && CanMove(trole, derect, map, y / 40 + 1, (x - speed) / 40))
							 //	if((map[y/40][(x-speed)/40] == SANDGROUND || map[y/40][(x-speed)/40] >= CANMOVE) && 
							 //		(map[y/40+1][(x-speed)/40] == SANDGROUND || map[y/40+1][(x-speed)/40] >= CANMOVE))//��ͨ
							 return true;
						 else if (!CanMove(trole, derect, map, y / 40, (x - speed) / 40) && !CanMove(trole, derect, map, y / 40 + 1, (x - speed) / 40))
							 //	else if(map[y/40][(x-speed)/40] > SANDGROUND && map[y/40+1][(x-speed)/40] > SANDGROUND
							 //		&& (map[y/40][(x-speed)/40] < CANMOVE && map[y/40+1][(x-speed)/40] < CANMOVE))//����ͨ
						 {
							 x = x / 40 * 40;//�ƶ�
							 return false;
						 }
						 else if (x == x / 40 * 40)//һ�������ͨ���ڶ���
						 {
							 if (CanMove(trole, derect, map, y / 40, (x - speed) / 40))
								 //	if(map[y/40][(x-speed)/40] == SANDGROUND
								 //		|| map[y/40][(x-speed)/40] >= CANMOVE)//���Ͽ�ͨ
							 {
								 if (y - y / 40 * 40 <= SKEW)
								 {
									 if (y - speed >= y / 40 * 40)
										 y = y - speed;
									 else
										 y = y / 40 * 40;
								 }
							 }
							 else //���Ͽ�ͨ
							 {
								 if ((y / 40 + 1) * 40 - y <= SKEW)
								 {
									 if (y + speed <= (y / 40 + 1) * 40)
										 y = y + speed;
									 else
										 y = (y / 40 + 1) * 40;
								 }
							 }
						 }
						 else
						 {
							 x = x / 40 * 40;
						 }
					 }
					 else
					 {
						 if (CanMove(trole, derect, map, y / 40, (x - speed) / 40))
							 //	if(map[y/40][(x-speed)/40] == SANDGROUND
							 //		|| map[y/40][(x-speed)/40] >= CANMOVE)
							 return true;
						 else
						 {
							 x = x / 40 * 40;
						 }
					 }
				 }
				 else
					 return true;
	}
		break;
	case RIGHT:
	{
				  if (x + 40 + speed > 600)
				  {
					  x = 560;
					  return false;
				  }
				  if ((x + speed - 1) / 40 != (x - 1) / 40 || x == 0) //��1�ܹؼ�
				  {
					  //�Ƿ�ռ��������
					  if (y != y / 40 * 40)//��
					  {
						  if (CanMove(trole, derect, map, y / 40, ((x - 1) + speed) / 40 + 1) && CanMove(trole, derect, map, y / 40 + 1, ((x - 1) + speed) / 40 + 1))
							  //	if((map[y/40][((x-1)+speed)/40+1] == SANDGROUND || map[y/40][((x-1)+speed)/40+1] >= CANMOVE) && 
							  //		(map[y/40+1][((x-1)+speed)/40+1] == SANDGROUND || map[y/40+1][((x-1)+speed)/40+1] >= CANMOVE))//��ͨ
							  return true;
						  else if (!CanMove(trole, derect, map, y / 40, ((x - 1) + speed) / 40 + 1) && !CanMove(trole, derect, map, y / 40 + 1, ((x - 1) + speed) / 40 + 1))
							  //	else if(map[y/40][((x-1)+speed)/40+1] > SANDGROUND && map[y/40+1][((x-1)+speed)/40+1] > SANDGROUND
							  //		&& (map[y/40][((x-1)+speed)/40+1] < CANMOVE && map[y/40+1][((x-1)+speed)/40+1] < CANMOVE))//����ͨ
						  {
							  if (x != 0)
								  x = (x - 1) / 40 * 40 + 40;//�ƶ�
							  return false;
						  }
						  else if (x == x / 40 * 40)//һ�������ͨ���ڶ���
						  {
							  if (CanMove(trole, derect, map, y / 40, ((x - 1) + speed) / 40 + 1))
								  //	if(map[y/40][((x-1)+speed)/40+1] == SANDGROUND
								  //		|| map[y/40][((x-1)+speed)/40+1] >= CANMOVE)//���Ͽ�ͨ
							  {
								  if (y - y / 40 * 40 <= SKEW)
								  {
									  if (y - speed >= y / 40 * 40)
										  y = y - speed;
									  else
										  y = y / 40 * 40;
								  }
							  }
							  else //���Ͽ�ͨ
							  {
								  if ((y / 40 + 1) * 40 - y <= SKEW)
								  {
									  if (y + speed <= (y / 40 + 1) * 40)
										  y = y + speed;
									  else
										  y = (y / 40 + 1) * 40;
								  }
							  }
						  }
						  else
						  {
							  if (x != 0)
								  x = (x - 1) / 40 * 40 + 40;
						  }
					  }
					  else
					  {
						  if (CanMove(trole, derect, map, y / 40, ((x - 1) + speed) / 40 + 1))
							  //	if(map[y/40][((x-1)+speed)/40+1] == SANDGROUND
							  //		|| map[y/40][((x-1)+speed)/40+1] >= CANMOVE)
							  return true;
						  else
						  {
							  if (x != 0)
								  x = (x - 1) / 40 * 40 + 40;
						  }
					  }
				  }
				  else
					  return true;
	}
		break;
	}
	return false;
}

//�ж������Ƿ�����ը�����ؼ�������  x,yΪ����  �����򷵻�false
bool Judge::JudgeDead(int x, int y)
{
	x = x + 10;
	y = y + 10;
	int x2 = x + SKEW_X;
	int y2 = y + SKEW_Y;

	if (map[y2 / 40][x / 40] >= EXPLOSIONCENTRE && map[y2 / 40][x2 / 40] >= EXPLOSIONCENTRE)
		return false;

	else if (map[y2 / 40][x / 40] >= EXPLOSIONCENTRE && map[y2 / 40][x2 / 40] >= EXPLOSIONCENTRE
		&&   map[y / 40][x / 40] >= EXPLOSIONCENTRE && map[y / 40][x2 / 40] >= EXPLOSIONCENTRE)
		return false;
	//else if(map[y/40][x/40] >= EXPLOSIONCENTRE && map[y/40][x2/40] >= EXPLOSIONCENTRE)
	//	return false;
	//else if(map[y/40][x/40] >= EXPLOSIONCENTRE && map[y2/40][x/40] >= EXPLOSIONCENTRE)
	//	return false;
	//else if(map[y/40][x2/40] >= EXPLOSIONCENTRE && map[y2/40][x2/40] >= EXPLOSIONCENTRE)
	//	return false;

	return true;
}