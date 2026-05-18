#include <iostream>

#ifndef POLY_H_INCLUDED
#define POLY_H_INCLUDED

class item
{
public:
    double coeff;//系数
    double degree;//次数
    item* next;//指向下一节点的指针

    item();
    item(double _coeff,double _degree);
    void ShowData(void) const;//显示该节点的数据
};

class poly
{
private:
    item* head;
    static int count_item;
    item* IsExisting(double _degree);
    void Trim(void);
public:
    poly();
    ~poly();
    poly(const poly& _poly);
    void ShowList(void) const;//显示全部数据
    void AddItem(double _coeff,double _degree);
    double Calculate(double x);
    friend poly operator+(const poly& a,const poly& b);
    friend poly operator-(const poly& a,const poly& b);
    poly& operator=(const poly& a);
    friend poly operator*(const poly& a,const poly& b);
};
#endif // POLY_H_INCLUDED
