#ifndef EDUSYS_H
#define EDUSYS_H

#include <QWidget>
#include <QDialog>
#include <QTableView>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebChannel>
#include "mywebengineview.h"

namespace Ui {
class Edusys;
}

class Edusys : public QDialog
{
    Q_OBJECT

public:
    explicit Edusys(QWidget *parent = nullptr, QTableView* table = nullptr);
    ~Edusys();

private slots:
    void on_switchToEdusysButton_clicked();

    void receiveData(const QVariantList &data);

    void on_importScoresButton_clicked(QString scriptPath = ".\\config\\import.js");

    void on_refreshButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::Edusys *ui;
    MyWebEngineView* browser;
    QTableView* table;
};

#endif // Edusys_H
