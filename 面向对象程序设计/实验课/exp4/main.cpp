#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include "Employee.h"

using namespace std;

int target=0;

int main()
{
    cout<<fixed<<setprecision(2);
    Employee* container[100];
    for(int i=0;i<25;i++)
    {
        container[i]=new SalariedEmployee("111",i,1999,3,14,2000);
    }
    for(int i=25;i<50;i++)
    {
        container[i]=new HourlyEmployee("222",i,2000,5,14,42,46);
    }
    for(int i=50;i<75;i++)
    {
        container[i]=new CommissionEmployee("333",i,2001,6,15,100,20);
    }
    for(int i=75;i<100;i++)
    {
        container[i]=new BasePlusCommissionEmployee("444",i,2002,9,29,100,15,400);
    }
    while(1)
    {
        cout<<"输入要显示的员工编号：";
        cin>>target;
        container[target]->Salary();
        container[target]->ShowInfo();
    }
}
