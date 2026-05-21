#include <iostream>
using namespace std;
class WMPPlayer
{
public:
    string playVideo()

    {
        return "wmp video";
    }
};
class RealPlayer
{
public:
    string playvideo()

    {
        return "RealPlayer video";
    }
};
class Monitor
{
public:
    virtual void playVideo()

    {
        cout << "playing" << endl;
    }
};
class WMPAdapter : public Monitor
{
private:
    WMPPlayer *wmpPlayer;

public:
    WMPAdapter(WMPPlayer *wmpPlayer)

    {
        this->wmpPlayer = wmpPlayer;
    }
    ~WMPAdapter()

    {
        delete wmpPlayer;
    }
    string transformVideo()

    {
        return "transformed " + wmpPlayer->playVideo();
    }
    void playVideo()

    {
        cout << "playing " + transformVideo() << endl;
    }
};
class RealAdapter : public Monitor
{
private:
    RealPlayer *realPlayer;

public:
    RealAdapter(RealPlayer *realPlayer)

    {
        this->realPlayer = realPlayer;
    }
    ~RealAdapter()

    {
        delete realPlayer;
    }
    string transformVideo()

    {
        return "transformed " + realPlayer->playvideo();
    }
    void playVideo()

    {
        cout << "playing " + transformVideo() << endl;
    }
};
int main()
{
    Monitor *m1 = new WMPAdapter(new WMPPlayer);
    Monitor *m2 = new RealAdapter(new RealPlayer);
    m1->playVideo();
    m2->playVideo();
    delete m1;
    delete m2;
    return 0;
}