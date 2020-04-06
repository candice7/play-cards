#include "programdesign.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <time.h>
#include <vector>   
#include <string>
using namespace std;

enum card {
	heart3, diamond3, club3, spade3, heart4, diamond4, club4, spade4, heart5, diamond5, club5, spade5, heart6, diamond6, club6, spade6, heart7, diamond7, club7, spade7,
	heart8, diamond8, club8, spade8, heart9, diamond9, club9, spade9, heart10, diamond10, club10, spade10, heartJ, diamondJ, clubJ, spadeJ, heartQ, diamondQ, clubQ, spadeQ,
	heartK, diamondK, clubK, spadeK, heartA, diamondA, clubA, spadeA, heart2, diamond2, club2, spade2, king, KING
};
//�Ƶ�˳�򲻱�
string s[54] = { "heart3", "diamond3", "club3", "spade3", "heart4",  "diamond4", "club4","spade4", "heart5",  "diamond5", "club5","spade5", "heart6", "diamond6", "club6", "spade6", "heart7", "diamond7", "club7", "spade7",
	"heart8", "diamond8", "club8", "spade8", "heart9", "diamond9", "club9",  "spade9","heart10",  "diamond10", "club10","spade10", "heartJ", "diamondJ", "clubJ", "spadeJ", "heartQ", "diamondQ", "clubQ", "spadeQ",
	"heartK",  "diamondK", "clubK","spadeK", "heartA", "diamondA", "clubA", "spadeA", "heart2", "diamond2", "club2","spade2", "king", "KING" };

class player
{
private:card* mycards;
		int card_num;
		bool identity;
public:int able;          /*�жϳ���Ȩ�ޣ�0�����ܳ��ƣ�1�����Գ����ƣ�Ҳ���Գ�ը��������ʡ�ԣ���2�����Գ��ԣ�3�����Գ�����һ���ģ�4�����Գ�����һ��5�����Գ�����һ�ԣ�6��ֻ�ܳ�ը��
							7������������8�����Գ�2������һ��9�����Գ�5˳�ӣ�10�����Գ�6˳�ӣ�11�����Գ�7˳�ӣ�12�����Գ�8˳�ӣ�13�����Գ�9˳�ӣ�14�����Գ�10˳�ӣ�15�����Գ�11˳�ӣ�
							16�����Գ�12˳�ӣ�17�����Գ�3���ԣ�18�����Գ�4���ԣ�19�����Գ�5���ԣ�20�����Գ�6���ԣ�21�����Գ�7���ԣ�22�����Գ�8���ԣ�9���Ժ�10����Ҳ�б����Ŀ��ܣ�
							��ֻ���ǵ����ĵ�һ�ֳ��ƣ����Բ���Ҫ�����Ȩ�ޣ�*/
	   void getcards(card* newcards)
	   {
		   mycards = newcards;
		   if (identity)    card_num = 20;
		   else             card_num = 17;
	   }
	   void showcards();
	   void givecards(vector<card>out_cards);
	   int get_card_num()
	   {
		   return card_num;
	   }
	   bool show_identity()
	   {
		   if (identity)
			   return 1;
		   else    return 0;
	   }
	   void get_identity(bool iden)
	   {
		   identity = iden;
	   }
};

void player::showcards()                                 //ֻ����ʾ�����������򣬴洢��������,��ʾ������     
{
	vector<card>p;
	for (int i = 0; i < card_num; i++)
	{
		p.push_back(mycards[i]);
	}
	for (int i = 0; i < card_num - 1; i++)
		for (int j = 0; j < card_num - 1; j++)
		{
			if (p[j] < p[j + 1])
			{
				card c = p[j];
				p.erase(p.begin() + j);
				p.insert(p.begin() + j + 1, c);
			}
		}
	for (int i = 0; i < card_num; i++)
	{
		cout << s[p[i]] << " ";
	}
}

