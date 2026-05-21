#include <iostream>
#include <vector>
using namespace std;
class Employee
{
private:
    double saleroom = 0;
    double returned = 0;

public:
    Employee(double sale, double retu) : saleroom(sale), returned(retu) {};
    double getSale()
    {
        return saleroom;
    }
    double getReturn()
    {
        return returned;
    }
};
class Manager : public Employee
{
private:
    vector<Employee *> groupMember;

public:
    Manager(double sale, double retu) : Employee(sale, retu) {};
    void addMember(Employee *emp)
    {
        groupMember.push_back(emp);
    }
    double getGroupSale()
    {
        double total = 0.0;
        for (int i = 0; i < (int)groupMember.size(); i++)
        {
            total += groupMember[i]->getSale();
        }
        return total;
    }
};
class BusinessAward : public Employee
{
private:
    Employee *emp;

public:
    BusinessAward(Employee *emp) : Employee(*emp), emp(emp) {};
    double getBusinessAward()
    {
        return 0.03 * getSale();
    }
};
class ReturnedAward : public Employee
{
private:
    Employee *emp;

public:
    ReturnedAward(Employee *emp) : Employee(*emp), emp(emp) {};
    double getReturnedAward()
    {
        return 0.001 * getReturn();
    }
};
class GroupAward : public Manager
{
private:
    Manager *man;

public:
    GroupAward(Manager *man) : Manager(*man), man(man) {};
    double getGroupAward()
    {
        return 0.1 * getGroupSale();
    }
};
int main(void)
{
    Employee *e1 = new Employee(8000, 9000);
    Employee *e2 = new Employee(10000, 8000);
    Employee *e3 = new Employee(9000, 10000);
    Manager *m1 = new Manager(9000, 9000);
    m1->addMember(e1);
    m1->addMember(e2);
    m1->addMember(e3);
    BusinessAward *ba1 = new BusinessAward(e1);
    BusinessAward *ba2 = new BusinessAward(e2);
    BusinessAward *ba3 = new BusinessAward(e3);
    BusinessAward *ba4 = new BusinessAward(m1);
    ReturnedAward *ra1 = new ReturnedAward(e1);
    ReturnedAward *ra2 = new ReturnedAward(e2);
    ReturnedAward *ra3 = new ReturnedAward(e3);
    ReturnedAward *ra4 = new ReturnedAward(m1);
    GroupAward *ga1 = new GroupAward(m1);
    cout << ba1->getBusinessAward() << endl;
    cout << ba2->getBusinessAward() << endl;
    cout << ba3->getBusinessAward() << endl;
    cout << ba4->getBusinessAward() << endl;
    cout << ra1->getReturnedAward() << endl;
    cout << ra2->getReturnedAward() << endl;
    cout << ra3->getReturnedAward() << endl;
    cout << ra4->getReturnedAward() << endl;
    cout << ga1->getGroupAward() << endl;
    return 0;
}