#include "course.h"

Course::Course()
{

}

Course::Course(QString cname, double credits)
{
    this->cname=cname;
    this->credits=credits;
}

Course::~Course()
{
    foreach (section, sectionList) {
        sectionList.erase(find(sectionList.begin(),sectionList.end(),section));
    }
}

void Course::addSection(CourseSection *section)
{
    sectionList.push_back(section);
}

bool Course::isHavingClass(int week, int period)
{
    for(auto section:sectionList)
    {
        if(section->weekSet.constFind(week) && section->periodSet.constFind(period))
        {
            return true;
        }
    }

    return false;
}

CourseSection::CourseSection(QString cteacher, QString clocation)
{
    this->clocation=clocation;
    this->cteacher=cteacher;
}

void CourseSection::addWeek(int week)
{
    weeks.push_back(week);
    weekSet.insert(week);
}

void CourseSection::addPeriod(int period)
{
    periods.push_back(period);
    periodSet.insert(period);
}
