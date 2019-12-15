#include "stdafx.h"
#include"GameOutput.h"
#include"Paopao.h"

extern struct Role *role1, *role2;
extern Paopao paopao;
extern int map[HEIGHT][WIDTH];
extern int giftMap[HEIGHT][WIDTH];
extern bool begin;//开始准备状态
extern bool end;//结束状态
extern int Ani;




//加载图像
void InitImages::InitFile(HDC hdc, HDC imageDC)
{

	bRole1Death1 = CreateCompatibleDC(hdc);
	bRole1Death2 = CreateCompatibleDC(hdc);
	bRole2Death1 = CreateCompatibleDC(hdc);
	bRole2Death2 = CreateCompatibleDC(hdc);

	SelectObject(bRole1Death1, CreateCompatibleBitmap(hdc, PWIDTH, PHEIGHT));
	SelectObject(bRole1Death2, CreateCompatibleBitmap(hdc, PWIDTH, PHEIGHT));
	SelectObject(bRole2Death1, CreateCompatibleBitmap(hdc, PWIDTH, PHEIGHT));
	SelectObject(bRole2Death2, CreateCompatibleBitmap(hdc, PWIDTH, PHEIGHT));

	
	InitImage(hdc, imageDC, SandOasisAni1, SandOasisAni2, 480, 71, "Pic\\SandOasisAni.bmp");
	InitImage(hdc, imageDC, SandOasis1, SandOasis2, 160, 72, "Pic\\SandOasis.bmp");
	InitImage(hdc, imageDC, Help1, Help2, 800, 600, "Pic\\Help.bmp");
	InitImage(hdc, imageDC, BG1, BG2, 800, 600, "Pic\\enter.bmp");
	InitImage(hdc, imageDC, bBG, cBG, 800, 600, "Pic\\BG.bmp");
	InitImage(hdc, imageDC, bBigPopo, cBigPopo, 648, 72, "Pic\\BigPopo.bmp");
	InitImage(hdc, imageDC, bDraw, cDraw, 204, 68, "Pic\\Draw.bmp");
	InitImage(hdc, imageDC, bExplosion, cExplosion, 560, 200, "Pic\\Explosion.bmp");
	InitImage(hdc, imageDC, bGift[0], cGift[0], 126, 45, "Pic\\Gift1.bmp");
	InitImage(hdc, imageDC, bGift[1], cGift[1], 126, 45, "Pic\\Gift2.bmp");
	InitImage(hdc, imageDC, bGift[2], cGift[2], 126, 45, "Pic\\Gift3.bmp");
	InitImage(hdc, imageDC, bGift[3], cGift[3], 126, 45, "Pic\\Gift4.bmp");
	InitImage(hdc, imageDC, bGift[4], cGift[4], 126, 45, "Pic\\Gift5.bmp");
	InitImage(hdc, imageDC, bGift[5], cGift[5], 126, 45, "Pic\\Gift6.bmp");
	InitImage(hdc, imageDC, bGift[6], cGift[6], 126, 45, "Pic\\Gift7.bmp");
	InitImage(hdc, imageDC, bGift[7], cGift[7], 126, 45, "Pic\\Gift8.bmp");
	InitImage(hdc, imageDC, bGift[8], cGift[8], 126, 46, "Pic\\Gift9.bmp");
	InitImage(hdc, imageDC, bPlayer, cPlayer, 110, 50, "Pic\\Player.bmp");
	InitImage(hdc, imageDC, bPopo, cPopo, 132, 41, "Pic\\Popo.bmp");
	InitImage(hdc, imageDC, bRole1, cRole1, 288, 256, "Pic\\Role1.bmp");
	InitImage(hdc, imageDC, bRole1Ani, cRole1Ani, 384, 64, "Pic\\Role1Ani.bmp");
	InitImage(hdc, imageDC, bRole1Start, cRole1Start, 480, 64, "Pic\\Role1Start.bmp");
	InitImage(hdc, imageDC, bRole2, cRole2, 336, 268, "Pic\\Role2.bmp");
	InitImage(hdc, imageDC, bRole2Ani, cRole2Ani, 448, 70, "Pic\\Role2Ani.bmp");
	InitImage(hdc, imageDC, bRole2Start, cRole2Start, 560, 71, "Pic\\Role2Start.bmp");
	InitImage(hdc, imageDC, bSandBlockBuff, cSandBlockBuff, 40, 44, "Pic\\SandBlockBuff.bmp");
	InitImage(hdc, imageDC, bSandBlockYellow, cSandBlockYellow, 40, 44, "Pic\\SandBlockYellow.bmp");
	InitImage(hdc, imageDC, bSandGround, cSandGround, 80, 40, "Pic\\SandGround.bmp");
	InitImage(hdc, imageDC, bSandTree, cSandTree, 63, 80, "Pic\\SandTree.bmp");
	InitImage(hdc, imageDC, bSandTreeYellow, cSandTreeYellow, 63, 80, "Pic\\SandTreeYellow.bmp");
	InitImage(hdc, imageDC, bShadowBlock, cShadowBlock, 45, 45, "Pic\\ShadowBlock.bmp");
	InitImage(hdc, imageDC, bShadowGift, cShadowGift, 36, 9, "Pic\\ShadowGift.bmp");
	InitImage(hdc, imageDC, bShadowPopo, cShadowPopo, 105, 16, "Pic\\ShadowPopo.bmp");
	InitImage(hdc, imageDC, bShadowRole, cShadowRole, 32, 15, "Pic\\ShadowRole.bmp");
	InitImage(hdc, imageDC, bStart, cStart, 204, 68, "Pic\\Start.bmp");
	InitImage(hdc, imageDC, bWin, cWin, 204, 70, "Pic\\Win.bmp");
	InitImage(hdc, imageDC, bSandTentBlue, cSandTentBlue, 132, 71, "Pic\\SandTentBlue.bmp");
	InitImage(hdc, imageDC, bSandTentRed, cSandTentRed, 132, 71, "Pic\\SandTentRed.bmp");
	InitImage(hdc, imageDC, bFastUFO, cFastUFO, 104, 124, "Pic\\FastUFO.bmp");
	InitImage(hdc, imageDC, bFastTurtle, cFastTurtle, 96, 128, "Pic\\FastTurtle.bmp");
	InitImage(hdc, imageDC, bOwl, cOwl, 80, 128, "Pic\\Owl.bmp");
	InitImage(hdc, imageDC, bRole1Ride, cRole1Ride, 192, 56, "Pic\\Role1Ride.bmp");
	InitImage(hdc, imageDC, bRole2Ride, cRole2Ride, 224, 60, "Pic\\Role2Ride.bmp");




	InitDeathImage(hdc, bRole1Death1, bRole1Death2, bRole1Ani, 48, 64, 12, 4);
	InitDeathImage(hdc, bRole2Death1, bRole2Death2, bRole2Ani, 56, 70, 7, 2);
}

