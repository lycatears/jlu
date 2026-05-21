#include <bits/stdc++.h>
#include <vector>
#include <memory>
using namespace std;
class System;
class State
{
public:
    virtual void work(System *system) = 0;
    virtual ~State() = default;
};
class Closed : public State
{
public:
    void work(System *system)
    {
        cout << "System closed!" << endl;
    }
};
class System
{
private:
    State *state;
    double T;
    double currentT;
public:
    System(double T, double nowT)
    {
        this->T = T;
        this->currentT = nowT;
        this->state = new Closed;
    }
    double getT()
    {
        return T;
    }
    void setT(double T)
    {
        this->T = T;
    }
    double getcurrentT()
    {
        return currentT;
    }
    void setcurrentT(double currentT)
    {
        this->currentT = currentT;
    }
    void open();
    void close()
    {
        this->state = new Closed;
    }
};
class Heating : public State
{
public:
    void work(System *system)
    {
        while (system->getT() > system->getcurrentT())
        {
            cout << "setT = " << system->getT() << " and currentT = " << system->getcurrentT() << endl;
            system->setcurrentT(system->getcurrentT() + 1);
        }
        cout << "Heat Finished." << endl;
    }
};
class Cooling : public State
{
public:
    void work(System *system)
    {
        while (system->getT() < system->getcurrentT())
        {
            cout << "setT = " << system->getT() << " and currentT = " << system->getcurrentT() << endl;
            system->setcurrentT(system->getcurrentT() - 1);
        }
        cout << "Cool Finished." << endl;
    }
};
void System::open()
{
    delete state;
    if (currentT > T)
    {
        state = new Cooling;
    }
    else if (currentT < T)
    {
        state = new Heating;
    }
    else
    {
        state = new Closed;
    }
    state->work(this);
}
int main()
{
    System *sys = new System(26, 30);
    sys->open();
    return 0;
}