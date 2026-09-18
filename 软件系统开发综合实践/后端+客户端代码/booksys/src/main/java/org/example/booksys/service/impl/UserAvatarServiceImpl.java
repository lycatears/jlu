package org.example.booksys.service.impl;

import org.example.booksys.service.UserAvatarService;
import org.springframework.stereotype.Service;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

@Service
public class UserAvatarServiceImpl implements UserAvatarService {

    private static final String AVATAR_BASE_PATH = "D:\\java\\book\\upload\\";

    @Override
    public void saveOrUpdateAvatar(Long userId, byte[] avatar) throws IOException {
        System.out.println("当前工作目录：" + System.getProperty("user.dir"));

        File dir = new File(AVATAR_BASE_PATH);
        if (!dir.exists()) {
            dir.mkdirs();
        }
        String filePath = AVATAR_BASE_PATH + userId + ".img";
        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(avatar);
        }
    }

    @Override
    public byte[] getAvatar(Long userId) throws IOException {
        String filePath = AVATAR_BASE_PATH + userId + ".img";
        File file = new File(filePath);
        if (!file.exists()) {
            return null;
        }
        return Files.readAllBytes(Paths.get(filePath));
    }
}
