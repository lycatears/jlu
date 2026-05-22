package com.db2work;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;

public class TestFIlter {
    public static void main(String[] args) {
        // 创建窗口
        JFrame frame = new JFrame("JTable 筛选示例");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(600, 400);

        // 创建表格数据
        String[] columns = {"ID", "Name", "Score"};
        Object[][] data = {
                {1, "Alice", 85},
                {2, "Bob", 90},
                {3, "Charlie", 75},
                {4, "David", 88},
                {5, "Eve", 92}
        };

        // 创建表格和模型
        DefaultTableModel model = new DefaultTableModel(data, columns);
        JTable table = new JTable(model);

        // 设置排序器
        TableRowSorter<TableModel> sorter = new TableRowSorter<>(model);
        table.setRowSorter(sorter);

        // 创建过滤文本框
        JTextField filterField = new JTextField(20);
        JLabel filterLabel = new JLabel("输入关键字进行筛选：");

        // 监听文本框的输入事件
        filterField.getDocument().addDocumentListener(new javax.swing.event.DocumentListener() {
            @Override
            public void insertUpdate(javax.swing.event.DocumentEvent e) {
                filter();
            }

            @Override
            public void removeUpdate(javax.swing.event.DocumentEvent e) {
                filter();
            }

            @Override
            public void changedUpdate(javax.swing.event.DocumentEvent e) {
                filter();
            }

            // 定义筛选逻辑
            private void filter() {
                String text = filterField.getText();
                if (text.trim().isEmpty()) {
                    sorter.setRowFilter(null); // 显示所有行
                } else {
                    // 按照所有列筛选，忽略大小写
                    sorter.setRowFilter(RowFilter.regexFilter("(?i)" + text));
                }
            }
        });

        // 布局设置
        JPanel panel = new JPanel(new FlowLayout());
        panel.add(filterLabel);
        panel.add(filterField);

        frame.add(panel, BorderLayout.NORTH);
        frame.add(new JScrollPane(table), BorderLayout.CENTER);

        // 显示窗口
        frame.setVisible(true);
    }
}
