#ifndef EDITGPARULES_H
#define EDITGPARULES_H

#include <QDialog>
#include "WindowCompositionAttribute.h"

namespace Ui {
class EditGPARules;
}

class EditGPARules : public QDialog
{
    Q_OBJECT

public:
    explicit EditGPARules(QWidget *parent = nullptr);
    ~EditGPARules();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_cancelButton_clicked();

    void on_addGPARuleItemButton_clicked();

    void on_removeGPARuleButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::EditGPARules *ui;
    HWND hwnd;
    HMODULE huser;
    pfnSetWindowCompositionAttribute setWindowCompositionAttribute;
    QColor acryBackground;	//用来控制背景颜色
    int acryOpacity;	//用来控制透明度
};

#endif // EDITGPARULES_H
