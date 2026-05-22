package com.db2work;
import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import javax.swing.*;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.*;

public class ExportToExcel {

    private JTree tree1;
    private JTabbedPane tabbedPane1;
    private JSlider slider1;
    private JButton button1;
    private JRadioButton radioButton1;
    private JList list1;
    private JScrollBar scrollBar1;
    private JProgressBar progressBar1;

    public static void main(String[] args) {
        String jdbcURL = "jdbc:mysql://localhost:3306/university";
        String username = "root";
        String password = "1376abc6MySQL";

        String excelFilePath = "students.xlsx";

        try (Connection connection = DriverManager.getConnection(jdbcURL, username, password)) {
            String sql = "SELECT * FROM student";

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(sql);

            XSSFWorkbook workbook = new XSSFWorkbook();
            Sheet sheet = workbook.createSheet("Students");

            writeHeaderLine(sheet);

            int rowCount = 0;

            while (resultSet.next()) {
                Row row = sheet.createRow(++rowCount);
                writeDataLine(resultSet, row);
            }

            try (FileOutputStream outputStream = new FileOutputStream(excelFilePath)) {
                workbook.write(outputStream);
                workbook.close();
            }

            System.out.println("Excel file created successfully!");

        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }

    private static void writeHeaderLine(Sheet sheet) {
        Row headerRow = sheet.createRow(0);

        Cell headerCell = headerRow.createCell(0);
        headerCell.setCellValue("ID");

        headerCell = headerRow.createCell(1);
        headerCell.setCellValue("Name");

        headerCell = headerRow.createCell(2);
        headerCell.setCellValue("dept_name");

        headerCell = headerRow.createCell(3);
        headerCell.setCellValue("tot_cred");
    }

    private static void writeDataLine(ResultSet resultSet, Row row) throws SQLException {
        Cell cell = row.createCell(0);
        cell.setCellValue(resultSet.getInt("ID"));

        cell = row.createCell(1);
        cell.setCellValue(resultSet.getString("name"));

        cell = row.createCell(2);
        cell.setCellValue(resultSet.getString("dept_name"));

        cell = row.createCell(3);
        cell.setCellValue(resultSet.getString("tot_cred"));
    }
}
