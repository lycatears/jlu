#include <QWidget>
#include <QWebEngineView>
#include "mywebengineview.h"

void MyWebEngineView::injectJavaScript() {
    QString script = R"(
            function getScoresData() {
                var table = document.getElementById("pinnedtabledqxq-index-table");
                var data = [];
                for (var i = 0; i < table.rows.length; i++) {
                    var row = table.rows[i];
                    var rowData = [];
                    for (var j = 0; j < row.cells.length; j++) {
                        rowData.push(row.cells[j].innerText);
                    }
                    data.push(rowData);
                }
                // 发送数据到Qt
                qtReceiveData(data);
            };
        )";
    this->page()->runJavaScript(script);
}

QWebEngineView* MyWebEngineView::createWindow(QWebEnginePage::WebWindowType type)
{
    return this;
}
