//基于广度优先搜索求解牧师和野人的问题
#include <iostream>
#include<queue>
//#include<Query.h>
using namespace std;

struct States
{
	int X1;//起始岸上的牧师人数
	int X2;//起始岸上的野人人数
	int X3;//小船现在位置(1表示起始岸，0表示目的岸)
	int tree_depth = 0;//该状态第一次出现的最低层
	States * pre;//指向前驱的指针
};
States * hasgone[1000];//已经走过的状态,用于避免以后重复
int num = 0;//hasgone的数量
int n = 0;//牧师和野人的总人数
int c = 0;//小船上可承载人数
queue<States *> que;//队列，用于进行广度优先搜索
//保存路径，以及它对应的船来回次数
States *answer[1000];
int num_answer = 0;
int step_num[1000];//路径对应的步数

//int tree_depth = 0;
queue<States*> rubbish;//垃圾队列,用来存放最后运算完未delete的数据


States* Start2Destination(States* pre,int x1, int x2)//now当前状态,从开始到目的地(x1是船上牧师人数，x2是船上野人人数)
{
	int Start_Priests= pre->X1 - x1;//现在岸上的牧师人数
	int Start_savages= pre->X2 - x2;//现在岸上的野人人数
	int End_Priests = n-pre->X1 + x1;//现在目的地的牧师人数
	int End_savages = n-pre->X2 +x2;//现在目的地的野人人数
	if ((x1 >= x2||x1==0)&& (Start_Priests >= Start_savages|| Start_Priests==0) &&( End_Priests >= End_savages|| End_Priests==0))//符合要求
	{
		States * now = new States;
		now->pre = pre;
		now->X1 = Start_Priests;
		now->X2 = Start_savages;
		now->tree_depth = pre->tree_depth + 1;
		now->X3 = 0;
		return now;
	}
	return NULL;
}

States* Destination2Start(States* pre,int x1, int x2)//从目的地到开始地(x1是船上牧师人数，x2是船上野人人数)
{
	int Start_Priests = pre->X1 +x1;//现在岸上的牧师人数
	int Start_savages = pre->X2 + x2;//现在岸上的野人人数
	int End_Priests = n - pre->X1 - x1;//现在目的地的牧师人数
	int End_savages = n - pre->X2 - x2;//现在目的地的野人人数
	if ((x1 >= x2 || x1 == 0) && (Start_Priests >= Start_savages || Start_Priests == 0) && (End_Priests >= End_savages || End_Priests == 0))//符合要求
	{
		States * now = new States;
		now->pre = pre;
		now->X1 = Start_Priests;
		now->X2 = Start_savages;
		now->tree_depth = pre->tree_depth + 1;
		now->X3 = 1;
		return now;

	}
	return NULL;
}

void showSolution(States * states, int time)
{
	if (states == NULL)
	{
		step_num[num_answer] = time;
		cout << endl;
	}
	else
	{
		showSolution(states->pre, ++time);
		cout << "(" << states->X1 << "," << states->X2 << "," << states->X3 << ")   ";
	}
}

bool Hasgone(States* one)//判断这个是否前面已经走过的
{
	for (int i = 0; i < num; i++)
	{
		if (one->X1 == hasgone[i]->X1&&one->X2 == hasgone[i]->X2&&one->X3 == hasgone[i]->X3&&one->tree_depth>hasgone[i]->tree_depth)//有重复的,且不再同一层,删除new的东西,return,true
		{
			delete one;
	
			return true;
		}
	}
	//该状态之前未走过
	//加入hasgone里面并num++
	hasgone[num] = one;
	num++;
	return false;
}
int route = 0;
void Nextstep()
{
	if (que.empty()) return;//队列为空
	States*pre = que.front();
	rubbish.push(pre);
	que.pop();
	if (pre->X1 == 0 && pre->X2 == 0 && pre->X3 == 0)//路程已经走完了
	{
		route++;
		cout << "第"<<route<<"条路径：";
		showSolution(pre,0);
		cout << "           路径长度为" << step_num[num_answer] << endl;
		answer[num_answer] = pre;
		num_answer++;
		Nextstep();
	}
	//if (Hasgone(pre)) return;//这个状态之前走过了,返回
	if (pre->X3 == 1)//在起始岸
	{
		int Max1 = pre->X1 > c ? c : pre->X1;
		int Max2 = pre->X2 > c ? c : pre->X2;
		for (int i = 0; i <= Max1; i++)
		{
			for (int j = 0; j <= Max2; j++)
			{
				if (i + j <= c&&i+j>=1)
				{
					States* now=Start2Destination(pre,i,j);
					if (now!=NULL&&!Hasgone(now))
					{
						que.push(now);
					}
				}
			}
		}
		Nextstep();
	}
	else//在目的岸
	{
		int Max1 = n - pre->X1 > c ? c : n-pre->X1;
		int Max2 = n - pre->X2 > c ? c : n-pre->X2;
		for (int i = 0; i <= Max1; i++)
		{
			for (int j = 0; j <= Max2; j++)
			{
				if (i + j <= c && i + j >= 1)
				{
					States* now = Destination2Start(pre, i, j);
					if (now != NULL && !Hasgone(now))
					{
						que.push(now);
					}
				}
			}
		}
		Nextstep();
	}
}



void delete_rubbish()
{
	while (!rubbish.empty())
	{
		States*del = rubbish.front();
		rubbish.pop();
		delete del;
	}
}

int main()
{
	cout << "请输入牧师和野人的人数n"<<endl;
	cin >> n;
	cout << "请输入小船上能承载的人数" << endl;
	cin >> c;
	States* initial = new States();
	initial->X1 = n;
	initial->X2 = n;
	initial->X3 = 1;
	initial->tree_depth = 0;
	initial->pre = NULL;
	que.push(initial);
	Hasgone(initial);
	Nextstep();
	if (num_answer == 0) cout << "答案是false" << endl;
	else cout << "答案是succed" << endl;
	delete_rubbish();
}