//初始化死亡的图像
void InitImages::InitDeathImage(HDC hdc, HDC &bDeath1, HDC &bDeath2, HDC bRoleAni, int width, int height, int beginx, int beginy)
{
	HBITMAP temp1 = CreateCompatibleBitmap(hdc, 72, 72);
	HBITMAP temp2 = CreateCompatibleBitmap(hdc, 72, 72);
	//获取泡泡数据结构
	HDC tBigPopo;
	unsigned char *bigPopoStruct;
	BITMAP bigPopoBmp;
	bigPopoStruct = GetStruct(hdc, bBigPopo, tBigPopo, bigPopoBmp,
		3 * 72, 0, 72, 72);

	HDC tRole1;
	unsigned char *role1Struct = NULL;
	BITMAP role1Bmp;
	role1Struct = GetStruct(hdc, bRoleAni, tRole1, role1Bmp, 0, 0, width, height);

	HDC tRole2;
	unsigned char *role2Struct = NULL;
	BITMAP role2Bmp;
	role2Struct = GetStruct(hdc, bRoleAni, tRole2, role2Bmp, width, 0, width, height);

	ChangeImage(temp1, tRole1, bigPopoStruct, role1Struct, 40, bigPopoBmp, role1Bmp, width, height, beginx, beginy);
	SelectObject(bDeath1, temp1);

	ChangeImage(temp2, tRole2, bigPopoStruct, role2Struct, 40, bigPopoBmp, role2Bmp, width, height, beginx, beginy);
	SelectObject(bDeath2, temp2);
}

