#define VK_W              0x57
#define VK_S              0x53
#define VK_A              0x41
#define VK_D              0x44
#define VK_0              0x30
#define WIN32_LEAN_AND_MEAN 
#define WINDOW_CLASS_NAME "WINCLASS1"
#define WIDTH 15
#define HEIGHT 13
#define SKEW 32//可以存在的偏移
#define SKEW_X 20//X方向判断死亡存在的偏移
#define SKEW_Y 22//Y方向判断死亡存在的偏移
#define POPOLIFE 32//生命周期
#define POPO 10
#define DPOPO 11
#define DANPOPO 17//危险周期
#define WDEXPLOTION 12//准备危险区
#define DEXPLOTION 13//危险区
//方向
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define RSHIFT 16
#define LSHIFT 20
#define DEATH -1
#define SANDGROUND 0//空白
#define SANDBLOCKYELLOW 50//墙
#define SandTree 51
#define SandOasisAni 52
#define SandTent 53
//道具
#define GIFT1 1 //泡泡
#define GIFT2 2 //鞋子
#define GIFT3 3 //药瓶
#define GIFT4 4 //大威力
#define GIFT5 5 //大速度
#define GIFT6 6 //飞碟
#define GIFT7 7 //乌龟
#define GIFT8 8 //鸟
#define ROLE1 200
#define ROLE2 201

//爆炸状态
#define EXPLOSIONCENTRE 101//爆炸中心
#define EXPLOSIONUP 113
#define EXPLOSIONDOWN 127
#define EXPLOSIONLEFT 141
#define EXPLOSIONRIGHT 156

#define CANMOVE 100//可以移动的最小值
//#define CANNOTMOVE 6

//游戏数据
#define HELPTIME 100
#define MAXPOPOLEN 13//最大泡泡长
#define NUMOFPOPO 8
#define PWIDTH 72
#define PHEIGHT 72
#define RWIDTH 48
#define RHEIGHT 64
#define BEGINSTATE 20
#define ENDSTATE 80
#define MAXPOPO 9
#define MAXLENGOFPOPO 10
#define MAXSPEED 11
#define Limit_gift4 2
#define Limit_gift5 2
#define Limit_ride 4

//游戏角色数据结构
struct Role{
	int x;
	int y;
	int roleId;
	int ride;//坐骑
	int speed;//速度
	int state;//生死
	int direction;//方向
	int numOfPopo;//可放泡泡数
	int putPopo;//已经放的泡泡数
	int lengthOfPopo;//泡泡威力
	bool keyState[4];
	bool addPopo;
	bool Active_keystate;
	bool Auto;
	int immunex;
	int immuney;
};

//障碍物数据结构
struct Block
{
	int x;
	int y;
	int total;
	int need;
	int use;
	struct Block *next;
};

#define BEGINRIDE 0 //开始
#define BEGINSPEED 3 //开始速度
#define BEGINLENGTHOFPOPO 2//泡泡长
#define BEGINNUMOFPOPO 1//泡泡数
