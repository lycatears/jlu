package com.monitor;
import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.net.*;
import java.util.Map;


class ServerThread implements Runnable {
    private final Map<String, JLabel> userLabels;

    public ServerThread(Map<String, JLabel> userLabels) {
        this.userLabels = userLabels;
    }

    @Override
    public void run() {
        try (ServerSocket serverSocket = new ServerSocket(12345)) {
            while (true) {
                Socket clientSocket = serverSocket.accept();
                new Thread(new ClientHandler(clientSocket, userLabels)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class ClientHandler implements Runnable {
    private final Socket clientSocket;
    private final Map<String, JLabel> userLabels;

    public ClientHandler(Socket clientSocket, Map<String, JLabel> userLabels) {
        this.clientSocket = clientSocket;
        this.userLabels = userLabels;
    }

    @Override
    public void run() {
        try (
                BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)
        ) {
            String username = in.readLine();
            String password = in.readLine();

            if (userLabels.containsKey(username)&&password.equals("12345")) {
                JLabel label = userLabels.get(username);
                SwingUtilities.invokeLater(() -> {
                    label.setText(username + " - Logged In from " + clientSocket.getInetAddress());
                    label.setBackground(Color.GREEN);
                });
                out.println("Login Successful");
            } else {
                out.println("Login Failed");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