//获取一个hdc一个矩形区域的像素数据结构，source:源hdc，tImage 对象图像，imageStruct:图像数据结构，bmp BITMAP属性，begin_x, begin_y, width, height   开始的坐标，宽度和高度
unsigned char *InitImages::GetStruct(HDC hdc, HDC source, HDC &tImage, BITMAP &bmp, int begin_x, int begin_y, int width, int height)
{
	unsigned char *imageStruct;

	tImage = CreateCompatibleDC(hdc);
	SelectObject(tImage, CreateCompatibleBitmap(hdc, width, height));
	//函数从源矩形中复制一个位图到目标矩形，必要时按目标设备设置的模式进行图像的拉伸或压缩
	StretchBlt(tImage, 0, 0, width, height, source, begin_x, begin_y, width, height, SRCCOPY);

	HBITMAP image = CreateCompatibleBitmap(hdc, width, height);
	HBITMAP imageOld = CreateCompatibleBitmap(hdc, width, height);

	image = (HBITMAP)SelectObject(tImage, imageOld);

	GetObject(image, sizeof(BITMAP), &bmp);

	imageStruct = new unsigned char[bmp.bmHeight*bmp.bmWidthBytes];
	GetBitmapBits(image, bmp.bmHeight*bmp.bmWidthBytes, imageStruct);

	SelectObject(tImage, image);
	DeleteObject(imageOld);

	return imageStruct;
}

//透明处理，value为透明度，image为返回的图像，frontStruct 前景色的数据结构，backStruct后景色的数据结构，透明度 1 - 100，width,height，begin, beginy
void InitImages::ChangeImage(HBITMAP &image, HDC SourceRole, unsigned char *frontStruct, unsigned char *backStruct, int value, BITMAP front, BITMAP back, int width, int height, int beginx, int beginy)
{
	int PxBytes = front.bmBitsPixel / 8;
	int PxBytes2 = back.bmBitsPixel / 8;
	int rgb_b, x;
	unsigned char *temp = new unsigned char[front.bmHeight*front.bmWidthBytes];
	memcpy(temp, frontStruct, sizeof(unsigned char)*front.bmHeight*front.bmWidthBytes);

	for (int i = 0; i<height; i++)
	for (int j = 0; j<width; j++)
	{
		if (GetPixel(SourceRole, j, i) != RGB(0, 0, 0))
		{
			x = (i + beginy)*front.bmWidthBytes + (j + beginx)*PxBytes;
			rgb_b = i*back.bmWidthBytes + j*PxBytes2;
			temp[x] = backStruct[rgb_b] * value / 100 + frontStruct[x] * (100 - value) / 100;
			temp[x + 1] = backStruct[rgb_b + 1] * value / 100 + frontStruct[x + 1] * (100 - value) / 100;
			temp[x + 2] = backStruct[rgb_b + 2] * value / 100 + frontStruct[x + 2] * (100 - value) / 100;
		}
	}
	SetBitmapBits(image, front.bmHeight*front.bmWidthBytes, temp);
}

//图片的加载，bImage:加载图片1，bImage:图片2，width height 图片宽度高度，fileName图片名,含路径
void InitImages::InitImage(HDC hdc, HDC imageDC, HDC &bImage, HDC &cImage,
	int width, int height, char fileName[])
{
	bImage = CreateCompatibleDC(hdc);
	cImage = CreateCompatibleDC(hdc);
	HBITMAP tempImage = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, width,
		height, LR_LOADFROMFILE);
	SelectObject(imageDC, tempImage);
	SelectObject(bImage, CreateCompatibleBitmap(hdc, width, height));
	SelectObject(cImage, CreateCompatibleBitmap(hdc, width, height));
	for (int i = 0; i<width; i++)
	{
		for (int j = 0; j<height; j++)
		{
			if (GetPixel(imageDC, i, j) != RGB(255, 0, 255))
				BitBlt(bImage, i, j, 1, 1, imageDC, i, j, SRCCOPY);
			else
				SetPixel(cImage, i, j, RGB(255, 255, 255));
		}
	}
	DeleteObject(tempImage);
}



void GameOutput::PaintMain(HDC hdc, HDC bufHdc)
{
	BitBlt(bufHdc, 0, 0, 800, 600, BG1, 0, 0, SRCCOPY);
	BitBlt(hdc, 0, 0, 800, 600, bufHdc, 0, 0, SRCCOPY);
}

void GameOutput::PaintHelp(HDC hdc, HDC bufHdc)
{
	BitBlt(bufHdc, 0, 0, 800, 600, Help1, 0, 0, SRCCOPY);
	BitBlt(hdc, 0, 0, 800, 600, bufHdc, 0, 0, SRCCOPY);
}


