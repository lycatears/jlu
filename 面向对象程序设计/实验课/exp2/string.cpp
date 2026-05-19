#include <iostream>
#include "string.h"

string::string()
{
    //默认构造函数
    pString=NULL;
}

string::string(const char* pSource)
{
    //使用C语言风格字符串初始化string对象
    int src_length=0;
    const char* p=pSource;
    while(p!=NULL&&*p!='\0')
    {
        src_length++;
        p++;
    }
    pString=new char[src_length+1];//开辟堆内存，并为终止符预留空间
    char* q=pString;
    p=pSource;
    while(p!=NULL&&*p!='\0')
    {
        *q=*p;
        p++;
        q++;
    }
    *q='\0';
    return;
}

string::string(string const& str)
{
    //用string对象初始化string对象
    const char* q=str.pString;
    pString=new char[str.length()+1];
    char* p=pString;

    while(p!=NULL&&q!=NULL&&*q!='\0')
    {
        *p=*q;
        p++;
        q++;
    }
    *p='\0';
    return;
}

string::~string()
{
    //析构函数，同时删除堆内存中的字符串
    delete[] pString;
}

void string::operator=(const char* pSource)
{
    //用C语言风格字符串赋值string对象
    int src_length=0;
    const char* p=pSource;
    while(p!=NULL&&*p!='\0')
    {
        src_length++;
        p++;
    }//统计源字符串长度

    pString=new char[src_length+1];//开辟堆内存存储字符串
    char* q=pString;
    p=pSource;
    while(p!=NULL&&*p!='\0')
    {
        *q=*p;
        p++;
        q++;
    }
    *q='\0';
    return;
}

void string::ShowString(void)
{
    //显示字符串内容
    std::cout<<pString<<std::endl;
    return;
}

int string::length() const
{
    //定义常成员函数，用于查看字符串长度
    const char* p=pString;
    int str_length=0;
    while(p!=NULL&&*p!='\0')
    {
        str_length++;
        p++;
    }
    return str_length;
}

string& string::operator=(string const& str)
{
    //重载赋值运算符，用string对象赋值string对象
    if(this==&str)
    {
        return *this;
    }

    delete[] this->pString;
    const char* pSource=str.pString;

    pString=new char[str.length()+1];
    char* p=pString;
    while(pSource!=NULL&&*pSource!='\0')
    {
        *p=*pSource;
        p++;
        pSource++;
    }
    *p='\0';
    return *this;
}

string& string::cat(string const& str)
{
    //连接两个字符串
    const char* q=str.pString;
    char* p=this->pString;
    char* new_string=new char[length()+str.length()+1],*r=new_string;
    //求出新字符串的长度，并为终止符预留位置
    if(new_string==NULL)
    {
        std::cout<<"Out of memory!"<<std::endl;
        return *this;
    }

    while(r!=NULL&&p!=NULL&&*p!='\0')
    {
        *r=*p;
        p++;
        r++;
    }
    while(r!=NULL&&q!=NULL&&*q!='\0')
    {
        *r=*q;
        q++;
        r++;
    }
    *r='\0';

    delete[] pString;//删除连接前的字符串
    pString=new_string;
    return *this;
}


std::ostream & operator<<(std::ostream & os,const string &str)
{
    os<<str.pString;
	return os;

}

std::istream & operator>>(std::istream & is,string & str)
{
    char temp[1024]={0};
    is.get(temp,1024);
    str=temp;

    while (is && is.get() !='\n')
    {
        continue;
    }
    return is;
}
