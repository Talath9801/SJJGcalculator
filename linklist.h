#ifndef LINKLIST_H
#define LINKLIST_H
//用链表实现的多项式运算
using namespace std;
#include <iostream>
#include <math.h>
typedef double ElemType;

typedef struct Node{
    double coef;//系数
    int expn;//指数
    struct Node *next;
}Node;
typedef struct{
    Node*head;
    Node*rear;
    int length;
}poly;
void initPol(poly &L)//构造空链表
{
    L.head=(Node*)malloc(sizeof(Node));
    L.head->next=NULL;
    L.rear=L.head;
    L.length=0;
}

void createPol(poly &L, int n)//已经有一个头结点，多项式的初始化，输入n项的系数和指数
{
    cout<<"input the ceof of polynomial 1, for example, 1 1 2 3 stands for x+2x^3"<<endl;
    for(int i=0;i<n;i++)
    {
        Node *p;
        p=(Node*)malloc(sizeof(Node));
        cin>>p->coef;
        cin>>p->expn;
        p->next=L.rear->next;
        L.rear->next=p;
        L.rear=p;
        L.length++;
    }
}
void clearPol(poly &L)//清空链表，剩下一个头结点
{
    while(L.head->next)//不空
    {
        Node*q;
        q=L.head->next;
        L.head->next=q->next;
        if(q->next==NULL)//如果只剩下一个结点
        {
            L.rear=L.head;
        }
        free(q);
    }

}
void destroyPol(poly &L)//销毁链表
{
    clearPol(L);//先清空只剩一个头结点
    free(L.head);
    L.rear=NULL;
    L.head=NULL;
}
void printPol(poly &L)
{
    Node *p;//游走指针
    bool flag=1;//默认为0多项式，如果遇到非零项则改为不是0多项式，最后如果真的是0多项式特殊处理
    p=L.head->next;//有头节点，使得p先指向第一个元素，往后看
    while(p)//p不为空
    {
        if(p->expn==0)
        {
            if(p->coef!=0)
            {
                cout<<p->coef;
                flag=0;
            }
        }
        else
        {
            if(p->coef<0)
            {
                cout<<"  "<<p->coef<<"x^"<<p->expn;
                flag=0;
            }
            if(p->coef>0)
            {
                cout<<"  +"<<p->coef<<"x^"<<p->expn;
                flag=0;
            }
        }

        p=p->next;
    }
    if(flag==1)//真的是0多项式
        cout<<0;
    cout<<endl;
}
void addinto(poly &L1,poly &L2)//将L1,L2相加，直接在L1上修改，并释放掉L2
{
    Node* p1,*pre1;
    Node* p2,*pre2;//游走指针
    p1=L1.head->next;
    p2=L2.head->next;//指向当前结点
    pre1=L1.head;
    pre2=L2.head;//指向对应的前驱
    while(p1&&p2)
    {
        //当前结点均非空
        int e1=p1->expn;//
        int e2=p2->expn;//指数值
        if(e1<e2)//p1的指数小
        {
            pre1=pre1->next;
            p1=p1->next;
        }
        else if(e1==e2)
        {
            double sum=p1->coef+p2->coef;//系数和
            if(sum!=0)
            {
                p1->coef=sum;//修改系数
                p1=p1->next;
                pre1=pre1->next;

                pre2->next=p2->next;
                free(p2);
                p2=pre2->next;//释放L2中已经走过的结点
            }
            else
            {
                pre1->next=p1->next;
                free(p1);
                p1=pre1->next;
                pre2->next=p2->next;
                free(p2);
                p2=pre2->next;//释放相抵消的结点
            }
        }
        else//e1>e2
        {
            Node *q;
            q=(Node*)malloc(sizeof (Node));
            q->coef=p2->coef;
            q->expn=p2->expn;//生成新结点
            q->next=pre1->next;
            pre1->next=q;
            pre1=pre1->next;//插入L1
            pre2->next=p2->next;
            free(p2);
            p2=pre2->next;
        }
    }
    //如果L1走完了L2没有走完
    if(L2.head->next!=NULL)//如果L2非空
    {
        //先把L1的尾指针移到尾部
        while(L1.rear->next)
            L1.rear=L1.rear->next;
        L1.rear->next=L2.head->next;//连接
        L1.rear=L2.rear;
        free(L2.head);
    }
}
void addpol(poly &L1,poly &L2,poly &L)//将L1和L2相加，结果保存到L中（不直接改动L1，L2
{
    clearPol(L);//由于L采用头插，要保证L清空
    if(L1.head==L1.rear)//L1为空
    {
        L.head=L2.head;
        L.rear=L2.rear;
        L.length=L2.length;
    }

    if(L2.head==L2.rear)//L2为空
    {
        L.head=L1.head;
        L.rear=L1.rear;
        L.length=L1.length;
    }
    if(L1.head!=L1.rear&&L2.head!=L2.rear)//两个表都不为空
    {
        Node *pp1,*pp2,*pp;//游走指针
        pp1=L1.head->next;
        pp2=L2.head->next;
        pp=L.head;//游走指针的初始化
        while(pp1&&pp2)//L1,L2都没有走完
        {
            if(pp1->expn<pp2->expn)//L1当前项的指数比L2小，将L1的结点放入L
            {
                Node *p;
                p=(Node*)malloc(sizeof(Node));
                p->coef=pp1->coef;
                p->expn=pp1->expn;
                p->next=L.rear->next;
                L.rear->next=p;
                L.rear=p;
                L.length++;//将L1的结点放入L
                pp1=pp1->next;
            }
            else if(pp1->expn>pp2->expn)//L2当前项的指数比L1小，将L2的结点放入L
            {
                Node *p;
                p=(Node*)malloc(sizeof(Node));
                p->coef=pp2->coef;
                p->expn=pp2->expn;
                p->next=L.rear->next;
                L.rear->next=p;
                L.rear=p;
                L.length++;//将L2的结点放入L
                pp2=pp2->next;
            }
            else if(pp1->expn==pp2->expn)
            {
                double temp;
                temp=pp1->coef+pp2->coef;
                if(temp!=0)//系数和不为零时，才将加总之后的项放入L中
                {
                    Node *p;
                    p=(Node*)malloc(sizeof(Node));
                    p->coef=temp;
                    p->expn=pp2->expn;
                    p->next=L.rear->next;
                    L.rear->next=p;
                    L.rear=p;
                    L.length++;
                }
                pp1=pp1->next;
                pp2=pp2->next;
            }
        }
        if(pp1==NULL&&pp2)//L1走完了，L2没走完
        {
            L.rear->next=pp2;
            L.rear=L2.rear;
            while(pp2)
            {
                pp2=pp2->next;
                L.length++;
            }
        }
        if(pp2==NULL&&pp1)//L2走完了，L1没走完
        {
            L.rear->next=pp1;
            L.rear=L1.rear;
            while(pp1)
            {
                pp1=pp1->next;
                L.length++;
            }
        }
    }
}


