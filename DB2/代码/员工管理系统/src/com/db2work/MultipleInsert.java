package com.db2work;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.math.BigDecimal;
import java.sql.*;
import java.util.ArrayList;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

public class MultipleInsert {
    JPanel MultipleInsert;
    private JPanel ImportFromFilePanel;
    private JTextField FilePath;
    private JLabel ImportFromFileLabel;
    private JButton BrowseFileButton;
    private JButton ImportButton;
    private JButton CommitButton;
    private JScrollPane ToImportPanel;
    private JTable ImportTable;
    private JButton DeleteRowButton;
    private JButton NewRowButton;
    private JLabel PromptLabel;
    private JPanel ToImport;
    private JTextField Keyword;
    private JButton SearchButton;
    private JLabel SearchLabel;
    private JButton SelectAllButton;
    private JButton DeSelectAllButton;
    private Connection conn;
    private Statement stmt;

    public MultipleInsert(Connection conn, Statement stmt) {
        this.conn = conn;
        this.stmt = stmt;
        JDialog loadingDialog = ManagerMain.createWaitingDialog("正在加载", "正在加载数据，请稍等...");
        loadingDialog.setVisible(true);

        String[] columnNames = {
                "选择", "工号", "名", "中间名", "姓", "部门",
                "电话分机号", "入职日期", "职位", "职级",
                "性别", "出生日期", "薪水", "奖金", "绩效"
        };

        DefaultTableModel model = new DefaultTableModel() {
            @Override
            public Class<?> getColumnClass(int columnIndex) {
                if (columnIndex >= 12) {
                    return BigDecimal.class;
                }
                return super.getColumnClass(columnIndex);
            }
        };
        ImportTable.setModel(model);
        for (String columnName : columnNames) {
            model.addColumn(columnName);
        }
        ImportTable.getColumnModel().getColumn(0).setCellRenderer(new ExportEmployeeToExcel.CheckboxRenderer());
        ImportTable.getColumnModel().getColumn(0).setCellEditor(new ExportEmployeeToExcel.CheckboxEditor());
        TableRowSorter<TableModel> sorter = new TableRowSorter<>(model);
        ImportTable.setRowSorter(sorter);
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

        ResultSet rs = null;
        BrowseFileButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFileChooser fileChooser = new JFileChooser();

                // 设置初始目录（可选）
                fileChooser.setCurrentDirectory(new File(System.getProperty("user.home")));

                // 显示打开文件对话框
                int returnValue = fileChooser.showOpenDialog(null);

                // 如果用户选择了文件，显示文件路径
                if (returnValue == JFileChooser.APPROVE_OPTION) {
                    if (fileChooser.getSelectedFile().getName().endsWith(".xlsx")) {
                        File selectedFile = fileChooser.getSelectedFile();
                        FilePath.setText(selectedFile.getAbsolutePath());
                    } else {
                        JOptionPane.showMessageDialog(null, "请选择.xlsx文件。", "错误", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }


        });
        ImportButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                //删除现有数据
                DefaultTableModel dtm = (DefaultTableModel) ImportTable.getModel();
                for (int i = 0; i < dtm.getRowCount(); i++) {
                    dtm.removeRow(i);
                }

                File excelFile = new File(FilePath.getText());
                ArrayList<ArrayList<Object>> data = new ArrayList<>();

                try {
                    // 读取第一个工作表
                    FileInputStream fis = new FileInputStream(excelFile);
                    Workbook workbook = new XSSFWorkbook(fis);
                    Sheet sheet = workbook.getSheetAt(0);

                    // 获取数据
                    for (int rowIndex = 1; rowIndex <= sheet.getLastRowNum(); rowIndex++) {
                        Row row = sheet.getRow(rowIndex);
                        data.add(new ArrayList<>());
                        if (row != null) {
                            for (int colIndex = 0; colIndex < columnNames.length; colIndex++) {
                                Cell cell = row.getCell(colIndex);
                                if (cell != null) {
                                    data.get(rowIndex - 1).add(cell.getStringCellValue());
                                } else {
                                    data.get(rowIndex - 1).add("空");
                                }
                            }
                        }
                    }
                    fis.close();
                    workbook.close();

                    for (int i = 0; i < data.size(); i++) {
                        Object[] row = new Object[columnNames.length + 1];
                        row[0] = true;
                        for (int j = 1; j <= columnNames.length; j++) {
                            String str = data.get(i).get(j - 1).toString();
                            row[j] = str;
                        }
                        model.addRow(row);
                    }

                } catch (FileNotFoundException ex) {
                    JOptionPane.showMessageDialog(null, "无法读取您指定的文件。这可能是以下原因导致的：\n" +
                                    "1.您选择的文件名指向文件夹，而非文件；\n" +
                                    "2.您选择的文件被其他程序占用；\n" +
                                    "3.指定的文件名过长，导致文件路径长度超出操作系统限制。\n" +
                                    "请检查是否有正在使用该文件的其他程序，然后修改文件路径，或者稍后重试。",
                            "错误", JOptionPane.ERROR_MESSAGE, null);
                } catch (IOException ioe) {
                    ioe.printStackTrace();
                }
            }
        });
        loadingDialog.dispose();
        DeleteRowButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                ArrayList<Integer> list = new ArrayList<>();
                for (int i = 0; i < ImportTable.getRowCount(); i++) {
                    if (ImportTable.getValueAt(i, 0).toString() == "true") {
                        list.add(i);
                    }
                }
                for (int i = list.size() - 1; i >= 0; i--) {
                    DefaultTableModel dtm = (DefaultTableModel) ImportTable.getModel();
                    int deleteIndex = ImportTable.convertRowIndexToModel(list.get(i));
                    dtm.removeRow(deleteIndex);
                }
            }
        });
        CommitButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                try {
                    int insertCount = 0;
                    PreparedStatement pStmt = conn.prepareStatement("insert into templ values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
                    for (int i = 0; i < ImportTable.getRowCount(); i++) {
                        if (ImportTable.getValueAt(i, 0).toString().equals("false")) {
                            continue;
                        }
                        pStmt.setString(1, ImportTable.getValueAt(i, 1).toString().trim());
                        pStmt.setString(2, ImportTable.getValueAt(i, 2).toString().trim());
                        if (!ImportTable.getValueAt(i, 3).toString().trim().equals("空") || ImportTable.getValueAt(i, 3).toString().trim().isEmpty()) {
                            pStmt.setString(3, ImportTable.getValueAt(i, 3).toString().trim());
                        } else {
                            pStmt.setNull(3, Types.CHAR);
                        }
                        pStmt.setString(4, ImportTable.getValueAt(i, 4).toString().trim());
                        pStmt.setString(5, ImportTable.getValueAt(i, 5).toString().trim());
                        pStmt.setString(6, ImportTable.getValueAt(i, 6).toString().trim());
                        pStmt.setDate(7, Date.valueOf(ImportTable.getValueAt(i, 7).toString().trim()));
                        pStmt.setString(8, ImportTable.getValueAt(i, 8).toString().trim());
                        pStmt.setShort(9, Short.parseShort(ImportTable.getValueAt(i, 9).toString().trim()));
                        pStmt.setString(10, ImportTable.getValueAt(i, 10).toString().trim());
                        pStmt.setDate(11, Date.valueOf(ImportTable.getValueAt(i, 11).toString().trim()));
                        pStmt.setBigDecimal(12, new BigDecimal(ImportTable.getValueAt(i, 12).toString().trim()));
                        pStmt.setBigDecimal(13, new BigDecimal(ImportTable.getValueAt(i, 13).toString().trim()));
                        pStmt.setBigDecimal(14, new BigDecimal(ImportTable.getValueAt(i, 14).toString().trim()));
                        pStmt.addBatch();
                        insertCount++;
                    }
                    int continueChoice = JOptionPane.showOptionDialog(null, "您即将插入" +
                            +insertCount + "行，是否确认？", "警告", JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE, null, null, null);
                    if (continueChoice == JOptionPane.YES_OPTION) {
                        pStmt.executeBatch();
                    }
                    JOptionPane.showMessageDialog(null, "添加成功！", "成功", JOptionPane.INFORMATION_MESSAGE);
                } catch (SQLException ex) {
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
        NewRowButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                SingleInsert.getEmployee(conn, stmt, ImportTable);
            }
        });
        SelectAllButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                int rowCount = ImportTable.getRowCount();
                for (int i = 0; i < rowCount; i++) {
                    ImportTable.setValueAt(true, i, 0);
                }
            }
        });
        DeSelectAllButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                int rowCount = ImportTable.getRowCount();
                for (int i = 0; i < rowCount; i++) {
                    ImportTable.setValueAt(false, i, 0);
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