//界面的绘制，x:第几个方向，y:第几个状态
void GameOutput::Paint(HDC hdc, HDC bufHdc)
{
	//地图
	BitBlt(bufHdc, 0, 0, 800, 600, bBG, 0, 0, SRCCOPY);//对指定的源设备环境区域中的像素进行位块（bit_block）转换

	//空地板
	for (int i = WIDTH - 1; i >= 0; i--)
	for (int j = 0; j<HEIGHT; j++)
	{
		PaintXY(i, j, bufHdc, SANDGROUND);
	}

	//算出y1,y2占的位置

	int y1=0, y2=0, x1=0, x2=0;//角色位置
	if (role1 != NULL)
	{
		//是否占完整一格
		if (role1->y == (role1->y / 40 * 40))
			y1 = role1->y / 40;
		else
			y1 = role1->y / 40 + 1;
		if (role1->x == (role1->x / 40 * 40))
			x1 = role1->x / 40;
		else
			x1 = role1->x / 40 + 1;
	}
	if (role2 != NULL)
	{
		//是否占完整一格
		if (role2->y == (role2->y / 40 * 40))
			y2 = role2->y / 40;
		else
			y2 = role2->y / 40 + 1;


		if (role2->x == (role2->x / 40 * 40))
			x2 = role2->x / 40;
		else
			x2 = role2->x / 40 + 1;
	}

	struct Popo *p = paopao.get_popo();
	for (int j = 0; j<HEIGHT; j++)
	for (int i = WIDTH - 1; i >= 0; i--)
	{
		if (map[j][i] >= EXPLOSIONCENTRE)
			PaintExplosion(bufHdc, i, j);
		else if (map[j][i] == POPO && p != NULL )
		{
			PaintPopo(p, bufHdc);
			//防止泡泡在人上
			if (role1 != NULL && j == y1 && i == x1 - 1 )
				PaintRole(bufHdc, role1->direction, role1->state / 2, 1, role1);
			if (role2 != NULL && j == y2 && i == x2 - 1)
				PaintRole(bufHdc, role2->direction, role2->state / 2, 2, role2);
			p = p->next;
		}
		else if (map[j][i] != SANDGROUND || (map[j][i] >= GIFT1 && map[j][i] <= GIFT8))
		{
			PaintXY(i, j, bufHdc, map[j][i]);
		}
		if (role1 != NULL && j == y1 && i == x1 && map[y1][x1] != SandTent)
			PaintRole(bufHdc, role1->direction, role1->state / 2, 1, role1);
		if (role2 != NULL && j == y2 && i == x2 && map[y2][x2] != SandTent)
			PaintRole(bufHdc, role2->direction, role2->state / 2, 2, role2);

		//防止箱子在人上
		if (role1 != NULL && role1->ride  && map[y1][x1] != SandTent)
			PaintRole(bufHdc, role1->direction, role1->state / 2, 1, role1);
		if (role2 != NULL && role2->ride && map[y2][x2] != SandTent)
			PaintRole(bufHdc, role2->direction, role2->state / 2, 2, role2);

	}

	//输出树，防止树在人上
	for (int j = 0; j<HEIGHT; j++)
	for (int i = WIDTH - 1; i >= 0; i--)
	if (map[j][i] == SandTree)
	{
		PaintXY(i, j, bufHdc, map[j][i]);
		if (map[j][i] == SandTree && j==y1-1)
		{
			PaintRole(bufHdc, role1->direction, role1->state / 2, 1, role1);
		}
		if (map[j][i] == SandTree && j == y2 - 1)
		{
			PaintRole(bufHdc, role2->direction, role2->state / 2, 2, role2);
		}
	}

	//输出绿洲，防止人在绿洲下
	BitBlt(bufHdc, 20 + 6 * 40, 36 + 6 * 40 -72, 160, 72, SandOasis2, 0, 0, SRCAND);
	BitBlt(bufHdc, 20 + 6 * 40, 36 + 6 * 40 -72, 160, 72, SandOasis1, 0, 0, SRCPAINT);
	BitBlt(bufHdc, 20 + 6 * 40, 36 + 6 * 40, 160, 71, SandOasisAni2, (Ani / 1500) * 160 , 0, SRCAND);
	BitBlt(bufHdc, 20 + 6 * 40, 36 + 6 * 40, 160, 71, SandOasisAni1, (Ani / 1500) * 160, 0, SRCPAINT);
	if (role1 != NULL && y1 == 8 && (x1 >= 6 && x1 <= 9))
	{
		PaintRole(bufHdc, role1->direction, role1->state / 2, 1, role1);
	}
	if (role2 != NULL && y2 == 8 && (x2 >= 6 && x2 <= 9))
	{
		PaintRole(bufHdc, role2->direction, role2->state / 2, 2, role2);
	}



	if (begin)
	{
		BitBlt(bufHdc, 250, 200, 204, 68, cStart, 0, 0, SRCAND);
		BitBlt(bufHdc, 250, 200, 204, 68, bStart, 0, 0, SRCPAINT);
	}
	else if (end)
	{

		if (role2 != NULL)
		{
			BitBlt(bufHdc, 275, 175, 110, 25, cPlayer, 0, 25, SRCAND);//玩家2赢
			BitBlt(bufHdc, 275, 175, 110, 25, bPlayer, 0, 25, SRCPAINT);
			BitBlt(bufHdc, 250, 200, 204, 70, cWin, 0, 0, SRCAND);
			BitBlt(bufHdc, 250, 200, 204, 70, bWin, 0, 0, SRCPAINT);
		}
		else if (role1 != NULL)
		{
			BitBlt(bufHdc, 275, 175, 110, 25, cPlayer, 0, 0, SRCAND);//玩家1赢
			BitBlt(bufHdc, 275, 175, 110, 25, bPlayer, 0, 0, SRCPAINT);
			BitBlt(bufHdc, 250, 200, 204, 70, cWin, 0, 0, SRCAND);
			BitBlt(bufHdc, 250, 200, 204, 70, bWin, 0, 0, SRCPAINT);
		}
		else
		{
			BitBlt(bufHdc, 250, 200, 204, 68, cDraw, 0, 0, SRCAND);//平局
			BitBlt(bufHdc, 250, 200, 204, 68, bDraw, 0, 0, SRCPAINT);
		}

	}

	BitBlt(hdc, 0, 0, 800, 600, bufHdc, 0, 0, SRCCOPY);
}

