#include"stdAfx.h"
#include"Judge.h"
extern int map[HEIGHT][WIDTH];
//判断指定位置是否能通过
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

//判断人物是否能移动,能则返回true ，方向，role的x坐标，y坐标，role速度
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
				   //是否占两块区域
				   if (x != x / 40 * 40)//是
				   {
					   if (CanMove(trole, derect, map, (y - speed) / 40, x / 40) && CanMove(trole, derect, map, (y - speed) / 40, x / 40 + 1))
						   return true;
					   else if ((!CanMove(trole, derect, map, (y - speed) / 40, x / 40)) && (!CanMove(trole, derect, map, (y - speed) / 40, x / 40 + 1)))
					   {
						   y = y / 40 * 40;//移顶
						   return false;
					   }
					   else if (y == y / 40 * 40)//一块区域可通且在顶部
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
						   else //右上可通
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

				 if ((y + speed - 1) / 40 != (y - 1) / 40 || y == 0) //减1很关键,0的处理也很关键
				 {
					 //是否占两块区域
					 if (x != x / 40 * 40)//是
					 {
						 if (CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40) && CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40 + 1))
							 //	if((map[(y+speed-1)/40+1][x/40] == SANDGROUND ||map[(y+speed-1)/40+1][x/40] >= CANMOVE) && 
							 //		(map[(y+speed-1)/40+1][x/40+1] == SANDGROUND || map[(y+speed-1)/40+1][x/40+1] >= CANMOVE))//都通
							 return true;
						 else if (!CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40) && !CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40 + 1))
							 //	else if(map[(y+speed-1)/40+1][x/40] > SANDGROUND && map[(y+speed-1)/40+1][x/40+1] > SANDGROUND
							 //		&&(map[(y+speed-1)/40+1][x/40] < CANMOVE && map[(y+speed-1)/40+1][x/40+1] < CANMOVE))//都不通
						 {
							 if (y != 0)
								 y = (y - 1) / 40 * 40 + 40;//移顶

							 return false;
						 }
						 else if (y == y / 40 * 40)//一块区域可通且在顶部
						 {
							 if (CanMove(trole, derect, map, (y + speed - 1) / 40 + 1, x / 40))
								 //	if(map[(y+speed-1)/40+1][x/40] == SANDGROUND
								 //		|| map[(y+speed-1)/40+1][x/40] >= CANMOVE)//左下可通
							 {
								 if (x - x / 40 * 40 <= SKEW)
								 {
									 if (x - speed >= x / 40 * 40)
										 x = x - speed;
									 else
										 x = x / 40 * 40;
								 }
							 }
							 else //右上可通
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
					 //是否占两块区域
					 if (y != y / 40 * 40)//是
					 {
						 if (CanMove(trole, derect, map, y / 40, (x - speed) / 40) && CanMove(trole, derect, map, y / 40 + 1, (x - speed) / 40))
							 //	if((map[y/40][(x-speed)/40] == SANDGROUND || map[y/40][(x-speed)/40] >= CANMOVE) && 
							 //		(map[y/40+1][(x-speed)/40] == SANDGROUND || map[y/40+1][(x-speed)/40] >= CANMOVE))//都通
							 return true;
						 else if (!CanMove(trole, derect, map, y / 40, (x - speed) / 40) && !CanMove(trole, derect, map, y / 40 + 1, (x - speed) / 40))
							 //	else if(map[y/40][(x-speed)/40] > SANDGROUND && map[y/40+1][(x-speed)/40] > SANDGROUND
							 //		&& (map[y/40][(x-speed)/40] < CANMOVE && map[y/40+1][(x-speed)/40] < CANMOVE))//都不通
						 {
							 x = x / 40 * 40;//移顶
							 return false;
						 }
						 else if (x == x / 40 * 40)//一块区域可通且在顶部
						 {
							 if (CanMove(trole, derect, map, y / 40, (x - speed) / 40))
								 //	if(map[y/40][(x-speed)/40] == SANDGROUND
								 //		|| map[y/40][(x-speed)/40] >= CANMOVE)//左上可通
							 {
								 if (y - y / 40 * 40 <= SKEW)
								 {
									 if (y - speed >= y / 40 * 40)
										 y = y - speed;
									 else
										 y = y / 40 * 40;
								 }
							 }
							 else //右上可通
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
				  if ((x + speed - 1) / 40 != (x - 1) / 40 || x == 0) //减1很关键
				  {
					  //是否占两块区域
					  if (y != y / 40 * 40)//是
					  {
						  if (CanMove(trole, derect, map, y / 40, ((x - 1) + speed) / 40 + 1) && CanMove(trole, derect, map, y / 40 + 1, ((x - 1) + speed) / 40 + 1))
							  //	if((map[y/40][((x-1)+speed)/40+1] == SANDGROUND || map[y/40][((x-1)+speed)/40+1] >= CANMOVE) && 
							  //		(map[y/40+1][((x-1)+speed)/40+1] == SANDGROUND || map[y/40+1][((x-1)+speed)/40+1] >= CANMOVE))//都通
							  return true;
						  else if (!CanMove(trole, derect, map, y / 40, ((x - 1) + speed) / 40 + 1) && !CanMove(trole, derect, map, y / 40 + 1, ((x - 1) + speed) / 40 + 1))
							  //	else if(map[y/40][((x-1)+speed)/40+1] > SANDGROUND && map[y/40+1][((x-1)+speed)/40+1] > SANDGROUND
							  //		&& (map[y/40][((x-1)+speed)/40+1] < CANMOVE && map[y/40+1][((x-1)+speed)/40+1] < CANMOVE))//都不通
						  {
							  if (x != 0)
								  x = (x - 1) / 40 * 40 + 40;//移顶
							  return false;
						  }
						  else if (x == x / 40 * 40)//一块区域可通且在顶部
						  {
							  if (CanMove(trole, derect, map, y / 40, ((x - 1) + speed) / 40 + 1))
								  //	if(map[y/40][((x-1)+speed)/40+1] == SANDGROUND
								  //		|| map[y/40][((x-1)+speed)/40+1] >= CANMOVE)//左上可通
							  {
								  if (y - y / 40 * 40 <= SKEW)
								  {
									  if (y - speed >= y / 40 * 40)
										  y = y - speed;
									  else
										  y = y / 40 * 40;
								  }
							  }
							  else //右上可通
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

//判断人物是否被泡泡炸到，关键半身处理  x,y为坐标  死亡则返回false
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