package org.example.booksys;

import org.example.booksys.entities.User;
import org.example.booksys.mapper.UserMapper;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

@SpringBootTest
class BooksysApplicationTests {

    @Autowired
    private UserMapper userMapper;
    private static final Logger logger = LoggerFactory.getLogger(BooksysApplicationTests.class);

    @Test
    void loadingTest() {
        logger.info("loadingTest Past");
    }

    @Test
    void sqlConnectionTest() throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:oracle:thin:@//localhost/orcl","BOOKMAN","lsw8261325027904");
        logger.info("sqlConnectionTest Past");
        connection.close();
    }

    @Test
    void selectUserTest() {
        User u = userMapper.findById(1);
        if (u != null) {
            logger.info(u.toString());
        }
        logger.info("selectUserTest Past");
    }

}
