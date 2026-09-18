package org.example.booksys.mapper;

import org.apache.ibatis.annotations.*;
import org.example.booksys.utils.BlobTypeHandler;

import java.sql.Blob;

import static org.apache.ibatis.type.JdbcType.BLOB;

@Mapper
public interface UserAvatarMapper {
    @Insert("INSERT INTO BOOKMAN.\"user_avatar\" (\"user_id\", \"avatar\") VALUES (#{userId}, #{avatar})")
    void insertAvatar(@Param("userId") Long userId, @Param("avatar") byte[] avatar);

    @Update("UPDATE BOOKMAN.\"user_avatar\" SET \"avatar\" = #{avatar} WHERE \"user_id\" = #{userId}")
    void updateAvatar(@Param("userId") Long userId, @Param("avatar") byte[] avatar);

    @Select("SELECT \"avatar\" FROM BOOKMAN.\"user_avatar\" WHERE \"user_id\" = #{userId}")
    @Result(column = "avatar", property = "avatar", typeHandler = org.example.booksys.utils.BlobToBytesTypeHandler.class)
    byte[] getAvatarByUserId(@Param("userId") Long userId);
}
