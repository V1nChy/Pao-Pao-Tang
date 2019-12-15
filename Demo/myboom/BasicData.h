#define VK_W              0x57
#define VK_S              0x53
#define VK_A              0x41
#define VK_D              0x44
#define VK_0              0x30
#define WIN32_LEAN_AND_MEAN 
#define WINDOW_CLASS_NAME "WINCLASS1"
#define WIDTH 15
#define HEIGHT 13
#define SKEW 32//���Դ��ڵ�ƫ��
#define SKEW_X 20//X�����ж��������ڵ�ƫ��
#define SKEW_Y 22//Y�����ж��������ڵ�ƫ��
#define POPOLIFE 32//��������
#define POPO 10
#define DPOPO 11
#define DANPOPO 17//Σ������
#define WDEXPLOTION 12//׼��Σ����
#define DEXPLOTION 13//Σ����
//����
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define RSHIFT 16
#define LSHIFT 20
#define DEATH -1
#define SANDGROUND 0//�հ�
#define SANDBLOCKYELLOW 50//ǽ
#define SandTree 51
#define SandOasisAni 52
#define SandTent 53
//����
#define GIFT1 1 //����
#define GIFT2 2 //Ь��
#define GIFT3 3 //ҩƿ
#define GIFT4 4 //������
#define GIFT5 5 //���ٶ�
#define GIFT6 6 //�ɵ�
#define GIFT7 7 //�ڹ�
#define GIFT8 8 //��
#define ROLE1 200
#define ROLE2 201

//��ը״̬
#define EXPLOSIONCENTRE 101//��ը����
#define EXPLOSIONUP 113
#define EXPLOSIONDOWN 127
#define EXPLOSIONLEFT 141
#define EXPLOSIONRIGHT 156

#define CANMOVE 100//�����ƶ�����Сֵ
//#define CANNOTMOVE 6

//��Ϸ����
#define HELPTIME 100
#define MAXPOPOLEN 13//������ݳ�
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

//��Ϸ��ɫ���ݽṹ
struct Role{
	int x;
	int y;
	int roleId;
	int ride;//����
	int speed;//�ٶ�
	int state;//����
	int direction;//����
	int numOfPopo;//�ɷ�������
	int putPopo;//�Ѿ��ŵ�������
	int lengthOfPopo;//��������
	bool keyState[4];
	bool addPopo;
	bool Active_keystate;
	bool Auto;
	int immunex;
	int immuney;
};

//�ϰ������ݽṹ
struct Block
{
	int x;
	int y;
	int total;
	int need;
	int use;
	struct Block *next;
};

#define BEGINRIDE 0 //��ʼ
#define BEGINSPEED 3 //��ʼ�ٶ�
#define BEGINLENGTHOFPOPO 2//���ݳ�
#define BEGINNUMOFPOPO 1//������
