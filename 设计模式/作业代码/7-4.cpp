#include <bits/stdc++.h>
#include <vector>
#include <memory>
using namespace std;
class Manager
{
public:
    void respond()
    {
        cout << "Got it!" << endl;
    }
};
class House
{
protected:
    vector<Manager *> manager;

public:
    void rent()
    {
        cout << "Rented a house at " << this << endl;
        for (int i = 0; i < (int)manager.size(); i++)
        {
            manager[i]->respond();
        }
    }
    void addManager(Manager *m)
    {
        manager.push_back(m);
    }
};
class Apartment : public House
{
};
class Shop : public House
{
};
class Builder
{
public:
    virtual House *build() = 0;
};
class ApartmentBuilder : public Builder
{
public:
    House *build()
    {
        return new Apartment;
    }
};
class ShopBuilder : public Builder
{
public:
    House *build()
    {
        return new Shop;
    }
};
int main()
{
    Builder *b1 = new ApartmentBuilder;
    Builder *b2 = new ShopBuilder;
    House *h1 = b1->build();
    House *h2 = b2->build();
    Manager *m1 = new Manager;
    Manager *m2 = new Manager;
    h1->addManager(m1);
    h2->addManager(m2);
    h1->rent();
    h2->rent();
    return 0;
}