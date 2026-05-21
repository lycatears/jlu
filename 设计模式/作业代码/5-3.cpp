#include <iostream>
#include <vector>

using namespace std;

class Beverage
{
protected:
    int price = 0;

public:
    virtual int getPrice()
    {
        return price;
    }

    virtual ~Beverage() = default;
};

class MilkTea : public Beverage
{
public:
    MilkTea()
    {
        price = 8;
    }
};

class MilkShake : public Beverage
{
public:
    MilkShake()
    {
        price = 9;
    }
};

class Coffee : public Beverage
{
public:
    Coffee()
    {
        price = 10;
    }
};

class Condiment : public Beverage
{
protected:
    Beverage *beverage;

public:
    int getPrice()
    {
        return price + beverage->getPrice();
    }

    Condiment(Beverage *beverage)
    {
        this->beverage = beverage;
    }

    virtual ~Condiment()
    {
        delete beverage;
    }
};

class Strawberry : public Condiment
{
public:
    Strawberry(Beverage *beverage) : Condiment(beverage)
    {
        price = 2;
    };
};

class Pudding : public Condiment
{
public:
    Pudding(Beverage *beverage) : Condiment(beverage)
    {
        price = 3;
    };
};

class Cheese : public Condiment
{
public:
    Cheese(Beverage *beverage) : Condiment(beverage)
    {
        price = 4;
    };
};

int main(void)
{
    Condiment *c1 = new Cheese(new Coffee);
    Condiment *c2 = new Strawberry(new MilkShake);
    Condiment *c3 = new Pudding(new MilkTea);

    cout << c1->getPrice() << endl;
    cout << c2->getPrice() << endl;
    cout << c3->getPrice() << endl;

    delete c1;
    delete c2;
    delete c3;

    return 0;
}