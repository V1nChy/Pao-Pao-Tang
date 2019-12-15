#include "stdafx.h"
#include"Judge.h"
class AI :public Judge
{
public:

	//��ȡ����
	int GetDirection(int tMap[HEIGHT][WIDTH], const int popoExpMap[HEIGHT][WIDTH], struct Role *AI, struct Role *enemy, struct Popo *popo, bool &agreePutPopo);

	//��ȡ�Ƿ������
	//tMap��ͼ��Ϣ//popoExpMap��ǰ��ը����Ϣ����//AI,enemy//popo ����ͷָ��
	bool GetPutPopo(int tMap[HEIGHT][WIDTH], const int popoExpMap[HEIGHT][WIDTH],struct Role *AI, struct Role *enemy, struct Popo *popo);

	//����ָ��valueֵ�ĵط�  
	//popoExpMap ��ǰ��ը����Ϣ  //AIx,AIy AI�������� //x,y���صİ�ȫ�ط�������
	//value �������ֵΪvalue�ĵط�  //û�ҵ���x��y=-1  //prior�Ƿ��Ƿ����ҵ���ʱ����֮ǰһ����
	bool GetPoint(int tMap[HEIGHT][WIDTH], const int popoExpMap[HEIGHT][WIDTH],
		int AIx, int AIy, int &x, int &y, int value, int prior);

	//A Ѱ·�㷨
	//�ƶ���ĳ��//tMap��ͼ//AI ���ܵ���//d_x,d_yĿ������
	int MoveToPoint(struct Role *AI,int tMap[HEIGHT][WIDTH], int AIx, int AIy, int d_x, int d_y);//�ƶ���һ������Ҫ�ķ��򣬷��ط���

	//��ȡ����ľ��룬�������
	int GetDistance(int x1, int x2);

	//AI//��ȡ��ǰ�ı�ը��Ϣ
	//popo ����ָ��ͷ//popoExpMap Ҫ���浽�Ķ�ά����
	void GetPopoExpMap(struct Role *AI,int tMap[HEIGHT][WIDTH], struct Popo *popo, int popoExpMap[HEIGHT][WIDTH]);

	//��ȡһ��������ǰ�����ı�ը��Ϣ
	//popoExpMap Ҫ���浽�Ķ�ά����//x, y�������ڵ��������//level��ǰ��ը����
	void GetDMap(struct Role *AI,int tMap[HEIGHT][WIDTH], int popoExpMap[HEIGHT][WIDTH], int x, int y, int level);

	//A*Ѱ·�㷨ʹ��
	//����һ������
	void AddBlock(int x, int y, int need, int use, int total);

	//һ����������ݽṹ�ĸ�ֵ
	//temp blockָ��//x,y��������//need��Ŀ����Ҫ�ļ���
	//use�Ѿ�ʹ�õļ���//total�ܹ���Ҫ��·��
	void InitBlock(struct Block *temp, int x, int y, int need, int use, int total);

	//ɾ�����з���
	void DeleteAll(struct Block *head);

	//AI�Ĵ���//AI,enemy����ָ��//directionҪ���صķ���//putPopo�Ƿ�����ݣ�����//popo ����ͷָ��
	void AIDeal(int tMap[HEIGHT][WIDTH], struct Role *AI, struct Role *enemy,
	struct Popo *popo, int &direction, bool &putPopo);

	//�ж�ָ��λ�õ�������û��ָ��ֵ������
	//x,y����//value ��Ʒ��Ӧֵ
	bool HavePoint(int tMap[HEIGHT][WIDTH], int x, int y, int value, int &point_x, int &point_y);

	void GetPutPopoXY(int x, int y, int &popo_x, int &popo_y);
	void AutoProcess(Role *role2, Role *role1);
};