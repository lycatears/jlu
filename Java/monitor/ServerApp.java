package com.monitor;

import javax.swing.*;
import java.awt.*;
import java.net.*;
import java.io.*;
import java.util.*;

public class ServerApp extends JFrame {
    private final Map<String, JLabel> userLabels;

    public ServerApp() {
        setTitle("Server Monitor");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(5, 1));

        userLabels = new HashMap<>();
        String[] users = {"user1", "user2", "user3", "user4", "user5"};

        for (String user : users) {
            JLabel label = new JLabel(user + " - Not Logged In", SwingConstants.CENTER);
            label.setOpaque(true);
            label.setBackground(Color.GRAY);
            add(label);
            userLabels.put(user, label);
        }

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
        setSize(300,200);

        new Thread(new ServerThread(userLabels)).start();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(ServerApp::new);
    }
}
