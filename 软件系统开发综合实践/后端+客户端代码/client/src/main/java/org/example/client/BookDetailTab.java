package org.example.client;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

import java.util.List;
import java.util.stream.Collectors;

public class BookDetailTab extends Tab {

    private Label ratingLabel;
    private TableView<Comment> tableView;

    public BookDetailTab(BookmanClientApp app) {
        setText("图书详情");

        // 输入框 + 按钮
        TextField bookIdField = new TextField();
        bookIdField.setPromptText("请输入图书 ID");
        Button fetchBtn = new Button("查询详情");

        HBox topBox = new HBox(10, bookIdField, fetchBtn);
        topBox.setAlignment(Pos.CENTER_LEFT);

        // 评分 Label
        ratingLabel = new Label("评分：");
        ratingLabel.setStyle("-fx-font-size: 16px; -fx-font-weight: bold;");
        HBox ratingBox = new HBox(ratingLabel);
        ratingBox.setAlignment(Pos.CENTER_LEFT);

        // 表格
        tableView = new TableView<>();

        TableColumn<Comment, Integer> userCol = new TableColumn<>("用户ID");
        userCol.setCellValueFactory(new PropertyValueFactory<>("userId"));

        TableColumn<Comment, Integer> ratingCol = new TableColumn<>("评分");
        ratingCol.setCellValueFactory(new PropertyValueFactory<>("rating"));

        TableColumn<Comment, String> contextCol = new TableColumn<>("评论内容");
        contextCol.setCellValueFactory(new PropertyValueFactory<>("context"));

        TableColumn<Comment, String> timeCol = new TableColumn<>("评论时间");
        timeCol.setCellValueFactory(new PropertyValueFactory<>("createTime"));

        tableView.getColumns().addAll(userCol, ratingCol, contextCol, timeCol);

        VBox root = new VBox(10, topBox, ratingBox, tableView);
        root.setPadding(new Insets(15));

        fetchBtn.setOnAction(e -> {
            String bookIdText = bookIdField.getText().trim();
            if (!bookIdText.matches("\\d+")) {
                showAlert("请输入合法图书 ID！");
                return;
            }

            int bookId = Integer.parseInt(bookIdText);
            fetchRating(bookId, app);
            fetchComments(bookId, app);
        });

        setContent(root);
    }

    private void fetchRating(int bookId, BookmanClientApp app) {
        new Thread(() -> {
            try {
                String url = "http://localhost:8080/api/comment/rating/" + bookId;
                String json = HttpUtil.get(url, app.token);

                JsonNode root = new ObjectMapper().readTree(json);
                double rating = root.path("data").path("rating").asDouble();
                String title = root.path("data").path("title").asText();

                Platform.runLater(() -> ratingLabel.setText("图书 "+ title + " 评分：" + rating));
            } catch (Exception e) {
                e.printStackTrace();
                Platform.runLater(() -> showAlert("获取评分失败：" + e.getMessage()));
            }
        }).start();
    }

    private void fetchComments(int bookId, BookmanClientApp app) {
        new Thread(() -> {
            try {
                String url = "http://localhost:8080/api/comment/book/" + bookId;
                String json = HttpUtil.get(url, app.token);

                JsonNode root = new ObjectMapper().readTree(json);
                JsonNode rows = root.path("data").path("rows");

                List<Comment> comments = new ObjectMapper().readValue(
                        rows.traverse(),
                        new TypeReference<List<Comment>>() {}
                );

                Platform.runLater(() -> {
                    tableView.getItems().setAll(
                            comments.stream().limit(10).collect(Collectors.toList())
                    );
                });
            } catch (Exception e) {
                e.printStackTrace();
                Platform.runLater(() -> showAlert("获取评论失败：" + e.getMessage()));
            }
        }).start();
    }

    private void showAlert(String msg) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION, msg, ButtonType.OK);
        alert.setHeaderText(null);
        alert.showAndWait();
    }
}
