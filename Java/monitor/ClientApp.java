package com.monitor;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;

public class ClientApp extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JLabel statusLabel;

    public ClientApp() {
        setTitle("Client Login");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(4, 1));

        usernameField = new JTextField();
        passwordField = new JPasswordField();
        statusLabel = new JLabel("MyLogin", SwingConstants.CENTER);

        JButton loginButton = new JButton("Login");
        loginButton.addActionListener(new LoginAction());

        add(new JLabel("Username: ", SwingConstants.CENTER));
        add(usernameField);
        add(new JLabel("Password: ", SwingConstants.CENTER));
        add(passwordField);
        add(loginButton);
        add(statusLabel);

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
        setSize(300,200);
    }

    private class LoginAction implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String username = usernameField.getText();
            String password = new String(passwordField.getPassword());
            Socket socket = null;
            try{
                socket = new Socket("localhost", 12345);
            }catch(Exception e1){
                JOptionPane.showMessageDialog(null,"Could not connect to server");
            }

            try{
                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                out.println(username);
                out.println(password);

                String response = in.readLine();
                statusLabel.setText(response);
                if ("Login Successful".equals(response)) {
                    JOptionPane.showMessageDialog(null, "Login Successful");
                }
                else{
                    JOptionPane.showMessageDialog(null, "Login Failed");
                }
            } catch (Exception ex) {
                statusLabel.setText("Connection error");
                ex.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(ClientApp::new);
    }
}
