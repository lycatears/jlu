package com.example.demo.service.impl;

import com.example.demo.dao.UserDao;
import com.example.demo.dao.impl.UserDaoImpl;
import com.example.demo.pojo.User;
import com.example.demo.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Component;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

@Component
@Primary
public class UserServiceImpl implements UserService {
    @Autowired
    UserDao userDao;

    @Override
    public List<User> findAll() throws SQLException {
        ResultSet rs = userDao.findAll();
        ArrayList<User> resList = new ArrayList<>();
        while (rs.next()) {
            User user = new User(
                    rs.getInt("uid"),
                    rs.getString("uname"),
                    rs.getString("email"),
                    rs.getString("hashPassword")
            );
            resList.add(user);
        }

        return resList;
    }
}