void substractpol(poly &L1,poly &L2,poly &L)//将L1和L2相减，结果保存到L中（不直接改动L1，L2
{
    //思路：转化为L1和-L2的和
    clearPol(L);//保证L清空
    poly Ltemp;
    initPol(Ltemp);
    Node* p;
    p=L2.head->next;
    Ltemp.rear=Ltemp.head;
    while(p)
    {
        //将P指向的数据经过系数取相反数，赋给一个新开的结点，然后插入Ltemp中
        Node* q;
        q=(Node*)malloc(sizeof(Node));
        q->coef=-p->coef;
        q->expn=p->expn;
        //将q插在temp的后面
        q->next=Ltemp.rear->next;
        Ltemp.rear->next=q;
        Ltemp.rear=q;
        p=p->next;
    }
    Ltemp.length=L2.length;//Ltemp即为L2的相反数
    addpol(L1,Ltemp,L);//计算L1+(-L2)，保存到L中
}

void multiplyPol(poly &L1,poly &L2, poly &L)//将L1和L2相乘，结果保存到L中
{
    if(L1.head==L1.rear||L2.head==L2.rear)//empty
    {
        cout<<"0"<<endl;
    }
    clearPol(L);//保证L清空
//    poly ltemp;//临时储存L1的每一个结点与L2的乘积
//    initPol(ltemp);//初始化为有头结点的空链表

    Node *pp1;//遍历L1的指针
    Node *pp2;//遍历L2的指针
    pp1=L1.head->next;
    while(pp1)//pp1非空
    {
        //该结点与L2相乘，存入ltemp
        poly ltemp;//临时储存L1的每一个结点与L2的乘积
        initPol(ltemp);

        pp2=L2.head->next;//pp2从头遍历
        while(pp2)
        {
            //将pp1和pp2所指向的结点进行乘法之后，存入一个新生成的结点，插入到ltemp中
            Node*s;
            s=(Node*)malloc(sizeof(Node));
            s->coef=pp1->coef*pp2->coef;
            s->expn=pp1->expn+pp2->expn;
            s->next=ltemp.rear->next;
            ltemp.rear->next=s;
            ltemp.rear=s;
            ltemp.length++;//尾插
            pp2=pp2->next;
        }
        //这样就在生成了一个ltemp，下将ltemp加到L中

        addinto(L,ltemp);//修改L，释放临时生成的ltemp
        pp1=pp1->next;
    }
}
void deriv(poly &L)//求一阶导
{
    Node *p,*pre;
    pre=L.head;
    p=L.head->next;

    while(p)
    {
        //遍历链表，依次求导，每次求完一项立刻检查是否已经为0，为0则删除节点，如果求导求到0，最后输出0

        p->coef=p->coef*p->expn;
        p->expn=p->expn-1;
        if(p->coef==0)//系数为0，删除结点
        {
            pre->next=p->next;
            free(p);
            p=pre->next;
            //若为尾结点，要修改尾指针
            if(L.head->next==NULL)
                L.rear=L.head;
        }
        else
        {
            p=p->next;
            pre=pre->next;
        }
    }
}

#endif // LINKLIST_H
