#include <iostream>
#include "camera.h"
using namespace std;

int main()
{
    cout<<"A型行车记录仪：public继承"<<endl;
    DashcamA A;
    A.Menu();
    A.Record();
    cout<<"B型行车记录仪：protected继承"<<endl;
    DashcamB B;
    B.Menu();
    cout<<"C型行车记录仪：private继承"<<endl;
    DashcamC C;
    C.Menu();
    cout<<"D型行车记录仪：组合"<<endl;
    DashcamD D;
    D.Menu();
    D.Record();

    product* a[2];
    a[0]=new Camera;
    a[1]=new DashcamA;

    a[0]->Shoot();
    a[1]->Shoot();
}
