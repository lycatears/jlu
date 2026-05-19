#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
#include <iostream>

class string
{
private:
    char* pString;
public:
    string();
    string(const char* pSource);
    string(string const& str);
    ~string();
    void ShowString(void);
    int length(void) const;
    string& cat(string const & str);
    void operator=(const char* pSource);
    string& operator=(string const& str);
	friend std::ostream & operator<<(std::ostream & os,const string &st);
	friend std::istream & operator>>(std::istream & is,string & s);
};

#endif // STRING_H_INCLUDED