void player::givecards(vector<card>out_cards)                        //����������ʣ�µ���
{
	int n = out_cards.size();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (mycards[j] == out_cards[i])
				for (int k = j; k < n; k++)
					mycards[j] = mycards[j + 1];
	card_num = card_num - n;
}

void random_array(vector<card>old_cards, vector<card>&new_cards)      //�ο�https://blog.csdn.net/qq_19841133/article/details/88907051
{                                                                   //�����Ƶ�˳��
	for (int i = 54; i > 0; i--)
	{
		srand(unsigned(time(NULL)));
		int index = rand() % i;
		new_cards.push_back(old_cards[index]);
		old_cards.erase(old_cards.begin() + index);
	}
}

void big_to_small(vector<card>old_cards, vector<card>&new_cards)              //���ƴӴ�С����
{
	int n = old_cards.size();
	for (int i = 0; i < n; i++)
	{
		new_cards.push_back(old_cards[i]);
	}
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - 1; j++)
		{
			if (new_cards[j] < new_cards[j + 1])
			{
				card c = new_cards[j];
				new_cards.erase(new_cards.begin() + j);
				new_cards.insert(new_cards.begin() + j + 1, c);
			}
		}
}

void more_to_less(vector<card>old_cards, vector<card>&new_cards)            //���ƴӶൽ������        
{
	int many[14] = { 0 };
	int n = old_cards.size();
	for (int i = 0; i < n; i++)
		many[(old_cards[i]) / 4]++;
	new_cards.push_back(old_cards[0]);
	for (int i = 1; i < n; i++)
	{
		int hold = new_cards.size();
		for (int j = 0; j < new_cards.size(); j++)
		{
			if (many[(old_cards[i] / 4)] > many[new_cards[j] / 4])
			{
				new_cards.insert(new_cards.begin() + j, old_cards[i]);   break;
			}
			else if (many[(old_cards[i] / 4)] == many[new_cards[j] / 4] && old_cards[i] > new_cards[j])
			{
				new_cards.insert(new_cards.begin() + j, old_cards[i]);   break;
			}
		}
		if (new_cards.size() == hold)
			new_cards.push_back(old_cards[i]);
	}
}

void show(vector<card>out_cards)                        //��ʾ�����ƣ�out_cards��Ϊ�ǴӶൽ�������
{
	int n = out_cards.size();
	for (int i = 0; i < n; i++)
	{
		cout << out_cards[i] << "   ";
	}
}

bool one(vector<card>out_cards)                 //�жϳ����ǲ��ǵ���
{
	if (out_cards.size() == 1)
		return 1;
	else return 0;
}

bool two(vector<card>out_cards)                 //�жϳ����ǲ��Ƕ�
{
	if (out_cards.size() == 2)
	{
		if (out_cards[0] / 4 == out_cards[1] / 4)  return 1;
		else return 0;
	}
	else return 0;
}

bool three(vector<card>out_cards)               //�жϳ����ǲ�������һ����
{
	if (out_cards.size() == 3)
	{
		if (out_cards[0] / 4 == out_cards[1] / 4 && out_cards[0] / 4 == out_cards[2] / 4)
			return 1;
		else return 0;
	}
	else return 0;
}

bool four(vector<card>out_cards)               //�жϳ����ǲ�������һ,��Ϊout_cards�ѴӶൽ������            
{
	if (out_cards.size() == 4)
	{
		if (out_cards[0] / 4 == out_cards[1] / 4 && out_cards[0] / 4 == out_cards[2] / 4 && out_cards[3] / 4 != out_cards[0] / 4)
			return 1;
		else return 0;
	}
	else return 0;
}

bool five(vector<card>out_cards)                  //�жϳ����Ƿ�����һ��
{
	if (out_cards.size() == 5)
	{
		if (out_cards[0] / 4 == out_cards[1] / 4 && out_cards[0] / 4 == out_cards[2] / 4 && out_cards[3] / 4 == out_cards[4] / 4)
			return 1;
		else return 0;
	}
	else return 0;
}

