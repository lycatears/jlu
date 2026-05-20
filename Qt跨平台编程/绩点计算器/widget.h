#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "WindowCompositionAttribute.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_resetSubjectButton_clicked();

    void on_overrideShownGradesCheckbox_stateChanged(int arg1);

    void on_confirmAddSubjectButton_clicked();

    void on_clearAllButton_clicked();

    void on_deleteSelectedRowButton_clicked();

    void on_confirmCalculateButton_clicked();

    void on_editGPARulesButton_clicked();

    void on_clearFilePathButton_clicked();

    void on_browseFileButton_clicked();

    void on_saveResultButton_clicked();

    void on_confirmExportButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    HWND hwnd;
    HMODULE huser;
    pfnSetWindowCompositionAttribute setWindowCompositionAttribute;
    QColor acryBackground;	//用来控制背景颜色
    int acryOpacity;	//用来控制透明度

    bool isNightModeEnabled();
};
#endif // WIDGET_H