void GameOutput::PaintXY(int x, int y, HDC bufDC, int value)
{
	switch (value)
	{
		case SANDGROUND:
		{
				//黄白相间，然并卵
				if (((x + 1) % 2 == 0 && (y + 1) % 2 == 0) || ((x + 1) % 2 == 1 && (y + 1) % 2 == 1))
					BitBlt(bufDC, 20 + x * 40, 40 + y * 40, 40, 40, bSandGround, 0, 0, SRCCOPY);
				else
					BitBlt(bufDC, 20 + x * 40, 40 + y * 40, 40, 40, bSandGround, 40, 0, SRCCOPY);
		}
		return;
		case SANDBLOCKYELLOW:
		{
				//阴影部分
				BitBlt(bufDC, 15 + x * 40, 40 + y * 40, 45, 45, cShadowBlock, 0, 0, SRCAND);
				BitBlt(bufDC, 15 + x * 40, 40 + y * 40, 45, 45, bShadowBlock, 0, 0, SRCPAINT);

				if (((x + 1) % 2 == 0 && (y + 1) % 2 == 0) || ((x + 1) % 2 == 1 && (y + 1) % 2 == 1))
				{
						BitBlt(bufDC, 20 + x * 40, 36 + y * 40, 40, 44, cSandBlockYellow, 0, 0, SRCAND);
						BitBlt(bufDC, 20 + x * 40, 36 + y * 40, 40, 44, bSandBlockYellow, 0, 0, SRCPAINT);
				}

				else
				{
						BitBlt(bufDC, 20 + x * 40, 36 + y * 40, 40, 44, cSandBlockBuff, 0, 0, SRCAND);
						BitBlt(bufDC, 20 + x * 40, 36 + y * 40, 40, 44, bSandBlockBuff, 0, 0, SRCPAINT);
				}

		}
		return;
		case SandTree:
		{
						 if (((x + 1) % 2 == 0 && (y + 1) % 2 == 0) || ((x + 1) % 2 == 1 && (y + 1) % 2 == 1))
						 {
							 BitBlt(bufDC, x * 40 + 5, y * 40 - 10, 63, 80, cSandTree, 0, 0, SRCAND);
							 BitBlt(bufDC, x * 40 + 5, y * 40 - 10, 63, 80, bSandTree, 0, 0, SRCPAINT);
						 }
						 else
						 {
							 BitBlt(bufDC, x * 40 + 5, y * 40 - 10, 63, 80, cSandTreeYellow, 0, 0, SRCAND);
							 BitBlt(bufDC, x * 40 + 5, y * 40 - 10, 63, 80, bSandTreeYellow, 0, 0, SRCPAINT);
						 }
		}
		return;
		case SandTent:
		{
						 if (((x + 1) % 2 == 0 && (y + 1) % 2 == 0) || ((x + 1) % 2 == 1 && (y + 1) % 2 == 1))
						 {
							 BitBlt(bufDC, 20 + x * 40 - 2, 36 + y * 40 - 31, 44, 71, cSandTentBlue, (Ani / 1500) * 44, 0, SRCAND);
							 BitBlt(bufDC, 20 + x * 40 - 2, 36 + y * 40 - 31, 44, 71, bSandTentBlue, (Ani / 1500) * 44, 0, SRCPAINT);
						 }
						 else
						 {
							 BitBlt(bufDC, 20 + x * 40 - 2, 36 + y * 40 - 31, 44, 71, cSandTentRed, (Ani / 1500) * 44, 0, SRCAND);
							 BitBlt(bufDC, 20 + x * 40 - 2, 36 + y * 40 - 31, 44, 71, bSandTentRed, (Ani / 1500) * 44, 0, SRCPAINT);
						 }
		}
		return;
		case GIFT1:
		case GIFT2:
		case GIFT3:
		case GIFT4:
		case GIFT5:
		case GIFT6:
		case GIFT7:
		case GIFT8:
		{		//阴影部分周期为2，道具为3
				  BitBlt(bufDC, 32 + x * 40, 75 + y * 40, 18, 9, cShadowGift, 18 * ((giftMap[y][x] / 9)), 0, SRCAND);
				  BitBlt(bufDC, 32 + x * 40, 75 + y * 40, 18, 9, bShadowGift, 18 * ((giftMap[y][x] / 9)), 0, SRCPAINT);
				  BitBlt(bufDC, 20 + x * 40, 36 + y * 40, 42, 45, cGift[value - GIFT1], 42 * ((giftMap[y][x] / 6)), 0, SRCAND);
				  BitBlt(bufDC, 20 + x * 40, 36 + y * 40, 42, 45, bGift[value - GIFT1], 42 * ((giftMap[y][x] / 6)), 0, SRCPAINT);
		}return;
		default:
			return;
	}
}