bool six(vector<card>out_cards)                    //�жϳ����Ƿ�ը��
{
	if (out_cards.size() == 2)
	{
		if (out_cards[0] / 4 == 14 && out_cards[1] / 4 == 14)
			return 1;
		else return 0;
	}
	else if (out_cards.size() == 4)
	{
		if (out_cards[0] / 4 == out_cards[1] / 4 && out_cards[0] / 4 == out_cards[2] / 4 && out_cards[3] / 4 == out_cards[0] / 4)
			return 1;
		else return 0;
	}
	else return 0;
}

bool eight(vector<card>out_cards)           //�ж��Ƿ�Ϊ��������һ
{
	if (out_cards.size() == 8)
	{
		int a[8] = { 0 };
		for (int i = 0; i < 8; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] == a[1] && a[0] == a[2] && a[3] == a[4] && a[3] == a[5] && a[6] != a[0] && a[6] != a[3] && a[7] != a[0] && a[7] != a[3])
			return 1;
		else return 0;
	}
	else return 0;
}

bool nine(vector<card>out_cards)                         //�жϳ����Ƿ�Ϊ5˳��
{
	if (out_cards.size() == 5)
	{
		int a[5] = { 0 };
		for (int i = 0; i < 5; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] < 12 && a[0] - 1 == a[1] && a[1] - 1 == a[2] && a[2] - 1 == a[3] && a[3] - 1 == a[4])
			return 1;
		else return 0;
	}
	else return 0;
}

bool ten(vector<card>out_cards)                         //�жϳ����Ƿ�Ϊ6˳��
{
	if (out_cards.size() == 6)
	{
		int a[6] = { 0 };
		for (int i = 0; i < 6; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] < 12 && a[0] - 1 == a[1] && a[1] - 1 == a[2] && a[2] - 1 == a[3] && a[3] - 1 == a[4] && a[4] - 1 == a[5])
			return 1;
		else return 0;
	}
	else return 0;
}

bool eleven(vector<card>out_cards)                         //�жϳ����Ƿ�Ϊ7˳��
{
	if (out_cards.size() == 7)
	{
		int a[7] = { 0 };
		for (int i = 0; i < 7; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] < 12 && a[0] - 1 == a[1] && a[1] - 1 == a[2] && a[2] - 1 == a[3] && a[3] - 1 == a[4] && a[4] - 1 == a[5] && a[5] - 1 == a[6])
			return 1;
		else return 0;
	}
	else return 0;
}

bool twelve(vector<card>out_cards)                         //�жϳ����Ƿ�Ϊ8˳��
{
	if (out_cards.size() == 8)
	{
		int a[8] = { 0 };
		for (int i = 0; i < 8; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] < 12 && a[0] - 1 == a[1] && a[1] - 1 == a[2] && a[2] - 1 == a[3] && a[3] - 1 == a[4] && a[4] - 1 == a[5] && a[5] - 1 == a[6] && a[6] - 1 == a[7])
			return 1;
		else return 0;
	}
	else return 0;
}

bool thirteen(vector<card>out_cards)                         //�жϳ����Ƿ�Ϊ9˳��
{
	if (out_cards.size() == 9)
	{
		int a[9] = { 0 };
		for (int i = 0; i < 9; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] < 12 && a[0] - 1 == a[1] && a[1] - 1 == a[2] && a[2] - 1 == a[3] && a[3] - 1 == a[4] && a[4] - 1 == a[5] && a[5] - 1 == a[6] && a[6] - 1 == a[7] && a[7] - 1 == a[8])
			return 1;
		else return 0;
	}
	else return 0;
}

bool fourteen(vector<card>out_cards)                         //�жϳ����Ƿ�Ϊ10˳��
{
	if (out_cards.size() == 10)
	{
		int a[10] = { 0 };
		for (int i = 0; i < 10; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] < 12 && a[0] - 1 == a[1] && a[1] - 1 == a[2] && a[2] - 1 == a[3] && a[3] - 1 == a[4] && a[4] - 1 == a[5] && a[5] - 1 == a[6] && a[6] - 1 == a[7] && a[7] - 1 == a[8]
			&& a[8] - 1 == a[9])
			return 1;
		else return 0;
	}
	else return 0;
}

