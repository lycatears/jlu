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
class DataFile
{
private:
    string head;
    string body;
    string tail;

public:
    void setHead(string head)

    {
        this->head = head;
    }
    void setBody(string body)

    {
        this->body = body;
    }
    void setTail(string tail)

    {
        this->tail = tail;
    }
    string getHead()

    {
        return head;
    }
    string getBody()

    {
        return body;
    }
    string getTail()

    {
        return tail;
    }
};
class FileBuilder
{
private:
    DataFile *df = new DataFile();

public:
    virtual void buildHead(string deptId, string date) = 0;
    virtual void buildBody(string tableName, vector<string> context) = 0;
    virtual void buildTail(string oper) = 0;
    DataFile *getDataFile()

    {
        return df;
    }
};
class ExcelBuilder : public FileBuilder
{
public:
    void buildHead(string deptId, string date);
    void buildBody(string tableName, vector<string> context);
    void buildTail(string oper);
};
class XMLBuilder : public FileBuilder
{
public:
    void buildHead(string deptId, string date);
    void buildBody(string tableName, vector<string> context);
    void buildTail(string oper);
};
class TextBuilder : public FileBuilder
{
public:
    void buildHead(string deptId, string date)

    {
        getDataFile()->setHead(deptId + ',' + date + '\n');
    }
    void buildBody(string tableName, vector<string> context)

    {
        string resBody = (tableName + '\n');
        for (int i = 0; i < (int)context.size(); i++)

        {
            resBody += (context[i] + ",\n");
        }
        getDataFile()->setBody(resBody);
    }
    void buildTail(string oper)

    {
        getDataFile()->setTail(oper);
    }
};
class Director
{
private:
    FileBuilder *fb;

public:
    void setFileBuilder(FileBuilder *fb)

    {
        this->fb = fb;
    }
    DataFile *construct(string deptId, string date, string tableName, vector<string> context, string oper)

    {
        fb->buildHead(deptId, date);
        fb->buildBody(tableName, context);
        fb->buildTail(oper);
        return fb->getDataFile();
    }
};
int main(void)
{
    Director *director = new Director();
    FileBuilder *fb = new TextBuilder();
    director->setFileBuilder(fb);
    DataFile *df = director->construct("666", "2024-10-12", "Salary", {"9000", "8000", "10000"}, "Bob");
    cout << df->getHead() << df->getBody() << df->getTail();
}