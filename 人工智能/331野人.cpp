#include <iostream>
#include <vector>
#include <list>
using namespace std;
 
typedef struct
{
	int m;//��ʾ����ʿ
	int c;// ��ʾҰ��
	int b;//��״̬,1Ϊ�˰���0Ϊ������ʼ�Ӱ� 
}MCNode;
 
list<MCNode> open;//�൱�ڶ���
vector<MCNode> closed;//closed��
 
//�ж��Ƿ���Ŀ����
bool IsGoal(MCNode tNode)
{
	if(tNode.m==0&&tNode.c==0&&tNode.b==0)
		return true;
	else
		return false;
}
//�ж��Ƿ��ǺϷ�״̬
bool IsLegal(MCNode tNode)
{
	if(tNode.m>=0&&tNode.m<=3&&tNode.c>=0&&tNode.c<=3)
	{
		if((tNode.m==tNode.c)||(tNode.m==3)||(tNode.m==0))//��ʵ��������֡�2��1��1����������԰��Ѿ��ǲ��Ϸ����ˣ��Ϸ�ֻ����������� 
			return true;
		else
			return false;
	}
	else
		return false;
}
//������������ж����ṹ���Ƿ����
bool operator==(MCNode m1,MCNode m2)
{
	if(m1.m==m2.m&&m1.c==m2.c&&m1.b==m2.b)
		return true;
	else
		return false;
}
//�ж��Ƿ�����closed����
bool IsClosed(MCNode tNode)
{
	int i;
	for(i=0;i!=closed.size();i++)
	{
		if(tNode==closed[i])
			return true;
	}
	if(i==closed.size())
		return false;
}
void ExpandNode(MCNode tNode,int b,list<MCNode> &open)
{
	MCNode node[5];//Ӧ��5�����������½��
	if(b==1)
	{
		for(int i=0;i<5;i++)
			node[i].b=0;
		node[0].m=tNode.m-2;
		node[0].c=tNode.c;
		node[1].m=tNode.m;
		node[1].c=tNode.c-2;
		node[2].m=tNode.m-1;
		node[2].c=tNode.c-1;
		node[3].m=tNode.m-1;
		node[3].c=tNode.c;
		node[4].m=tNode.m;
		node[4].c=tNode.c-1;
	}
	else
	{
		for(int i=0;i<5;i++)
			node[i].b=1;
		node[0].m=tNode.m+2;
		node[0].c=tNode.c;
		node[1].m=tNode.m;
		node[1].c=tNode.c+2;
		node[2].m=tNode.m+1;
		node[2].c=tNode.c+1;
		node[3].m=tNode.m+1;
		node[3].c=tNode.c;
		node[4].m=tNode.m;
		node[4].c=tNode.c+1;
	}
	for(int i=0;i<5;i++)
		if(IsLegal(node[i])&&!IsClosed(node[i]))
			//open.push_front(node[i]);//���к���ȳ�������������������õ�һ����С������
			open.push_back(node[i]);//���к�����������������������õ���С������״̬�ռ�ͼ
}
 int main()
{
	MCNode InitNode,unode;
	InitNode.m=3;
	InitNode.c=3;
	InitNode.b=1;
	open.push_back(InitNode);//����ʼ״̬�ռ���뵽����
	while(!open.empty())
	{
		unode=open.front();
		open.pop_front();
		if(IsGoal(unode))
		{
			closed.push_back(unode);
			for(int i=0;i!=closed.size();i++)
				cout<<closed[i].m<<","<<closed[i].c<<","<<closed[i].b<<endl;
			break;
		}
		if(!IsClosed(unode))
		{
			closed.push_back(unode);
			ExpandNode(unode,unode.b,open);
		}
	}
	return 0;
}
