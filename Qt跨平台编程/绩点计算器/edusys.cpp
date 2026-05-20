#include <QMessageBox>
#include <QWebEngineFrame>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItem>
#include <QTableView>
#include <QFile>
#include <QDir>
#include "edusys.h"
#include "mywebengineview.h"
#include "ui_edusys.h"

Edusys::Edusys(QWidget *parent, QTableView* table) :
    QDialog(parent),
    ui(new Ui::Edusys),
    table(table)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(ui->browserContainer);
    browser = new MyWebEngineView(ui->browserContainer);
    layout->addWidget(browser);
    browser->injectJavaScript();

    //    connect(button, &QPushButton::clicked, this, &MainWindow::openBrowser);
//    connect(browser, &MyWebEngineView::qtReceiveData, this, &Edusys::receiveData);
}

Edusys::~Edusys()
{
    delete browser;
    delete ui;
}

void Edusys::on_switchToEdusysButton_clicked()
{
    QString url = ui->edusysUrl->text();
    if(!url.startsWith("https://",Qt::CaseInsensitive))
    {
        url="https://"+url;
    }
    browser->setUrl(QUrl(url));
}

void Edusys::receiveData(const QVariantList &data) {
    // 把获取的数据展示到文本框中
    QString displayText;
    for (const QVariant &row : data) {
        displayText += row.toStringList().join(", ") + "\n";
    }
    QMessageBox::information(this,"test",displayText);
}


void Edusys::on_importScoresButton_clicked(QString scriptPath){
    QFile scriptFile(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + scriptPath));
    if(!scriptFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"错误","找不到导入脚本文件，请检查config目录。");
        return;
    }
    QByteArray scriptBytes = scriptFile.readAll();
    QString script(scriptBytes);

    browser->page()->runJavaScript(script, 0, [=](const QVariant& data)
                                   {
                                       qDebug()<<data.toString();
                                       QJsonDocument doc = QJsonDocument::fromJson(data.toString().toUtf8());
                                       if(!doc.isArray())
                                       {
                                           QMessageBox::critical(this,
                                                                 "错误",
                                                                 "数据格式错误，请检查导入数据的配置是否正确。");
                                           return;
                                       }
                                       QJsonArray array = doc.array();
                                       for(int i=0;i<array.count();i++)
                                       {
                                           if(!array.at(i).isObject())
                                           {
                                               QMessageBox::critical(this,
                                                                     "错误",
                                                                     "数据格式错误，请检查导入数据的配置是否正确。");
                                               return;
                                           }
                                           QJsonObject obj = array.at(i).toObject();
                                           QString subjectName = obj["subject-name"].toString("?");
                                           QString score = obj["score"].toString("0");
                                           QString credit = obj["credit"].toString("0");
                                           QString gpa = obj["gpa"].toString("0");

                                           auto model = static_cast<QStandardItemModel*>(table->model());
                                           QList<QStandardItem*> items;
                                           items << new QStandardItem(subjectName)
                                                 << new QStandardItem(score)
                                                 << new QStandardItem(credit)
                                                 << new QStandardItem(gpa);
                                           model->appendRow(items);
                                       }

                                       QMessageBox::information(this,"成功导入",QString("成功导入了%1行。").arg(array.count()));
                                   });
}


void Edusys::on_refreshButton_clicked()
{
    browser->page()->runJavaScript("location.reload();");
}

void Edusys::on_exitButton_clicked()
{
    this->close();
}

