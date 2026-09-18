package com.example.demo.controller;

import com.example.demo.mapper.UserMapper;
import com.example.demo.pojo.User;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.List;

@SpringBootTest
public class TestClass {

    @Autowired
    private UserMapper userMapper;

    @Test
    public void testFindAll(){
        List<User> users = userMapper.findAll();
        users.forEach(System.out::println);
    }
}
