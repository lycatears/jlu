package org.example.booksys.controller;

import jakarta.servlet.http.HttpServletRequest;
import org.example.booksys.entities.LoginData;
import org.example.booksys.entities.RegisteringUser;
import org.example.booksys.entities.Result;
import org.example.booksys.service.UserService;
import org.example.booksys.utils.RequestIP;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@CrossOrigin
@RestController
public class LoginController {
    @Autowired
    private UserService userService;

    @PostMapping("/api/login")
    public Result login(@RequestBody RegisteringUser user, HttpServletRequest servletRequest) {
        try {
            LoginData ld = userService.login(user, RequestIP.getClientIp(servletRequest));
            if (ld != null) {
                if (ld.enableAfter != null) {
                    return Result.error("您已被封禁，请在 " + ld.enableAfter + "后登录");
                }
                return Result.success(ld);
            } else {
                return Result.error();
            }
        } catch (Exception e) {
            return Result.error(e.getMessage());
        }
    }

}
