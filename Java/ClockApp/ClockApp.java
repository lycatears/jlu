package com.ClockApp;

import javax.swing.*;
import java.awt.*;

public class ClockApp extends JFrame {
    public ClockApp() {
        setTitle("Digital Clock and Alarm");
        setLayout(new BorderLayout());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        DigitalClockPanel clockPanel = new DigitalClockPanel();
        AlarmClockPanel alarmPanel = new AlarmClockPanel(clockPanel);

        add(clockPanel, BorderLayout.CENTER);
        add(alarmPanel, BorderLayout.SOUTH);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);

        Thread clockThread = new Thread(clockPanel);
        Thread alarmThread = new Thread(alarmPanel);

        clockThread.start();
        alarmThread.start();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(ClockApp::new);
    }
}
