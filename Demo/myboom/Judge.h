#include "stdafx.h"
#ifndef JUDGE_H
#define JUDGE_H
class Judge
{
public:
	bool CanMove(struct Role *&trole,int derect, int tMap[HEIGHT][WIDTH], int x, int y);
	bool MoveJudge(struct Role *&trole,int derect, int &x, int &y, int speed);
	bool JudgeDead(int x, int y);
};
#endif