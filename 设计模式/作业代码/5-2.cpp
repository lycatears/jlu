#include <iostream>
#include <vector>
using namespace std;
class OS
{
public:
    virtual ~OS() {}
    virtual void osapi() = 0;
};
class Windows : public OS
{
public:
    void osapi()

    {
        cout << "Windows ";
    }
};
class Unix : public OS
{
public:
    void osapi()

    {
        cout << "Unix ";
    }
};
class Linux : public OS
{
public:
    void osapi()

    {
        cout << "Linux ";
    }
};
class Algorithm
{
public:
    virtual ~Algorithm() {}
    virtual void conduct() = 0;
};
class TimeSlice : public Algorithm
{
public:
    void conduct()

    {
        cout << "TimeSlice" << endl;
    }
};
class Robbery : public Algorithm
{
public:
    void conduct()

    {
        cout << "Robbery" << endl;
    }
};
class Conductor
{
private:
    OS *os;
    Algorithm *algo;

public:
    Conductor(OS *os, Algorithm *algo)

    {
        this->algo = algo;
        this->os = os;
    }
    ~Conductor()

    {
        delete os;
        delete algo;
    }
    void conductThread()

    {
        os->osapi();
        algo->conduct();
    }
};
int main(void)
{
    Conductor *con1 = new Conductor(new Windows(), new TimeSlice());
    Conductor *con2 = new Conductor(new Linux(), new Robbery());
    Conductor *con3 = new Conductor(new Unix(), new TimeSlice());
    con1->conductThread();
    con2->conductThread();
    con3->conductThread();
    delete con1;
    delete con2;
    delete con3;
    return 0;
}