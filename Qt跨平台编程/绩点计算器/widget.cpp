#include "widget.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "ui_widget.h"
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QStandardItemModel>
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonObject>
#include <windows.h>
#include "gparules.h"
#include "editgparules.h"
#include "edusys.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //    setWindowFlags(Qt::FramelessWindowHint);
    //    setAttribute(Qt::WA_StyledBackground);
    //    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    QStandardItemModel* model = new QStandardItemModel();
    ui->previewTable->setModel(model);
    QStringList tableHeaders = QStringList()<<"课程名称"<<"成绩"<<"学分"<<"绩点";
                               model->setHorizontalHeaderLabels(tableHeaders);
    this->setWindowIcon(QIcon(":/res/eyes.png"));
    this->setWindowTitle("猫娘计算器 v1.1.54");

    if(!isNightModeEnabled())
    {
        ui->previewTable->setStyleSheet("alternate-background-color: rgb(255, 217, 235);");
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_checkBox_stateChanged(int arg1)
{
    qDebug()<<arg1;
}


void Widget::on_resetSubjectButton_clicked()
{
    ui->subjectName->setText("");
    ui->grade->setValue(90.0l);
    ui->credit->setValue(3);
}

void Widget::paintEvent(QPaintEvent *event){
    //    QPainter painter(this);
    //    painter.setRenderHint(QPainter::Antialiasing);
    //    QPen pen;
    //    pen.setColor(QColor(255,255,255,127));  //前三个参数设定背景颜色的RGB值，最后一个参数设定颜色的透明度
    //    pen.setStyle(Qt::SolidLine);
    //    pen.setWidth(1);
    //    painter.setPen(pen);
    //    painter.setBrush(acryBackground);
    //    painter.drawRect(this->rect());
    //    painter.setOpacity(0.5);
    //    acryBackground = QColor(255, 220, 240, 127);
    //    acryOpacity = 50;
    //    hwnd = HWND(winId());
    //    huser = GetModuleHandle(L"user32.dll");

    //以下这段代码可以启动Aero效果
    //    if(huser){
    //        setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(huser, "SetWindowCompositionAttribute");
    //        if(setWindowCompositionAttribute){
    //            //DWORD gradientColor = DWORD(0x50FFFFFF);
    //            ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
    //            WINDOWCOMPOSITIONATTRIBDATA data;
    //            data.Attrib = WCA_ACCENT_POLICY;
    //            data.pvData = &accent;
    //            data.cbData = sizeof(accent);
    //            setWindowCompositionAttribute(hwnd, &data);
    //        }
    //    }
}

void Widget::on_overrideShownGradesCheckbox_stateChanged(int arg1)
{

}


void Widget::on_confirmAddSubjectButton_clicked()
{
    QString subjectName = ui->subjectName->text();
    double score = ui->grade->value();
    double credit = ui->credit->value();
    GPARules* rule = new GPARules();
    QStringList data = QStringList() << subjectName
                                     << QString::number(score)
                                     << QString::number(credit)
                                     << QString::number(rule->getGPA(score));

    QTableView* table = ui->previewTable;
    auto model = static_cast<QStandardItemModel*>(table->model());
    QList<QStandardItem*> items;
    for(int i=0;i<data.length();i++){
        items.push_back(new QStandardItem(data[i]));
    }
    model->appendRow(items);
    delete rule;
}


void Widget::on_clearAllButton_clicked()
{
    QTableView* table = ui->previewTable;
    auto model = table->model();
    model->removeRows(0,model->rowCount());
}


void Widget::on_deleteSelectedRowButton_clicked()
{
    QTableView* table = ui->previewTable;
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


void Widget::on_confirmCalculateButton_clicked()
{
    QTableView* table = ui->previewTable;
    auto model = static_cast<QStandardItemModel*>(table->model());
    GPARules* rule = new GPARules();
    if(model->rowCount()<=0)
    {
        delete rule;
        QMessageBox::critical(this,"错误","尚未添加科目成绩，请检查后重试X_X");
        return;
    }

    QList<double> scores;
    QList<double> gpas;
    QList<double> credits;
    double totalCredits=0;

    for(int i=0;i<model->rowCount();i++)
    {
        scores<<model->data(model->index(i,1)).toDouble();
        gpas<<model->data(model->index(i,3)).toDouble();
        credits<<model->data(model->index(i,2)).toDouble();
        totalCredits+=model->data(model->index(i,2)).toDouble();
        //        ui->progressBar->setValue(50*(i+1)/model->rowCount());
    }

    double totalWeighedGPA=0,totalNumericScore=0,totalWeighedScore=0;
    for(int i=0;i<model->rowCount();i++)
    {
        totalWeighedGPA+=gpas[i]*credits[i];
        totalNumericScore+=scores[i];
        totalWeighedScore+=scores[i]*credits[i];
        //        ui->progressBar->setValue(50*(i+1)/model->rowCount()+50);
    }

    ui->GPALcd->display(totalWeighedGPA/totalCredits);
    ui->weighedAvgLcd->display(totalWeighedScore/totalCredits);
    ui->numericAvgLcd->display(totalNumericScore/model->rowCount());

    delete rule;
}


void Widget::on_editGPARulesButton_clicked()
{
    QDialog* dlg = new EditGPARules();
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setWindowTitle("绩点规则修改");
    dlg->setWindowIcon(QIcon(":/res/edit.png"));
    dlg->show();
}


void Widget::on_clearFilePathButton_clicked()
{
    ui->filePath->setText("");
}


void Widget::on_browseFileButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "打开",
                                                QDir::homePath(),
                                                "JSON文件 (*.json)");
    if(!path.isEmpty())
    {
        ui->filePath->setText(path);
    }
}


