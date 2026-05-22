package com.db2work;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableRowSorter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TableWithCheckboxExample {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("JTable 复选框示例");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(500, 300);

            // 表格数据：在每行添加一个布尔值列（复选框列）
            Object[][] data = {
                    {false, "John", 30},
                    {true, "Mary", 25},
                    {false, "Tom", 35},
                    {true, "Anna", 28}
            };
            String[] columnNames = {"选择", "姓名", "年龄"};

            // 创建表格模型
            DefaultTableModel model = new DefaultTableModel(data, columnNames);
            JTable table = new JTable(model);
            table.setRowSorter(new TableRowSorter<>(model));

            // 设置复选框列的渲染器和编辑器
            table.getColumnModel().getColumn(0).setCellRenderer(new CheckboxRenderer());
            table.getColumnModel().getColumn(0).setCellEditor(new CheckboxEditor());

            // 创建按钮，点击后输出选中的行
            JButton btnGetSelected = new JButton("获取选中的行");
            btnGetSelected.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    for (int row = 0; row < table.getRowCount(); row++) {
                        Boolean isSelected = (Boolean) table.getValueAt(row, 0); // 获取复选框的状态
                        if (isSelected != null && isSelected) {
                            // 输出选中的行信息
                            System.out.println("选中的行: 姓名: " + table.getValueAt(row, 1) + ", 年龄: " + table.getValueAt(row, 2));
                        }
                    }
                }
            });

            // 布局
            frame.setLayout(new BorderLayout());
            frame.add(new JScrollPane(table), BorderLayout.CENTER);
            frame.add(btnGetSelected, BorderLayout.SOUTH);

            // 显示窗口
            frame.setVisible(true);
        });
    }

    // 复选框渲染器（绘制复选框）
    static class CheckboxRenderer extends JCheckBox implements TableCellRenderer {
        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
            setSelected(value != null && (Boolean) value);
            return this;
        }
    }

    // 复选框编辑器（用于在表格中编辑复选框）
    static class CheckboxEditor extends DefaultCellEditor {
        public CheckboxEditor() {
            super(new JCheckBox());
        }

        @Override
        public Component getTableCellEditorComponent(JTable table, Object value, boolean isSelected, int row, int column) {
            JCheckBox checkBox = (JCheckBox) getComponent();
            checkBox.setSelected(value != null && (Boolean) value);
            return checkBox;
        }
    }
}
