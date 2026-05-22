package com.db2work;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.*;
import java.sql.*;

public class InsertPhoto {
    JPanel ShowPhoto;
    private JPanel EmpnoPanel;
    private JTextField EMPNO;
    private JLabel EnterEmpnoPrompt;
    private JButton OKButton;
    private JLabel FilePathPrompt;
    private JTextField FilePath;
    private JButton BrowseButton;
    private JButton 预览Button;
    private JPanel PreviewPanel;
    private JLabel PhotoLabel;
    private Connection conn;
    private JFrame frame;

    public InsertPhoto(Connection conn, JFrame userFrame) {
        super();
        this.conn = conn;
        frame = userFrame;

        OKButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                try {
                    PreparedStatement ps = conn.prepareStatement("select picture from emp_photo where EMPNO=?");
                    ps.setString(1, EMPNO.getText());
                    ResultSet rs = ps.executeQuery();

                    File file = new File(FilePath.getText());
                    FileInputStream fis = new FileInputStream(file);
                    if (rs.next()) {
                        ps = conn.prepareStatement("update emp_photo set PICTURE=? where EMPNO=?");
                        ps.setBlob(1, fis, fis.available());
                        ps.setString(2, EMPNO.getText());
                        ps.executeUpdate();
                    } else {
                        ps = conn.prepareStatement("insert into emp_photo (EMPNO,PHOTO_FORMAT, PICTURE) values(?,'bitmap',?)");
                        ps.setString(1, EMPNO.getText());
                        ps.setBlob(2, fis, fis.available());
                        ps.executeUpdate();
                    }

                    ps.close();
                    fis.close();
                    JOptionPane.showMessageDialog(null, "成功设置图片！",
                            "信息", JOptionPane.INFORMATION_MESSAGE, null);
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
                fileChooser.setCurrentDirectory(new File(System.getProperty("user.home")));
                fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("jpg图片", "jpg"));
                fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("png图片", "png"));
                fileChooser.addChoosableFileFilter(new FileNameExtensionFilter("bmp图片", "bmp"));

                int returnValue = fileChooser.showOpenDialog(null);

                // 如果用户选择了文件，显示文件路径
                if (returnValue == JFileChooser.APPROVE_OPTION) {
                    if (fileChooser.getSelectedFile().isFile()) {
                        File selectedFile = fileChooser.getSelectedFile();
                        FilePath.setText(selectedFile.getAbsolutePath());
                    } else {
                        JOptionPane.showMessageDialog(null, "请选择合法的文件。", "错误", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });
        预览Button.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                try {
                    File file = new File(FilePath.getText());
                    FileInputStream fis = new FileInputStream(file);
                    PhotoLabel.setText(null);
                    PhotoLabel.setIcon(new ImageIcon(javax.imageio.ImageIO.read(fis)));

                    fis.close();
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
    }
}
