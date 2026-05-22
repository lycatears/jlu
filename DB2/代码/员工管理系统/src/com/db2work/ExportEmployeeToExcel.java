package com.db2work;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;
import javax.swing.text.DateFormatter;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.math.BigDecimal;
import java.sql.*;
import java.text.DateFormat;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class ExportEmployeeToExcel {
    JPanel ExportEmployeeToExcel;
    private JPanel ExportFilePanel;
    private JTextField FilePath;
    private JButton BrowseButton;
    private JLabel FilenameLabel;
    private JLabel FilePathLabel;
    private JTextField FileName;
    private JButton UseDateButton;
    private JButton UseTimeButton;
    private JButton OKButton;
    private JButton CancelButton;
    private JTable PreviewTable;
    private JScrollPane PreviewPanel;
    private JButton DeleteButton;
    private JButton ExportSelectedButton;
    private JPanel Preview;
    private JTextField Keyword;
    private JButton SearchButton;
    private JLabel SearchLabel;
    private JProgressBar progressBar1;
    private JLabel MsgBar;
    private JLabel ProgressBarLabel;
    private Connection conn;
    private JFrame frame;

    public ExportEmployeeToExcel(Connection conn, JFrame frame) {
        this.conn = conn;
        this.frame = frame;
        JDialog loadingDialog = ManagerMain.createWaitingDialog("正在加载", "正在加载数据，请稍等...");
        loadingDialog.setVisible(true);
        BrowseButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setCurrentDirectory(new File(System.getProperty("user.home")));
                fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                int returnValue = fileChooser.showOpenDialog(null);

                if (returnValue == JFileChooser.APPROVE_OPTION) {
                    File selectedFile = fileChooser.getSelectedFile();
                    FilePath.setText(selectedFile.getAbsolutePath());
                }
            }
        });
        UseDateButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                FileName.setText(LocalDate.now().toString() + ".xlsx");
            }
        });
        UseTimeButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                FileName.setText(LocalTime.now().format(DateTimeFormatter.ofPattern("HH-mm-ss")) + ".xlsx");
            }
        });
        FilePath.setText((new File(System.getProperty("user.home"))).getPath());

        // 打开导出界面时，默认显示全部员工信息
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
        PreviewTable.setModel(model);
        TableRowSorter<TableModel> sorter = new TableRowSorter<>(model);
        PreviewTable.setRowSorter(sorter);
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
            rs = stmt.executeQuery("select * from TEMPL");
            ResultSetMetaData metaData = rs.getMetaData();
            int columnCount = metaData.getColumnCount();
            int rowCount = 0;

            PreviewTable.getColumnModel().getColumn(0).setCellRenderer(new CheckboxRenderer());
            PreviewTable.getColumnModel().getColumn(0).setCellEditor(new CheckboxEditor());

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

        CancelButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                frame.dispose();
            }
        });
        DeleteButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                int rowCount = PreviewTable.getRowCount();
                for (int i = 0; i < rowCount; i++) {
                    PreviewTable.setValueAt(false, i, 0);
                }
            }
        });
        OKButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                MsgBar.setText("正在创建Excel表格");
                String excelFilePath = FilePath.getText() + File.separator + FileName.getText();
                XSSFWorkbook workbook = new XSSFWorkbook();
                Sheet sheet = workbook.createSheet();
                int tickedRowCount = 0;
                for(int i=0;i<PreviewTable.getRowCount();i++) {
                    if(PreviewTable.getValueAt(i,0).toString()=="true"){
                        tickedRowCount++;
                    }
                }
                progressBar1.setMaximum(tickedRowCount);

                // 写入表头
                MsgBar.setText("正在写入表头");
                Row headerRow = sheet.createRow(0);
                for (int i = 1; i < columnNames.length; i++) {
                    Cell headerCell = headerRow.createCell(i - 1);
                    headerCell.setCellValue(columnNames[i]);
                }

                // 写入实际数据
                MsgBar.setText("正在写入数据");
                for (int i = 0; i < PreviewTable.getRowCount(); i++) {
                    Row dataRow = sheet.createRow(i + 1);
                    for (int j = 1; j < columnNames.length; j++) {
                        Cell dataCell = dataRow.createCell(j - 1);
                        dataCell.setCellValue(PreviewTable.getValueAt(i, j).toString());
                    }
                    progressBar1.setValue(i + 1);
                }

                try {
                    MsgBar.setText("正在完成导出");
                    FileOutputStream fos = new FileOutputStream(excelFilePath);
                    workbook.write(fos);
                    workbook.close();
                    fos.close();
                    JOptionPane.showMessageDialog(null, "导出成功！");
                    MsgBar.setText("导出成功");
                } catch (FileNotFoundException ex) {
                    JOptionPane.showMessageDialog(null, "文件无法写入。这可能是以下原因导致的：\n" +
                                    "1.您选择的文件名指向文件夹，而非文件；\n" +
                                    "2.您选择的文件被其他程序占用，或者被设为只读属性；\n" +
                                    "3.指定的文件名过长，导致文件路径长度超出操作系统限制。\n" +
                                    "请检查您选择的文件是否为只读属性，是否有正在使用该文件的其他程序，然后修改文件路径，或者稍后重试。",
                            "错误", JOptionPane.ERROR_MESSAGE, null);
                    MsgBar.setText("导出文件失败");
                } catch (IOException ex) {
                    JOptionPane.showMessageDialog(null, "IO异常", "错误", JOptionPane.ERROR_MESSAGE);
                    MsgBar.setText("IO设备异常");
                }
            }
        });
        ExportSelectedButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {

                MsgBar.setText("正在创建Excel表格");
                String excelFilePath = FilePath.getText() + File.separator + FileName.getText();
                XSSFWorkbook workbook = new XSSFWorkbook();
                Sheet sheet = workbook.createSheet();

                // 写入表头
                MsgBar.setText("正在写入表头");
                Row headerRow = sheet.createRow(0);
                for (int i = 1; i < columnNames.length; i++) {
                    Cell headerCell = headerRow.createCell(i - 1);
                    headerCell.setCellValue(columnNames[i]);
                }

                // 写入实际数据
                MsgBar.setText("正在写入数据");
                ArrayList<Integer> list = new ArrayList<>();
                for (int i = 0; i < PreviewTable.getRowCount(); i++) {
                    if (PreviewTable.getValueAt(i, 0).toString() == "true") {
                        list.add(i);
                    }
                }
                progressBar1.setMaximum(list.size());

                for(int i = 0; i < list.size(); i++){
                    Row dataRow = sheet.createRow(i+1);
                    for (int j = 1; j < columnNames.length; j++) {
                        Cell dataCell = dataRow.createCell(j - 1);
                        dataCell.setCellValue(PreviewTable.getValueAt(i, j).toString());
                    }
                    progressBar1.setValue(i + 1);
                }

                try {
                    MsgBar.setText("正在完成导出");
                    FileOutputStream fos = new FileOutputStream(excelFilePath);
                    workbook.write(fos);
                    workbook.close();
                    fos.close();
                    JOptionPane.showMessageDialog(null, "导出成功！");
                    MsgBar.setText("导出成功");
                } catch (FileNotFoundException ex) {
                    JOptionPane.showMessageDialog(null, "文件无法写入。这可能是以下原因导致的：\n" +
                                    "1.您选择的文件名指向文件夹，而非文件；\n" +
                                    "2.您选择的文件被其他程序占用，或者被设为只读属性；\n" +
                                    "3.指定的文件名过长，导致文件路径长度超出操作系统限制。\n" +
                                    "请检查您选择的文件是否为只读属性，是否有正在使用该文件的其他程序，然后修改文件路径，或者稍后重试。",
                            "错误", JOptionPane.ERROR_MESSAGE, null);
                    MsgBar.setText("导出文件失败");
                } catch (IOException ex) {
                    JOptionPane.showMessageDialog(null, "IO异常", "错误", JOptionPane.ERROR_MESSAGE);
                    MsgBar.setText("IO设备异常");
                }
            }
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
