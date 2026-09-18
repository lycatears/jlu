package org.example.booksys.service.impl;

import org.example.booksys.entities.LoginData;
import org.example.booksys.entities.LoginLog;
import org.example.booksys.entities.RegisteringUser;
import org.example.booksys.entities.User;
import org.example.booksys.mapper.LoginLogMapper;
import org.example.booksys.mapper.UserMapper;
import org.example.booksys.service.UserService;
import org.example.booksys.utils.HashPassword;
import org.example.booksys.utils.JwtUtil;
import org.example.booksys.utils.RandomString;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cglib.core.Local;
import org.springframework.stereotype.Service;

import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.*;

@Service
public class UserServiceImpl implements UserService {

    @Autowired
    private UserMapper userMapper;

    @Autowired
    private LoginLogMapper loginLogMapper;

    @Override
    public List<User> getUsers() {
        return userMapper.findAll();
    }

    @Override
    public Integer getUserCount() {
        return userMapper.getUserCount();
    }

    @Override
    public List<User> getPagedUsers(Integer start, Integer end) {
        return userMapper.pageFindUser(start, end);
    }

    @Override
    public User getUser(String idOrName) {
        try {
            Integer id = Integer.valueOf(idOrName);
            User res = userMapper.findById(id);

            if (res == null) {
                return userMapper.findByUsername(idOrName);
            }

            return res;
        } catch (NumberFormatException e) {
            return userMapper.findByUsername(idOrName);
        }
    }

    @Override
    public void addUser(RegisteringUser rUser) {
        User user = new User();
        user.uname = rUser.uname;
        user.email = rUser.email;
        user.salt = RandomString.getRandomString(16);
        user.hashPassword = HashPassword.hashPassword(rUser.password, user.salt);
        user.registerTime = new Date();
        user.enableAfter = new Date(0);
        user.lastLoginTime = new Date(0);
        user.group = "user";
        user.slogan = "";
        user.avatar = "";
        userMapper.addUser(user);
    }

    @Override
    public void deleteUser(Integer uid) {
        userMapper.deleteUser(uid);
    }

    @Override
    public void updateUser(User newUser) {
        User oldUser = this.getUser(String.valueOf(newUser.uid));
        oldUser.email = newUser.email != null ? newUser.email : oldUser.email;
        oldUser.slogan = newUser.slogan != null ? newUser.slogan : "";
        oldUser.avatar = newUser.avatar != null ? newUser.avatar : "";
        oldUser.enableAfter = newUser.enableAfter != null ? newUser.enableAfter : new Date();
        oldUser.lastLoginTime = newUser.lastLoginTime != null ? newUser.lastLoginTime : new Date();
        oldUser.group = newUser.group != null ? newUser.group : oldUser.group;
//        oldUser.salt = newUser.salt != null ? newUser.salt : oldUser.salt;
//        oldUser.hashPassword = newUser.hashPassword != null ? HashPassword.hashPassword(newUser.hashPassword, oldUser.salt) : oldUser.hashPassword;
        oldUser.uname = newUser.uname != null ? newUser.uname : oldUser.uname;
        oldUser.registerTime = newUser.registerTime != null ? newUser.registerTime : new Date();
        userMapper.updateUser(oldUser);
    }

    @Override
    public List<User> getPagedDeletedUsers(Integer start, Integer end) {
        return userMapper.getPagedDeletedUsers(start, end);
    }

    @Override
    public Integer getDeletedUserCount() {
        return userMapper.getDeletedUserCount();
    }

    @Override
    public User getDeletedUser(String idOrName) {
        try {
            Integer id = Integer.valueOf(idOrName);
            return userMapper.findDeletedUserById(id);
        } catch (NumberFormatException e) {
            return userMapper.findDeletedUserByUsername(idOrName);
        }
    }

    @Override
    public void recoverUser(String idOrName) throws Exception {
        User user = this.getDeletedUser(idOrName);
        userMapper.addUser(user);
        userMapper.permanentlyDeleteUser(user.uid);
    }

    @Override
    public void permanentlyDeleteUser(Integer uid) {
        userMapper.permanentlyDeleteUser(uid);
    }

    @Override
    public LoginData login(RegisteringUser user, String ip) throws Exception {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        String currentTime = formatter.format(LocalDateTime.now());
        User rawUser = userMapper.findByUsername(user.uname);
        if (rawUser == null) {
            return null;
        }

        Instant instant = rawUser.enableAfter.toInstant(); // 将Date转换为Instant
        ZoneId zoneId = ZoneId.systemDefault(); // 获取系统默认时区
        LocalDateTime localDateTime = instant.atZone(zoneId).toLocalDateTime();
        String enableAfter = localDateTime.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));

        String salt = rawUser.salt;
        String hashed = HashPassword.hashPassword(user.password, salt);
        boolean res = hashed.equals(rawUser.hashPassword);

        rawUser.lastLoginTime = new Date();
        this.updateUser(rawUser);

        LoginData loginData = new LoginData();

        if (currentTime.compareTo(enableAfter) < 0) {
            loginData.enableAfter = enableAfter;
        } else {
            Map<String, Object> map = new HashMap<>();
            map.put("enableAfter", enableAfter);
            map.put("uname", rawUser.uname);
            map.put("uid", rawUser.uid);
            map.put("isAdmin", rawUser.group.equals("admin"));
            loginData.token = JwtUtil.generateToken(map);
            loginData.uname = rawUser.uname;
            loginData.avatar = rawUser.avatar;
            loginData.email = rawUser.email;
            loginData.isAdmin = Objects.equals(rawUser.group, "admin");
            loginData.uid = rawUser.uid;
        }

        insertLog(user.uname, ip, res && loginData.enableAfter == null ? "OK" : "Failed");

        return res ? loginData : null;
    }

    @Override
    public List<LoginLog> getPagedLoginLog(Integer start, Integer end) {
        return loginLogMapper.pageFindLog(start, end);
    }

    public void insertLog(String uname, String ip, String status) {
        User user = getUser(uname);
        LoginLog loginLog = new LoginLog();
        loginLog.ip = ip;
        loginLog.time = new Date();
        loginLog.uid = user.uid;
        loginLog.status = status;

        loginLogMapper.insertLog(loginLog);
    }

    public Integer getLoginLogCount() {
        return loginLogMapper.getLogCount();
    }

    public Boolean verifyUser(String token) {
        return JwtUtil.validateToken(token);
    }

    @Override
    public List<User> searchUser(String keyword) {
        return userMapper.searchUser(keyword);
    }
}
