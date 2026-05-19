#include <iostream>
#include <string>
#include <time.h>
#include "sever_time.h"
#include "Employee.h"
using namespace std;

Date::Date(void)
{
    //默认构造函数，将员工生日设置为1900-1-1
    //输入：无
    //输出：无
    year=1900;
    month=1;
    month=1;
    return;
}

Date::~Date()
{

}

Date::Date(int yy,int mm,int dd)
{
    //带参构造函数，提供具体日期信息
    //输入：年月日三个整型数据
    //输出：无
    year=yy;
    month=mm;
    day=dd;
    return;
}

void Date::ShowDate(void)const
{
    //显示Date对象中的日期信息
    //输入：无
    //输出：无
    cout<<year<<'-'<<month<<'-'<<day<<endl;
    return;
}

bool Date::DateCheck(void)const
{
    //检查日期是否合法，合法返回1
    //输入：无
    //输出：合法返回1，否则返回0
    if(month>12||month<1||day<1||day>31)
    {
        return 0;
    }
    if(month==4||month==6||month==9||month==11)
    {
        if(day>30)
        {
            return 0;
        }
    }
    if(month==2)
    {
        if(year%4!=0||(year%100==0&&year%400!=0))
        {
            if(day>28)
            {
                return 0;
            }
        }
        else
        {
            if(day>29)
            {
                return 0;
            }
        }
    }
    return 1;
}

void Date::ChangeDate(void)
{
    //改变日期信息
    //输入：无
    //输出：无
    while(1)
    {
        cout<<"输入新的日期：";
        cin>>year>>month>>day;
        if(DateCheck())
        {
            return;
        }
        else
        {
            cout<<"时间数据非法，请重试！"<<endl;
        }
    }
    return;
}

bool Date::CompareDate(const Date& target_date)const
{
    //比较时间信息，若月份相同返回1
    //输入：另一个日期对象的引用
    //输出：相同返回1，否则返回0
    if(month==target_date.month)
    {
        return 1;
    }
    return 0;
}

bool Date::CompareWithCurrent(void)
{
    struct tm* t;
    t=GetNormalTime(GetOriginalTime());
    Date curDate(t->tm_year+1900,t->tm_mon+1,t->tm_mday);
    return CompareDate(curDate);
}

Employee::Employee(){};

Employee::Employee(string str,int _id,int _yy,int _mm,int _dd):name(str),id(_id),birthDate(_yy,_mm,_dd){};

void Employee::SetName(void)
{
    cout<<"请输入员工姓名：";
    cin>>name;
    return;
}

void Employee::SetId(void)
{
    cout<<"请输入工号：";
    cin>>id;
    return;
}

void Employee::SetBirth(void)
{
    cout<<"请输入员工生日：";
    birthDate.ChangeDate();
    return;
}

void Employee::Init(void)
{
    SetName();
    SetId();
    SetBirth();
    return;
}

void Employee::ShowInfo(void)
{
    ShowEmployeeType();
    cout<<"员工姓名："<<name<<endl;
    cout<<"工号："<<id<<endl;
    cout<<"生日：";
    birthDate.ShowDate();
    ShowSalary();
    return;
}

SalariedEmployee::SalariedEmployee(string str,int _id,int _yy,int _mm,int _dd,int salary)
{
    name=str;
    id=_id;
    birthDate=Date(_yy,_mm,_dd);
    WeekSalary=salary;
}

void SalariedEmployee::ShowEmployeeType(void)
{
    cout<<"员工类型：周薪员工\n";
    return;
}

double SalariedEmployee::Salary(void)
{
    return WeekSalary;
}

void SalariedEmployee::ShowSalary(void)
{
    cout<<"工资明细："<<endl;
    cout<<"固定周薪："<<WeekSalary<<"元"<<endl;
    if(birthDate.CompareWithCurrent())
    {
        cout<<"生日补助：100.00元"<<endl;
        cout<<"总计："<<WeekSalary+100<<endl;
        return;
    }
    else
    {
        cout<<"总计："<<WeekSalary<<endl;
        return;
    }
}

