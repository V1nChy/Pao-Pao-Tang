struct Popo{
	int x;
	int y;
	int roleId;//��������
	int life;//����
	int lengthOfPopo;//����
	struct Popo *next;
}; 
class Paopao
{
	Popo *popo;
public:
	void AddRealPopo(struct Role *&trole);
	void AddPopo(int lengthOfPopo, int life, int x, int y, int roleId, struct Role *trole);
	struct Popo * GetPopo(int x, int y);
	void GetPutPopoXY(int x, int y, int &popo_x, int &popo_y);
	void DeletePopo(struct Popo *p);
	void DealExPopo(int x, int y);
	void Deleteall();
	Popo * get_popo()
	{
		return popo;
	}
};