package com.db2work;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.math.BigDecimal;
import java.sql.*;
import java.util.Date;

public class SingleInsert extends JPanel {
    JPanel SingleInsert;
    private JPanel SingleInputPanel;
    private JLabel EMPNOLabel;
    private JTextField EMPNO;
    private JTextField FirstName;
    private JLabel FirstNameLabel;
    private JLabel MidinitLabel;
    private JTextField Midinit;
    private JLabel LastNameLabel;
    private JTextField LastName;
    private JTextField DEPTNO;
    private JLabel DEPTNOLabel;
    private JLabel PhoneLabel;
    private JTextField Phone;
    private JLabel HireDateLabel;
    private JSpinner HireYear;
    private JLabel HireYearLabel;
    private JSpinner HireMonth;
    private JLabel HireMonthLabel;
    private JSpinner HireDay;
    private JLabel EdlevelLabel;
    private JSpinner Edlevel;
    private JLabel SexLabel;
    private JComboBox Sex;
    private JLabel BirthdayLabel;
    private JTextField Salary;
    private JLabel SalaryLabel;
    private JSpinner BirthYear;
    private JLabel BirthYearLabel;
    private JSpinner BirthMonth;
    private JLabel BirthMonthLabel;
    private JSpinner BirthDay;
    private JLabel BirthDayLabel;
    private JTextField Bonus;
    private JLabel BonusLabel;
    private JLabel CommissionLabel;
    private JTextField Commission;
    private JLabel JobLabel;
    private JTextField Job;
    private JButton CommitButton;
    private Connection conn;
    private Statement stmt;

    public SingleInsert(Connection conn, Statement stmt) {
        this.conn = conn;
        this.stmt = stmt;
        HireYear.setModel(new SpinnerNumberModel(new Date().getYear() + 1900, 1900, 2100, 1));
        HireYear.setEditor(new JSpinner.NumberEditor(HireYear, "####"));
        HireMonth.setModel(new SpinnerNumberModel(new Date().getMonth() + 1, 1, 12, 1));
        HireDay.setModel(new SpinnerNumberModel(new Date().getDate(), 1, 31, 1));
        BirthYear.setModel(new SpinnerNumberModel(new Date().getYear() + 1900, 1900, 2100, 1));
        BirthYear.setEditor(new JSpinner.NumberEditor(BirthYear, "####"));
        BirthMonth.setModel(new SpinnerNumberModel(new Date().getMonth() + 1, 1, 12, 1));
        BirthDay.setModel(new SpinnerNumberModel(new Date().getDate(), 1, 31, 1));

        CommitButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (checkIntegrity()) {
                    try {
                        PreparedStatement pStmt = conn.prepareStatement("insert into templ values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
                        pStmt.setString(1, EMPNO.getText().trim());
                        pStmt.setString(2, FirstName.getText().trim());
                        if (!Midinit.getText().equals("")) {
                            pStmt.setString(3, Midinit.getText().trim());
                        } else {
                            pStmt.setNull(3, Types.CHAR);
                        }
                        pStmt.setString(4, LastName.getText().trim());
                        pStmt.setString(5, DEPTNO.getText().trim());
                        pStmt.setString(6, Phone.getText().trim());
                        pStmt.setDate(7, new java.sql.Date((Integer) HireYear.getValue()-1900, (Integer) HireMonth.getValue(), (Integer) HireDay.getValue()));
                        pStmt.setString(8, Job.getText().trim());
                        pStmt.setShort(9, ((Integer) Edlevel.getValue()).shortValue());
                        if (Sex.getSelectedIndex() == 0) {
                            pStmt.setString(10, "M");
                        } else {
                            pStmt.setString(10, "F");
                        }
                        pStmt.setDate(11, new java.sql.Date((Integer) BirthYear.getValue()-1900, (Integer) BirthMonth.getValue(), (Integer) BirthDay.getValue()));
                        pStmt.setBigDecimal(12, new BigDecimal(Salary.getText().trim()));
                        pStmt.setBigDecimal(13, new BigDecimal(Bonus.getText().trim()));
                        pStmt.setBigDecimal(14, new BigDecimal(Commission.getText().trim()));
                        pStmt.execute();
                        JOptionPane.showMessageDialog(null, "插入成功！", "成功", JOptionPane.INFORMATION_MESSAGE);
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
            }
        });
    }