//画泡泡，struct Popo* 为泡泡指针，bufDC 图像输出缓冲
void GameOutput::PaintPopo(struct Popo *p, HDC bufDC)
{
	if (map[p->y][p->x] == SandTent)
		return;
	BitBlt(bufDC, 20 + p->x * 40 - 2, 40 + p->y * 40 - 1, 44, 41, cPopo, (p->life % 8) / 3 * 44, 0, SRCAND);
	BitBlt(bufDC, 20 + p->x * 40 - 2, 40 + p->y * 40 - 1, 44, 41, bPopo, (p->life % 8) / 3 * 44, 0, SRCPAINT);

	BitBlt(bufDC, 20 + p->x * 40 - 4, 40 + p->y * 40 - 1 + 30, 35, 16, cShadowPopo, (p->life % 8) / 3 * 35, 0, SRCAND);
	BitBlt(bufDC, 20 + p->x * 40 - 4, 40 + p->y * 40 - 1 + 30, 35, 16, bShadowPopo, (p->life % 8) / 3 * 35, 0, SRCPAINT);

	//		p = p->next;
	//	}
}

//画泡泡的爆炸，bufDC为缓冲
void GameOutput::PaintExplosion(HDC bufDC, int i, int j)
{
	if (map[j][i] >= EXPLOSIONRIGHT)
	{
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, cExplosion, 40 * (map[j][i] - EXPLOSIONRIGHT), 120, SRCAND);
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, bExplosion, 40 * (map[j][i] - EXPLOSIONRIGHT), 120, SRCPAINT);
	}
	else if (map[j][i] >= EXPLOSIONLEFT)
	{
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, cExplosion, 40 * (map[j][i] - EXPLOSIONLEFT), 80, SRCAND);
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, bExplosion, 40 * (map[j][i] - EXPLOSIONLEFT), 80, SRCPAINT);
	}
	else if (map[j][i] >= EXPLOSIONDOWN)
	{
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, cExplosion, 40 * (map[j][i] - EXPLOSIONDOWN), 40, SRCAND);
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, bExplosion, 40 * (map[j][i] - EXPLOSIONDOWN), 40, SRCPAINT);
	}
	else if (map[j][i] >= EXPLOSIONUP)
	{
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, cExplosion, 40 * (map[j][i] - EXPLOSIONUP), 0, SRCAND);
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, bExplosion, 40 * (map[j][i] - EXPLOSIONUP), 0, SRCPAINT);
	}
	else if (map[j][i] >= EXPLOSIONCENTRE)
	{
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, cExplosion, 40 * ((map[j][i] - EXPLOSIONCENTRE) / 2), 160, SRCAND);
		BitBlt(bufDC, 20 + i * 40, 40 + j * 40, 40, 40, bExplosion, 40 * ((map[j][i] - EXPLOSIONCENTRE) / 2), 160, SRCPAINT);
	}

	//	}
}

