package org.example.booksys.controller;

import org.example.booksys.service.UserAvatarService;
import org.example.booksys.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.sql.SQLException;

@RestController
@RequestMapping("/api/avatar")
public class UserAvatarController {

    @Autowired
    private UserAvatarService userAvatarService;

    @Autowired
    private UserService userService;

    @PostMapping(value = "/{uname}", consumes = MediaType.MULTIPART_FORM_DATA_VALUE)
    public ResponseEntity<?> uploadAvatar(@PathVariable String uname, @RequestBody MultipartFile file) throws Exception {
        try {
            Integer userId = userService.getUser(uname).uid;
            userAvatarService.saveOrUpdateAvatar(Long.valueOf(userId), file.getBytes());
            return ResponseEntity.ok("Avatar uploaded successfully.");
        } catch (IOException e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("Upload failed.");
        }
    }

    @GetMapping(value = "/{uname}", produces = MediaType.IMAGE_JPEG_VALUE)
    public ResponseEntity<byte[]> getAvatar(@PathVariable String uname) throws SQLException, IOException {
        Integer userId = userService.getUser(uname).uid;
        byte[] image = userAvatarService.getAvatar(Long.valueOf(userId));
        if (image == null || image.length == 0) {
            return ResponseEntity.status(HttpStatus.NOT_FOUND).build();
        }
        return ResponseEntity.ok(image);
    }
}
