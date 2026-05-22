package com.db2work;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.math.BigDecimal;
import java.sql.*;
import java.util.ArrayList;

public class SubqueryInsert {


    JPanel SubqueryInsert;
    JFrame frame;
    private JScrollPane EmployeePanel;
    private JTable EmployeeTable;
    private JPanel OperationPanel;
    private JButton ImportSubqueryButton;
    private JLabel TitleButton;
    private JButton DeleteRowButton;
    private JButton ImportButton;
    private JButton ImportSelectedButton;
    private JLabel SearchLabel;
    private JTextField Keyword;
    private JButton SearchButton;
    private JPanel SearchPanel;
    private JButton ExitButton;
    private JButton SelectAll;
    private JButton DeSeletAllButton;
    private Connection conn;

    public SubqueryInsert(Connection conn, JFrame frame) {
        this.conn = conn;
        this.frame = frame;
        JDialog loadingDialog = ManagerMain.createWaitingDialog("正在加载", "正在加载数据，请稍等...");
        loadingDialog.setVisible(true);

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
        for (String columnName : columnNames) {
            model.addColumn(columnName);
        }

        ResultSet rs = null;
        try {
            Statement stmt = conn.createStatement();
            rs = stmt.executeQuery("select * from employee");
            ResultSetMetaData metaData = rs.getMetaData();
            int columnCount = metaData.getColumnCount();
            int rowCount = 0;

            EmployeeTable.getColumnModel().getColumn(0).setCellRenderer(new CheckboxRenderer());
            EmployeeTable.getColumnModel().getColumn(0).setCellEditor(new CheckboxEditor());
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

            while (rs.next()) {
                Object[] row = new Object[columnCount + 1];
                row[0] = true;
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
        ExitButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                frame.dispose();
            }
        });
        ImportButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                try {
                    PreparedStatement pStmt = conn.prepareStatement("insert into templ select * from employee");
                    if (JOptionPane.showOptionDialog(
                            null, "确定要全部导入吗？", "确认导入",
                            JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null) == JOptionPane.YES_OPTION) {
                        pStmt.execute();
                    }
                } catch (SQLException ex) {
                    JOptionPane.showMessageDialog(null, "违反约束条件：存在重复行。\n" + ex.getMessage(), "错误", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        DeleteRowButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                ArrayList<Integer> list = new ArrayList<>();
                for (int i = 0; i < EmployeeTable.getRowCount(); i++) {
                    if (EmployeeTable.getValueAt(i, 0).toString() == "true") {
                        list.add(i);
                    }
                }
                for (int i = list.size() - 1; i >= 0; i--) {
                    DefaultTableModel dtm = (DefaultTableModel) EmployeeTable.getModel();
                    int deleteIndex = EmployeeTable.convertRowIndexToModel(list.get(i));
                    dtm.removeRow(deleteIndex);
                }
            }
        });
        SelectAll.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                for (int i = 0; i < EmployeeTable.getRowCount(); i++) {
                    EmployeeTable.setValueAt(true, i, 0);
                }
            }
        });
        DeSeletAllButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                for (int i = 0; i < EmployeeTable.getRowCount(); i++) {
                    EmployeeTable.setValueAt(false, i, 0);
                }
            }
        });
        ImportSelectedButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                try {
                    int insertCount = 0;
                    PreparedStatement pStmt = conn.prepareStatement("insert into templ values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
                    for (int i = 0; i < EmployeeTable.getRowCount(); i++) {
                        if (EmployeeTable.getValueAt(i, 0).toString().equals("false")) {
                            continue;
                        }
                        pStmt.setString(1, EmployeeTable.getValueAt(i, 1).toString().trim());
                        pStmt.setString(2, EmployeeTable.getValueAt(i, 2).toString().trim());
                        if (!EmployeeTable.getValueAt(i, 1).toString().trim().equals("空")) {
                            pStmt.setString(3, EmployeeTable.getValueAt(i, 3).toString().trim());
                        } else {
                            pStmt.setNull(3, Types.CHAR);
                        }
                        pStmt.setString(4, EmployeeTable.getValueAt(i, 4).toString().trim());
                        pStmt.setString(5, EmployeeTable.getValueAt(i, 5).toString().trim());
                        pStmt.setString(6, EmployeeTable.getValueAt(i, 6).toString().trim());
                        pStmt.setDate(7, Date.valueOf(EmployeeTable.getValueAt(i, 7).toString().trim()));
                        pStmt.setString(8, EmployeeTable.getValueAt(i, 8).toString().trim());
                        pStmt.setShort(9, Short.parseShort(EmployeeTable.getValueAt(i, 9).toString().trim()));
                        pStmt.setString(10, EmployeeTable.getValueAt(i, 10).toString().trim());
                        pStmt.setDate(11, Date.valueOf(EmployeeTable.getValueAt(i, 11).toString().trim()));
                        pStmt.setBigDecimal(12, new BigDecimal(EmployeeTable.getValueAt(i, 12).toString().trim()));
                        pStmt.setBigDecimal(13, new BigDecimal(EmployeeTable.getValueAt(i, 13).toString().trim()));
                        pStmt.setBigDecimal(14, new BigDecimal(EmployeeTable.getValueAt(i, 14).toString().trim()));
                        pStmt.addBatch();
                        insertCount++;
                    }
                    int continueChoice = JOptionPane.showOptionDialog(null, "您即将插入" +
                            +insertCount + "行，是否确认？", "警告", JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE, null, null, null);
                    if (continueChoice == JOptionPane.YES_OPTION) {
                        pStmt.executeBatch();
                    }
                } catch (SQLException ex) {
                    JOptionPane.showMessageDialog(null, "违反约束条件：存在重复行。\n" + ex.getMessage(), "错误", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        ImportSubqueryButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                ResultSet rs = null;
                try {
                    Statement stmt = conn.createStatement();
                    rs = stmt.executeQuery("select * from employee");
                    ResultSetMetaData metaData = rs.getMetaData();
                    int columnCount = metaData.getColumnCount();
                    int rowCount = 0;

                    EmployeeTable.getColumnModel().getColumn(0).setCellRenderer(new CheckboxRenderer());
                    EmployeeTable.getColumnModel().getColumn(0).setCellEditor(new CheckboxEditor());

                    while (rs.next()) {
                        Object[] row = new Object[columnCount + 1];
                        row[0] = true;
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
