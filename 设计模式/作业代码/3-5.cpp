#include <iostream>
#include <vector>
using namespace std;
class DBConnections
{
private:
    int instanceId;
    static vector<DBConnections *> dbConnections;
    DBConnections(int instanceId);

public:
    DBConnections() = delete;
    ~DBConnections();
    static DBConnections *getInstance();
    void ConnectionInfo();
};
vector<DBConnections *> DBConnections::dbConnections;
DBConnections::~DBConnections()
{
}
DBConnections::DBConnections(int instanceId)
{
    this->instanceId = instanceId;
}
DBConnections *DBConnections::getInstance()
{
    if (dbConnections.size() >= 3)
    {
        return nullptr;
    }
    DBConnections *newInstance = new DBConnections((int)dbConnections.size());
    dbConnections.push_back(newInstance);
    return newInstance;
}
void DBConnections::ConnectionInfo()
{
    if (this == nullptr)
    {
        cout << "No Instance!" << endl;
        return;
    }
    cout << "DBConnection#" << instanceId << " at" << this << endl;
    return;
}
int main(void)
{
    DBConnections::getInstance()->ConnectionInfo();
    DBConnections::getInstance()->ConnectionInfo();
    DBConnections::getInstance()->ConnectionInfo();
    DBConnections::getInstance()->ConnectionInfo();
    return 0;
}