bool fifteen(vector<card>out_cards)                         //�жϳ����Ƿ�Ϊ11˳��
{
	if (out_cards.size() == 11)
	{
		int a[11] = { 0 };
		for (int i = 0; i < 11; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] < 12 && a[0] - 1 == a[1] && a[1] - 1 == a[2] && a[2] - 1 == a[3] && a[3] - 1 == a[4] && a[4] - 1 == a[5] && a[5] - 1 == a[6] && a[6] - 1 == a[7] && a[7] - 1 == a[8]
			&& a[8] - 1 == a[9] && a[9] - 1 == a[10])
			return 1;
		else return 0;
	}
	else return 0;
}

bool sixteen(vector<card>out_cards)                         //�жϳ����Ƿ�Ϊ12˳��
{
	if (out_cards.size() == 12)
	{
		int a[12] = { 0 };
		for (int i = 0; i < 12; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] < 12 && a[0] - 1 == a[1] && a[1] - 1 == a[2] && a[2] - 1 == a[3] && a[3] - 1 == a[4] && a[4] - 1 == a[5] && a[5] - 1 == a[6] && a[6] - 1 == a[7] && a[7] - 1 == a[8]
			&& a[8] - 1 == a[9] && a[9] - 1 == a[10] && a[10] - 1 == a[11])
			return 1;
		else return 0;
	}
	else return 0;
}

bool seventeen(vector<card>out_cards)                     //�ж��Ƿ�Ϊ������  
{
	if (out_cards.size() == 6)
	{
		int a[6] = { 0 };
		for (int i = 0; i < 6; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] - 1 == a[2] && a[2] - 1 == a[4] && a[1] - 1 == a[3] && a[3] - 1 == a[5] && a[0] == a[1])
			return 1;
		else return 0;
	}
	else return 0;
}

bool eighteen(vector<card>out_cards)                     //�ж��Ƿ�Ϊ������  
{
	if (out_cards.size() == 8)
	{
		int a[8] = { 0 };
		for (int i = 0; i < 8; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] - 1 == a[2] && a[2] - 1 == a[4] && a[1] - 1 == a[3] && a[3] - 1 == a[5] && a[0] == a[1] && a[4] - 1 == a[6] && a[5] - 1 == a[7])
			return 1;
		else return 0;
	}
	else return 0;
}

bool nineteen(vector<card>out_cards)                     //�ж��Ƿ�Ϊ������  
{
	if (out_cards.size() == 10)
	{
		int a[10] = { 0 };
		for (int i = 0; i < 10; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] - 1 == a[2] && a[2] - 1 == a[4] && a[1] - 1 == a[3] && a[3] - 1 == a[5] && a[0] == a[1] && a[4] - 1 == a[6] && a[5] - 1 == a[7] && a[6] - 1 == a[8] && a[7] - 1 == a[9])
			return 1;
		else return 0;
	}
	else return 0;
}

bool twenty(vector<card>out_cards)                     //�ж��Ƿ�Ϊ������  
{
	if (out_cards.size() == 12)
	{
		int a[12] = { 0 };
		for (int i = 0; i < 12; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] - 1 == a[2] && a[2] - 1 == a[4] && a[1] - 1 == a[3] && a[3] - 1 == a[5] && a[0] == a[1] && a[4] - 1 == a[6] && a[5] - 1 == a[7] && a[6] - 1 == a[8] && a[7] - 1 == a[9]
			&& a[8] - 1 == a[10] && a[9] - 1 == a[11])
			return 1;
		else return 0;
	}
	else return 0;
}

