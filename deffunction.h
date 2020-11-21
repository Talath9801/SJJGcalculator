#ifndef DEFFUNCTION_H
#define DEFFUNCTION_H

#include<expression.h>

typedef struct myFun
{
    char funName[10];//函数名称
    char funExpre[50];//函数内容
    myFun *next;
}myFun;

myFun* checkHistory(char string[],int pos)
//检查字符串从pos下标开始的字串是不是与历史函数名称中的某一个相同
//如果是某个历史函数，返回这个历史函数的结点指针，如果不存在，返回空指针
{

}

void dofunction(myFun *funcList)
{

    char myInput[50];
    char t;
    int ii=0;
    while(cin>>t)
    {
        myInput[ii]=t;
        ii++;
        if(t=='#')
            break;
    }//将输入的内容存到数组里面
    if(myInput[0]=='D'&&myInput[1]=='E'&&myInput[2]=='F')//正在定义函数
    {
        myFun *newnode;
        newnode=(myFun*)malloc(sizeof(myFun));
//        char expre[50];//函数表达
        int temp=3;//从DEF后面开始看

        bool ifName=1;
        bool ifContent=0;//函数内容
        int count=0;
        int exppp=0;
        for(;;temp++)
        {
            if(myInput[temp]=='(')
            {
                ifName=0;//函数名称部分结束
                newnode->funName[count]='\0';
            }
            if(myInput[temp]!=' '&&ifName==1)//函数名称部分
            {
                newnode->funName[count]=myInput[temp];
                count++;
            }

            if(myInput[temp]=='=')
            {
                ifContent=1;
            }
            if(ifContent==1&&myInput[temp]!='=')//等号后面的部分
            {
                //比较当前字符与历史函数名称的首字母，如果不是历史函数首字母，计入“函数内容”

                newnode->funExpre[exppp]=myInput[temp];
                exppp++;
            }
            if(myInput[temp]=='#')
            {
                newnode->funExpre[exppp]=myInput[temp];
                exppp++;
                break;
            }
        }//将函数名称存到新构造的结点的funName中，将表达式部分存到expre中
        //下面将newNode插入到函数链表中
        newnode->next=funcList->next;
        funcList->next=newnode;
    }
    else if(myInput[0]=='R'&&myInput[1]=='U'&&myInput[2]=='N')//开始运行函数
    {

        int temp=3;//从RUN后面开始看
        char runName[10];
        int tt=0;

        for(;;temp++)//拿到函数名称
        {
            if(myInput[temp]=='(')
            {
                runName[tt]='\0';
                break;
            }
            else if(myInput[temp]!=' ')
            {
                runName[tt]=myInput[temp];
                tt++;
            }
        }

        myFun *pp;
        pp=funcList->next;
        for(int i=0;;i++)
        {
            if(runName[0]!=pp->funName[0])//比较函数名称的第一个字符
            {
                pp=pp->next;
            }
            else
            {
                int temp=1;
                bool rightName=1;
                while(runName[temp]!='\0')
                {
                    if(runName[temp]==pp->funName[temp])
                      temp++;
                    else//函数名不是这个
                    {
                        rightName=0;
                        break;
                    }
                }//进一步判断运行的是不是这个函数
                if(rightName==0)
                {
                    pp=pp->next;
                }
                else
                {
                    break;//pp所指向的就是当前函数
                }
            }
        }
        //假设是一位整数
        temp=0;
        while(myInput[temp]!='(')temp++;
        temp++;//找到变量的值的第一位数字的位置

        double value;//赋给变量的值

        bool ifF=0;//进入小数
        int countF=0;//小数数位

        bool ifE=0;//进入科学计数法的指数部分

        value=myInput[temp]-'0';

        int afterE=0;
        for(int i=0;;i++)
        {
            if(myInput[temp]!=')')temp++;
            else break;
            if(myInput[temp]=='.')
            {
                ifF=1;
            }
            if(myInput[temp]=='e')
            {

                ifE=1;
            }
            if(ifNumber(myInput[temp])&&ifF==0&&ifE==0)
            {
                value=value*10+myInput[temp]-'0';
            }
            else if(ifNumber(myInput[temp])&&ifF==1&&ifE==0)
            {
                countF++;
                double myfrac=myInput[temp]-'0';
                for(int j=0;j<countF;j++)
                {
                    myfrac=myfrac/10;
                }
                value+=myfrac;
            }
            else if(ifNumber(myInput[temp])&&ifE==1)//指数部分默认整数
            {
                afterE=afterE*10+myInput[temp]-'0';
                if(myInput[temp+1]==')')
                {
                    for(int i=0;i<afterE;i++)
                    {
                        value=value*10;//处理科学计数法的变量值
                    }
                }
            }
        }//处理小数

        double myresult;
        calcuVal(pp->funExpre,value,myresult);
        cout<<"="<<myresult<<endl;
        cout<<"----------------"<<endl;
        //第一个函数

    }
}

#endif // DEFFUNCTION_H