//num:人物的ID，bufDC图形缓冲，x表示状态，y表示方向
void GameOutput::PaintRole(HDC bufDC, int x, int y, int num, struct Role *trole)
{

	if (trole->state > DEATH)
	{
		BitBlt(bufDC, 24 + trole->x, 65 + trole->y, 32, 15, cShadowRole, 0, 0, SRCAND);
		BitBlt(bufDC, 24 + trole->x, 65 + trole->y, 32, 15, bShadowRole, 0, 0, SRCPAINT);

		if (num == 1)
		{
			if (trole->state >= ENDSTATE)
			{
				BitBlt(bufDC, 16 + trole->x, 15 + trole->y, 48, 64, cRole1Ani, 48 * (((trole->state - ENDSTATE) / 3) % 6 + 2), 0, SRCAND);
				BitBlt(bufDC, 16 + trole->x, 15 + trole->y, 48, 64, bRole1Ani, 48 * (((trole->state - ENDSTATE) / 3) % 6 + 2), 0, SRCPAINT);
			}
			else if (trole->state >= BEGINSTATE)
			{
				BitBlt(bufDC, 16 + trole->x, 15 + trole->y, 48, 64, cRole1Start, 48 * (((trole->state - BEGINSTATE) / 3) % 10), 0, SRCAND);
				BitBlt(bufDC, 16 + trole->x, 15 + trole->y, 48, 64, bRole1Start, 48 * (((trole->state - BEGINSTATE) / 3) % 10), 0, SRCPAINT);
			}
			else if (trole->ride>1)
			{
				BitBlt(bufDC, 16 + trole->x, trole->y+10, 48, 56, cRole1Ride, 48 * x, 0, SRCAND);
				BitBlt(bufDC, 16 + trole->x, trole->y+10, 48, 56, bRole1Ride, 48 * x, 0, SRCPAINT);

				switch (trole->ride)
				{

				case GIFT6:
					BitBlt(bufDC, 14 + trole->x, 20 + trole->y + 25, 52, 31, cFastUFO, 52 * (y % 2), 31 * x, SRCAND);
					BitBlt(bufDC, 14 + trole->x, 20 + trole->y + 25, 52, 31, bFastUFO, 52 * (y % 2), 31 * x, SRCPAINT);
					break;
				case GIFT7:
					BitBlt(bufDC, 16 + trole->x, 20 + trole->y + 27, 48, 32, cFastTurtle, 48 * (y % 2), 32 * x, SRCAND);
					BitBlt(bufDC, 16 + trole->x, 20 + trole->y + 27, 48, 32, bFastTurtle, 48 * (y % 2), 32 * x, SRCPAINT);
					break;
				case GIFT8:
					BitBlt(bufDC, 20 + trole->x, 20 + trole->y + 27, 40, 32, cOwl, 40 * (y % 2), 32 * x, SRCAND);
					BitBlt(bufDC, 20 + trole->x, 20 + trole->y + 27, 40, 32, bOwl, 40 * (y % 2), 32 * x, SRCPAINT);
					break;

				}
				
			}
			else
			{
				
					BitBlt(bufDC, 16 + trole->x, 15 + trole->y, 48, 64, cRole1, 48 * y, 64 * x, SRCAND);
					BitBlt(bufDC, 16 + trole->x, 15 + trole->y, 48, 64, bRole1, 48 * y, 64 * x, SRCPAINT);
			
			}
		}
		else if (num == 2)
		{
			if (trole->state >= ENDSTATE)
			{
				BitBlt(bufDC, 12 + trole->x, 15 + trole->y, 56, 71, cRole2Ani, 56 * (((trole->state - ENDSTATE) / 3) % 6 + 2), 0, SRCAND);
				BitBlt(bufDC, 12 + trole->x, 15 + trole->y, 56, 71, bRole2Ani, 56 * (((trole->state - ENDSTATE) / 3) % 6 + 2), 0, SRCPAINT);
			}
			else if (trole->state >= BEGINSTATE)
			{
				BitBlt(bufDC, 12 + trole->x, 15 + trole->y, 56, 71, cRole2Start, 56 * (((trole->state - BEGINSTATE)) / 3 % 10), 0, SRCAND);
				BitBlt(bufDC, 12 + trole->x, 15 + trole->y, 56, 71, bRole2Start, 56 * (((trole->state - BEGINSTATE)) / 3 % 10), 0, SRCPAINT);
			}
			else if (trole->ride>1)
			{
				BitBlt(bufDC, 12 + trole->x, trole->y + 5, 56, 60, cRole2Ride, 56 * x, 0, SRCAND);
				BitBlt(bufDC, 12 + trole->x, trole->y + 5, 56, 60, bRole2Ride, 56 * x, 0, SRCPAINT);

				switch (trole->ride)
				{

				case GIFT6:
					BitBlt(bufDC, 14 + trole->x, 20 + trole->y + 25, 52, 31, cFastUFO, 52 * (y % 2), 31 * x, SRCAND);
					BitBlt(bufDC, 14 + trole->x, 20 + trole->y + 25, 52, 31, bFastUFO, 52 * (y % 2), 31 * x, SRCPAINT);
					break;
				case GIFT7:
					BitBlt(bufDC, 16 + trole->x, 20 + trole->y + 27, 48, 32, cFastTurtle, 48 * (y % 2), 32 * x, SRCAND);
					BitBlt(bufDC, 16 + trole->x, 20 + trole->y + 27, 48, 32, bFastTurtle, 48 * (y % 2), 32 * x, SRCPAINT);
					break;
				case GIFT8:
					BitBlt(bufDC, 20 + trole->x, 20 + trole->y + 27, 40, 32, cOwl, 40 * (y % 2), 32 * x, SRCAND);
					BitBlt(bufDC, 20 + trole->x, 20 + trole->y + 27, 40, 32, bOwl, 40 * (y % 2), 32 * x, SRCPAINT);
					break;

				}
			}
			else
			{
				
				
					BitBlt(bufDC, 12 + trole->x, 15 + trole->y, 56, 67, cRole2, 56 * y, 67 * x, SRCAND);
					BitBlt(bufDC, 12 + trole->x, 15 + trole->y, 56, 67, bRole2, 56 * y, 67 * x, SRCPAINT);
				
			}
		}

	}
	else
	{
		if (trole->state >= DEATH - 12 && trole->state <= DEATH)
		{
			BitBlt(bufDC, 10 + trole->x, 25 + trole->y, 72, 72, cBigPopo, (-trole->state - 1) / 6 * 72, 0, SRCAND);
			BitBlt(bufDC, 10 + trole->x, 25 + trole->y, 72, 72, bBigPopo, (-trole->state - 1) / 6 * 72, 0, SRCPAINT);
		}
		else if (trole->state < DEATH - 12 && trole->state > DEATH - HELPTIME - 12)
		{
			BitBlt(bufDC, 10 + trole->x, 25 + trole->y, 72, 72, cBigPopo, 3 * 72, 0, SRCAND);
			if (num == 1)
			{
				if ((DEATH - 12 - trole->state) / 5 % 2 == 0)
					BitBlt(bufDC, 10 + trole->x, 25 + trole->y, 72, 72, bRole1Death1, 0, 0, SRCPAINT);
				else
					BitBlt(bufDC, 10 + trole->x, 25 + trole->y, 72, 72, bRole1Death2, 0, 0, SRCPAINT);
			}
			else
			{
				if ((DEATH - 12 - trole->state) / 5 % 2 == 0)
					BitBlt(bufDC, 10 + trole->x, 25 + trole->y, 72, 72, bRole2Death1, 0, 0, SRCPAINT);
				else
					BitBlt(bufDC, 10 + trole->x, 25 + trole->y, 72, 72, bRole2Death2, 0, 0, SRCPAINT);
			}

		}
		else if (trole->state < DEATH - HELPTIME - 12 && trole->state > DEATH - HELPTIME - 37)
		{
			BitBlt(bufDC, 10 + trole->x, 25 + trole->y, 72, 72, cBigPopo, ((-trole->state + (DEATH - HELPTIME)) / 5 + 5) * 72, 0, SRCAND);
			BitBlt(bufDC, 10 + trole->x, 25 + trole->y, 72, 72, bBigPopo, ((-trole->state + (DEATH - HELPTIME)) / 5 + 5) * 72, 0, SRCPAINT);
		}
	}
}
