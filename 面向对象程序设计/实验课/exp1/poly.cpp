#include <iostream>
#include <cmath>
#include "poly.h"

using namespace std;

int poly::count_item=0;
item::item(void)
{
    this->coeff=0;
    this->degree=0;
    this->next=NULL;
    return;
}

item::item(double _coeff,double _degree):coeff(_coeff),degree(_degree)
{
    next=NULL;
    return;
}

void item::ShowData(void) const
{
    if(coeff<0&&degree!=0&&abs(coeff)!=1)
    {
        cout<<coeff<<"x";
        if(degree!=1)
        {
            cout<<'^'<<degree;
        }
    }
    if(coeff>0&&degree!=0&&abs(coeff)!=1)
    {
        cout<<'+'<<coeff<<"x";
        if(degree!=1)
        {
            cout<<'^'<<degree;
        }
    }
    if(degree!=0&&coeff==1)
    {
        cout<<'+'<<"x";
        if(degree!=1)
        {
            cout<<'^'<<degree;
        }
    }
    if(degree!=0&&coeff==-1)
    {
        cout<<'-'<<"x";
        if(degree!=1)
        {
            cout<<'^'<<degree;
        }
    }
    if(degree==0)
    {
        if(coeff>0)
        {
            cout<<"+"<<coeff;
        }
        else
        {
            cout<<coeff;
        }
    }
    return;
}

poly::poly()
{
    head=NULL;
    count_item++;
    return;
}

poly::~poly()
{
    item* p=head;
    item* q=head;
    while(p!=NULL)
    {
        q=q->next;
        delete p;
        p=q;
    }
    count_item--;
}

poly::poly(const poly& _poly)
{
    item* pItem=_poly.head;
    head=NULL;
    while(pItem!=NULL)
    {
        AddItem(pItem->coeff,pItem->degree);
        pItem=pItem->next;
    }
}

item* poly::IsExisting(double _degree)
{
    item* pItem=head;
    while(pItem!=NULL)
    {
        if(pItem->degree==_degree)
        {
            return pItem;
        }
        pItem=pItem->next;
    }
    return NULL;
}

void poly::ShowList(void) const
{
    if(head==NULL)
    {
        cout<<"0";
        return;
    }
    if(head->coeff!=1&&head->coeff!=0)
    {
        cout<<head->coeff;
    }
    if(head->degree!=1&&head->degree!=0&&head->coeff!=0)
    {
        cout<<"x^"<<head->degree;
    }
    if(head->degree==1&&head->coeff!=0)
    {
        cout<<'x';
    }
    item* pItem=head->next;
    while(pItem!=NULL)
    {
        pItem->ShowData();
        pItem=pItem->next;
    }
}

void poly::AddItem(double _coeff,double _degree)
{
    if(head==NULL)
    {
        head=new item(_coeff,_degree);
        return;
    }
    if(IsExisting(_degree)!=NULL)
    {
        IsExisting(_degree)->coeff+=_coeff;
        return;
    }
    item* pItem=head;
    while(1)
    {
        if(pItem->next==NULL)
        {
            break;
        }
        pItem=pItem->next;
    }
    pItem->next=new item(_coeff,_degree);
    Trim();
    return;
}

double poly::Calculate(double x)
{
    double sum=0;
    item* pItem=head;
    while(pItem!=NULL)
    {
        sum+=(pItem->coeff)*pow(x,pItem->degree);
        pItem=pItem->next;
    }
    return sum;
}

poly operator+(const poly& a,const poly& b)
{
    poly target_poly;
    item* pItem_a=a.head;
    item* pItem_b=b.head;
    while(pItem_a!=NULL)
    {
        target_poly.AddItem(pItem_a->coeff,pItem_a->degree);
        pItem_a=pItem_a->next;
    }
    while(pItem_b!=NULL)
    {
        target_poly.AddItem(pItem_b->coeff,pItem_b->degree);
        pItem_b=pItem_b->next;
    }
    target_poly.Trim();
    return target_poly;
}

poly operator-(const poly& a,const poly& b)
{
    poly target_poly;
    item* pItem_a=a.head;
    item* pItem_b=b.head;
    while(pItem_a!=NULL)
    {
        target_poly.AddItem(pItem_a->coeff,pItem_a->degree);
        pItem_a=pItem_a->next;
    }
    while(pItem_b!=NULL)
    {
        target_poly.AddItem(-pItem_b->coeff,pItem_b->degree);
        pItem_b=pItem_b->next;
    }
    target_poly.Trim();
    return target_poly;
}

poly& poly::operator=(const poly& a)
{
    item* pItem=a.head;
    while(pItem!=NULL)
    {
        AddItem(pItem->coeff,pItem->degree);
        pItem=pItem->next;
    }
    return *this;
}

poly operator*(const poly& a,const poly& b)
{
    poly target_poly;
    item* pItem_a=a.head;
    item* pItem_b=b.head;
    if(pItem_a==NULL||pItem_b==NULL)
    {
        target_poly.head=NULL;
        return target_poly;
    }
    while(pItem_a!=NULL)
    {
        pItem_b=b.head;
        while(pItem_b!=NULL)
        {
            target_poly.AddItem(pItem_a->coeff*pItem_b->coeff,
                                pItem_a->degree+pItem_b->degree);
            pItem_b=pItem_b->next;
        }
        pItem_a=pItem_a->next;
    }
    target_poly.Trim();
    return target_poly;
}

void poly::Trim(void)
{
    item* p=head;
    item* q=head;
    while(p!=NULL)
    {
        if(p->next==NULL)
        {
            break;
        }
        q=head;
        while(q->next!=NULL)
        {
            if(q->degree < q->next->degree)
            {
                double v;
                v=q->coeff;
                q->coeff=q->next->coeff;
                q->next->coeff=v;
                v=q->degree;
                q->degree=q->next->degree;
                q->next->degree=v;
            }
            q=q->next;
        }
        p=p->next;
    }
    return;
}
