package org.example.booksys.service;

import java.io.IOException;
import java.sql.SQLException;

public interface UserAvatarService {
    void saveOrUpdateAvatar(Long userId, byte[] avatar) throws SQLException, IOException;

    byte[] getAvatar(Long userId) throws SQLException, IOException;
}
