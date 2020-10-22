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
int ifLetterLine(char e)//判断是否为字母或下划线
{
    if(e>='a'&&e<='z')
        return 1;
    else if(e>='A'&&e<='Z')
        return 1;
    else if(e=='_')
        return 1;
    else
        return 0;
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

    bool ifFrac=0;//标识符，是否进入小数部分，遇到小数点改为1，遇到变量首位或操作符改为0
    int countFrac=0;//记录小数位数

    while(ch!='#'||GetTop(&OPTR).object.optr!='#')
    {
        if(ifNumber(ch))//如果是数字
        {
            if(preType==-1||preType==OPERATOR)//是数字的第一位数
            {
                SElemType temp;
                temp.type=NUMBER;
                temp.object.number=ch-'0';//构造一个结点，用ASC码表计算出对应的十进制数值
                curType=NUMBER;

                Push(&OPND,temp);//进入操作数的栈
                ch=getchar();//去拿下一个字符
                preType=curType;
            }
            else if(preType==NUMBER)//是多位数中，非第一位数字
            {
                if(ifFrac==0)//还在整数部分
                {
                    (OPND.top-1)->object.number=(OPND.top-1)->object.number*10+ch-'0';
                    ch=getchar();//去拿下一个字符
                    preType=curType;
                }
                else//开始小数部分
                {
                    countFrac++;//在录入数码的时候除以10的次数
                    double myfrac=ch-'0';//当前输入的数码转化为数字
                    for(int i=0;i<countFrac;i++)
                    {
                        myfrac=myfrac/10;
                    }
                    (OPND.top-1)->object.number=(OPND.top-1)->object.number+myfrac;
                    ch=getchar();//去拿下一个字符
                    preType=curType;
                }

            }
            else if(preType==VARIABLE)//是变量中的数字
            {
                //不入栈，但是改变下一个数码的算法
                curType=NUMBER;

                ch=getchar();
                preType=curType;
            }
        }//如果是数字
        else if(ch=='.')//小数点，仍在数字之内
        {
            ifFrac=1;//表示小数部分开始
            ch=getchar();
        }
        else if(ifOperator(ch)==1)//是操作符
        {
            ifFrac=0;
            countFrac=0;
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
        else if(ifLetterLine(ch)==1)//变量开头或内部
        {
            ifFrac=0;
            countFrac=0;
        }
        else
        {
            ch=getchar();//处理换行符
        }
    }
    cout<<GetTop(&OPND).object.number;
}
void calcuVal(char exp[],double value)
{
    int pos=0;//取字符
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
    ch=exp[pos];//拿到一个字符
    pos++;

    bool ifFrac=0;//标识符，是否进入小数部分，遇到小数点改为1，遇到变量首位或操作符改为0
    int countFrac=0;//记录小数位数
    bool isVariable=0;//是否是变量中的字符

    while(ch!='#'||GetTop(&OPTR).object.optr!='#')
    {
        if(ifNumber(ch))//如果是数字
        {
            if(preType==-1||preType==OPERATOR)//是数字的第一位数
            {
                SElemType temp;
                temp.type=NUMBER;
                temp.object.number=ch-'0';//构造一个结点，用ASC码表计算出对应的十进制数值
                curType=NUMBER;

                Push(&OPND,temp);//进入操作数的栈
                ch=exp[pos];//拿到一个字符
                pos++;
                preType=curType;
            }
            else if(preType==NUMBER&&isVariable==0)//是多位数中，非第一位数字
            {
                if(ifFrac==0)//还在整数部分
                {
                    (OPND.top-1)->object.number=(OPND.top-1)->object.number*10+ch-'0';
                    ch=exp[pos];//拿到一个字符
                    pos++;
                    preType=curType;
                }
                else//开始小数部分
                {
                    countFrac++;//在录入数码的时候除以10的次数
                    double myfrac=ch-'0';//当前输入的数码转化为数字
                    for(int i=0;i<countFrac;i++)
                    {
                        myfrac=myfrac/10;
                    }
                    (OPND.top-1)->object.number=(OPND.top-1)->object.number+myfrac;
                    ch=exp[pos];//拿到一个字符
                    pos++;
                    preType=curType;
                }

            }
            else if(preType==VARIABLE||isVariable==1)//是变量中的数字
            {
                //不入栈，但是改变下一个数码的算法
                //curType=NUMBER;

                ch=exp[pos];//拿到一个字符
                pos++;
                //preType=curType;
            }
        }//如果是数字
        else if(ch=='.')//小数点，仍在数字之内
        {
            ifFrac=1;//表示小数部分开始
            ch=exp[pos];//拿到一个字符
            pos++;
        }
        else if(ifOperator(ch)==1)//是操作符
        {
            ifFrac=0;
            isVariable=0;//结束变量字符串
            countFrac=0;
            SElemType temp;
            temp.type=OPERATOR;
            temp.object.optr=ch;//构造一个结点
            curType=OPERATOR;
            switch(optrCmp(GetTop(&OPTR).object.optr,ch))//和栈顶的操作符比较
            {
                case '<':
                    Push(&OPTR,temp);
                    ch=exp[pos];//拿到一个字符
                    pos++;
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
                    ch=exp[pos];//拿到一个字符
                    pos++;
                    preType=curType;//更新pre
                    break;
            }
        }
        else if(ifLetterLine(ch)==1)//变量开头或内部
        {
            ifFrac=0;
            countFrac=0;
            isVariable=1;

            curType=VARIABLE;

            if(preType==-1||preType==OPERATOR)//是变量标识符的第一个字符
            {
                SElemType temp;
                temp.type=NUMBER;
                temp.object.number=value;//构造一个结点，数值用输入的变量值代替
                curType=NUMBER;

                Push(&OPND,temp);//进入操作数的栈
                ch=exp[pos];//拿到一个字符
                pos++;
                preType=curType;
            }
            else  //是变量标识符的中间字符
            {
                ch=exp[pos];//拿到一个字符
                pos++;
            }

            preType=curType;
        }
//        else
//        {
//            ch=exp[pos];
//            pos++;//处理换行符
//        }
    }
    cout<<GetTop(&OPND).object.number<<endl;
}
#endif // EXPRESSION_H
