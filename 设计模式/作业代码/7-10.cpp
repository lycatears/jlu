#include <bits/stdc++.h>
#include <vector>
#include <memory>
using namespace std;
typedef void (*void_fptr)();
class AbstractTrigger
{
protected:
    vector<pair<string, void_fptr>> ftable;
    virtual void preProcess(string event) = 0;
    virtual void processEvent(string event) = 0;
    virtual void postProcess(string event) = 0;
    bool hasProcess(string event)
    {
        for (int i = 0; i < (int)ftable.size(); i++)
        {
            if (ftable[i].first == event)
            {
                return true;
            }
        }
        return false;
    }
public:
    virtual void on(string event, void_fptr f)
    {
        if (f == nullptr)
        {
            vector<int> deleteFunc;
            for (int i = 0; i < (int)ftable.size(); i++)
            {
                if (ftable[i].first == event)
                {
                    deleteFunc.push_back(i);
                }
            }
            for (int i = deleteFunc.size() - 1; i >= 0; i--)
            {
                ftable.erase(ftable.begin() + deleteFunc[i]);
            }
        }
        else
        {
            ftable.push_back(pair<string, void_fptr>(event, f));
        }
    }
    void raiseEvent(string event)
    {
        if (hasProcess(event))
        {
            processEvent(event);
        }
    }
};
class Trigger : public AbstractTrigger
{
protected:
    virtual void preProcess(string event)
    {
        cout << "Process " << event << " start" << endl;
    }
    virtual void processEvent(string event)
    {
        for (int i = 0; i < (int)ftable.size(); i++)
        {
            if (ftable[i].first == event)
            {
                preProcess(event);
                ftable[i].second();
                postProcess(event);
            }
        }
    }
    virtual void postProcess(string event)
    {
        cout << "Process " << event << " end" << endl;
    }
};
void func01()
{
    cout << "func01" << endl;
}
void func02()
{
    cout << "func02" << endl;
}
void func03()
{
    cout << "func03" << endl;
}
int main()
{
    Trigger *trigger = new Trigger;
    trigger->on("event01", &func01);
    trigger->on("event01", &func02);
    trigger->on("event02", &func02);
    trigger->on("event03", &func03);
    trigger->raiseEvent("event01");
    trigger->raiseEvent("event02");
    trigger->raiseEvent("event03");
    trigger->on("event01", nullptr);
    trigger->raiseEvent("event01");
    trigger->raiseEvent("event02");
    return 0;
}