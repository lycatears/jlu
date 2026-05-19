#include <iostream>
#include "string.h"
using std::cout;
using std::cin;
using std::endl;

int main(void)
{
    string a="吉林大学";
    string b="中心校区";
    string c="南岭校区";
    string d="南湖校区";
    string e;
    e="新民校区";

    cout<<a<<endl;
    string f=a;
    cout<<f<<endl;
    f.cat(b);
    cout<<f<<endl;
    cin>>c;
    cout<<c<<endl;
    a=a;
    a.cat(a);
    cout<<a<<endl;

    return 0;
}

