package org.example.client;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;


public class MyTab extends Tab {

    private ImageView avatarView;
    private Label unameLabel;
    private Label emailLabel;
    private Label registerLabel;
    private Label loginLabel;
    private Label sloganLabel;

    public MyTab(BookmanClientApp app) {
        setText("我的");

        // 头像图像视图
        avatarView = new ImageView();
        avatarView.setFitWidth(100);
        avatarView.setFitHeight(100);
        avatarView.setPreserveRatio(true);

        unameLabel = new Label("用户名：");
        unameLabel.setStyle("-fx-font-size: 16px; -fx-font-weight: bold;");

        VBox unameBox = new VBox(unameLabel);
        unameBox.setAlignment(Pos.CENTER_LEFT);

        HBox topBox = new HBox(20, avatarView, unameBox);
        topBox.setAlignment(Pos.CENTER_LEFT);

        // 信息项
        emailLabel = new Label("邮箱：");
        registerLabel = new Label("注册时间：");
        loginLabel = new Label("登录时间：");
        sloganLabel = new Label("个性签名：");

        VBox infoBox = new VBox(10, emailLabel, registerLabel, loginLabel, sloganLabel);
        infoBox.setPadding(new Insets(10));

        VBox root = new VBox(20, topBox, infoBox);
        root.setPadding(new Insets(20));

        setContent(root);

        loadUserInfo(app);
        loadAvatar(app);
    }

    private void loadUserInfo(BookmanClientApp app) {
        new Thread(() -> {
            try {
                String url = "http://localhost:8080/api/user/" + app.uid;
                String json = HttpUtil.get(url, app.token);

                JsonNode data = new ObjectMapper().readTree(json).path("data");

                Platform.runLater(() -> {
                    unameLabel.setText("用户名：" + app.uname);
                    emailLabel.setText("邮箱：" + data.path("email").asText());
                    registerLabel.setText("注册时间：" + data.path("registerTime").asText());
                    loginLabel.setText("登录时间：" + data.path("lastLoginTime").asText());
                    sloganLabel.setText("个性签名：" + data.path("slogan").asText());
                });
            } catch (Exception e) {
                e.printStackTrace();
                Platform.runLater(() -> showAlert("加载用户信息失败：" + e.getMessage()));
            }
        }).start();
    }

    private void loadAvatar(BookmanClientApp app) {
        new Thread(() -> {
            try {
                String url = "http://localhost:8080/api/avatar/" + app.uid;
                HttpURLConnection conn = (HttpURLConnection) new URL(url).openConnection();
                conn.setRequestProperty("Authorization", app.token);
                conn.setRequestMethod("GET");

                if (conn.getResponseCode() == 200) {
                    InputStream is = conn.getInputStream();
                    Image image = new Image(is);
                    Platform.runLater(() -> avatarView.setImage(image));
                } else {
                    Platform.runLater(() -> {
                        try {
                            showAlert("头像加载失败，状态码：" + conn.getResponseCode());
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        }
                    });
                }

            } catch (Exception e) {
                e.printStackTrace();
                Platform.runLater(() -> showAlert("加载头像失败：" + e.getMessage()));
            }
        }).start();
    }

    private void showAlert(String msg) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION, msg, ButtonType.OK);
        alert.setHeaderText(null);
        alert.showAndWait();
    }
}
