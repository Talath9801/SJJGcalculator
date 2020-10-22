#include <iostream>
#include <calculate.h>//向量计算用到的函数
#include <sqlist.h>//多项式计算，用顺序表
#include <linklist.h>//多项式计算，用链表
#include <expression.h>//表达式求值
#include <iomanip>
#include <stdlib.h>
using namespace std;




int main()
{
    int mode;//选择向量/多项式计算
    int _operate;//选择操作
    int polmode;//选择顺序表/链表操作多项式
    cout<<"choose the object you want to calculate,"<<endl<<"0 for expression evaluation, "<<endl<<"1 for between vectors, "<<endl<<"2 for between polynomials, "<<endl<<"3 for polynomial derivation"<<endl;
    cin>>mode;

    if(mode==0)//表达式求值
    {
        int exMode;//是否有变量
        int decimal;//小数点后精确位数
        double myresult;
        cout<<"if there is no variables, input 0, if there is a variable input 1"<<endl;
        cin>>exMode;
        cout<<"input expression, end with #"<<endl;
        if(exMode==0)
        {
            cout<<"for example: 8*(4-2)+9/3# "<<endl<<endl<<endl;
            EvaluateExpression(myresult);//不含变量的求值
            cout<<"input the numbers after the decimal point"<<endl;
            cin>>decimal;
            if(decimal==0)
            {
                cout<<"the result is  "<<int(myresult)<<endl;
            }
            else
            {
                cout<<"the result is  "<<setiosflags(ios::fixed)<<setprecision(decimal)<<myresult<<endl;
            }
            //cout<<"the result is  "<<myresult<<endl;
        }
        else if(exMode==1)//含变量的表达式
        {
            cout<<"for example: 8*(x12y3-2)+9/3#"<<endl<<endl<<endl;
            char myExp[50];
            char t;
            int ii=0;
            while(cin>>t)
            {
                myExp[ii]=t;
                ii++;
                if(t=='#')
                    break;
            }//将输入的表达式存到数组里面
            cout<<"input the value of the variable"<<endl;
            double value;
            while(cin>>value)
            {
                //计算的时候将变量的值替换为value
                //调用有变量的表达式求值函数

                calcuVal(myExp,value,myresult);
                cout<<"input the numbers after the decimal point"<<endl;
                cin>>decimal;
                if(decimal==0)
                {
                    cout<<"the result is  "<<int(myresult)<<endl;
                }
                else
                {
                    cout<<"the result is  "<<setiosflags(ios::fixed)<<setprecision(decimal)<<myresult<<endl;
                }
                cout<<"------------------"<<endl<<endl;
                cout<<"input the value of the variable"<<endl;
            }
        }//含变量的表达式
        else
            cout<<"input error"<<endl;


    }
    else if(mode==1)//向量计算
    {
        cout<<"input the dimension of vector"<<endl;
        int n;//dim
        cin>>n;
        SqList mylist1,mylist2;
        InitList(mylist1,n);//创建顺序表
        InitList(mylist2,n);
        cout<<"input vector1, for example, input 1 2 3 for vector(1,2,3)"<<endl;
        for(int i=0;i<n;i++)
        {
            cin>>mylist1.elem[i];
        }
        cout<<"input vecotr2, for example, input 1 2 3 for vector(1,2,3)"<<endl;
        for(int i=0;i<n;i++)
        {
            cin>>mylist2.elem[i];
        }
        cout<<"choose the operation, 1 for addtion, 2 for subtraction, 3 for dot-product, 4 for angle cos"<<endl;
        //注：为了输入一组向量之后可以分别进行多种操作而不用多次输入向量，新建了一个顺序表来存结果，而没有直接在原表中修改数值
        while(cin>>_operate)
        {
            if(_operate==1)//加法
            {
                SqList mylist;
                InitList(mylist,n);
                add(mylist1,mylist2,mylist);
                cout<<"--------------------------------------"<<endl;
                cout<<"the result of addtion is ";
                print(mylist);
                cout<<"--------------------------------------"<<endl;
            }
            else if(_operate==2)//减法
            {
                SqList mylist;
                InitList(mylist,n);
                subtract(mylist1,mylist2,mylist);
                cout<<"--------------------------------------"<<endl;
                cout<<"the result of subtraction is ";
                print(mylist);
                cout<<"--------------------------------------"<<endl;
            }
            else if(_operate==3)//内积
            {
                double result;
                result=dotProduct(mylist1,mylist2);
                cout<<"--------------------------------------"<<endl;
                cout<<"the dot product is "<<result<<endl;
                cout<<"--------------------------------------"<<endl;
            }
            else if(_operate==4)//夹角余弦
            {
                cout<<"--------------------------------------"<<endl;
                cout<<"the angle cos is "<<angleCos(mylist1,mylist2)<<endl;
                cout<<"--------------------------------------"<<endl;
            }
            else
            {
                cout<<"input error"<<endl;
            }
        }


    }//向量计算
    else if(mode==2)//多项式之间的计算
    {
        cout<<"input the mode for calculator, 1 for SequenceList(expn<=1000), 2 for LinkList"<<endl;
        //用顺序表输入1，用链表输入2
        cin>>polmode;
        if(polmode==1)//顺序表
        {
            polSqList list1,list2,list;
            InitSqList(list1);
            InitSqList(list2);
            InitSqList(list);
            ElemType xx;
            int xiangshu;
            cout<<"input the max expn of polynomial 1"<<endl;
            cin>>xiangshu;
            cout<<endl;
            cout<<endl;
            cout<<"input the ceof of polynomial 1, for example, 0 1 0 3 stands for x+3x^3"<<endl;//输入第一个多项式的系数
            for(int i=0;i<=xiangshu;i++)
            {
                cin>>xx;
                list1.elem[i]=xx;
                list1.length++;
            }
            cout<<"your polynomial 1 is       ";
            printSq(list1);

            cout<<endl;
            cout<<endl;
            cout<<"input the max expn of polynomial 2"<<endl;
            cin>>xiangshu;
            cout<<"input the ceof of polynomial 2, for example, 0 1 0 3 stands for x+3x^3"<<endl;//输入第二个多项式的系数
            for(int i=0;i<=xiangshu;i++)
            {
                cin>>xx;
                list2.elem[i]=xx;
                list2.length++;
            }
            cout<<"your polynomial 2 is       ";
            printSq(list2);


            cout<<endl;
            cout<<endl;
            cout<<"choose the operation, 1 for addtion, 2 for subtraction"<<endl;

            while(cin>>_operate)
            {
                if(_operate==1)
                {
                    addSq(list1,list2,list);
                    cout<<"--------------------------------------"<<endl;
                    cout<<"the result of addtion is     ";
                    printSq(list);
                    cout<<"--------------------------------------"<<endl;
                }
                else if(_operate==2)
                {
                    subtractSq(list1,list2,list);
                    cout<<"--------------------------------------"<<endl;
                    cout<<"the result of subtraction is     ";
                    printSq(list);
                    cout<<"--------------------------------------"<<endl;
                }
                else
                    cout<<"input error"<<endl;
            }

        }//顺序表
        if(polmode==2)//链表
        {
            int n1,n2;//两个多项式的项数
            poly polist1;
            poly polist2;
            poly polist;
            //poly tryy;
            initPol(polist1);
            initPol(polist2);
            cout<<"please input the number of terms for polynomial 1"<<endl;//输入项数
            cin>>n1;
            createPol(polist1,n1);//用户输入信息，创建链表
            cout<<endl;
            cout<<"--------------------------------------"<<endl;
            cout<<"your polynomial 1 is"<<endl;
            printPol(polist1);//给用户看一眼输入的多项式
            cout<<"--------------------------------------"<<endl;
            cout<<endl;


            cout<<"please input the number of terms for polynomial 2"<<endl;//输入项数
            cin>>n2;
            createPol(polist2,n2);//用户输入信息，创建链表
            cout<<endl;
            cout<<"--------------------------------------"<<endl;
            cout<<"your polynomial 2 is"<<endl;
            printPol(polist2);//给用户看一眼输入的多项式
            cout<<"--------------------------------------"<<endl;
            cout<<endl;


            //再创建一个储存计算结果的链表
            initPol(polist);

            cout<<"choose the operation, 1 for addtion, 2 for subtraction, 3 for multiplication"<<endl;
            cin>>mode;
            if(mode==1)
            {
                addpol(polist1,polist2,polist);
                cout<<endl;
                cout<<"--------------------------------------"<<endl;
                cout<<"the result of the addition is    ";
                printPol(polist);
                cout<<"--------------------------------------"<<endl;
                cout<<endl;

//                cout<<endl;
//                cout<<"----------"<<endl;
//                addinto(polist1,polist2);
//                printPol(polist1);
            }
            else if(mode==2)
            {
                substractpol(polist1,polist2,polist);
                cout<<endl;
                cout<<"--------------------------------------"<<endl;
                cout<<"the result of the subtraction is    ";
                printPol(polist);
                cout<<"--------------------------------------"<<endl;
                cout<<endl;
            }
            else if(mode==3)//乘法
            {
                multiplyPol(polist1,polist2,polist);
                cout<<endl;
                cout<<"--------------------------------------"<<endl;
                cout<<"the result of the multiplication is     "<<endl;
                printPol(polist);
                cout<<"--------------------------------------"<<endl;
                cout<<endl;
            }
            else cout<<"input error"<<endl;
        }
        else
        {
            cout<<"input error"<<endl;
        }
    }//多项式之间的计算

    else if(mode==3)//多项式求导
    {
        int xiangshu;//项数
        int n;//n阶导
        poly L;
        initPol(L);
        cout<<"please input the number of terms for the polynomial"<<endl;//输入项数
        cin>>xiangshu;
        createPol(L,xiangshu);
        cout<<"your polynomial is"<<endl;
        printPol(L);//给用户看一眼输入的多项式

        cout<<"please input the times of derivation"<<endl;//求导次数
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            deriv(L);//循环，求n次导
        }
        cout<<"--------------------------------------"<<endl;
        cout<<"the result of "<<n<<" times derivation is     ";
        printPol(L);
        cout<<"--------------------------------------"<<endl;
    }//多项式求导
    else
    {
        cout<<"input error"<<endl;
    }
    return 0;
}
