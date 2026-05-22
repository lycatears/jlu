package com.db2work;

import javax.swing.*;
import javax.swing.plaf.nimbus.State;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.math.BigDecimal;
import java.sql.*;

public class DeleteEmployee {
    JPanel DeleteEmployee;
    private JPanel EmployeeList;
    private JScrollPane EmployeePanel;
    private JTable EmployeeTable;
    private JTextField Keyword;
    private JLabel SearchLabel;
    private JButton SearchButton;
    private JButton DeleteButton;
    private JButton CancelButton;
    private Connection conn;
    private JFrame frame;

    public DeleteEmployee(Connection conn, JFrame frame) {
        JDialog loadingDialog = ManagerMain.createWaitingDialog("正在加载", "正在加载数据，请稍等...");
        loadingDialog.setVisible(true);
        this.conn = conn;
        this.frame = frame;

        String[] columnNames = {
                "选择", "工号", "名", "中间名", "姓", "部门",
                "电话分机号", "入职日期", "职位", "职级",
                "性别", "出生日期", "薪水", "奖金", "绩效"
        };
        DefaultTableModel model = new DefaultTableModel() {
            @Override
            public boolean isCellEditable(int row, int column) {
                return column == 0;
            }

            @Override
            public Class<?> getColumnClass(int columnIndex) {
                if (columnIndex >= 12) {
                    return BigDecimal.class;
                }
                return super.getColumnClass(columnIndex);
            }
        };
        EmployeeTable.setModel(model);
        TableRowSorter<TableModel> sorter = new TableRowSorter<>(model);
        EmployeeTable.setRowSorter(sorter);
        Keyword.getDocument().addDocumentListener(new javax.swing.event.DocumentListener() {
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
                String text = Keyword.getText();
                if (text.trim().isEmpty()) {
                    sorter.setRowFilter(null); // 显示所有行
                } else {
                    // 按照所有列筛选，忽略大小写
                    sorter.setRowFilter(RowFilter.regexFilter("(?i)" + text));
                }
            }
        });
        for (String columnName : columnNames) {
            model.addColumn(columnName);
        }

        ResultSet rs = null;
        try {
            Statement stmt = conn.createStatement();
            rs = stmt.executeQuery("select * from templ");
            ResultSetMetaData metaData = rs.getMetaData();
            int columnCount = metaData.getColumnCount();
            int rowCount = 0;

            EmployeeTable.getColumnModel().getColumn(0).setCellRenderer(new CheckboxRenderer());
            EmployeeTable.getColumnModel().getColumn(0).setCellEditor(new CheckboxEditor());

            while (rs.next()) {
                Object[] row = new Object[columnCount + 1];
                row[0] = false;
                for (int i = 1; i <= columnCount; i++) {
                    String str = rs.getString(i);
                    if (!rs.wasNull() && !str.trim().isEmpty()) {
                        row[i] = str;
                    } else {
                        row[i] = "空";
                    }
                }
                model.addRow(row);
                rowCount++;
            }

            rs.close();
            stmt.close();
        } catch (SQLException ex) {
            JOptionPane.showMessageDialog(null, ex.getMessage(), "错误", JOptionPane.ERROR_MESSAGE);
        }

        loadingDialog.dispose();

        CancelButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                frame.dispose();
            }
        });
        DeleteButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                try {
                    PreparedStatement pStmt = conn.prepareStatement("delete from TEMPL where EMPNO = ?");
                    int rowCount = EmployeeTable.getRowCount();
                    int toDeleteCount = 0;

                    for (int i = 0; i < rowCount; i++) {
                        if ((Boolean) EmployeeTable.getValueAt(i, 0)) {
                            pStmt.setString(1, (String) EmployeeTable.getValueAt(i, 1));
                            pStmt.addBatch();
                            toDeleteCount++;
                        }
                    }

                    if (toDeleteCount <= 0) {
                        JOptionPane.showMessageDialog(null, "您未选择删除行，请检查。", "错误", JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    if (JOptionPane.showOptionDialog(
                            null, "您即将删除" + toDeleteCount + "行，是否确认删除？", "警告",
                            JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE, null, null, null) == JOptionPane.YES_OPTION) {
                        pStmt.executeBatch();
                    }

                    pStmt.close();

                    JOptionPane.showMessageDialog(null, "删除成功！", "成功", JOptionPane.INFORMATION_MESSAGE);
                } catch (SQLException ex) {
                    JOptionPane.showMessageDialog(null, "数据库错误：\n" + ex.getMessage(), "错误", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

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
