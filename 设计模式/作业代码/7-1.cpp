#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Leader
{
protected:
    Leader *successor;
    int maxCost;

public:
    virtual bool handleRequest(int req)

    {
        if (req >= maxCost)

        {
            cout << "Cannot handle your request, examing by superior." << endl;
            return successor->handleRequest(req);
        }
        else
        {
            cout << "Approved." << endl;
            return true;
        }
    }
    virtual void setSuccessor(Leader *s)

    {
        this->successor = s;
        return;
    }
};
class Chief : public Leader
{
public:
    Chief()

    {
        maxCost = 10000;
    }
};
class Section : public Leader
{
public:
    Section()

    {
        maxCost = 50000;
    }
};
class VicePrincipal : public Leader
{
public:
    VicePrincipal()

    {
        maxCost = 100000;
    }
};
class Principal : public Leader
{
public:
    Principal()

    {
        maxCost = INT_MAX;
    }
};
int main(void)
{
    Leader *kezhang = new Chief;
    Leader *chuzhang = new Section;
    Leader *fuxiaozhang = new VicePrincipal;
    Leader *xiaozhang = new Principal;
    kezhang->setSuccessor(chuzhang);
    chuzhang->setSuccessor(fuxiaozhang);
    fuxiaozhang->setSuccessor(xiaozhang);
    kezhang->handleRequest(12345);
    kezhang->handleRequest(88888);
    kezhang->handleRequest(111111);
    return 0;
}