bool twentyone(vector<card>out_cards)                     //�ж��Ƿ�Ϊ������  
{
	if (out_cards.size() == 14)
	{
		int a[14] = { 0 };
		for (int i = 0; i < 14; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] - 1 == a[2] && a[2] - 1 == a[4] && a[1] - 1 == a[3] && a[3] - 1 == a[5] && a[0] == a[1] && a[4] - 1 == a[6] && a[5] - 1 == a[7] && a[6] - 1 == a[8] && a[7] - 1 == a[9]
			&& a[8] - 1 == a[10] && a[9] - 1 == a[11] && a[10] - 1 == a[12] && a[11] - 1 == a[13])
			return 1;
		else return 0;
	}
	else return 0;
}

bool twentytwo(vector<card>out_cards)                     //�ж��Ƿ�Ϊ������  
{
	if (out_cards.size() == 16)
	{
		int a[16] = { 0 };
		for (int i = 0; i < 16; i++)
			a[i] = out_cards[i] / 4;
		if (a[0] - 1 == a[2] && a[2] - 1 == a[4] && a[1] - 1 == a[3] && a[3] - 1 == a[5] && a[0] == a[1] && a[4] - 1 == a[6] && a[5] - 1 == a[7] && a[6] - 1 == a[8] && a[7] - 1 == a[9]
			&& a[8] - 1 == a[10] && a[9] - 1 == a[11] && a[10] - 1 == a[12] && a[11] - 1 == a[13] && a[12] - 1 == a[14] && a[13] - 1 == a[15])
			return 1;
		else return 0;
	}
	else return 0;
}

