package org.example.booksys.service;

import org.apache.ibatis.annotations.Param;
import org.example.booksys.entities.LoginData;
import org.example.booksys.entities.LoginLog;
import org.example.booksys.entities.RegisteringUser;
import org.example.booksys.entities.User;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

public interface UserService {

    List<User> getUsers();

    Integer getUserCount();

    List<User> getPagedUsers(Integer start, Integer end);

    User getUser(String idOrName);

    void addUser(RegisteringUser rUser);

    void deleteUser(Integer uid);

    void updateUser(User newUser);

    List<User> getPagedDeletedUsers(Integer start, Integer end);

    Integer getDeletedUserCount();

    User getDeletedUser(String idOrName);

    @Transactional
    void recoverUser(String idOrName) throws Exception;

    void permanentlyDeleteUser(Integer uid);

    @Transactional
    LoginData login(RegisteringUser user, String ip) throws Exception;

    List<LoginLog> getPagedLoginLog(@Param("start")Integer start, @Param("end")Integer end);

    void insertLog(String uname, String ip, String status);

    Integer getLoginLogCount();

    Boolean verifyUser(String token);

    List<User> searchUser(String keyword);
}
