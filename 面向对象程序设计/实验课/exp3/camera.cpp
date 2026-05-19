#include <iostream>
#include "camera.h"

using namespace std;

Camera::Camera()
{
    cout<<"Constructing Camera"<<endl;
}

Camera::~Camera()
{
    cout<<"Destructing Camera"<<endl;
}

void Camera::Encode(void)
{
    cout<<"Encoding Picture"<<endl;
}

void Camera::SetQuality(void)
{
    cout<<"Adjusting Picture Quality"<<endl;
}

void Camera::Shoot(void)
{
    Encode();
    cout<<"Take a Picture"<<endl;
}

DashcamA::DashcamA(void)
{
    cout<<"Constructing DashcamA"<<endl;
}

DashcamA::~DashcamA(void)
{
    cout<<"Destructing DashcamA"<<endl;
}

void DashcamA::Speed(void)
{
    cout<<"Speed is 30km/h"<<endl;
}

void DashcamA::Encode(void)
{
    cout<<"Dashcam Encoding"<<endl;
}

void DashcamA::Record(void)
{
    Shoot();
    cout<<"Recording"<<endl;
}

void DashcamA::Menu(void)
{
    cout<<"DashcamA Menu"<<endl;
}

void DashcamA::Shoot(void)
{
    Encode();
    cout<<"Take a Picture"<<endl;
}

DashcamB::DashcamB(void)
{
    cout<<"Constructing DashcamB"<<endl;
}

DashcamB::~DashcamB(void)
{
    cout<<"Destructing DashcamB"<<endl;
}

void DashcamB::Speed(void)
{
    cout<<"Speed is 30km/h"<<endl;
}

void DashcamB::Encode(void)
{
    cout<<"Dashcam Encoding"<<endl;
}

void DashcamB::Record(void)
{
    cout<<"Recording"<<endl;
}

void DashcamB::Menu(void)
{
    cout<<"DashcamB Menu"<<endl;
}

void DashcamB::Shoot(void)
{
    Encode();
    cout<<"Take a Picture"<<endl;
}

DashcamC::DashcamC(void)
{
    cout<<"Constructing DashcamC"<<endl;
}

DashcamC::~DashcamC(void)
{
    cout<<"Destructing DashcamC"<<endl;
}

void DashcamC::Speed(void)
{
    cout<<"Speed is 30km/h"<<endl;
}

void DashcamC::Encode(void)
{
    cout<<"Dashcam Encoding"<<endl;
}

void DashcamC::Record(void)
{
    cout<<"Recording"<<endl;
}

void DashcamC::Menu(void)
{
    cout<<"DashcamC Menu"<<endl;
}

DashcamD::DashcamD(void)
{
    cout<<"Constructing DashcamD"<<endl;
}

DashcamD::~DashcamD(void)
{
    cout<<"Destructing DashcamD"<<endl;
}

void DashcamD::Speed(void)
{
    cout<<"Speed is 30km/h"<<endl;
}

void DashcamD::Encode(void)
{
    cout<<"Dashcam Encoding"<<endl;
}

void DashcamD::Record(void)
{
    camera.Shoot();
    cout<<"Recording"<<endl;
}

void DashcamD::Menu(void)
{
    cout<<"DashcamD Menu"<<endl;
}
