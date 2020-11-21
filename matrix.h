#ifndef MATRIX_H
#define MATRIX_H

#include<iomanip>
#include<malloc.h>
#include<iostream>
using namespace std;
void printMat(double mat[],int n,int m)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<setw(8)<<left<<mat[i*m+j];
        }
        cout<<endl;
    }
}
void addmat()//将两个n*m的矩阵相加
{
    int n,m;
    cout<<"please input the row(n) and col(m) for the matrixs"<<endl;
    cin>>n;
    cin>>m;
    double *mat1,*mat2;
    mat1=(double*)malloc(n*m*sizeof (double));
    mat2=(double*)malloc(n*m*sizeof (double));
    cout<<"input matrix1"<<endl;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            cin>>mat1[i*m+j];
        }
    cout<<"input matrix2"<<endl;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            cin>>mat2[i*m+j];
        }
    //输入矩阵
    //下面将两个矩阵相加，结果存到mat1中，输出结果
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            mat1[i*m+j]+=mat2[i*m+j];
        }
    cout<<endl<<"the result of addition is"<<endl;
    printMat(mat1,n,m);
}
void submat()//将两个n*m的矩阵相减
{
    int n,m;
    cout<<"please input the row(n) and col(m) for the matrixs"<<endl;
    cin>>n;
    cin>>m;
    double *mat1,*mat2;
    mat1=(double*)malloc(n*m*sizeof (double));
    mat2=(double*)malloc(n*m*sizeof (double));
    cout<<"input matrix1"<<endl;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            cin>>mat1[i*m+j];
        }
    cout<<"input matrix2"<<endl;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            cin>>mat2[i*m+j];
        }
    //输入矩阵
    //下面将两个矩阵相减，结果存到mat1中，输出结果
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            mat1[i*m+j]-=mat2[i*m+j];
        }
    cout<<endl<<"the result of addition is"<<endl;
    printMat(mat1,n,m);
}
void multiMat()
{
    int n,m,t;

}
#endif // MATRIX_H
