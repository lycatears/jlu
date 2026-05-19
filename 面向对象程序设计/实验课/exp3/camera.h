#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include <iostream>
using namespace std;

class product
{
protected:
    virtual void Encode()=0;
public:
    product(){cout<<"product"<<endl;}
    virtual void Shoot()=0;
};

class Camera: public product
{
private:
    virtual void Encode(void);
    int version;
    string code;
public:
    virtual void Shoot(void);
    void SetQuality(void);
    Camera();
    ~Camera();
};

class DashcamA:public Camera
{
private:
    virtual void Encode(void);
    void Speed(void);
public:
    virtual void Shoot(void);
    void Record(void);
    DashcamA();
    ~DashcamA();
    void Menu(void);
};

class DashcamB:protected Camera
{
private:
    virtual void Encode(void);
    void Speed(void);
    void Record(void);
public:
    virtual void Shoot(void);
    DashcamB();
    ~DashcamB();
    void Menu(void);
};

class DashcamC:private Camera
{
private:
    void Encode(void);
    void Speed(void);
    void Record(void);
public:
    DashcamC();
    ~DashcamC();
    void Menu(void);
};

class DashcamD
{
private:
    Camera camera;
    void Encode(void);
    void Speed(void);
public:
    void Record(void);
    DashcamD();
    ~DashcamD();
    void Menu(void);
};

#endif // CAMERA_H_INCLUDED
