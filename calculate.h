#ifndef CALCULATE_H
#define CALCULATE_H
using namespace std;
#include <iostream>
#include <math.h>
//向量计算的函数
typedef double ElemType;

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}SqList,*pList;//顺序表

void InitList(SqList &L, int n)//顺序表的初始化
{
    L.elem=(ElemType*)malloc(n*sizeof(ElemType));
    L.length=n;
    L.listsize=n;
}
void add (SqList &L1,SqList &L2,SqList &L)//计算向量的和，保存到L中
{
    //InitList(L,L1.length);
    for(int i=0;i<L1.length;i++)
    {
        L.elem[i]=L1.elem[i]+L2.elem[i];
    }
}
void subtract (SqList &L1,SqList &L2,SqList &L)//计算向量的差，保存到L中
{
    //InitList(L,L1.length);
    for(int i=0;i<L1.length;i++)
    {
        L.elem[i]=L1.elem[i]-L2.elem[i];
    }
}
double dotProduct(SqList &L1,SqList &L2)//内积
{
    double inner=0;
    for(int i=0;i<L1.length;i++)
    {
        inner+=L1.elem[i]*L2.elem[i];
    }
    return inner;
}
double vLength(SqList &L)//向量模长
{
    double result=0;
    for (int i=0;i<L.length;i++)
    {
        result+=L.elem[i]*L.elem[i];
    }
    return sqrt(result);
}
double angleCos(SqList &L1,SqList &L2)//夹角余弦
{
    double result;
    if(vLength(L1)*vLength(L2)!=0.0)
         result=dotProduct(L1,L2)/(vLength(L1)*vLength(L2));
    else result=0;
    return result;
}
void print(SqList &L)//打印向量
{
    cout<<"(";
    for(int i=0;i<L.length-1;i++)
    {
        cout<<L.elem[i]<<", ";
    }
    cout<<L.elem[L.length-1];
    cout<<")"<<endl;
}



#endif // CALCULATE_H
