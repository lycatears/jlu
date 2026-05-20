#ifndef GPARULES_H
#define GPARULES_H
#include <QList>
#include <QDialog>


class GPARules
{
public:
    GPARules(QString ruleFilePath = ".\\config\\default.json");
    double getGPA(double score) const;
    int getRuleCount() const;
    double getRuleScore(int index) const;
    double getRuleGPA(int index) const;
private:
    QList<double> minScore;
    QList<double> gpa;
};

#endif // GPARULES_H
