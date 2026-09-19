package com.ClockApp;

import javax.swing.*;
import java.awt.*;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class AlarmClockPanel extends JPanel implements Runnable {
    private DigitalClockPanel clockPanel;
    private LocalTime now = LocalTime.now();
    private DateTimeFormatter timeFormatter = DateTimeFormatter.ofPattern("HH:mm:ss");

    public AlarmClockPanel(DigitalClockPanel clockPanel) {
        this.clockPanel = clockPanel;
        setPreferredSize(new Dimension(300, 100));
    }

    @Override
    public void run() {
        while (true) {
            now = LocalTime.now();
            if (now.getMinute() == 0 && now.getSecond() == 0) {
                clockPanel.suspendClock();
                for (int i = 0; i < 5; i++) {
                    repaint();
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }
                clockPanel.resumeClock();
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    protected void paintComponent(Graphics g) {
        String currentTime = timeFormatter.format(now);
        super.paintComponent(g);
        g.setFont(new Font("Arial", Font.BOLD, 40));
        g.setColor(Color.RED);
        try {
            if (now.getMinute() == 0 && now.getSecond() == 0) {
                g.drawString(currentTime, 50, 50);
            }
        } catch (Exception e) {
            g.drawString(" ", 50, 50);
        }
    }
}
