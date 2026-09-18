package org.example.booksys.controller;

import org.example.booksys.entities.*;
import org.example.booksys.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin
public class UserController {
    @Autowired
    private UserService userService;

    @GetMapping("/api/allUsers")
    public Result getAllUsers() {
        List<User> users = userService.getUsers();
        return Result.success(users);
    }

    @GetMapping("/api/user")
    public Result getUserPage(@RequestParam Integer start, @RequestParam Integer end) {
        PageResult<User> pr = new PageResult<>();
        pr.count = userService.getUserCount();
        pr.rows = userService.getPagedUsers(start, end);
        return Result.success(pr);
    }

    @GetMapping("/api/user/{uid}")
    public Result getUser(@PathVariable(value = "uid") String uid) {
        return Result.success(userService.getUser(uid));
    }

    @GetMapping("/userapi/user/{uid}")
    public Result userGetUser(@PathVariable(value = "uid") String uid) {
        return Result.success(userService.getUser(uid));
    }

    @DeleteMapping("/api/user/{uid}")
    public Result deleteUser(@PathVariable(value = "uid") String uid) {
        try {
            userService.deleteUser(Integer.parseInt(uid));
            return Result.success();
        } catch (Exception e) {
            return Result.error(e.getMessage());
        }
    }

    @PostMapping("/api/user")
    public Result addUser(@RequestBody RegisteringUser user) {
        User existUser = userService.getUser(user.uname);
        if (existUser != null) {
            return Result.success("用户名已存在，请选择其他用户名。");
        }
        if (user.uname == null || user.password == null || user.email == null) {
            return Result.error();
        }
        userService.addUser(user);
        return Result.success();
    }

    @PostMapping("/api/register")
    public Result registerUser(@RequestBody RegisteringUser user) {
        return addUser(user);
    }

    @PutMapping("/api/user")
    public Result updateUser(@RequestBody User user) {
        try {
            System.out.println(user.uid + String.valueOf(user.enableAfter));
            userService.updateUser(user);
            return Result.success();
        } catch (Exception e) {
            return Result.error(e.getMessage());
        }
    }

    @PostMapping("/api/deletedUser/{uid}")
    public Result recoverDeletedUser(@PathVariable(value = "uid") String uid) {
        try {
            userService.recoverUser(String.valueOf(uid));
            return Result.success();
        } catch (Exception e) {
            return Result.error(e.getMessage());
        }
    }

    @DeleteMapping("/api/deletedUser/{uid}")
    public Result permanentlyDeleteUser(@PathVariable(value = "uid") Integer uid) {
        try{
            userService.permanentlyDeleteUser(uid);
            return Result.success();
        }catch (Exception e){
            return Result.error(e.getMessage());
        }
    }

    @GetMapping("/api/deletedUser")
    public Result getDeletedUserPage(@RequestParam Integer start, @RequestParam Integer end) {
        PageResult<User> pr = new PageResult<>();
        pr.count = userService.getDeletedUserCount();
        pr.rows = userService.getPagedDeletedUsers(start, end);
        return Result.success(pr);
    }

    @GetMapping("/api/loginLog")
    public Result getPagedLoginLog(@RequestParam Integer start, @RequestParam Integer end){
        PageResult<LoginLog> pr = new PageResult<>();
        pr.count = userService.getLoginLogCount();
        pr.rows = userService.getPagedLoginLog(start, end);
        return Result.success(pr);
    }

    @GetMapping("/api/user/search")
    public Result getPagedLoginLog(@RequestParam String keyword){
        PageResult<User> pr = new PageResult<>();
        List<User> ls = userService.searchUser(keyword);
        pr.count = ls.size();
        pr.rows = ls;
        return Result.success(pr);
    }
}
