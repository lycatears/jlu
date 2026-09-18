package com.example.demo.dao.impl;

import com.example.demo.dao.UserDao;
import org.springframework.stereotype.Component;

import java.sql.*;

@Component
public class UserDaoImpl implements UserDao {
    @Override
    public ResultSet findAll() throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/website","root","1376abc6MySQL");
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("select uid, uname, email, password from user");

        return rs;
    }
}