bool judge(player you, vector<card>last_cards, vector<card>out_cards)                           //�ж���ҳ����Ƿ���Ϲ���    
{
	switch (you.able)
	{
	case 1: {if (one(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 2: {if (two(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 3: {if (three(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 4: {if (four(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 5: {if (five(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 6: {if (six(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 7: {if (one(out_cards) || two(out_cards) || three(out_cards) || four(out_cards) || five(out_cards) || six(out_cards) || eight(out_cards) || nine(out_cards) || ten(out_cards)
		|| eleven(out_cards) || twelve(out_cards) || thirteen(out_cards) || fourteen(out_cards) || fifteen(out_cards) || sixteen(out_cards) || seventeen(out_cards) || eighteen(out_cards)
		|| nineteen(out_cards) || twenty(out_cards) || twentyone(out_cards) || twentytwo(out_cards))return 1;  else return 0; }
	case 8: {if (eight(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 9: {if (nine(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 10: {if (ten(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 11: {if (eleven(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 12: {if (twelve(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 13: {if (thirteen(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 14: {if (fourteen(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 15: {if (fifteen(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 16: {if (sixteen(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 17: {if (seventeen(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 18: {if (eighteen(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 19: {if (nineteen(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 20: {if (twenty(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 21: {if (twentyone(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	case 22: {if (twentytwo(out_cards) && out_cards[0] > last_cards[0])return 1;  else return 0; }
	}
}

void cardout(player p1, player p2, vector<card>&last_cards)                  //������ҳ��ƺ���  00000000001����Ҫ�������е���(givecards��������˳���޸�ʣ������)������last_cards,����������ҵ�able������show������ʾ����,��������ʾ��������
{}

void mycardout(player you, player left, vector<card>&last_cards, int & illegal)              //�û����ƺ���  01
{
	you.showcards();
	cout << "�����" << endl;

}

int main()
{
	bool game = 1;
	do {
		cout << "ѡ�������ݣ�������1��ũ��0" << endl;
		bool iden;         cin >> iden;
		player you;      player left;          player right;
		you.get_identity(iden);                                     //ȷ����Һ�����������ҵ����,left��Զ��ũ��
		right.get_identity(!iden);
		left.get_identity(0);
		left.able = 0;
		card all_cards[54] = { heart3,spade3,diamond3,club3,heart4,spade4,diamond4,club4,heart5,spade5,diamond5, club5, heart6, spade6, diamond6, club6, heart7, spade7, diamond7, club7,
				   heart8, spade8, diamond8, club8, heart9, spade9, diamond9, club9,heart10, spade10, diamond10, club10,heartJ, spadeJ, diamondJ, clubJ, heartQ, spadeQ, diamondQ, clubQ,
				   heartK, spadeK, diamondK, clubK, heartA, spadeA, diamondA, clubA, heart2, spade2, diamond2, club2,king,KING };
		vector<card>old_cards, new_cards;
		for (int i = 0; i < 54; i++)                             //������ת��Ϊ������
			old_cards.push_back(all_cards[i]);
		random_array(old_cards, new_cards);                      //���������Ƶ�˳��
		for (int i = 0; i < 54; i++)                             //������ת��Ϊ������
			all_cards[i] = new_cards[i];
		cout << "������������ǣ�" << endl;                      //���������
		cout << s[all_cards[51]] << "  " << s[all_cards[52]] << "  " << s[all_cards[53]] << endl;
		//����
		card l_cards[17] = { all_cards[2],all_cards[5],all_cards[8],all_cards[11],all_cards[14],all_cards[17],all_cards[20],all_cards[23],all_cards[26],all_cards[29],all_cards[32],
								 all_cards[35],all_cards[38],all_cards[41],all_cards[44],all_cards[47],all_cards[50] };
		left.getcards(l_cards);
		if (iden)
		{
			right.able = 0;       you.able = 7;
			card y_cards[20] = { all_cards[1],all_cards[4],all_cards[7],all_cards[10],all_cards[13],all_cards[16],all_cards[19],all_cards[22],all_cards[25],all_cards[28],all_cards[31],
								 all_cards[34],all_cards[37],all_cards[40],all_cards[43],all_cards[46],all_cards[49],all_cards[51],all_cards[52],all_cards[53] };
			card r_cards[17] = { all_cards[0],all_cards[3],all_cards[6],all_cards[9],all_cards[12],all_cards[15],all_cards[18],all_cards[21],all_cards[24],all_cards[27],all_cards[30],
								 all_cards[33],all_cards[36],all_cards[39],all_cards[42],all_cards[45],all_cards[48] };
			you.getcards(y_cards);
			right.getcards(r_cards);
		}
		else
		{
			right.able = 7;     you.able = 0;
			card r_cards[20] = { all_cards[1],all_cards[4],all_cards[7],all_cards[10],all_cards[13],all_cards[16],all_cards[19],all_cards[22],all_cards[25],all_cards[28],all_cards[31],
								 all_cards[34],all_cards[37],all_cards[40],all_cards[43],all_cards[46],all_cards[49],all_cards[51],all_cards[52],all_cards[53] };
			card y_cards[17] = { all_cards[0],all_cards[3],all_cards[6],all_cards[9],all_cards[12],all_cards[15],all_cards[18],all_cards[21],all_cards[24],all_cards[27],all_cards[30],
								 all_cards[33],all_cards[36],all_cards[39],all_cards[42],all_cards[45],all_cards[48] };
			you.getcards(y_cards);
			right.getcards(r_cards);
		}

		int illegal = 0;               //���Ʋ����߼�����Ϊ0
		vector<card> last_cards;       //�洢��һ�ֳ���
		do {
			if (illegal > 4)     break;
			if (you.able) { mycardout(you, left, last_cards, illegal); }
			else if (left.able) { cardout(left, right, last_cards); }
			else if (right.able) { cardout(right, you, last_cards); }
		} while (you.get_card_num() && left.get_card_num() && right.get_card_num());   //����ѭ��       ���ϴ���һ����Ϸ����5�β�������Ϸ����ĳ��ƣ���Ϸʧ�ܡ� 02
		if (you.get_card_num())
			cout << "�����ˡ�" << endl;
		else cout << "��Ӯ�ˣ�" << endl;
		cout << "�Ƿ�����һ�֣�  1����   0����" << endl;
		bool gam;    cin >> gam;
		if (gam)   game = 1;   else  game = 0;
	} while (game);
	return 0;
}
