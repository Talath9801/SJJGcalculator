#ifndef EXPRESSION_H
#define EXPRESSION_H


#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;


#define OPERATOR 1
#define NUMBER 2
#define VARIABLE 3
//标识符-操作符，操作数，变量

#define STACK_INIT_SIZE 100
#define  STACKINCREMENT 10

typedef union
{
    double number;//操作数
    int optr;//操作符--ASCII码可以用int表示char
}ob;
typedef struct
{
    ob object;//操作数或操作符
    int type;//标识符--是操作数还是操作符
}SElemType;

typedef struct{
        SElemType *base;
        SElemType *top;
        int  stacksize;
}sqStack;//栈的定义


void InitStack(sqStack  *s)//初始化为一个空栈
{
    s->base=(SElemType*)malloc(STACK_INIT_SIZE* sizeof(SElemType));
    if(!s->base)
    {
        exit(1);//内存分配失败
    }
    s->top=s->base;//空栈
    s->stacksize=STACK_INIT_SIZE;
}
void Push(sqStack *s,SElemType e)//入栈
{
    if(s->top-s->base>=s->stacksize) //栈满追加储存空间
    {
        s->base=(SElemType*)realloc(s->base,(s->stacksize+STACKINCREMENT)*sizeof(SElemType));
       if(!s->base)
       {
        exit(1);//内存分配失败
        }
        s->top=s->base+s->stacksize;
        s->stacksize+=STACKINCREMENT;
    }
    if(e.type==NUMBER)
    {
        s->top->object.number=e.object.number;
        s->top->type=e.type;
    }
    else if(e.type==OPERATOR)
    {
        s->top->object.optr=e.object.optr;
        s->top->type=e.type;
    }
    else if(e.type==VARIABLE)
    {
        s->top->object.number=0;//暂时以0代替，之后在输入时，通过检查type的值来找到变量
        s->top->type=e.type;
    }
    else
    {
        cout<<"input error"<<endl;
        exit(-1);
    }
    //*(s->top)=e;
     s->top++;

}
void  Pop(sqStack *s,SElemType *e)//出栈
{
        if(s->top==s->base)
             exit(1);//空栈，不能出栈
        s->top--;
        if(s->top->type==NUMBER)
        {
            e->object.number=s->top->object.number;
            e->type=s->top->type;
        }
        else if(s->top->type==OPERATOR)
        {
            e->object.optr=s->top->object.optr;
            e->type=s->top->type;
        }
        else if(s->top->type==VARIABLE)
        {
            e->object.number=s->top->object.number;
            e->type=s->top->type;
        }
        else
            cout<<"error"<<endl;
        //用e记录退栈元素

}
SElemType GetTop(sqStack *s)
{
    if(s->top==s->base)
    {
        exit(-1);//空栈，没有栈顶元素
    }
        return  *(s->top-1);//返回栈顶结点

}
int ifNumber(char e)//判断输入的字符是否为数字
{
    if(e>='0'&&e<='9')
        return 1;
    else
        return 0;
}
int ifOperator(char e)//判断读入字符是否为运算符
{
    if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#')
        return 1;//是
    else
        return 0; //不是
}

char optrCmp(char op1,char op2)//比较运算符的优先级
{
    char result;
    if(op1=='+'||op1=='-')
    {
        if(op2=='+'||op2=='-'||op2==')'||op2=='#')
            result='>';
        else if(op2=='*'||op2=='/'||op2=='(')
            result='<';
    }
    else if(op1=='*'||op1=='/')
    {
        if(op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2==')'||op2=='#')
           result='>';
        else if(op2=='(')
           result='<';
    }
    else if(op1=='(')
    {
        if(op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2=='(')
           result='<';
        else if(op2==')')
           result='=';
    }
    else if(op1==')')
    {
        if(op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2==')'||op2=='#')
           result='>';
    }
    else if(op1=='#')
    {
        if(op2=='+'||op2=='-'||op2=='*'||op2=='/'||op2=='(')
           result='<';
        else if(op2=='#')
           result='=';
    }
    return result;
}
SElemType Operate(SElemType a,SElemType theta,SElemType b)//运算
{
    SElemType result;
    result.type=NUMBER;
    if(theta.object.optr=='+')
    {
        result.object.number=a.object.number+b.object.number;
    }
    else if(theta.object.optr=='-')
    {
        result.object.number=a.object.number-b.object.number;
    }
    else if(theta.object.optr=='*')
    {
        result.object.number=a.object.number*b.object.number;
    }
    else if(theta.object.optr=='/')
    {
        result.object.number=a.object.number/b.object.number;
    }
    return result;

}
void EvaluateExpression()
{
    sqStack OPND,OPTR;
    //char ch,a,b,theta,x;//ch时拿到的字符，ab是运算数，x是弹出的栈顶元素
    int ch;//当前拿到的字符
    SElemType a,b,theta;//进行计算的操作数和运算符
    SElemType mytop;//弹出栈顶元素

    InitStack(&OPND);//操作数和运算结果
    InitStack(&OPTR);//运算符

    int preType=-1;//记录上一个读入的字符的类型（数，变量，运算符）初始化为-1，什么也不是
    int curType=-1;//记录当前读入的字符的类型

    SElemType mybase;//给一个压栈底的#作为结束标识符
    mybase.type=OPERATOR;
    mybase.object.optr='#';
    Push(&OPTR,mybase);//先给一个首尾标识符压栈底
    ch=getchar();//拿到一个字符


    while(ch!='#'||GetTop(&OPTR).object.optr!='#')
    {
        if(!ifOperator(ch))//如果不是操作符
        {
            SElemType temp;
            temp.type=NUMBER;
            temp.object.number=ch-'0';//构造一个结点，用ASC码表计算出对应的十进制数值
            curType=NUMBER;

            Push(&OPND,temp);//进入操作数的栈
            ch=getchar();//去拿下一个字符
            preType=curType;
        }
        else//是操作符
        {
            SElemType temp;
            temp.type=OPERATOR;
            temp.object.optr=ch;//构造一个结点
            curType=OPERATOR;
            switch(optrCmp(GetTop(&OPTR).object.optr,ch))//和栈顶的操作符比较
            {
                case '<':
                    Push(&OPTR,temp);
                    ch=getchar();
                    preType=curType;//更新pre
                    break;
                case '>':
                    Pop(&OPTR,&theta);
                    Pop(&OPND,&b);
                    Pop(&OPND,&a);
                    Push(&OPND,Operate(a,theta,b));
                    break;
                case '=':
                    Pop(&OPTR,&mytop);//弹出栈顶操作符
                    ch=getchar();
                    preType=curType;//更新pre
                    break;
            }
        }
    }
    cout<<GetTop(&OPND).object.number;
}
#endif // EXPRESSION_H
