#include "stdafx.h"
#include"Judge.h"
class AI :public Judge
{
public:

	//获取方向
	int GetDirection(int tMap[HEIGHT][WIDTH], const int popoExpMap[HEIGHT][WIDTH], struct Role *AI, struct Role *enemy, struct Popo *popo, bool &agreePutPopo);

	//获取是否放泡泡
	//tMap地图信息//popoExpMap提前爆炸的信息数组//AI,enemy//popo 泡泡头指针
	bool GetPutPopo(int tMap[HEIGHT][WIDTH], const int popoExpMap[HEIGHT][WIDTH],struct Role *AI, struct Role *enemy, struct Popo *popo);

	//查找指定value值的地方  
	//popoExpMap 提前爆炸的信息  //AIx,AIy AI所在坐标 //x,y返回的安全地方的坐标
	//value 查找最近值为value的地方  //没找到则x，y=-1  //prior是否是返回找到它时它的之前一个块
	bool GetPoint(int tMap[HEIGHT][WIDTH], const int popoExpMap[HEIGHT][WIDTH],
		int AIx, int AIy, int &x, int &y, int value, int prior);

	//A 寻路算法
	//移动到某点//tMap地图//AI 智能电脑//d_x,d_y目标坐标
	int MoveToPoint(struct Role *AI,int tMap[HEIGHT][WIDTH], int AIx, int AIy, int d_x, int d_y);//移动到一个点所要的方向，返回方向

	//获取两点的距离，理想距离
	int GetDistance(int x1, int x2);

	//AI//获取提前的爆炸信息
	//popo 泡泡指针头//popoExpMap 要保存到的二维数组
	void GetPopoExpMap(struct Role *AI,int tMap[HEIGHT][WIDTH], struct Popo *popo, int popoExpMap[HEIGHT][WIDTH]);

	//获取一个泡泡提前产生的爆炸信息
	//popoExpMap 要保存到的二维数组//x, y泡泡所在的坐标矩阵//level提前爆炸级别
	void GetDMap(struct Role *AI,int tMap[HEIGHT][WIDTH], int popoExpMap[HEIGHT][WIDTH], int x, int y, int level);

	//A*寻路算法使用
	//增加一个方块
	void AddBlock(int x, int y, int need, int use, int total);

	//一个方块的数据结构的赋值
	//temp block指针//x,y方块坐标//need到目的所要的计数
	//use已经使用的计数//total总共需要的路程
	void InitBlock(struct Block *temp, int x, int y, int need, int use, int total);

	//删除所有方块
	void DeleteAll(struct Block *head);

	//AI的处理//AI,enemy人物指针//direction要返回的方向//putPopo是否放泡泡，返回//popo 泡泡头指针
	void AIDeal(int tMap[HEIGHT][WIDTH], struct Role *AI, struct Role *enemy,
	struct Popo *popo, int &direction, bool &putPopo);

	//判断指定位置的四周有没有指定值的物质
	//x,y坐标//value 物品对应值
	bool HavePoint(int tMap[HEIGHT][WIDTH], int x, int y, int value, int &point_x, int &point_y);

	void GetPutPopoXY(int x, int y, int &popo_x, int &popo_y);
	void AutoProcess(Role *role2, Role *role1);
};