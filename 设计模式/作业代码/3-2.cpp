#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <ctime>
#include <algorithm>
using namespace std;
class SummerUniform
{
private:
    string style;

public:
    virtual void setStyle(string style)

    {
        this->style = style;
    }
    virtual string getStyle(void)

    {
        return style;
    }
};
class SummerUniform1 : public SummerUniform
{
};
class SummerUniform2 : public SummerUniform
{
};
class SummerUniform3 : public SummerUniform
{
};
class AutumnUniform
{
private:
    string style;

public:
    virtual void setStyle(string style)

    {
        this->style = style;
    }
    virtual string getStyle(void)

    {
        return style;
    }
};
class AutumnUniform1 : public AutumnUniform
{
};
class AutumnUniform2 : public AutumnUniform
{
};
class AutumnUniform3 : public AutumnUniform
{
};
class School
{
public:
    virtual AutumnUniform *getAutumnUniform() = 0;
    virtual SummerUniform *getSummerUniform() = 0;
};
class School1 : public School
{
public:
    virtual AutumnUniform *getAutumnUniform()

    {
        AutumnUniform *au = new AutumnUniform1;
        au->setStyle("一中 长袖上衣 秋季长裤");
        return au;
    }
    virtual SummerUniform *getSummerUniform()

    {
        SummerUniform *su = new SummerUniform1;
        su->setStyle("一中 短袖衬衣 短袖T恤 夏季长裤 短裤");
        return su;
    }
};
class School2 : public School
{
public:
    virtual AutumnUniform *getAutumnUniform()

    {
        AutumnUniform *au = new AutumnUniform2;
        au->setStyle("二中 长袖上衣 秋季长裤");
        return au;
    }
    virtual SummerUniform *getSummerUniform()

    {
        SummerUniform *su = new SummerUniform2;
        su->setStyle("二中 短袖衬衣 短袖T恤 夏季长裤 短裤");
        return su;
    }
};
class School3 : public School
{
public:
    virtual AutumnUniform *getAutumnUniform()

    {
        AutumnUniform *au = new AutumnUniform3;
        au->setStyle("三中 长袖上衣 秋季长裤");
        return au;
    }
    virtual SummerUniform *getSummerUniform()

    {
        SummerUniform *su = new SummerUniform3;
        su->setStyle("三中 短袖衬衣 短袖T恤 夏季长裤 短裤");
        return su;
    }
};
int main(void)
{
    char schoolName[100] = {0}, seasonName[100] = {0};
    scanf("%s+%s", schoolName, seasonName);
    string sch = string(schoolName);
    string sea = string(seasonName);
    School *school = nullptr;
    AutumnUniform *au = nullptr;
    SummerUniform *su = nullptr;
    if (schoolName == string("一中"))

    {
        school = new School1;
    }
    else if (schoolName == string("二中"))

    {
        school = new School2;
    }
    else
    {
        school = new School3;
    }
    if (seasonName == string("夏季"))

    {
        su = school->getSummerUniform();
        cout << su->getStyle();
    }
    else
    {
        au = school->getAutumnUniform();
        cout << au->getStyle();
    }
    return 0;
}