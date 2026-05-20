#ifndef COURSE_H
#define COURSE_H
#include <QString>
#include <QList>
#include <QSet>

class Course
{
public:
    Course();
    Course(QString cname, double credits);
    ~Course();
    void addSection(CourseSection* section);
    bool isHavingClass(int week, int period);

private:
    QString cname;
    double credits;
    QList<CourseSection*> sectionList;
};

class CourseSection
{
private:
    QList<int> weeks;
    QSet<int> weekSet;

    QList<int> periods;
    QSet<int> periodSet;

    QString cteacher;
    QString clocation;

public:
    CourseSection(QString cteacher, QString clocation);
    void addWeek(int week);
    void addPeriod(int period);
};

#endif // COURSE_H
