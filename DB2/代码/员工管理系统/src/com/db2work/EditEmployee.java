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

public class EditEmployee {
    JPanel EditEmployee;
    private JPanel EmployeeList;
    private JScrollPane EmployeePanel;
    private JTable EmployeeTable;
    private JLabel SearchLabel;
    private JTextField Keyword;
    private JButton SearchButton;
    private JButton CommitButton;
    private JButton CancelButton;
    private JLabel Hint;
    private Connection conn;
    private JFrame frame;

    public EditEmployee(Connection conn, JFrame frame) {
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
                if (column == 0) {
                    return true;
                }
                return this.getValueAt(row, 0).toString() == "true";
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
        CommitButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                try {
                    /*
                    PreparedStatement pStmt = conn.prepareStatement("update TEMPL " +
                            "set FIRSTNME=?,MIDINIT=?,LASTNAME=?,WORKDEPT=?," +
                            "PHONENO=?,HIREDATE=?,JOB=?,EDLEVEL=?,SEX=?,BIRTHDATE=?," +
                            "SALARY=?,BONUS=?,COMM=?" +
                            "where EMPNO=?");
                    int rowCount = EmployeeTable.getRowCount();
                    int modifyCount = 0;
                    for (int i = 0; i < rowCount; i++) {
                        if (EmployeeTable.getValueAt(i, 0).toString() == "false") {
                            continue;
                        }
                        pStmt.setString(1, EmployeeTable.getValueAt(i, 2).toString());
                        if (EmployeeTable.getValueAt(i, 3).toString() == "空") {
                            pStmt.setNull(2, Types.CHAR);
                        } else {
                            pStmt.setString(2, EmployeeTable.getValueAt(i, 3).toString());
                        }
                        pStmt.setString(3, EmployeeTable.getValueAt(i, 4).toString());
                        pStmt.setString(4, EmployeeTable.getValueAt(i, 5).toString());
                        pStmt.setString(5, EmployeeTable.getValueAt(i, 6).toString());
                        pStmt.setString(6, EmployeeTable.getValueAt(i, 7).toString());
                        pStmt.setString(7, EmployeeTable.getValueAt(i, 8).toString());
                        pStmt.setString(8, EmployeeTable.getValueAt(i, 9).toString());
                        pStmt.setString(9, EmployeeTable.getValueAt(i, 10).toString());
                        pStmt.setString(10, EmployeeTable.getValueAt(i, 11).toString());
                        pStmt.setString(11, EmployeeTable.getValueAt(i, 12).toString());
                        pStmt.setString(12, EmployeeTable.getValueAt(i, 13).toString());
                        pStmt.setString(13, EmployeeTable.getValueAt(i, 14).toString());
                        pStmt.setString(14, EmployeeTable.getValueAt(i, 1).toString());
                        pStmt.addBatch();
                        modifyCount++;
                    }
                    if (JOptionPane.showOptionDialog(
                            null, "您即将修改" + modifyCount + "行，是否确认修改？", "警告",
                            JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE, null, null, null) == JOptionPane.YES_OPTION) {
                        pStmt.executeBatch();
                        int continueEdit = JOptionPane.showOptionDialog(null, "修改成功！是否继续修改？", "提示",
                                JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE, null, null, null);
                        if (continueEdit == JOptionPane.NO_OPTION) {
                            frame.dispose();
                        }
                    }*/
                    String selectQuery = "select * from templ for update";
                    Statement pStmtSelect = conn.createStatement();
                    ResultSet rsSelect = pStmtSelect.executeQuery(selectQuery);
                    int rowCount = EmployeeTable.getRowCount();

                    String updateQuery = "update TEMPL " +
                            "set EMPNO=?, FIRSTNME=?,MIDINIT=?,LASTNAME=?,WORKDEPT=?," +
                            "PHONENO=?,HIREDATE=?,JOB=?,EDLEVEL=?,SEX=?,BIRTHDATE=?," +
                            "SALARY=?,BONUS=?,COMM=?" +
                            "where current of ";
                    String cursorName = rsSelect.getCursorName();
                    PreparedStatement pStmt = conn.prepareStatement(updateQuery + cursorName);

                    int modifyCount = 0;
                    for (int i = 0; i < rowCount; i++) {
                        rsSelect.next();
                        if (EmployeeTable.getValueAt(EmployeeTable.convertRowIndexToModel(i), 0).toString() == "false") {
                            continue;
                        }
                        for (int j = 1; j <= 14; j++) {
                            if (EmployeeTable.getValueAt(EmployeeTable.convertRowIndexToModel(i), j).toString() == "空" || EmployeeTable.getValueAt(i, j).toString().trim().isEmpty()) {
                                pStmt.setNull(j, Types.CHAR);
                            } else {
                                pStmt.setString(j, EmployeeTable.getValueAt(EmployeeTable.convertRowIndexToModel(i), j).toString());
                            }
                        }
                        pStmt.executeUpdate();
                        modifyCount++;
                    }

                    int continueEdit = JOptionPane.showOptionDialog(null, "修改成功！是否继续修改？", "提示",
                            JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE, null, null, null);
                    if (continueEdit == JOptionPane.NO_OPTION) {
                        frame.dispose();
                    }

                } catch (SQLException ex) {
                    JOptionPane.showMessageDialog(null, "修改过程中出错！");
                    if (null != ex.getSQLState()) {
                        if (ex.getSQLState().equals("22018")) {
                            JOptionPane.showMessageDialog(null, "数据类型不匹配。请检查是否在表格中填写了正确的数据类型。");
                        } else if (ex.getSQLState().equals("23505")) {
                            JOptionPane.showMessageDialog(null, "您指定的员工工号重复，请检查！");
                        } else if (ex.getSQLState().equals("23503")) {
                            JOptionPane.showMessageDialog(null, "您指定的部门不存在，请检查！");
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
