package com.ClockApp;
import javax.swing.*;
import java.awt.*;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class DigitalClockPanel extends JPanel implements Runnable {
    private volatile boolean suspended = false;
    private Object lock = new Object();
    private String currentTime;

    public DigitalClockPanel() {
        setPreferredSize(new Dimension(300, 100));
    }

    @Override
    public void run() {
        DateTimeFormatter timeFormatter = DateTimeFormatter.ofPattern("HH:mm:ss");
        while (true) {
            synchronized (lock) {
                while (suspended) {
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }
            }
            currentTime = LocalTime.now().format(timeFormatter);
            repaint();
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    public void suspendClock() {
        suspended = true;
    }

    public void resumeClock() {
        synchronized (lock) {
            suspended = false;
            lock.notify();
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setFont(new Font("Arial", Font.BOLD, 40));
        try{
            g.drawString(currentTime, 50, 50);
        }catch(Exception e){
            g.drawString(" ", 50, 50);
        }
    }
}
