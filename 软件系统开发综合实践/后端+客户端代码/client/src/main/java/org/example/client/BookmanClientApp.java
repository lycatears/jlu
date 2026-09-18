package org.example.client;

import com.fasterxml.jackson.databind.JsonNode;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.stage.Stage;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import com.fasterxml.jackson.databind.ObjectMapper;
import javafx.util.Pair;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class BookmanClientApp extends Application {

    private Stage primaryStage;
    private final ObjectMapper objectMapper = new ObjectMapper();
    String token;
    Integer uid;
    String uname;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        this.primaryStage = primaryStage;
        showLoginDialog();
    }

    private void showLoginDialog() {
        Stage loginStage = new Stage();
        loginStage.setTitle("登录");

        Label userLabel = new Label("用户名:");
        TextField userField = new TextField();

        Label passLabel = new Label("密码:");
        PasswordField passField = new PasswordField();

        Button loginButton = new Button("登录");
        Button registerButton = new Button("注册");

        HBox buttonBox = new HBox(10, loginButton, registerButton);
        VBox vbox = new VBox(10, userLabel, userField, passLabel, passField, buttonBox);
        vbox.setPadding(new Insets(20));

        loginButton.setOnAction(e -> {
            uname = userField.getText();
            String password = passField.getText();
            try {
                Map<String, String> requestBody = new HashMap<>();
                requestBody.put("uname", uname);
                requestBody.put("password", password);

                String json = objectMapper.writeValueAsString(requestBody);

                HttpRequest request = HttpRequest.newBuilder()
                        .uri(URI.create("http://localhost:8080/api/login"))
                        .header("Content-Type", "application/json")
                        .POST(HttpRequest.BodyPublishers.ofString(json))
                        .build();

                HttpClient.newHttpClient().sendAsync(request, HttpResponse.BodyHandlers.ofString())
                        .thenApply(HttpResponse::body)
                        .thenAccept(responseBody -> {
                            try {
                                Map<?, ?> response = objectMapper.readValue(responseBody, Map.class);
                                int code = (int) response.get("code");
                                if (code == 0) {
                                    Map<String, Object> data = (Map<String, Object>) response.get("data");
                                    token = (String) data.get("token");
                                    uid = (Integer) data.get("uid");
                                    javafx.application.Platform.runLater(() -> {
                                        loginStage.close();
                                        showMainInterface((String) data.get("uname"));
                                    });
                                } else {
                                    javafx.application.Platform.runLater(() -> showAlert("登录失败", "用户名或密码错误！"));
                                }
                            } catch (Exception ex) {
                                ex.printStackTrace();
                                javafx.application.Platform.runLater(() -> showAlert("错误", "解析服务器响应失败"));
                            }
                        });
            } catch (Exception ex) {
                ex.printStackTrace();
                showAlert("错误", "请求发送失败");
            }
        });
        registerButton.setOnAction(e->handleRegister());

        loginStage.setScene(new Scene(vbox));
        loginStage.setOnCloseRequest(e -> System.exit(0)); // 登录窗口关闭即退出程序
        loginStage.show();
    }

    private void showMainInterface(String username) {
        primaryStage.setTitle("图书管理系统(客户端) - 欢迎 " + username);

        TabPane tabPane = new TabPane();
        tabPane.getTabs().add(new HomeTab(this));
        tabPane.getTabs().add(new BorrowTab(this));
        tabPane.getTabs().add(new ReturnTab(this));
        tabPane.getTabs().add(new BookDetailTab(this));
        tabPane.getTabs().add(new MyTab(this));


        BorderPane mainPane = new BorderPane(tabPane);
        mainPane.setPadding(new Insets(10));

        Scene scene = new Scene(mainPane, 800, 600);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void handleRegister() {
        Dialog<Pair<String, String>> dialog = new Dialog<>();
        dialog.setTitle("用户注册");
        dialog.setHeaderText("请输入注册信息");

        ButtonType registerButtonType = new ButtonType("注册", ButtonBar.ButtonData.OK_DONE);
        dialog.getDialogPane().getButtonTypes().addAll(registerButtonType, ButtonType.CANCEL);

        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(20, 150, 10, 10));

        TextField usernameField = new TextField();
        usernameField.setPromptText("用户名");
        PasswordField passwordField = new PasswordField();
        passwordField.setPromptText("密码");
        TextField emailField = new TextField();
        emailField.setPromptText("邮箱");

        grid.add(new Label("用户名:"), 0, 0);
        grid.add(usernameField, 1, 0);
        grid.add(new Label("密码:"), 0, 1);
        grid.add(passwordField, 1, 1);
        grid.add(new Label("邮箱:"), 0, 2);
        grid.add(emailField, 1, 2);

        dialog.getDialogPane().setContent(grid);

        Platform.runLater(usernameField::requestFocus);

        dialog.setResultConverter(dialogButton -> {
            if (dialogButton == registerButtonType) {
                return new Pair<>(usernameField.getText(), passwordField.getText());
            }
            return null;
        });

        Optional<Pair<String, String>> result = dialog.showAndWait();

        result.ifPresent(usernamePassword -> {
            String uname = usernameField.getText();
            String password = passwordField.getText();
            String email = emailField.getText();

            if (uname.isEmpty() || password.isEmpty() || email.isEmpty()) {
                showAlert("错误", "请填写所有字段！");
                return;
            }

            try {
                HttpClient client = HttpClient.newHttpClient();
                ObjectMapper mapper = new ObjectMapper();
                Map<String, String> requestMap = new HashMap<>();
                requestMap.put("uname", uname);
                requestMap.put("password", password);
                requestMap.put("email", email);
                String json = mapper.writeValueAsString(requestMap);

                HttpRequest request = HttpRequest.newBuilder()
                        .uri(URI.create("http://localhost:8080/api/register"))
                        .header("Content-Type", "application/json")
                        .POST(HttpRequest.BodyPublishers.ofString(json))
                        .build();

                client.sendAsync(request, HttpResponse.BodyHandlers.ofString())
                        .thenAccept(response -> {
                            try {
                                JsonNode jsonResponse = mapper.readTree(response.body());
                                int code = jsonResponse.get("code").asInt();
                                String message = jsonResponse.get("message").asText();

                                Platform.runLater(() -> {
                                    if (code == 0) {
                                        showAlert("成功", "注册成功！");
                                    } else {
                                        showAlert("注册失败", message);
                                    }
                                });
                            } catch (Exception e) {
                                e.printStackTrace();
                                Platform.runLater(() -> showAlert("错误", "解析响应失败"));
                            }
                        })
                        .exceptionally(e -> {
                            e.printStackTrace();
                            Platform.runLater(() -> showAlert("错误", "注册请求失败"));
                            return null;
                        });

            } catch (Exception e) {
                e.printStackTrace();
                showAlert("错误", "注册时发生异常");
            }
        });
    }

}
