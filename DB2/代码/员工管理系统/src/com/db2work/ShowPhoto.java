package com.db2work;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.*;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.*;

public class ShowPhoto {
    JPanel ShowPhoto;
    private JPanel EmpnoPanel;
    private JTextField EMPNO;
    private JButton OKButton;
    private JLabel EnterEmpnoPrompt;
    private JTextField FilePath;
    private JButton BrowseButton;
    private JLabel FilePathPrompt;
    private JButton ShowButton;
    private JPanel PreviewPanel;
    private JLabel PhotoLabel;
    private JFrame frame;
    private Connection conn;

    public ShowPhoto(Connection conn, JFrame userFrame) {
        super();
        this.conn = conn;
        frame = userFrame;

        OKButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                int photoCount = 0;
                try {
                    PreparedStatement stmt = conn.prepareStatement("select picture from emp_photo where empno=?");
                    stmt.setString(1, EMPNO.getText());
                    ResultSet rs = stmt.executeQuery();
                    while (rs.next()) {
                        photoCount++;
                        String path = FilePath.getText();

                        Blob blob = rs.getBlob(1);
                        InputStream bis = blob.getBinaryStream();

                        if (photoCount > 1) {
                            int nextPhotoChoice = JOptionPane.showOptionDialog(
                                    null, "该员工还有其他图片，是否继续下载？", "提示",
                                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null);
                            if (nextPhotoChoice == JOptionPane.NO_OPTION) {
                                break;
                            }
                            String[] temp = path.split("\\\\");
                            temp[temp.length - 1] = temp[temp.length - 1] + "(" + photoCount + ")" + ".jpg";
                            path = String.join("\\", temp);
                        }

                        File file = new File(path);
                        FileOutputStream fos = new FileOutputStream(file);

                        int u = 0;
                        while ((u = bis.read()) != -1) {
                            fos.write(u);
                        }

                        rs.close();
                        fos.close();
                        bis.close();

                        JOptionPane.showMessageDialog(null, "成功下载图片！",
                                "信息", JOptionPane.INFORMATION_MESSAGE, null);
                    }
                } catch (SQLException ex) {
                    if (null != ex.getSQLState()) {
                        if (ex.getSQLState().equals("22018")) {
                            JOptionPane.showMessageDialog(null, "数据类型不匹配。请检查是否在表格中填写了正确的数据类型。");
                        } else if (ex.getSQLState().equals("23505")) {
                            JOptionPane.showMessageDialog(null, "您指定的员工工号重复，请检查！");
                        } else if (ex.getSQLState().equals("23503")) {
                            JOptionPane.showMessageDialog(null, "您指定的员工不存在，请检查！");
                        } else if (ex.getSQLState().equals("22001")) {
                            JOptionPane.showMessageDialog(null, "您输入的数据过长，发生截断错误！请检查！");
                        } else if (ex.getSQLState().equals("22003")) {
                            JOptionPane.showMessageDialog(null, "您输入的数字过大，发生溢出错误！请检查！");
                        } else if (ex.getSQLState().equals("22007")) {
                            JOptionPane.showMessageDialog(null, "日期格式不正确！请检查！");
                        }
                    } else {
                        if (ex.getErrorCode() == -4220) {
                            JOptionPane.showMessageDialog(null, "您输入的数字过大，发生溢出错误！请检查！");
                        }
                    }
                } catch (IOException ioe) {
                    JOptionPane.showMessageDialog(null, "无法读取您指定的文件。这可能是以下原因导致的：\n" +
                                    "1.您选择的文件名指向文件夹，而非文件；\n" +
                                    "2.您选择的文件被其他程序占用；\n" +
                                    "3.指定的文件名过长，导致文件路径长度超出操作系统限制。\n" +
                                    "请检查是否有正在使用该文件的其他程序，然后修改文件路径，或者稍后重试。",
                            "错误", JOptionPane.ERROR_MESSAGE, null);
                }
            }
        });
        BrowseButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                fileChooser.setCurrentDirectory(new File(System.getProperty("user.home")));

                int returnValue = fileChooser.showOpenDialog(null);

                // 如果用户选择了文件，显示文件路径
                if (returnValue == JFileChooser.APPROVE_OPTION) {
                    if (fileChooser.getSelectedFile().isDirectory()) {
                        File selectedFile = fileChooser.getSelectedFile();
                        FilePath.setText(selectedFile.getAbsolutePath() + File.separator + "export.jpg");
                    } else {
                        JOptionPane.showMessageDialog(null, "请选择合法的文件夹。", "错误", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });
        ShowButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                try {
                    PreviewPanel.removeAll();
                    PreparedStatement stmt = conn.prepareStatement("select picture from emp_photo where empno=?");
                    stmt.setString(1, EMPNO.getText());
                    ResultSet rs = stmt.executeQuery();
                    while (rs.next()) {
                        Blob blob = rs.getBlob(1);
                        InputStream bis = blob.getBinaryStream();

                        ImageIcon imageIcon = new ImageIcon(javax.imageio.ImageIO.read(bis));

                        // 设置到 JLabel
                        JLabel newLabel = new JLabel();
                        PreviewPanel.add(newLabel);
                        newLabel.setText(null);
                        newLabel.setIcon(imageIcon);
                    }
                } catch (SQLException ex) {
                    if (null != ex.getSQLState()) {
                        if (ex.getSQLState().equals("22018")) {
                            JOptionPane.showMessageDialog(null, "数据类型不匹配。请检查是否在表格中填写了正确的数据类型。");
                        } else if (ex.getSQLState().equals("23505")) {
                            JOptionPane.showMessageDialog(null, "您指定的员工工号重复，请检查！");
                        } else if (ex.getSQLState().equals("23503")) {
                            JOptionPane.showMessageDialog(null, "您指定的员工不存在，请检查！");
                        } else if (ex.getSQLState().equals("22001")) {
                            JOptionPane.showMessageDialog(null, "您输入的数据过长，发生截断错误！请检查！");
                        } else if (ex.getSQLState().equals("22003")) {
                            JOptionPane.showMessageDialog(null, "您输入的数字过大，发生溢出错误！请检查！");
                        } else if (ex.getSQLState().equals("22007")) {
                            JOptionPane.showMessageDialog(null, "日期格式不正确！请检查！");
                        }
                    } else {
                        if (ex.getErrorCode() == -4220) {
                            JOptionPane.showMessageDialog(null, "您输入的数字过大，发生溢出错误！请检查！");
                        }
                    }
                } catch (IOException ioe) {
                    PhotoLabel.setText("图片加载失败");
                }
            }
        });
    }
}
