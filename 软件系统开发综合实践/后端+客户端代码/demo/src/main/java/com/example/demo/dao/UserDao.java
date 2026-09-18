package com.example.demo.dao;

import com.example.demo.pojo.User;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

public interface UserDao {
    ResultSet findAll() throws SQLException;
}
