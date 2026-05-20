#include <QPainter>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QJsonValue>
#include "editgparules.h"
#include "gparules.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qstandarditemmodel.h"
#include "ui_editgparules.h"
#include "WindowCompositionAttribute.h"

EditGPARules::EditGPARules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGPARules)
{
//    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    QStandardItemModel* model = new QStandardItemModel();
    QStringList tableHeaders = QStringList()<<"百分制成绩"<<"绩点";
    model->setHorizontalHeaderLabels(tableHeaders);
    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);

    GPARules* rules = new GPARules();
    int ruleConut = rules->getRuleCount();
    for(int i=ruleConut-1;i>=0;i--)
    {
        QList<QStandardItem*> items;
        items.push_back(new QStandardItem(QString::number(rules->getRuleScore(i))));
        items.push_back(new QStandardItem(QString::number(rules->getRuleGPA(i))));
        model->appendRow(items);
    }
    delete rules;
}

EditGPARules::~EditGPARules()
{
    delete ui;
}

void EditGPARules::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setColor(QColor(255,255,255,64));  //前三个参数设定背景颜色的RGB值，最后一个参数设定颜色的透明度
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(acryBackground);
    painter.drawRect(this->rect());
    painter.setOpacity(0.3);
    acryBackground = QColor(255, 220, 240, 64);
    acryOpacity = 30;
    hwnd = HWND(winId());
    huser = GetModuleHandle(L"user32.dll");

    //以下这段代码可以启动Aero效果
    if(huser){
        setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(huser, "SetWindowCompositionAttribute");
        if(setWindowCompositionAttribute){
            //DWORD gradientColor = DWORD(0x50FFFFFF);
            ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
            WINDOWCOMPOSITIONATTRIBDATA data;
            data.Attrib = WCA_ACCENT_POLICY;
            data.pvData = &accent;
            data.cbData = sizeof(accent);
            setWindowCompositionAttribute(hwnd, &data);
        }
    }
}

void EditGPARules::on_cancelButton_clicked()
{
    this->close();
}


void EditGPARules::on_addGPARuleItemButton_clicked()
{
    QList<QStandardItem*> items;
    items.push_back(new QStandardItem(QString::number(ui->GPARuleScore->value())));
    items.push_back(new QStandardItem(QString::number(ui->GPARuleGPA->value())));
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->tableView->model());
    model->appendRow(items);
}


void EditGPARules::on_removeGPARuleButton_clicked()
{
    QTableView* table = ui->tableView;
    auto model = table->model();
    QList<QModelIndex> selectedRows = table->selectionModel()->selectedRows();
    if(selectedRows.empty())
    {
        return;
    }

    for(int i=selectedRows.length()-1;i>=0;i--)
    {
        model->removeRow(selectedRows[i].row());
    }
}


void EditGPARules::on_confirmButton_clicked()
{
    QTableView* table = ui->tableView;
    auto model = static_cast<QStandardItemModel*>(table->model());

    if(model->rowCount()<=0)
    {
        QMessageBox::critical(this,"错误","尚未添加绩点规则，请检查后重试*_*");
        return;
    }

    QList<double> scores;
    QList<double> gpas;
    for(int i=0;i<model->rowCount();i++)
    {
        scores<<model->data(model->index(i,0)).toDouble();
        gpas<<model->data(model->index(i,1)).toDouble();
    }
    std::sort(scores.begin(),scores.end(),std::greater<double>());
    std::sort(gpas.begin(),gpas.end(),std::greater<double>());


    QFile* cfg = new QFile(QDir::cleanPath(QCoreApplication::applicationDirPath()
                                           + QDir::separator()
                                           + "config"
                                           + QDir::separator()
                                           + "default.json"));

    // default values when error in reading config file
    if(!cfg->open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,
                              "错误",
                              "配置文件读写失败，请检查您的用户权限#_#");
        return;
    }
    QJsonArray cfgScoreArray, cfgGPAArray;
    for(int i=0;i<scores.count();i++)
    {
        cfgScoreArray.append(QJsonValue(scores[i]));
        cfgGPAArray.append(QJsonValue(gpas[i]));
    }
    QJsonObject obj;
    obj["min-scores"] = cfgScoreArray;
    obj["gpa"] = cfgGPAArray;
    QJsonDocument doc(obj);
    QByteArray arr = doc.toJson();
    cfg->write(arr);
    cfg->close();
    delete cfg;

    QMessageBox::information(this,
                             "操作成功",
                             "修改绩点规则成功！");
    this->close();
}

