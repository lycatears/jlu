#include <bits/stdc++.h>
#include <vector>
#include <memory>
using namespace std;
class Cook
{
private:
    string name;

public:
    Cook(string name)

    {
        this->name = name;
    }
    ~Cook() = default;
    void work(string dish)

    {
        cout << name << " is working for dish: " << dish << endl;
    }
};
class Order
{
private:
    string name;
    Cook *cook;

public:
    Order(string name, Cook *cook)

    {
        this->name = name;
        this->cook = cook;
    }
    virtual void makeDish()

    {
        cook->work(name);
    }
};
class Order1 : public Order
{
public:
    Order1(string name, Cook *cook) : Order(name, cook) {};
};
class Order2 : public Order
{
public:
    Order2(string name, Cook *cook) : Order(name, cook) {};
};
class Order3 : public Order
{
public:
    Order3(string name, Cook *cook) : Order(name, cook) {};
};
class Waiter
{
private:
    vector<Order *> orders;
    string name;

public:
    void addOrder(Order *o)

    {
        orders.push_back(o);
    }
    void removeOrder(Order *o)

    {
        orders.erase(find(orders.begin(), orders.end(), o));
    }
    Waiter(string name)

    {
        this->name = name;
    }
    void execute()

    {
        cout << name << " is sending orders..." << endl;
        for (int i = 0; i < (int)orders.size(); i++)

        {
            orders[i]->makeDish();
        }
    }
};
class Customer
{
private:
    Waiter *waiter;

public:
    void newOrder(Order *o)

    {
        waiter->addOrder(o);
    }
    void deleteOrder(Order *o)

    {
        waiter->removeOrder(o);
    }
    void callWaiter(Waiter *w)

    {
        this->waiter = w;
    }
};
int main()
{
    Cook *c1 = new Cook("cook1");
    Cook *c2 = new Cook("cook2");
    Waiter *w1 = new Waiter("waiter1");
    Waiter *w2 = new Waiter("waiter2");
    Order1 *o1 = new Order1("hamburger", c1);
    Order2 *o2 = new Order2("vegetable", c2);
    Order3 *o3 = new Order3("ItalianNoodles", c1);
    Customer *customer = new Customer;
    customer->callWaiter(w1);
    customer->newOrder(o1);
    customer->newOrder(o3);
    customer->newOrder(o2);
    w1->execute();
    return 0;
}