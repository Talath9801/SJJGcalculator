#ifndef SQLIST_H
#define SQLIST_H

//用顺序表实现的多项式运算
using namespace std;
#include <iostream>
#include <math.h>
typedef double ElemType;
#define MAXSIZE 1003


typedef struct
{
    ElemType *elem;
    int length;
}polSqList,*psqList;

//由于使用顺序表时，每一项的指数隐含在其系数的序号中，稀疏多项式采用链表进行计算
//故此处限制多项式次数为1000以内


void InitSqList(polSqList &L)//初始化
{
    L.elem=(ElemType*)malloc(MAXSIZE*sizeof(ElemType));
    L.length=0;
}
void addSq(polSqList &L1,polSqList &L2, polSqList &L)//多项式的和，结果保存到L中
{
    for(int i=0;i<max(L1.length,L2.length);i++)
    {
        L.elem[i]=L1.elem[i]+L2.elem[i];
    }
    for(int i=max(L1.length,L2.length);i<MAXSIZE;i++)
    {
        L.elem[i]=0;
    }
    L.length=max(L1.length,L2.length);
}
void subtractSq(polSqList &L1,polSqList &L2, polSqList &L)//多项式的差，结果保存到L中
{
    for(int i=0;i<max(L1.length,L2.length);i++)
    {
        L.elem[i]=L1.elem[i]-L2.elem[i];
    }
    for(int i=max(L1.length,L2.length);i<MAXSIZE;i++)
    {
        L.elem[i]=0;
    }
    L.length=max(L1.length,L2.length);
}

void printSq(polSqList &L)
{
    bool flag=1;//多项式是否为0，默认是0，碰到非零项，改为非零，如果最后发现真的是0则特殊处理
    for(int i=0;i<L.length;i++)
    {
        if(L.elem[i]!=0&&i==0)
        {
            cout<<L.elem[i];
            flag=0;
        }
        if(L.elem[i]<0&&i!=0)
        {
            cout<<"  "<<L.elem[i]<<"x^"<<i;
            flag=0;
        }
        if(L.elem[i]>0&&i!=0)
        {
            cout<<"  "<<"+"<<L.elem[i]<<"x^"<<i;
            flag=0;
        }
    }
    //如果多项式为0，特殊处理
    if(flag==1)
    {
        cout<<"0";
    }
    cout<<endl;
}

#endif // SQLIST_H
