package org.example.client;

import com.fasterxml.jackson.databind.ObjectMapper;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.geometry.Pos;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;
import java.util.Map;

public class ReturnTab extends Tab {

    public ReturnTab(BookmanClientApp app) {
        setText("还书");

        // ✅ 归还图书部分
        TextField returnBookIdField = new TextField();
        returnBookIdField.setPromptText("请输入归还的图书编号");

        Button returnBtn = new Button("归还图书");
        HBox returnBox = new HBox(10, returnBookIdField, returnBtn);
        returnBox.setAlignment(Pos.CENTER_LEFT);

        // ✅ 评论部分
        TextField commentBookIdField = new TextField();
        commentBookIdField.setPromptText("请输入图书编号（用于评论）");

        TextArea commentArea = new TextArea();
        commentArea.setPromptText("请输入您的评论内容");
        commentArea.setWrapText(true);
        commentArea.setPrefRowCount(3);

        Spinner<Integer> ratingSpinner = new Spinner<>(1, 5, 5);
        ratingSpinner.setEditable(true);

        Button commentBtn = new Button("提交评论");

        VBox commentBox = new VBox(10,
                new Label("书看完了，聊聊你的看法？评论内容："), commentArea,
                new Label("评分（1-5）：" ), ratingSpinner,
                new Label("评论图书编号："), commentBookIdField,
                commentBtn
        );
        commentBox.setPadding(new Insets(10));
        commentBox.setStyle("-fx-border-color: #ccc; -fx-border-width: 1px; -fx-border-radius: 5px;");

        // 按钮事件绑定
        returnBtn.setOnAction(e -> {
            String bookIdText = returnBookIdField.getText().trim();
            if (!bookIdText.matches("\\d+")) {
                showAlert("请输入合法的图书编号！");
                return;
            }
            int bookId = Integer.parseInt(bookIdText);
            returnBook(bookId, app);
        });

        commentBtn.setOnAction(e -> {
            String content = commentArea.getText().trim();
            String bookIdText = commentBookIdField.getText().trim();
            int rating = ratingSpinner.getValue();

            if (content.isEmpty() || !bookIdText.matches("\\d+")) {
                showAlert("请输入合法的评论内容和图书编号！");
                return;
            }

            int bookId = Integer.parseInt(bookIdText);
            commentOnBook(bookId, app.uid, rating, content, app);
        });

        VBox root = new VBox(15, returnBox, commentBox);
        root.setPadding(new Insets(15));
        setContent(root);
    }

    private void returnBook(int bookId, BookmanClientApp app) {
        new Thread(() -> {
            try {
                String url = String.format("http://localhost:8080/userapi/record?userId=%d&bookId=%d", app.uid, bookId);
                String json = HttpUtil.put(url, "", app.token);
                if(json.contains("0")){
                    Platform.runLater(() -> showAlert("归还成功"));
                }else{
                    Platform.runLater(()->showAlert("您未借过该书，或已经归还！"));
                }
            } catch (Exception e) {
                e.printStackTrace();
                Platform.runLater(() -> showAlert("归还失败：" + e.getMessage()));
            }
        }).start();
    }

    private void commentOnBook(int bookId, int userId, int rating, String context, BookmanClientApp app) {
        new Thread(() -> {
            try {
                String now = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));

                Map<String, Object> data = new HashMap<>();
                data.put("bookId", bookId);
                data.put("userId", userId);
                data.put("rating", rating);
                data.put("context", context);
                data.put("createTime", now);

                String jsonBody = new ObjectMapper().writeValueAsString(data);
                String response = HttpUtil.post("http://localhost:8080/userapi/comment", jsonBody, app.token);
                if(response.contains("0")){
                    Platform.runLater(() -> showAlert("评论发表成功" ));
                }else{
                    Platform.runLater(() -> showAlert("您的发言含有违规内容，请修改后重试！" ));
                }
            } catch (Exception e) {
                e.printStackTrace();
                Platform.runLater(() -> showAlert("评论失败：" + e.getMessage()));
            }
        }).start();
    }

    private void showAlert(String msg) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION, msg, ButtonType.OK);
        alert.setHeaderText(null);
        alert.showAndWait();
    }
}
