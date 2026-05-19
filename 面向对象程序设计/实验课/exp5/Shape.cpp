#include <iostream>
#include <cmath>
#include "Shape.h"

Circle::Circle(void):r(0)
{
    r=0;
}

Circle::Circle(double a):r(a)
{
    r=a;
}

Shape* Circle::Clone(void)
{//克隆函数，用于深拷贝中拷贝图形类对象
    Circle* new_circle=new Circle;
    new_circle->r=this->r;
    return new_circle;
}

double Circle::area(void)
{//计算面积
    return pi*r*r;
}

Triangle::Triangle(void)
{
    a=b=c=0;
}

Triangle::Triangle(double m,double n,double p)
{
    a=m;
    b=n;
    c=p;
}

double Triangle::area(void)
{//计算面积
    double p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

Shape* Triangle::Clone(void)
{//克隆函数，用于深拷贝中拷贝图形类对象
    Triangle* new_triangle=new Triangle;
    new_triangle->a=this->a;
    new_triangle->b=this->b;
    new_triangle->c=this->c;
    return new_triangle;
}

Manage::Manage()
{
    for(int i=0;i<100;i++)
    {
        a[i]=NULL;
    }
}

Manage::~Manage()
{
    for(int i=0;i<100;i++)
    {
        if(a[i]!=NULL)
        {
            delete a[i];
        }
    }
}

Shape* Manage::ShowShape(int pos) const
{
    return a[pos];
}

Manage::Manage(const Manage& target)
{
    for(int i=0;i<100;i++)
    {
        if(target.ShowShape(i)==NULL)
        {
            a[i]=NULL;
        }
        else
        {
            a[i]=(target.a[i])->Clone();
        }
    }
}

void Manage::ChangeShape(Shape* s,int pos)
{
    a[pos]=s;
    return;
}

double Manage::TotalArea(void) const
{
    double sumArea=0;
    for(int i=0;i<100;i++)
    {
        sumArea+=a[i]->area();
    }
    return sumArea;
}
