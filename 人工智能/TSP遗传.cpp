#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define cities 10  //���еĸ���
#define MAXX 100//��������
#define pc 0.8 //�������
#define pm 0.05 //�������
#define num 10//��Ⱥ�Ĵ�С
int bestsolution;//����Ⱦɫ��
int distance[cities][cities];//����֮��ľ���
struct group  //Ⱦɫ��Ľṹ
{
	int city[cities];//���е�˳��
	int adapt;//��Ӧ��
	double p;//����Ⱥ�е��Ҵ����
}group[num];
//�������cities������֮����໥����
void init()
{
	int i,j;
	memset(distance,0,sizeof(distance));
	srand((unsigned)time(NULL));
    for(i=0;i<cities;i++)
	{
	    for(j=i+1;j<cities;j++)
		{
		   distance[i][j]=rand()%100;
		   distance[j][i]=distance[i][j];
		}
	}
	//��ӡ�������
	printf("���еľ����������\n");
	for(i=0;i<cities;i++)
	{
		for(j=0;j<cities;j++)
		printf("%4d",distance[i][j]);
		printf("\n");
	}
}
//�����������Ⱥ
void groupproduce()
{
	int i,j,t,k,flag;
	for(i=0;i<num;i++)  //��ʼ��
	for(j=0;j<cities;j++)
	group[i].city[j]=-1;
	srand((unsigned)time(NULL));
    for(i=0;i<num;i++)
	{
		//����10������ͬ������
		for(j=0;j<cities;)
		{
			t=rand()%cities;
			flag=1;
			for(k=0;k<j;k++)
			{
				if(group[i].city[k]==t)
				{
					flag=0;
					break;
				}
			}
			if(flag)
			{
				group[i].city[j]=t;
				j++;
			}
		}
	}
	//��ӡ��Ⱥ����
	printf("��ʼ����Ⱥ\n");
	for(i=0;i<num;i++)
	{
		for(j=0;j<cities;j++)
		printf("%4d",group[i].city[j]);
		printf("\n");
	}
}
//���ۺ���,�ҳ�����Ⱦɫ��
void pingjia()
{
	int i,j;
	int n1,n2;
	int sumdistance,biggestsum=0;
	double biggestp=0;
	for(i=0;i<num;i++)
	{
		sumdistance=0;
		for(j=1;j<cities;j++)
		{
			n1=group[i].city[j-1];
			n2=group[i].city[j];
			sumdistance+=distance[n1][n2];
		}
		group[i].adapt=sumdistance; //ÿ��Ⱦɫ���·���ܺ�
		biggestsum+=sumdistance; //��Ⱥ����·��
	}
	//����Ⱦɫ����Ҵ�����,·��Խ���������Խ��
	for(i=0;i<num;i++)
	{
		group[i].p=1-(double)group[i].adapt/(double)biggestsum; 
		biggestp+=group[i].p;
	}
	for(i=0;i<num;i++)
	group[i].p=group[i].p/biggestp;  //����Ⱥ�е��Ҵ����,�ܺ�Ϊ1
	//�����·�� 
	bestsolution=0;
	for(i=0;i<num;i++)
	if(group[i].p>group[bestsolution].p)
	bestsolution=i;
	//��ӡ��Ӧ��
	for(i=0;i<num;i++)
	printf("Ⱦɫ��%d��·��֮����������ʷֱ�Ϊ%4d  %.4f\n",i,group[i].adapt,group[i].p);
	printf("��ǰ��Ⱥ������Ⱦɫ����%d��Ⱦɫ��\n",bestsolution);
}
//ѡ��
void xuanze()
{
	int i,j,temp;
	double gradient[num];//�ݶȸ���
	double xuanze[num];//ѡ��Ⱦɫ����������
	int xuan[num];//ѡ���˵�Ⱦɫ��
	//��ʼ���ݶȸ���
	for(i=0;i<num;i++)
	{
		gradient[i]=0.0;
		xuanze[i]=0.0;
	}
	gradient[0]=group[0].p;
	for(i=1;i<num;i++)
	gradient[i]=gradient[i-1]+group[i].p;
	srand((unsigned)time(NULL));
	//�������Ⱦɫ��Ĵ�����
	for(i=0;i<num;i++)
	{
		xuanze[i]=(rand()%100);
		xuanze[i]/=100;
	}
	//ѡ���������Ⱦɫ��
	for(i=0;i<num;i++)
	{
		for(j=0;j<num;j++)
		{
			if(xuanze[i]<gradient[j])
			{
				xuan[i]=j; //��i��λ�ô�ŵ�j��Ⱦɫ��
				break;
			}
		}
	}
	//������Ⱥ
	for(i=0;i<num;i++)
	{
		grouptemp[i].adapt=group[i].adapt;
		grouptemp[i].p=group[i].p;
		for(j=0;j<cities;j++)
		grouptemp[i].city[j]=group[i].city[j];
	}
	//���ݸ���
	for(i=0;i<num;i++)
	{
		temp=xuan[i];
		group[i].adapt=grouptemp[temp].adapt;
		group[i].p=grouptemp[temp].p;
		for(j=0;j<cities;j++)
		group[i].city[j]=grouptemp[temp].city[j];
	}
	//���ڲ���
	/*
	printf("<------------------------------->\n");
	for(i=0;i<num;i++)
	{
		for(j=0;j<cities;j++)
		printf("%4d",group[i].city[j]);
		printf("\n");
		printf("Ⱦɫ��%d��·��֮����������ʷֱ�Ϊ%4d  %.4f\n",i,group[i].adapt,group[i].p);
	}
	*/
}
//����,��ÿ��Ⱦɫ������������,���㽻���ʵ�Ⱦɫ����н���
//����,��ÿ��Ⱦɫ������������,���㽻���ʵ�Ⱦɫ����н���
void  jiaopei()
{
	int i,j,k,kk;
	int t;//���뽻���Ⱦɫ��ĸ���
	int point1,point2,temp;//����ϵ�
	int pointnum;
	int temp1,temp2;
	int map1[cities],map2[cities];
	double jiaopeip[num];//Ⱦɫ��Ľ������
	int jiaopeiflag[num];//Ⱦɫ��Ŀɽ������
	int kkk,flag=0;
	//��ʼ��
	for(i=0;i<num;i++)
	{
		jiaopeiflag[i]=0;
	}
	//��������������
	srand((unsigned)time(NULL));
	for(i=0;i<num;i++)
	{
		jiaopeip[i]=(rand()%100);
		jiaopeip[i]/=100;
	}
	//ȷ�����Խ����Ⱦɫ��
	t=0;
	for(i=0;i<num;i++)
	{
		if(jiaopeip[i]<pc)
		{
			jiaopeiflag[i]=1;
			t++;
		}
	}
	t=t/2*2;//t����Ϊż��
	//����t/2��0-9����ϵ�
    srand((unsigned)time(NULL));
	temp1=0;
	//temp1��Ⱦɫ���temp2Ⱦɫ�彻��
	for(i=0;i<t/2;i++)
	{
		point1=rand()%cities;//�����1
		point2=rand()%cities;//�����2
		//ѡ��һ����Ҫ�����Ⱦɫ��1
		for(j=temp1;j<num;j++)
		{
			if(jiaopeiflag[j]==1)
			{
				temp1=j;
				break;
			}
		}
		//ѡ����һ����Ҫ�����Ⱦɫ��2��1����
		for(j=temp1+1;j<num;j++)
		{
			if(jiaopeiflag[j]==1)
			{
				temp2=j;
				break;
			}
		}
		//���л�����
		if(point1>point2) //��֤point1<=point2
		{
			temp=point1;
			point1=point2;
			point2=temp;
		}
		//��ʼ��
        memset(map1,-1,sizeof(map1));
		memset(map2,-1,sizeof(map2));
		//�ϵ�֮��Ļ������ӳ��
		for(k=point1;k<=point2;k++)
		{
			map1[group[temp1].city[k]]=group[temp2].city[k];
			map2[group[temp2].city[k]]=group[temp1].city[k];
		}
		//�ϵ����ߵĻ��򻥻�
		for(k=0;k<point1;k++)
		{
			temp=group[temp1].city[k];
			group[temp1].city[k]=group[temp2].city[k];
			group[temp2].city[k]=temp;
		}
		for(k=point2+1;k<cities;k++)
		{
			temp=group[temp1].city[k];
			group[temp1].city[k]=group[temp2].city[k];
			group[temp2].city[k]=temp;
		}
		printf("�����ͻ---------------------\n");
		//����Ⱦɫ��1�����ĳ�ͻ����
		for(k=0;k<point1;k++)
		{
			for(kk=point1;kk<=point2;kk++)
			{
				if(group[temp1].city[k]==group[temp1].city[kk])
				{
					group[temp1].city[k]=map1[group[temp1].city[k]];
					//find
					for(kkk=point1;kkk<=point2;kkk++)
					{
						if(group[temp1].city[k]==group[temp1].city[kkk])
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						kk=point1-1;
						flag=0;
					}
					else
					{
						flag=0;
						break;
					}
				}
			}
			
		}
		for(k=point2+1;k<cities;k++)
		{
			for(kk=point1;kk<=point2;kk++)
			{
				if(group[temp1].city[k]==group[temp1].city[kk])
				{
					group[temp1].city[k]=map1[group[temp1].city[k]];
					//find
					for(kkk=point1;kkk<=point2;kkk++)
					{
						if(group[temp1].city[k]==group[temp1].city[kkk])
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						kk=point1-1;
						flag=0;
					}
					else
					{
						flag=0;
						break;
					}
				}
			}
		}
		//����2Ⱦɫ������ĳ�ͻ����
		for(k=0;k<point1;k++)
		{
			for(kk=point1;kk<=point2;kk++)
			{
				if(group[temp2].city[k]==group[temp2].city[kk])
				{
					group[temp2].city[k]=map2[group[temp2].city[k]];
					//find
					for(kkk=point1;kkk<=point2;kkk++)
					{
						if(group[temp2].city[k]==group[temp2].city[kkk])
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						kk=point1-1;
						flag=0;
					}
					else
					{
						flag=0;
						break;
					}
				}
			}
		}
		for(k=point2+1;k<cities;k++)
		{
			for(kk=point1;kk<=point2;kk++)
			{
				if(group[temp2].city[k]==group[temp2].city[kk])
				{
					group[temp2].city[k]=map2[group[temp2].city[k]];
					//find
					for(kkk=point1;kkk<=point2;kkk++)
					{
						if(group[temp2].city[k]==group[temp2].city[kkk])
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						kk=point1-1;
						flag=0;
					}
					else
					{
						flag=0;
						break;
					}
				}
			}
		}
        temp1=temp2+1;
	}
}
//����
void bianyi()
{
	int i,j;
	int t;
	int temp1,temp2,point;
	double bianyip[num]; //Ⱦɫ��ı������
	int bianyiflag[num];//Ⱦɫ��ı������
	for(i=0;i<num;i++)//��ʼ��
	bianyiflag[i]=0;
	//��������������
	srand((unsigned)time(NULL));
	for(i=0;i<num;i++)
	{
		bianyip[i]=(rand()%100);
		bianyip[i]/=100;
	}
	//ȷ�����Ա����Ⱦɫ��
	t=0;
	for(i=0;i<num;i++)
	{
		if(bianyip[i]<pm)
		{
			bianyiflag[i]=1;
			t++;
		}
	}
	//�������,������Ⱦɫ��������ڵ�
	srand((unsigned)time(NULL));
	for(i=0;i<num;i++)
	{
		if(bianyiflag[i]==1)
		{
	        temp1=rand()%10;
			temp2=rand()%10;
			point=group[i].city[temp1];
            group[i].city[temp1]=group[i].city[temp2];
			group[i].city[temp2]=point;
		}
	}
}
int main()
{
	int i,j,t;
    init();
	groupproduce();
	//��ʼ��Ⱥ����
	pingjia();
	t=0;
    while(t++<MAXX)
	{
	     xuanze();
		 jiaopei();
		 bianyi();
		 pingjia();
	}
	//������Ⱥ������
	printf("\n������յ���Ⱥ����\n");
	for(i=0;i<num;i++)
	{
		for(j=0;j<cities;j++)
		{
			printf("%4d",group[i].city[j]);
		}
		printf("  adapt:%4d, p:%.4f\n",group[i].adapt,group[i].p);
	}
	printf("���Ž�Ϊ%d��Ⱦɫ��\n",bestsolution);
	return 0;
}
