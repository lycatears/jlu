#include <bits/stdc++.h>
#include <vector>
#include <memory>
using namespace std;
class Center
{
public:
    void log()
    {
        cout << "Logged the use." << endl;
    }
    void respond()
    {
        cout << "ALARMING!!!" << endl;
    }
    void call()
    {
        cout << "Call the center." << endl;
    }
    void messgae()
    {
        cout << "Message the center." << endl;
    }
};
class Treasury;
class State
{
protected:
    Treasury *treasury;
    Center *center;
public:
    State(Treasury *treasury, Center *center)
    {
        this->treasury = treasury;
    }
    ~State() = default;
    void setCenter(Center *c)
    {
        this->center = c;
    }
    virtual void phone() = 0;
    virtual void use() = 0;
    virtual void alarm()
    {
        cout << "Alarm the center." << endl;
        center->respond();
    }
};
class Treasury
{
private:
    State *state;
    Center *center;
public:
    void phone()
    {
        state->phone();
    }
    void alarm()
    {
        state->alarm();
    }
    void use()
    {
        state->use();
    }
    void setState(State *s)
    {
        this->state = s;
    }
    void setCenter(Center *c)
    {
        state->setCenter(c);
    }
};
class Day : public State
{
public:
    Day(Treasury *treasury, Center *center) : State(treasury, center) {};
    void phone()
    {
        cout << "Call the phone." << endl;
        center->call();
    }
    void use()
    {
        cout << "Use the treasury." << endl;
        center->log();
    }
};
class Night : public State
{
public:
    Night(Treasury *treasury, Center *center) : State(treasury, center) {};
    void phone()
    {
        cout << "Call the message phone." << endl;
        center->messgae();
    }
    void use()
    {
        cout << "Use the treasury." << endl;
        center->respond();
    }
};
int main()
{
    Center *center = new Center;
    Treasury *t = new Treasury;
    t->setState(new Day(t, center));
    t->setCenter(center);
    t->phone();
    t->use();
    t->alarm();
    t->setState(new Night(t, center));
    t->phone();
    t->use();
    t->alarm();
    return 0;
}