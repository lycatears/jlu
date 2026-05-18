#include <iostream>
#include "poly.h"

using namespace std;

int main()
{
    poly A;
    while(1)
    {
        double a=0,b=0;
        cin>>a>>b;
        if(a==0&&b==0)
        {
            break;
        }
        A.AddItem(a,b);
    }
    cout<<"Calculate A(2)="<<A.Calculate(2)<<endl<<"A=";
    A.ShowList();
    poly B;
    while(1)
    {
        double a=0,b=0;
        cin>>a>>b;
        if(a==0&&b==0)
        {
            break;
        }
        B.AddItem(a,b);
    }
    cout<<"\nCalculate B(2)="<<B.Calculate(2)<<endl<<"B=";
    B.ShowList();
    poly C;
    C=A+B;
    cout<<"\nC=A+B,Calculate C(2)="<<C.Calculate(2)<<endl<<"C=";
    C.ShowList();
    poly D=A-B;
    poly E=A*B;
    cout<<"\nD=A-B,Calculate D(2)="<<D.Calculate(2)<<endl<<"D=";
    D.ShowList();
    cout<<"\nE=A*B,Calculate E(2)="<<E.Calculate(2)<<endl<<"E=";
    E.ShowList();
}
