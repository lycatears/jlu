package com.db2work;


import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.util.Date;

public class Employee {
    private String employeeNo;
    private String firstName;
    private String lastName;
    private String midInit;
    private char sex;
    private short phoneNo;
    private short edLevel;
    private Date dateOfBirth;
    private Date dateOfHire;
    private String workDept;
    private String job;
    private BigDecimal salary;
    private BigDecimal bonus;
    private BigDecimal commission;

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getEmployeeNo() {
        return employeeNo;
    }

    public void setEmployeeNo(String employeeNo) {
        this.employeeNo = employeeNo;
    }

    public String getMidInit() {
        return midInit;
    }

    public void setMidInit(String midInit) {
        this.midInit = midInit;
    }

    public char getSex() {
        return sex;
    }

    public void setSex(char sex) {
        if (sex == 'M' || sex == 'F') {
            this.sex = sex;
        } else if (sex == 'm' || sex == 'f') {
            this.sex = (char) (sex - 'a' + 'A');
        }
    }

    public short getPhoneNo() {
        return phoneNo;
    }

    public void setPhoneNo(short phoneNo) {
        this.phoneNo = phoneNo;
    }

    public short getEdLevel() {
        return edLevel;
    }

    public void setEdLevel(short edLevel) {
        this.edLevel = edLevel;
    }

    public Date getDateOfBirth() {
        return dateOfBirth;
    }

    public void setDateOfBirth(Date dateOfBirth) {
        this.dateOfBirth = dateOfBirth;
    }

    public Date getDateOfHire() {
        return dateOfHire;
    }

    public String getDateOfBirthString() {
        return new String(String.valueOf(dateOfBirth.getYear() + 1900) + '-' + (dateOfBirth.getMonth() + 1) + '-' + dateOfBirth.getDay());
    }

    public void setDateOfHire(Date dateOfHire) {
        this.dateOfHire = dateOfHire;
    }

    public String getDateOfHireString() {
        return new String(String.valueOf(dateOfHire.getYear() + 1900) + '-' + (dateOfHire.getMonth() + 1) + '-' + dateOfHire.getDay());
    }

    public String getWorkDept() {
        return workDept;
    }

    public void setWorkDept(String workDept) {
        this.workDept = workDept;
    }

    public String getJob() {
        return job;
    }

    public void setJob(String job) {
        this.job = job;
    }

    public BigDecimal getSalary() {
        return salary;
    }

    public void setSalary(BigDecimal salary) {
        this.salary = salary;
    }

    public BigDecimal getBonus() {
        return bonus;
    }

    public void setBonus(BigDecimal bonus) {
        this.bonus = bonus;
    }

    public BigDecimal getCommission() {
        return commission;
    }

    public void setCommission(BigDecimal commission) {
        this.commission = commission;
    }

}
