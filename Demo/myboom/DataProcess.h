#include "stdafx.h"
#include"Judge.h"
class DataProcess:public Judge
{
public:
	void DealRole(int tMap[HEIGHT][WIDTH], struct Role *&trole, bool tstate);
	void InitRole(struct Role *&trole, int x, int y, int roleId);
	void InitDate();
	void GameStart();
};
