#include <iostream>
#include <iomanip>
#include "Shape.h"
using namespace std;

int main()
{//下面开始测试
    cout<<fixed<<setprecision(4);
    Manage container1;//声明容器类对象
    for(int i=0;i<50;i++)//现在在容器中存放50个不同半径的圆
    {
        container1.ChangeShape(new Circle(i),i);
    }
    for(int i=50;i<100;i++)//在容器中存放50个三角形
    {
        container1.ChangeShape(new Triangle(i-1,i,i+1),i);
    }
    //以下打印测试信息，显示container1中各个图形的指针
    cout<<"&container1="<<&container1<<endl;
    cout<<"Total Area="<<container1.TotalArea()<<endl;
    cout<<"The pointer to Shape#0="<<container1.ShowShape(0)
        <<" and area="<<container1.ShowShape(0)->area()<<endl;
    cout<<"The pointer to Shape#14="<<container1.ShowShape(14)
        <<" and area="<<container1.ShowShape(14)->area()<<endl;
    cout<<"The pointer to Shape#56="<<container1.ShowShape(56)
        <<" and area="<<container1.ShowShape(56)->area()<<endl;
    cout<<"The pointer to Shape#99="<<container1.ShowShape(99)
        <<" and area="<<container1.ShowShape(99)->area()<<endl;

    Manage container2=container1;//拷贝构造容器类

    //以下打印测试信息，以显示进行了深拷贝
    cout<<"&container2="<<&container2<<endl;
    cout<<"Total Area="<<container2.TotalArea()<<endl;
    cout<<"The pointer to Shape#0="<<container2.ShowShape(0)
        <<" and area="<<container2.ShowShape(0)->area()<<endl;
    cout<<"The pointer to Shape#14="<<container2.ShowShape(14)
        <<" and area="<<container2.ShowShape(14)->area()<<endl;
    cout<<"The pointer to Shape#56="<<container2.ShowShape(56)
        <<" and area="<<container2.ShowShape(56)->area()<<endl;
    cout<<"The pointer to Shape#99="<<container2.ShowShape(99)
        <<" and area="<<container2.ShowShape(99)->area()<<endl;
}
