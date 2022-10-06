//���ڹ���������������ʦ��Ұ�˵�����
#include <iostream>
#include<queue>
//#include<Query.h>
using namespace std;

struct States
{
	int X1;//��ʼ���ϵ���ʦ����
	int X2;//��ʼ���ϵ�Ұ������
	int X3;//С������λ��(1��ʾ��ʼ����0��ʾĿ�İ�)
	int tree_depth = 0;//��״̬��һ�γ��ֵ���Ͳ�
	States * pre;//ָ��ǰ����ָ��
};
States * hasgone[1000];//�Ѿ��߹���״̬,���ڱ����Ժ��ظ�
int num = 0;//hasgone������
int n = 0;//��ʦ��Ұ�˵�������
int c = 0;//С���Ͽɳ�������
queue<States *> que;//���У����ڽ��й����������
//����·�����Լ�����Ӧ�Ĵ����ش���
States *answer[1000];
int num_answer = 0;
int step_num[1000];//·����Ӧ�Ĳ���

//int tree_depth = 0;
queue<States*> rubbish;//��������,����������������δdelete������


States* Start2Destination(States* pre,int x1, int x2)//now��ǰ״̬,�ӿ�ʼ��Ŀ�ĵ�(x1�Ǵ�����ʦ������x2�Ǵ���Ұ������)
{
	int Start_Priests= pre->X1 - x1;//���ڰ��ϵ���ʦ����
	int Start_savages= pre->X2 - x2;//���ڰ��ϵ�Ұ������
	int End_Priests = n-pre->X1 + x1;//����Ŀ�ĵص���ʦ����
	int End_savages = n-pre->X2 +x2;//����Ŀ�ĵص�Ұ������
	if ((x1 >= x2||x1==0)&& (Start_Priests >= Start_savages|| Start_Priests==0) &&( End_Priests >= End_savages|| End_Priests==0))//����Ҫ��
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

States* Destination2Start(States* pre,int x1, int x2)//��Ŀ�ĵص���ʼ��(x1�Ǵ�����ʦ������x2�Ǵ���Ұ������)
{
	int Start_Priests = pre->X1 +x1;//���ڰ��ϵ���ʦ����
	int Start_savages = pre->X2 + x2;//���ڰ��ϵ�Ұ������
	int End_Priests = n - pre->X1 - x1;//����Ŀ�ĵص���ʦ����
	int End_savages = n - pre->X2 - x2;//����Ŀ�ĵص�Ұ������
	if ((x1 >= x2 || x1 == 0) && (Start_Priests >= Start_savages || Start_Priests == 0) && (End_Priests >= End_savages || End_Priests == 0))//����Ҫ��
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

bool Hasgone(States* one)//�ж�����Ƿ�ǰ���Ѿ��߹���
{
	for (int i = 0; i < num; i++)
	{
		if (one->X1 == hasgone[i]->X1&&one->X2 == hasgone[i]->X2&&one->X3 == hasgone[i]->X3&&one->tree_depth>hasgone[i]->tree_depth)//���ظ���,�Ҳ���ͬһ��,ɾ��new�Ķ���,return,true
		{
			delete one;
	
			return true;
		}
	}
	//��״̬֮ǰδ�߹�
	//����hasgone���沢num++
	hasgone[num] = one;
	num++;
	return false;
}
int route = 0;
void Nextstep()
{
	if (que.empty()) return;//����Ϊ��
	States*pre = que.front();
	rubbish.push(pre);
	que.pop();
	if (pre->X1 == 0 && pre->X2 == 0 && pre->X3 == 0)//·���Ѿ�������
	{
		route++;
		cout << "��"<<route<<"��·����";
		showSolution(pre,0);
		cout << "           ·������Ϊ" << step_num[num_answer] << endl;
		answer[num_answer] = pre;
		num_answer++;
		Nextstep();
	}
	//if (Hasgone(pre)) return;//���״̬֮ǰ�߹���,����
	if (pre->X3 == 1)//����ʼ��
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
	else//��Ŀ�İ�
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
	cout << "��������ʦ��Ұ�˵�����n"<<endl;
	cin >> n;
	cout << "������С�����ܳ��ص�����" << endl;
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
	if (num_answer == 0) cout << "����false" << endl;
	else cout << "����succed" << endl;
	delete_rubbish();
}

