#ifndef MYWEBENGINEVIEW_H
#define MYWEBENGINEVIEW_H
#include <QWebEngineView>
#include <QWidget>

class MyWebEngineView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit MyWebEngineView(QWidget* parent): QWebEngineView(parent){}

    void injectJavaScript();

    QWebEngineView* createWindow(QWebEnginePage::WebWindowType type);

signals:
    void qtReceiveData(const QVariantList &data);
};

#endif // MYWEBENGINEVIEW_H
