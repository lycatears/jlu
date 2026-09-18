package org.example.booksys;

import javax.swing.*;
import java.io.File;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class BlobTest {
    public static void main(String[] args) {
        // 提示用户输入用户ID
        String userId = JOptionPane.showInputDialog("请输入用户ID：");
        if (userId == null || userId.trim().isEmpty()) {
            JOptionPane.showMessageDialog(null, "用户ID不能为空！");
            return;
        }

        // 文件选择器选择图片文件
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("选择头像图片文件");
        int result = fileChooser.showOpenDialog(null);
        if (result != JFileChooser.APPROVE_OPTION) {
            JOptionPane.showMessageDialog(null, "未选择文件！");
            return;
        }

        File file = fileChooser.getSelectedFile();

        // 上传到数据库
        try (Connection conn = DriverManager.getConnection(
                "jdbc:oracle:thin:@localhost:1521:orcl", // 替换为你的连接字符串
                "BOOKMAN",                        // 替换为你的用户名
                "lsw8261325027904");                       // 替换为你的密码
             FileInputStream fis = new FileInputStream(file)) {

            // 插入或更新语句
//            String sql = "MERGE INTO BOOKMAN.\"user_avatar\" t " +
//                    "USING (SELECT ? AS user_id FROM dual) s " +
//                    "ON (t.\"user_id\" = s.\"user_id\") " +
//                    "WHEN MATCHED THEN UPDATE SET t.\"avatar\" = ? " +
//                    "WHEN NOT MATCHED THEN INSERT (\"user_id\", \"avatar\") VALUES (?, ?)";
            String sql = "insert into BOOKMAN.\"user_avatar\" values (?,?)";

            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, userId);
            pstmt.setBinaryStream(2, fis, (int) file.length()); // 用于更新
            try (FileInputStream fis2 = new FileInputStream(file)) {
//                pstmt.setBinaryStream(4, fis2, (int) file.length()); // 用于插入
                int rows = pstmt.executeUpdate();
                JOptionPane.showMessageDialog(null, "上传成功，影响行数：" + rows);
            }

        } catch (Exception e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(null, "上传失败：" + e.getMessage());
        }
    }
}
