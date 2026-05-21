#include <bits/stdc++.h>
#include <vector>
#include <memory>
using namespace std;
class AbstractDoctor;
class AbstractHospital
{
public:
    virtual void addDoctor(AbstractDoctor *d) = 0;
    virtual void deleteDoctor(AbstractDoctor *d) = 0;
    virtual void operation(string req) = 0;
    virtual void stop() = 0;
};
class AbstractDoctor
{
protected:
    string name;
    AbstractHospital *hospital;

public:
    AbstractDoctor(string name, AbstractHospital *hospital)

    {
        this->name = name;
        this->hospital = hospital;
    }
    virtual void respond(string req) = 0;
    virtual void stopRespond() = 0;
    virtual void operation() = 0;
    virtual void process() = 0;
};
class Hall : public AbstractDoctor
{
public:
    Hall(string name, AbstractHospital *hospital) : AbstractDoctor(name, hospital)

    {
        hospital->addDoctor(this);
    }
    void respond(string req)

    {
        cout << req << " patient needs help. " << name << " Display and alarm." << endl;
    }
    void stopRespond()

    {
        cout << name << " Stopped displaying and alarming." << endl;
    }
    void operation()

    {
        hospital->operation(name);
    }
    void process()

    {
        cout << name << " processed the emergency." << endl;
        hospital->stop();
    }
};
class Wrap : public AbstractDoctor
{
public:
    Wrap(string name, AbstractHospital *hospital) : AbstractDoctor(name, hospital)
    {
        hospital->addDoctor(this);
    };
    void respond(string req)
    {
        cout << req << " patient needs help. " << name << " Display." << endl;
    }
    void stopRespond()

    {
        cout << name << " Stopped displaying and alarming." << endl;
    }
    void operation()
    {
        hospital->operation(name);
    }
    void process()

    {
        cout << name << " processed the emergency." << endl;
        hospital->stop();
    }
};
class Hospital : public AbstractHospital
{
private:
    vector<AbstractDoctor *> doctorList;

public:
    void addDoctor(AbstractDoctor *d)

    {
        doctorList.push_back(d);
    }
    void deleteDoctor(AbstractDoctor *d)

    {
        doctorList.erase(find(doctorList.begin(), doctorList.end(), d));
    }
    void operation(string req)

    {
        for (int i = 0; i < (int)doctorList.size(); i++)
        {
            doctorList[i]->respond(req);
        }
    }
    void stop()

    {
        for (int i = 0; i < (int)doctorList.size(); i++)
        {
            doctorList[i]->stopRespond();
        }
    }
};
int main()
{
    Hospital *hospital = new Hospital;
    AbstractDoctor *w1 = new Wrap("001", hospital);
    AbstractDoctor *w2 = new Wrap("002", hospital);
    AbstractDoctor *w3 = new Wrap("003", hospital);
    AbstractDoctor *hall = new Hall("Hall", hospital);
    w1->operation();
    w3->process();
    w2->operation();
    hall->process();
    return 0;
}