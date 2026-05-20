#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtAlgorithms>
#include <QFile>
#include <QDir>

#include "gparules.h"
#include "qapplication.h"

GPARules::GPARules(QString ruleFilePath)
{
    QFile* cfg = new QFile(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + ruleFilePath));

    // default values when error in reading config file
    if(!cfg->open(QIODevice::ReadOnly))
    {
        minScore<<0<<60<<64<<67<<70<<74<<77<<80<<84<<87<<90;
        gpa<<0<<1.0<<1.3<<1.7<<2.0<<2.3<<2.7<<3.0<<3.3<<3.7<<4.0;
        return;
    }

    QByteArray data = cfg->readAll();
    QString gpaRuleString(data);
    cfg->close();
    delete cfg;

    QJsonObject jsonObj;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        jsonObj = doc.object();
    } else {
        minScore<<0<<60<<64<<67<<70<<74<<77<<80<<84<<87<<90;
        gpa<<0<<1.0<<1.3<<1.7<<2.0<<2.3<<2.7<<3.0<<3.3<<3.7<<4.0;
        return;
    }

    QJsonArray scoreStandardArray = jsonObj["min-scores"].toArray();
    QJsonArray gpaStandardArray = jsonObj["gpa"].toArray();
    for(int i=0;i<scoreStandardArray.count();i++)
    {
        minScore<<scoreStandardArray.at(i).toDouble(0);
        gpa<<gpaStandardArray.at(i).toDouble(0);
    }

    std::sort(minScore.begin(),minScore.end());
    std::sort(gpa.begin(),gpa.end());
}

double GPARules::getGPA(double score) const
{
    for(int i = minScore.length()-1; i>=0; i--)
    {
        if(score>=minScore[i])
        {
            return gpa[i];
        }
    }
    return 0.0;
}

int GPARules::getRuleCount() const
{
    return gpa.length();
}

double GPARules::getRuleScore(int index) const
{
    return minScore.at(index);
}

double GPARules::getRuleGPA(int index) const
{
    return gpa.at(index);
}
