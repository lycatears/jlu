#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Device
{
public:
    virtual void response() = 0;
};
class WarningLight : public Device
{
public:
    void flicker()
    {
        cout << "WARNING LIGHT FLICKING!!!" << endl;
    }
    void response()
    {
        flicker();
    }
};
class Alarm : public Device
{
public:
    void alarm()
    {
        cout << "ALARM!!!" << endl;
    }
    void response()
    {
        alarm();
    }
};
class SecurityDoor : public Device
{
public:
    void open()
    {
        cout << "SECRURITY DOOR OPENED!!!" << endl;
    }
    void response()
    {
        open();
    }
};
class InsulatedDoor : public Device
{
public:
    void close()
    {
        cout << "INSULULATED DOOR CLOSED!!!" << endl;
    }
    void response()
    {
        close();
    }
};
class Detector
{
private:
    vector<Device *> dev;

public:
    virtual void Attach(Device *d)
    {
        dev.push_back(d);
    }
    virtual void Detach(Device *d)
    {
        dev.erase(find(dev.begin(), dev.end(), d));
    }
    virtual void notify()
    {
        for (int i = 0; i < (int)dev.size(); i++)
        {
            dev[i]->response();
        }
    }
};
class FireDetector : public Detector
{
public:
    void detect()
    {
        cout << "DETECTED FIRE!!!" << endl;
        notify();
    }
};
int main(void)
{
    WarningLight *wl = new WarningLight;
    Alarm *ala = new Alarm;
    SecurityDoor *sd = new SecurityDoor;
    InsulatedDoor *isd = new InsulatedDoor;
    FireDetector *fd = new FireDetector;
    fd->Attach(wl);
    fd->Attach(ala);
    fd->Attach(sd);
    fd->Attach(isd);
    fd->detect();
    return 0;
}