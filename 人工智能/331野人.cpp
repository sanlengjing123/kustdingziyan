#include <iostream>
#include <vector>
#include <list>
using namespace std;
 
typedef struct
{
	int m;//表示传教士
	int c;// 表示野人
	int b;//船状态,1为此岸，0为不在起始子岸 
}MCNode;
 
list<MCNode> open;//相当于队列
vector<MCNode> closed;//closed表
 
//判断是否是目标结点
bool IsGoal(MCNode tNode)
{
	if(tNode.m==0&&tNode.c==0&&tNode.b==0)
		return true;
	else
		return false;
}
//判断是否是合法状态
bool IsLegal(MCNode tNode)
{
	if(tNode.m>=0&&tNode.m<=3&&tNode.c>=0&&tNode.c<=3)
	{
		if((tNode.m==tNode.c)||(tNode.m==3)||(tNode.m==0))//事实上如果出现【2，1，1】这种情况对岸已经是不合法的了，合法只有这三种情况 
			return true;
		else
			return false;
	}
	else
		return false;
}
//重载运算符，判断两结构体是否相等
bool operator==(MCNode m1,MCNode m2)
{
	if(m1.m==m2.m&&m1.c==m2.c&&m1.b==m2.b)
		return true;
	else
		return false;
}
//判断是否已在closed表中
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
	MCNode node[5];//应用5条规则集生成新结点
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
			//open.push_front(node[i]);//队列后进先出，深度优先搜索，最后得到一条最小解序列
			open.push_back(node[i]);//队列后进后出，广度优先搜索，最后得到最小解序列状态空间图
}
 int main()
{
	MCNode InitNode,unode;
	InitNode.m=3;
	InitNode.c=3;
	InitNode.b=1;
	open.push_back(InitNode);//将初始状态空间加入到队列
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
