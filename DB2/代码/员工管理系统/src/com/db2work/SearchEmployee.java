package com.db2work;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.math.BigDecimal;
import java.sql.*;
import java.util.Date;

public class SearchEmployee {
    private JTable SearchTable;
    private JScrollPane TablePanel;
    private JCheckBox EmpNoCheckBox;
    private JTextField EmpNo;
    private JCheckBox FirstNameCheckBox;
    private JTextField FirstName;
    private JCheckBox MidInitCheckBox;
    private JTextField MidInit;
    private JCheckBox LastNameCheckBox;
    private JTextField LastName;
    private JCheckBox SexCheckBox;
    private JComboBox Sex;
    private JTabbedPane InfoPanel;
    private JTextField DeptNo;
    private JCheckBox PhoneCheckBox;
    private JTextField Phone;
    private JCheckBox DeptNoCheckBox;
    private JButton SearchButton;
    private JButton ExportButton;
    private JPanel BasicInfoPanel;
    private JPanel TimePanel;
    private JPanel JobPanel;
    private JPanel IncomePanel;
    private JCheckBox EarlistHireCheckBox;
    private JPanel EarlistHire;
    private JSpinner EarlistHireYear;
    private JLabel EarlistHireYearLabel;
    private JSpinner EarlistHireMonth;
    private JLabel EarlistHireMonthLabel;
    private JSpinner EarlistHireDay;
    private JLabel EarlistHireDayLabel;
    private JCheckBox LatestHireCheckBox;
    private JSpinner LatestHireYear;
    private JLabel LatestHireYearLabel;
    private JSpinner LatestHireMonth;
    private JLabel LatestHireMonthLabel;
    private JSpinner LatestHireDay;
    private JLabel LatestHireDayLabel;
    private JCheckBox EarlistBirthCheckBox;
    private JSpinner EarlistBirthYear;
    private JLabel EarlistBirthYearLabel;
    private JSpinner EarlistBirthMonth;
    private JLabel EarlistBirthMonthLabel;
    private JSpinner EarlistBirthDay;
    private JLabel EarlistBirthDayLabel;
    private JCheckBox LatestBirthCheckBox;
    private JPanel EarlistBirth;
    private JPanel LatestHire;
    private JPanel LatestBirth;
    private JSpinner LatestBirthYear;
    private JLabel LatestBirthYearLabel;
    private JSpinner LatestBirthMonth;
    private JLabel LatestBirthMonthLabel;
    private JSpinner LatestBirthDay;
    private JLabel LatestBirthDayLabel;
    JPanel SearchEmployee;
    private JCheckBox EdLevelCheckBox;
    private JPanel EdLevel;
    private JLabel LowestEdLevelLabel;
    private JSpinner LowestEdLevel;
    private JLabel HighestestEdLevelLabel;
    private JSpinner HighestestEdLevel;
    private JCheckBox JobCheckBox;
    private JTextField Job;
    private JCheckBox SalaryCheckBox;
    private JPanel Salary;
    private JLabel LowestSalaryLabel;
    private JSpinner LowestSalary;
    private JLabel HighestSalaryLabel;
    private JSpinner HighestSalary;
    private JCheckBox BonusCheckBox;
    private JPanel Bonus;
    private JLabel LowestBonusLabel;
    private JSpinner LowestBonus;
    private JLabel HighestBonusLabel;
    private JSpinner HighestBonus;
    private JCheckBox CommisionCheckBox;
    private JLabel LowestCommisionLabel;
    private JPanel Commision;
    private JSpinner LowestCommision;
    private JLabel HighestCommisionLabel;
    private JSpinner HighestCommision;
    private JLabel Title;
    private JButton ExitButton;
    private Connection conn;
    private JFrame frame;

    public SearchEmployee(Connection conn, JFrame frame) {
        JDialog loadingDialog = ManagerMain.createWaitingDialog("正在加载", "正在加载数据，请稍等...");
        loadingDialog.setVisible(true);
        this.conn = conn;
        this.frame = frame;

        EarlistHireYear.setModel(new SpinnerNumberModel(new Date().getYear() + 1900, 1900, 2100, 1));
        EarlistHireYear.setEditor(new JSpinner.NumberEditor(EarlistHireYear, "####"));
        EarlistHireMonth.setModel(new SpinnerNumberModel(new Date().getMonth() + 1, 1, 12, 1));
        EarlistHireDay.setModel(new SpinnerNumberModel(new Date().getDate(), 1, 31, 1));
        EarlistBirthYear.setModel(new SpinnerNumberModel(new Date().getYear() + 1900, 1900, 2100, 1));
        EarlistBirthYear.setEditor(new JSpinner.NumberEditor(EarlistBirthYear, "####"));
        EarlistBirthMonth.setModel(new SpinnerNumberModel(new Date().getMonth() + 1, 1, 12, 1));
        EarlistBirthDay.setModel(new SpinnerNumberModel(new Date().getDate(), 1, 31, 1));
        LatestHireYear.setModel(new SpinnerNumberModel(new Date().getYear() + 1900, 1900, 2100, 1));
        LatestHireYear.setEditor(new JSpinner.NumberEditor(EarlistHireYear, "####"));
        LatestHireMonth.setModel(new SpinnerNumberModel(new Date().getMonth() + 1, 1, 12, 1));
        LatestHireDay.setModel(new SpinnerNumberModel(new Date().getDate(), 1, 31, 1));
        LatestBirthYear.setModel(new SpinnerNumberModel(new Date().getYear() + 1900, 1900, 2100, 1));
        LatestBirthYear.setEditor(new JSpinner.NumberEditor(EarlistBirthYear, "####"));
        LatestBirthMonth.setModel(new SpinnerNumberModel(new Date().getMonth() + 1, 1, 12, 1));
        LatestBirthDay.setModel(new SpinnerNumberModel(new Date().getDate(), 1, 31, 1));

        // 打开导出界面时，默认显示全部员工信息
        String[] columnNames = {
                "选择", "工号", "名", "中间名", "姓", "部门",
                "电话分机号", "入职日期", "职位", "职级",
                "性别", "出生日期", "薪水", "奖金", "绩效"
        };
        DefaultTableModel model = new DefaultTableModel(){
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

        SearchTable.setModel(model);
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

            SearchTable.getColumnModel().getColumn(0).setCellRenderer(new CheckboxRenderer());
            SearchTable.getColumnModel().getColumn(0).setCellEditor(new CheckboxEditor());

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
