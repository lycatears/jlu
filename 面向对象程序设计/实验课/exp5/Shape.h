#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED
const double pi=3.14;
class Shape
{
public:
    virtual double area()=0;
    virtual Shape* Clone()=0;
    virtual ~Shape(){};
};

class Circle:public Shape
{
public:
    double area();
    Circle();
    Circle(double a);
    Shape* Clone();
private:
    double r;
};

class Triangle:public Shape
{
public:
    double area();
    Triangle();
    Triangle(double m,double n,double p);
    Shape* Clone();
private:
    double a;
    double b;
    double c;
};

class Manage
{
private:
    Shape* a[100];
public:
    Manage();
    ~Manage();
    Manage(const Manage& target);
    void ChangeShape(Shape* s,int pos);
    Shape* ShowShape(int pos) const;
    double TotalArea(void) const;
};


#endif // SHAPE_H_INCLUDED