    private boolean checkIntegrity() {
        if (EMPNO.getText().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工工号未设置，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        }
        if (FirstName.getText().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工名未设置，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        }
        if (LastName.getText().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工姓氏未设置，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        }
        if (DEPTNO.getText().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工部门未设置，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        }
        if (Phone.getText().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工电话分机号码未设置，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        }
        if (HireYear.getValue().toString().trim().isEmpty() || HireMonth.getValue().toString().trim().isEmpty() || HireDay.getValue().toString().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工入职日期设置非法，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        }

        try {
            java.sql.Date date = new java.sql.Date((Integer) HireYear.getValue(), (Integer) HireMonth.getValue(), (Integer) HireDay.getValue());
            date = new java.sql.Date((Integer) BirthYear.getValue(), (Integer) BirthMonth.getValue(), (Integer) BirthDay.getValue());
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "日期设置错误，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
        }

        if (BirthYear.getValue().toString().trim().isEmpty() || BirthMonth.getValue().toString().trim().isEmpty() || BirthDay.getValue().toString().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工出生日期设置非法，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        }
        if (Edlevel.getValue().toString().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工职级设置非法，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        }
        if (Salary.getText().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工工资未设置，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        } else {
            BigDecimal tmpbd = BigDecimal.valueOf(0);
            try {
                tmpbd = new BigDecimal(Salary.getText().trim());
            } catch (Exception e) {
                JOptionPane.showMessageDialog(this, "员工工资数据非数字型，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
                return false;
            }
            if (tmpbd.compareTo(BigDecimal.valueOf(0)) == -1) {
                JOptionPane.showMessageDialog(this, "员工工资不可为负数，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
                return false;
            }
        }
        if (Bonus.getText().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工奖金未设置，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        } else {
            BigDecimal tmpbd = BigDecimal.valueOf(0);
            try {
                tmpbd = new BigDecimal(Bonus.getText().trim());
            } catch (Exception e) {
                JOptionPane.showMessageDialog(this, "员工奖金数据非数字型，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
                return false;
            }
            if (tmpbd.compareTo(BigDecimal.valueOf(0)) == -1) {
                JOptionPane.showMessageDialog(this, "员工奖金不可为负数，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
                return false;
            }
        }
        if (Commission.getText().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工绩效未设置，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        } else {
            BigDecimal tmpbd = BigDecimal.valueOf(0);
            try {
                tmpbd = new BigDecimal(Commission.getText().trim());
            } catch (Exception e) {
                JOptionPane.showMessageDialog(this, "员工绩效数据非数字型，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
                return false;
            }
            if (tmpbd.compareTo(BigDecimal.valueOf(0)) == -1) {
                JOptionPane.showMessageDialog(this, "员工绩效不可为负数，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
                return false;
            }
        }
        if (Job.getText().trim().isEmpty()) {
            JOptionPane.showMessageDialog(this, "员工岗位未设置，请检查输入。", "错误", JOptionPane.WARNING_MESSAGE);
            return false;
        }

        return true;
    }

    public static void getEmployee(Connection conn, Statement stmt, JTable table) {
        Employee emp = new Employee();
        SingleInsert singleInsertPanel = new SingleInsert(conn, stmt);

        JFrame userFrame = new JFrame("单行插入");
        userFrame.setIconImage(new ImageIcon(ExportEmployeeToExcel.class.getClassLoader().getResource("singleInsert.png")).getImage());
        userFrame.setContentPane(singleInsertPanel.SingleInsert);
        userFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        userFrame.pack();

        MouseListener[] listeners = singleInsertPanel.CommitButton.getListeners(MouseListener.class);
        for (MouseListener listener : listeners) {
            singleInsertPanel.CommitButton.removeMouseListener(listener);
        }
        singleInsertPanel.CommitButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (singleInsertPanel.checkIntegrity()) {
                    emp.setEmployeeNo(singleInsertPanel.EMPNO.getText().trim());
                    emp.setFirstName(singleInsertPanel.FirstName.getText().trim());
                    emp.setLastName(singleInsertPanel.LastName.getText().trim());
                    emp.setMidInit(singleInsertPanel.Midinit.getText().trim());
                    emp.setWorkDept(singleInsertPanel.DEPTNO.getText().trim());
                    emp.setPhoneNo(Short.parseShort(singleInsertPanel.Phone.getText().trim()));
                    emp.setDateOfHire(new java.sql.Date(((Integer) singleInsertPanel.HireYear.getValue()-1900), (Integer) singleInsertPanel.HireMonth.getValue(), (Integer) singleInsertPanel.HireDay.getValue()));
                    emp.setJob(singleInsertPanel.Job.getText().trim());
                    emp.setEdLevel(((Integer) singleInsertPanel.Edlevel.getValue()).shortValue());
                    if (singleInsertPanel.Sex.getSelectedIndex() == 0) {
                        emp.setSex('M');
                    } else {
                        emp.setSex('F');
                    }
                    emp.setDateOfBirth(new java.sql.Date(((Integer) singleInsertPanel.BirthYear.getValue()-1900), (Integer) singleInsertPanel.BirthMonth.getValue(), (Integer) singleInsertPanel.BirthDay.getValue()));
                    emp.setSalary(new BigDecimal(singleInsertPanel.Salary.getText().trim()));
                    emp.setBonus(new BigDecimal(singleInsertPanel.Bonus.getText().trim()));
                    emp.setCommission(new BigDecimal(singleInsertPanel.Commission.getText().trim()));

                    DefaultTableModel model = (DefaultTableModel) table.getModel();
                    model.addRow(new Object[]{
                            true, emp.getEmployeeNo(), emp.getFirstName(), emp.getMidInit(), emp.getLastName(),
                            emp.getWorkDept(), emp.getPhoneNo(), emp.getDateOfHire(),
                            emp.getJob(),emp.getEdLevel(),emp.getSex(), emp.getDateOfBirth(),
                            emp.getSalary(), emp.getBonus(), emp.getCommission()});

                    userFrame.dispose();
                }
            }
        });
        userFrame.setVisible(true);
    }
}