void Widget::on_saveResultButton_clicked()
{
    QTableView* table = ui->previewTable;
    auto model = static_cast<QStandardItemModel*>(table->model());
    if(model->rowCount()<=0)
    {
        QMessageBox::critical(this,"错误","尚未添加科目成绩，请检查后重试X_X");
        return;
    }

    QJsonArray array;
    int rowCount = model->rowCount();
    for(int i=0;i<rowCount;i++)
    {
        QJsonObject obj;
        obj["subject-name"]=model->data(model->index(i,0)).toString();
        obj["score"]=model->data(model->index(i,1)).toString();
        obj["credit"]=model->data(model->index(i,2)).toString();
        obj["gpa"]=model->data(model->index(i,3)).toString();
        array.append(obj);
    }

    QJsonDocument doc(array);
    QByteArray bytes = doc.toJson();
    QString savePath = QFileDialog::getSaveFileName(this,
                                                    "选择保存路径",
                                                    QDir::homePath(),
                                                    "JSON文件 (*.json)");

    QFile file(savePath);
    if(!file.open(QIODeviceBase::WriteOnly))
    {
        QMessageBox::critical(this,
                              "错误",
                              "无法在您指定的位置保存文件，用户权限可能受限。");
        return;
    }
    file.write(bytes);
    file.close();
    QMessageBox::information(this,
                             "操作成功",
                             "成功保存了本次计算结果！");
    return;
}


void Widget::on_confirmExportButton_clicked()
{
    QString exportFilePath = ui->filePath->text();
    QFile file(exportFilePath);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        QMessageBox::critical(this,
                              "错误",
                              "指定的文件不存在，请检查后重试。");
        file.close();
        return;
    }
    QByteArray savedScoreBytes = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(savedScoreBytes);
    if(!doc.isArray())
    {
        QMessageBox::critical(this,
                              "错误",
                              "文件格式错误，保存的文件可能已经损坏。");
        return;
    }
    QJsonArray array = doc.array();

    if(ui->overrideShownGradesCheckbox->checkState() == Qt::Checked)
    {
        this->on_clearAllButton_clicked();
    }

    for(int i=0;i<array.count();i++)
    {
        if(!array.at(i).isObject())
        {
            QMessageBox::critical(this,
                                  "错误",
                                  "文件格式错误，保存的文件可能已经损坏。");
            return;
        }
        QJsonObject obj = array.at(i).toObject();
        QString subjectName = obj["subject-name"].toString("?");
        QString score = obj["score"].toString("0");
        QString credit = obj["credit"].toString("0");
        QString gpa = obj["gpa"].toString("0");

        QTableView* table = ui->previewTable;
        auto model = static_cast<QStandardItemModel*>(table->model());
        QList<QStandardItem*> items;
        items <<new QStandardItem(subjectName)
              <<new QStandardItem(score)
              <<new QStandardItem(credit)
              <<new QStandardItem(gpa);
        model->appendRow(items);
    }
}


void Widget::on_pushButton_clicked()
{
    auto choice = QMessageBox::question(this,
                                        "确认操作",
                                        QString("将打开教务管理系统导入成绩数据。\n")+
                          QString("点击“确定”按钮，代表您理解并同意授权本次操作。数据仅用作计算成绩，不会进行任何上传操作。\n")+
                          QString("若确定要打开教务系统导入数据，请点击确定；否则请点击取消。\n")+
                          QString("请在页面上出现成绩表格后，再点击导入。"));
    if(choice==QMessageBox::No)
    {
        return;
    }

    QDialog* dlg = new Edusys(this, ui->previewTable);
    dlg->setWindowTitle("导入教务数据");
    dlg->setWindowIcon(QIcon(":/res/download.png"));
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();

    if(ui->overrideShownGradesCheckbox->checkState() == Qt::Checked)
    {
        this->on_clearAllButton_clicked();
    }
}

bool Widget::isNightModeEnabled()
{
    HKEY hKey;
    LONG lResult = RegOpenKeyEx(HKEY_CURRENT_USER,
                                L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                                0, KEY_READ, &hKey);

    if (lResult != ERROR_SUCCESS) {
        QMessageBox::warning(this,"警告","您正在使用的操作系统版本较低，尚未支持夜间模式，可能导致显示异常。");
        return false;
    }

    DWORD dwValue = 0;
    DWORD dwSize = sizeof(dwValue);
    lResult = RegQueryValueEx(hKey, L"AppsUseLightTheme", NULL, NULL, (LPBYTE)&dwValue, &dwSize);

    RegCloseKey(hKey);

    if (lResult == ERROR_SUCCESS) {
        return dwValue == 0; // 0 means dark mode is enabled, 1 means light mode
    }

    return false;
}
