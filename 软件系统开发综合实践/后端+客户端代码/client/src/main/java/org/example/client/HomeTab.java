package org.example.client;

import javafx.geometry.Insets;
import javafx.scene.control.Label;
import javafx.scene.control.Tab;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;

import java.util.List;

public class HomeTab extends Tab {
    private Label welcomeLabel;
    private TableView<BorrowRecord> tableView;

    public HomeTab(BookmanClientApp app) {
        setText("首页");

        welcomeLabel = new Label("欢迎您，" + app.uname + "! 您最近借阅了：");
        welcomeLabel.setStyle("-fx-font-size: 18px; -fx-font-weight: bold;");

        tableView = new TableView<>();

        TableColumn<BorrowRecord, String> titleCol = new TableColumn<>("图书标题");
        titleCol.setCellValueFactory(new PropertyValueFactory<>("bookTitle"));

        TableColumn<BorrowRecord, String> borrowDateCol = new TableColumn<>("借阅时间");
        borrowDateCol.setCellValueFactory(new PropertyValueFactory<>("borrowDate"));

        TableColumn<BorrowRecord, String> returnDateCol = new TableColumn<>("归还时间");
        returnDateCol.setCellValueFactory(new PropertyValueFactory<>("returnDate"));

        tableView.getColumns().addAll(titleCol, borrowDateCol, returnDateCol);

        tableView.setPrefHeight(300);
        VBox.setVgrow(tableView, Priority.ALWAYS);
        tableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

        VBox vbox = new VBox(10, welcomeLabel, tableView);
        vbox.setPadding(new Insets(15));
        BorderPane pane = new BorderPane(vbox);

        setContent(pane);

        // 异步加载数据
        loadRecentRecords(app);
    }

    private void loadRecentRecords(BookmanClientApp app) {
        try {
            String url = String.format("http://localhost:8080/userapi/record/user?start=1&end=20&userId=" + app.uid);
            String json = HttpUtil.get(url, app.token);

            List<BorrowRecord> records = JsonUtil.parseBorrowRecords(json);

            javafx.application.Platform.runLater(() -> tableView.getItems().setAll(records));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
