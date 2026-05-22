package com.db2work;

import javax.swing.*;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.math.BigDecimal;
import java.sql.*;

public class ManagerMain {
    private static final String SQL_URL = "jdbc:db2://192.168.232.131:50000/SAMPLE";
    private static final String SQL_USER = "JLU";
    private static final String SQL_PASSWORD = "826132";
    private static Connection conn = null;
    private static Statement stmt = null;

    static {
        try {
//            Class.forName("COM.ibm.db2.jdbc.app.DB2Driver");
            JDialog loadingDialog = createWaitingDialog("正在启动", "正在连接数据库，请稍等...");
            loadingDialog.setVisible(true);

            conn = DriverManager.getConnection(SQL_URL, SQL_USER, SQL_PASSWORD);
            stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);

            loadingDialog.dispose();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "\n  Error loading DB2 Driver...\n", "Error", JOptionPane.ERROR_MESSAGE);
            JOptionPane.showMessageDialog(null, "连接超时，请检查服务器连接。", "Error", JOptionPane.ERROR_MESSAGE);
            System.exit(1);
        }
    }

    private JPanel EmployeeManageMain;
    private JLabel EmployeeManageMainLabel;
    private JButton SingleInsertButton;
    private JButton MultipleInsertButton;
    private JButton RefreshButton;
    private JButton SubQueryButton;
    private JLabel EmployeeCountTextLabel;
    private JLabel EmployeeCount;
    private JTable TemplTable;
    private JScrollPane TemplPanel;
    private JButton ExportButton;
    private JButton DeleteButton;
    private JButton EditButton;
    private JButton SearchButton;
    private JLabel SearchLabel;
    private JTextField Keyword;
    private JButton MainSearchButton;
    private JButton SetPhotoButton;
    private JButton ShowPhotoButton;
    private JButton ExitButton;
    private  JFrame frame;

    public ManagerMain(JFrame frame) {
        SingleInsertButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFrame userFrame = new JFrame("单行插入");
                userFrame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("singleInsert.png")).getImage());
                userFrame.setContentPane(new SingleInsert(conn, stmt).SingleInsert);
                userFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                userFrame.pack();
                userFrame.setVisible(true);
            }
        });
        MultipleInsertButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFrame userFrame = new JFrame("多行插入向导");
                userFrame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("multipleInsert.png")).getImage());
                userFrame.setContentPane(new MultipleInsert(conn, stmt).MultipleInsert);
                userFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                userFrame.pack();
                userFrame.setVisible(true);
            }
        });
        SubQueryButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFrame userFrame = new JFrame("子查询插入向导");
                userFrame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("subqueryInsert.png")).getImage());
                userFrame.setContentPane(new SubqueryInsert(conn, userFrame).SubqueryInsert);
                userFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                userFrame.pack();
                userFrame.setVisible(true);
            }
        });
        RefreshButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JDialog loadingDataDialog = createWaitingDialog("加载数据", "正在加载数据，请稍等...");
                loadingDataDialog.setVisible(true);

                //设置表数据居中显示
                DefaultTableCellRenderer cr = new DefaultTableCellRenderer();
                cr.setHorizontalAlignment(JLabel.CENTER);
                TemplTable.setDefaultRenderer(Object.class, cr);

                String[] heads = {
                        "工号", "名", "中间名", "姓", "部门",
                        "电话分机号", "入职日期", "职位", "职级",
                        "性别", "出生日期", "薪水", "奖金", "绩效"
                };
                DefaultTableModel model = new DefaultTableModel(){
                    @Override
                    public Class<?> getColumnClass(int columnIndex) {
                        if (columnIndex >= 11) {
                            return BigDecimal.class;
                        }
                        return super.getColumnClass(columnIndex);
                    }
                };
                TableRowSorter<TableModel> sorter = new TableRowSorter<>(model);
                TemplTable.setModel(model);
                TemplTable.setRowSorter(sorter);
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
                for (String head : heads) {
                    model.addColumn(head);
                }

                ResultSet rs = null;
                try {
                    rs = stmt.executeQuery("select * from TEMPL");
                    ResultSetMetaData metaData = rs.getMetaData();
                    int columnCount = metaData.getColumnCount();
                    int rowCount = 0;

                    while (rs.next()) {
                        String[] row = new String[columnCount];
                        for (int i = 1; i <= columnCount; i++) {
                            String str = rs.getString(i);
                            if (!rs.wasNull() && !str.trim().isEmpty()) {
                                row[i - 1] = str;
                            } else {
                                row[i - 1] = "空";
                            }
                        }
                        model.addRow(row);
                        rowCount++;
                    }
                    EmployeeCount.setText(String.valueOf(rowCount));
                } catch (SQLException ex) {
                    JOptionPane.showMessageDialog(null, ex.getMessage(), "错误", JOptionPane.ERROR_MESSAGE);
                }
                loadingDataDialog.dispose();
            }
        });

        ExportButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFrame userFrame = new JFrame("导出员工信息表");
                userFrame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("exportToExcel.png")).getImage());
                userFrame.setContentPane(new ExportEmployeeToExcel(conn, userFrame).ExportEmployeeToExcel);
                userFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                userFrame.pack();
                userFrame.setVisible(true);
            }
        });
        DeleteButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFrame userFrame = new JFrame("删除员工信息");
                userFrame.setContentPane(new DeleteEmployee(conn, userFrame).DeleteEmployee);
                userFrame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("NO.png")).getImage());
                userFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                userFrame.pack();
                userFrame.setVisible(true);
            }
        });
        EditButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFrame userFrame = new JFrame("修改员工信息");
                userFrame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("edit.png")).getImage());
                userFrame.setContentPane(new EditEmployee(conn, userFrame).EditEmployee);
                userFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                userFrame.pack();
                userFrame.setVisible(true);
            }
        });
        ExitButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                System.exit(0);
            }
        });
        ShowPhotoButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFrame userFrame = new JFrame("查看员工照片");
                userFrame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("eyes.png")).getImage());
                userFrame.setContentPane(new ShowPhoto(conn, userFrame).ShowPhoto);
                userFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                userFrame.pack();
                userFrame.setSize(600,400);
                userFrame.setVisible(true);
            }
        });
        SetPhotoButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFrame userFrame = new JFrame("设置员工照片");
                userFrame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("setPhoto.png")).getImage());
                userFrame.setContentPane(new InsertPhoto(conn, userFrame).ShowPhoto);
                userFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                userFrame.pack();
                userFrame.setSize(600,400);
                userFrame.setVisible(true);
            }
        });
    }

    public static void main(String[] args) {
        try {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
        } catch (Exception e) {
            e.printStackTrace();
        }
        JFrame frame = new JFrame("员工信息管理");
        frame.setContentPane(new ManagerMain(frame).EmployeeManageMain);
        frame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("worker.png")).getImage());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
        frame.setSize(1000, 750);
    }

    static JDialog createWaitingDialog(String title, String message) {
        // 创建一个父窗体 JFrame
        JFrame frame = new JFrame("加载中");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 100);

        // 创建一个JDialog，用来显示正在连接的消息
        JDialog dialog = new JDialog(frame, title, false); // true表示模态对话框
        dialog.setLayout(new BoxLayout(dialog.getContentPane(), BoxLayout.Y_AXIS));
        dialog.setSize(300, 100);
        dialog.setLocationRelativeTo(frame);

        // 添加提示文本
        JLabel label = new JLabel(message, JLabel.CENTER);
        label.setFont(label.getFont().deriveFont(20.0f));
        dialog.add(label);
        dialog.setLayout(new FlowLayout(FlowLayout.CENTER));

        return dialog;
    }
}
