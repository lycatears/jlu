package com.example.demo.service;

import com.example.demo.pojo.User;

import java.sql.SQLException;
import java.util.List;

public interface UserService {
    List<User> findAll() throws SQLException;
}
