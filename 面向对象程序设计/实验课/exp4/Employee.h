#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED
#include <iostream>
#include <string>
#include <time.h>
#include "sever_time.h"
using namespace std;

class Date
{
private:
    int year;
    int month;
    int day;
    bool DateCheck(void)const;                         //检查日期是否合法，合法返回1，不合法返回0
public:
    Date();                                             //默认构造函数，初始化为1900-1-1
    Date(int yy,int mm,int dd);                        //带参数构造函数，指定日期
    ~Date();                                            //日期对象析构函数
    void ShowDate(void)const;
    void ChangeDate(void);                             //修改日期信息
    bool CompareDate(const Date& target_date)const;    //比较两个日期是否相同，相同返回，否则返回0
    bool CompareWithCurrent(void);
};

class Employee
{
protected:
    string name;
    int id;
    Date birthDate;
public:
    Employee();
    Employee(string str,int _id,int _yy,int _mm,int _dd);
    void SetName(void);
    void SetId(void);
    void SetBirth(void);
    void Init(void);
    virtual void ShowEmployeeType(void)=0;              //展示员工类型
    virtual double Salary(void)=0;                      //计算工资
    virtual void ShowSalary(void)=0;                    //显示应得工资
    virtual void ShowInfo(void);                      //显示员工的全部信息
};

class SalariedEmployee:public Employee
{
protected:
    double WeekSalary;
public:
    SalariedEmployee(string str,int _id,int _yy,int _mm,int _dd,int salary);
    virtual void ShowEmployeeType(void);              //展示员工类型
    virtual double Salary(void);                      //计算工资
    virtual void ShowSalary(void);                    //显示应得工资
};

class HourlyEmployee:public Employee
{
protected:
    double WorkHours;
    double HourSalary;
    double money;
public:
    HourlyEmployee(string str,int _id,int _yy,int _mm,int _dd,
                   double _WorkHours,double _HourSalary);
    virtual void ShowEmployeeType(void);              //展示员工类型
    virtual double Salary(void);                      //计算工资
    virtual void ShowSalary(void);                    //显示应得工资
};

class CommissionEmployee:public Employee
{
protected:
    double price;
    double sale;
    double money;
public:
    CommissionEmployee();
    CommissionEmployee(string str,int _id,int _yy,int _mm,int _dd,
                       double _price,double _sale);
    virtual void ShowEmployeeType(void);              //展示员工类型
    virtual double Salary(void);                      //计算工资
    virtual void ShowSalary(void);                    //显示应得工资
};

class BasePlusCommissionEmployee:public CommissionEmployee
{
protected:
    double BasicSalary;
public:
    BasePlusCommissionEmployee(string str,int _id,int _yy,int _mm,int _dd,
                               double _price,double _sale,double _BasicSalary);
    virtual void ShowEmployeeType(void);              //展示员工类型
    virtual double Salary(void);                      //计算工资
    virtual void ShowSalary(void);                    //显示应得工资
};
#endif // EMPLOYEE_H_INCLUDED
