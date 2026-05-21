#include <iostream>
#include <vector>
using namespace std;
class Dish
{
private:
    string name;

public:
    Dish(string name)

    {
        this->name = name;
    }
    virtual void order()

    {
        cout << name << endl;
    }
    virtual void add(Dish *d)

    {
    }
    virtual void remove(int i)

    {
    }
};
class ConcreteDish : public Dish
{
public:
    ConcreteDish(string name) : Dish(name) {};
};
class Menu : public Dish
{
private:
    vector<Dish *> dish;

public:
    Menu(string name) : Dish(name) {};
    void order()

    {
        for (int i = 0; i < (int)dish.size(); i++)

        {
            dish[i]->order();
        }
    }
    void add(Dish *d)

    {
        dish.push_back(d);
    }
    void remove(int i)

    {
        dish.erase(dish.begin() + i);
    }
};
int main(void)
{
    Dish *d1 = new ConcreteDish("Vegetable");
    Dish *d2 = new ConcreteDish("Hamburger");
    Dish *d3 = new ConcreteDish("Meat");
    Dish *d4 = new ConcreteDish("Spaghetti");
    Dish *d5 = new ConcreteDish("Welcome wine");
    Dish *d6 = new ConcreteDish("Pancake");
    Dish *d7 = new ConcreteDish("Cake");
    Dish *m1 = new Menu("Main menu");
    Dish *m2 = new Menu("Pancake");
    Dish *m3 = new Menu("Restaurant");
    Dish *m4 = new Menu("Dessert");
    m4->add(d2);
    m4->add(d7);
    m2->add(d6);
    m3->add(m4);
    m3->add(d1);
    m3->add(d3);
    m3->add(d4);
    m3->add(d5);
    m1->add(m2);
    m1->add(m3);

    d2->order();
    d6->order();
    m3->order();
    m2->order();
    return 0;
}