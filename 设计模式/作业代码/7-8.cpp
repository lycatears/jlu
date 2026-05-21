#include <bits/stdc++.h>
#include <vector>
#include <memory>

using namespace std;

class SaleStrategy
{
public:
    virtual ~SaleStrategy() = default;
    virtual double getPriceWithDiscount(double originalPrice) = 0;
};

class StudentStrategy : public SaleStrategy
{
public:
    double getPriceWithDiscount(double originalPrice)
    {
        cout << "Students get discount!" << endl;
        return 0.7 * originalPrice;
    }
};

class childStrategy : public SaleStrategy
{
public:
    double getPriceWithDiscount(double originalPrice)
    {
        cout << "Children get discount!" << endl;
        return originalPrice >= 30 ? originalPrice - 15 : originalPrice;
    }
};

class VIPStrategy : public SaleStrategy
{
public:
    double getPriceWithDiscount(double originalPrice)
    {
        cout << "VIP get scores and gifts!" << endl;
        return 0.5 * originalPrice;
    }
};

class Cinema
{
private:
    SaleStrategy *strategy = nullptr;

public:
    double getPrice(double price)
    {
        return strategy->getPriceWithDiscount(price);
    }

    void setStrategy(SaleStrategy *s)
    {
        if (this->strategy)
        {
            delete this->strategy;
        }
        this->strategy = s;
    }
};

int main()
{
    Cinema *cinema = new Cinema;
    cinema->setStrategy(new VIPStrategy);
    cout << "VIP: " << cinema->getPrice(50) << endl;
    cinema->setStrategy(new childStrategy);
    cout << "Child: " << cinema->getPrice(48) << endl;
    cout << "Child: " << cinema->getPrice(29) << endl;
    cinema->setStrategy(new StudentStrategy);
    cout << "Student: " << cinema->getPrice(36) << endl;

    return 0;
}