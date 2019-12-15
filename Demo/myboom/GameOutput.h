#include "stdafx.h"
class  InitImages
{
protected:
	HDC bRole1Death1, bRole1Death2;//死亡图片
	HDC bRole2Death1, bRole2Death2;
	HDC bBG, cBG;
	HDC bBigPopo, cBigPopo;
	HDC bDraw, cDraw;//平局
	HDC bExplosion, cExplosion;
	HDC bGift[9], cGift[9];
	HDC bPlayer, cPlayer;
	HDC bPopo, cPopo;
	HDC bRole1, cRole1;
	HDC bRole1Ani, cRole1Ani;
	HDC bRole1Start, cRole1Start;
	HDC bRole2, cRole2;
	HDC bRole2Ani, cRole2Ani;

	HDC bRole2Start, cRole2Start;
	HDC bSandBlockBuff, cSandBlockBuff;
	HDC bSandBlockYellow, cSandBlockYellow;

	HDC bSandGround, cSandGround;

	HDC bSandTree, cSandTree;

	HDC bShadowBlock, cShadowBlock;
	HDC bShadowGift, cShadowGift;
	HDC bShadowPopo, cShadowPopo;
	HDC bShadowRole, cShadowRole;

	HDC bStart, cStart;
	HDC bWin, cWin;
	HDC BG1, BG2;
	HDC Help1, Help2;
	HDC SandOasis1, SandOasis2;
	HDC SandOasisAni1, SandOasisAni2;
	HDC cSandTreeYellow, bSandTreeYellow;
	HDC cSandTentBlue, bSandTentBlue;
	HDC cSandTentRed, bSandTentRed;
	HDC cFastUFO, bFastUFO;
	HDC cRole1Ride, bRole1Ride;
	HDC cRole2Ride, bRole2Ride;
	HDC cFastTurtle, bFastTurtle;
	HDC cOwl, bOwl;
public:
	void InitFile(HDC hdc, HDC imageDC);

	//获取一个hdc一个矩形区域的像素数据结构//source:源hdc//tImage 对象图像//imageStruct:图像数据结构
	//bmp BITMAP属性//begin_x, begin_y, width, height   开始的坐标，宽度和高度
	unsigned char *GetStruct(HDC hdc, HDC source, HDC &tImage, BITMAP &bmp, int begin_x, int begin_y, int width, int height);

	//透明处理，value为透明度//image为返回的图像//frontStruct 前景色的数据结构//backStruct后景色的数据结构
	//透明度 1 - 100//width,height//begin, beginy
	void ChangeImage(HBITMAP &image, HDC SourceRole, unsigned char *frontStruct,unsigned char *backStruct, int value, BITMAP front, BITMAP back,int width, int height, int beginx, int beginy);

	//初始化死亡的图像
	void InitDeathImage(HDC hdc, HDC &bDeath1, HDC &bDeath2, HDC bRoleAni, int width, int height,int beginx, int beginy);

	//图片的加载//bImage:加载图片1//bImage:图片2//width height 图片宽度高度//fileName图片名,含路径
	void InitImage(HDC hdc, HDC imageDC, HDC &bImage, HDC &cImage, int width, int height, char fileName[]);

};

class GameOutput :public InitImages
{
public:
	void PaintMain(HDC hdc, HDC bufHdc);
	void PaintHelp(HDC hdc, HDC bufHdc);
	void Paint(HDC hdc, HDC bufHdc);
	void PaintXY(int x, int y, HDC bufDC, int value);
	void PaintPopo(struct Popo *p, HDC bufDC);
	void PaintRole(HDC bufDC, int x, int y, int num, struct Role *trole);
	void PaintExplosion(HDC bufDC, int i, int j);
};