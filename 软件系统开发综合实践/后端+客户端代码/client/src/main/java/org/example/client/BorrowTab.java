package org.example.client;

import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;

import java.net.URLEncoder;
import java.util.List;

public class BorrowTab extends Tab {

    private TableView<Book> tableView;

    public BorrowTab(BookmanClientApp app) {
        setText("借书");

        // 🔍 搜索框与按钮
        TextField keywordField = new TextField();
        keywordField.setPromptText("请输入关键词（如书名、作者）");

        Button searchBtn = new Button("搜索");
        HBox searchBox = new HBox(10, keywordField, searchBtn);
        searchBox.setAlignment(Pos.CENTER_LEFT);

        // 📋 表格展示
        tableView = new TableView<>();
        tableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        tableView.setPrefHeight(300);
        VBox.setVgrow(tableView, Priority.ALWAYS);

        TableColumn<Book, String> idCol = new TableColumn<>("编号");
        idCol.setCellValueFactory(new PropertyValueFactory<>("bookId"));

        TableColumn<Book, String> titleCol = new TableColumn<>("书名");
        titleCol.setCellValueFactory(new PropertyValueFactory<>("bookTitle"));

        TableColumn<Book, String> authorCol = new TableColumn<>("作者");
        authorCol.setCellValueFactory(new PropertyValueFactory<>("bookAuthor"));

        TableColumn<Book, String> yearCol = new TableColumn<>("出版时间");
        yearCol.setCellValueFactory(new PropertyValueFactory<>("bookYear"));

        TableColumn<Book, Integer> stockCol = new TableColumn<>("库存");
        stockCol.setCellValueFactory(new PropertyValueFactory<>("bookStock"));

        TableColumn<Book, Integer> descriptionCol = new TableColumn<>("简介");
        descriptionCol.setCellValueFactory(new PropertyValueFactory<>("description"));

        tableView.getColumns().addAll(idCol, titleCol, authorCol, yearCol, descriptionCol, stockCol );

        // ✏️ 借书区域
        TextField bookIdField = new TextField();
        bookIdField.setPromptText("请输入要借阅的图书编号");

        Button borrowBtn = new Button("确认借阅");
        HBox borrowBox = new HBox(10, bookIdField, borrowBtn);
        borrowBox.setAlignment(Pos.CENTER_LEFT);

        // 绑定搜索按钮
        searchBtn.setOnAction(e -> {
            String keyword = keywordField.getText().trim();
            if (!keyword.isEmpty()) {
                searchBooks(keyword, app);
            }
        });

        // 绑定借书按钮（逻辑后续可完善）
        borrowBtn.setOnAction(e -> {
            String bookIdText = bookIdField.getText().trim();
            if (!bookIdText.matches("\\d+")) {
                showAlert("请输入合法的图书编号！");
                return;
            }
            int bookId = Integer.parseInt(bookIdText);
            borrowBook(bookId, app);
        });

        VBox layout = new VBox(10, searchBox, tableView, borrowBox);
        layout.setPadding(new Insets(15));
        setContent(layout);
    }

    private void searchBooks(String keyword, BookmanClientApp app) {
        new Thread(() -> {
            try {
                String url = "http://localhost:8080/userapi/book/search?keyword=" + URLEncoder.encode(keyword, "UTF-8");
                String json = HttpUtil.get(url, app.token);
                List<Book> books = JsonUtil.parseBooks(json);
                Platform.runLater(() -> tableView.getItems().setAll(books));
            } catch (Exception e) {
                e.printStackTrace();
                Platform.runLater(() -> showAlert("搜索失败：" + e.getMessage()));
            }
        }).start();
    }

    private void borrowBook(int bookId, BookmanClientApp app) {
        new Thread(() -> {
            try {
                String url = String.format("http://localhost:8080/userapi/record?bookId=%d&userId=%d", bookId, app.uid);
                String json = HttpUtil.post(url, "", app.token); // POST 方法，body 可为空
                if(json.contains("0")){
                    Platform.runLater(() -> showAlert("借书成功"));
                }else{
                    Platform.runLater(() -> showAlert("借书失败：库存不足！"));
                }
            } catch (Exception e) {
                e.printStackTrace();
                Platform.runLater(() -> showAlert("借书失败：" + e.getMessage()));
            }
        }).start();
    }

    private void showAlert(String msg) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION, msg, ButtonType.OK);
        alert.setHeaderText(null);
        alert.showAndWait();
    }
}