HourlyEmployee::HourlyEmployee(string str,int _id,int _yy,int _mm,int _dd,double _WorkHours,double _HourSalary)
{
    name=str;
    id=_id;
    birthDate=Date(_yy,_mm,_dd);
    WorkHours=_WorkHours;
    HourSalary=_HourSalary;
}

void HourlyEmployee::ShowEmployeeType(void)
{
    cout<<"员工类型：时薪员工\n";
    return;
}

double HourlyEmployee::Salary(void)
{
    if(WorkHours<=40)
    {
        money=HourSalary*WorkHours;
        return money;
    }
    else
    {
        money=40*HourSalary+(WorkHours-40)*1.5*HourSalary;
        return money;
    }
}

void HourlyEmployee::ShowSalary(void)
{
    cout<<"工资明细："<<endl;
    cout<<"时薪："<<HourSalary<<"元"<<endl;
    cout<<"工作时长："<<WorkHours<<"小时"<<endl;
    cout<<"工资："<<money<<endl;
    if(WorkHours>40)
    {
        cout<<"加班"<<WorkHours-40<<"小时，该部分工资按照1.5倍计算"<<endl;
    }
    if(birthDate.CompareWithCurrent())
    {
        cout<<"生日补助：100.00元"<<endl;
        money+=100;
        cout<<"总计："<<money<<endl;
        return;
    }
    else
    {
        cout<<"总计："<<money<<endl;
        return;
    }
}

CommissionEmployee::CommissionEmployee(string str,int _id,int _yy,int _mm,int _dd,double _price,double _sale)
{
    name=str;
    id=_id;
    birthDate=Date(_yy,_mm,_dd);
    price=_price;
    sale=_sale;
}

CommissionEmployee::CommissionEmployee(){};

void CommissionEmployee::ShowEmployeeType(void)
{
    cout<<"员工类型：佣金员工\n";
    return;
}

double CommissionEmployee::Salary(void)
{
    money=price*sale;
    return money;
}

void CommissionEmployee::ShowSalary(void)
{
    cout<<"工资明细："<<endl;
    cout<<"商品销售佣金："<<price<<"元"<<endl;
    cout<<"销售量："<<sale<<"件"<<endl;
    cout<<"工资："<<money<<endl;
    if(birthDate.CompareWithCurrent())
    {
        cout<<"生日补助：100.00元"<<endl;
        money+=100;
        cout<<"总计："<<money<<endl;
        return;
    }
    else
    {
        cout<<"总计："<<money<<endl;
        return;
    }
}

BasePlusCommissionEmployee::BasePlusCommissionEmployee(string str,int _id,int _yy,int _mm,int _dd,
                                                        double _price,double _sale,double _BasicSalary)
{
    name=str;
    id=_id;
    birthDate=Date(_yy,_mm,_dd);
    price=_price;
    sale=_sale;
    BasicSalary=_BasicSalary;
}

void BasePlusCommissionEmployee::ShowEmployeeType(void)
{
    cout<<"员工类型：带底薪佣金雇员\n";
    return;
}

double BasePlusCommissionEmployee::Salary(void)
{
    BasicSalary*=1.1;
    money=BasicSalary;
    money+=price*sale;
    return money;
}

void BasePlusCommissionEmployee::ShowSalary(void)
{

    cout<<"工资明细："<<endl;
    cout<<"底薪：(公司提高10%)"<<BasicSalary<<"元"<<endl;
    cout<<"商品销售佣金："<<price<<"元"<<endl;
    cout<<"销售量："<<sale<<"件"<<endl;
    cout<<"工资："<<money<<endl;
    if(birthDate.CompareWithCurrent())
    {
        cout<<"生日补助：100.00元"<<endl;
        money+=100;
        cout<<"总计："<<money<<endl;
        return;
    }
    else
    {
        cout<<"总计："<<money<<endl;
        return;
    }
}

