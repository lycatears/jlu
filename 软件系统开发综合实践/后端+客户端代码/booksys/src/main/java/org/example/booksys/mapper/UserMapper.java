package org.example.booksys.mapper;

import org.apache.ibatis.annotations.*;
import org.example.booksys.entities.User;

import java.util.List;

@Mapper
public interface UserMapper {

    @Select("select * from BOOKMAN.\"user\" order by \"uid\"")
    List<User> findAll();

    List<User> pageFindUser(@Param("start")Integer start, @Param("end")Integer end);

    @Select("select count(*) from BOOKMAN.\"user\"")
    Integer getUserCount();


    @Select("select * from BOOKMAN.\"user\" where \"uid\" = #{id}")
    User findById(@Param("id")Integer id);

    @Select("select * from BOOKMAN.\"user\" where \"uname\" = #{uname}")
    User findByUsername(@Param("uname") String username);

    @UpdateProvider(type = UserSqlProvider.class, method = "updateUser")
    void updateUser(User user);

    @InsertProvider(type = UserSqlProvider.class, method = "addUser")
    void addUser(User user);

    @Delete("delete from BOOKMAN.\"user\" where \"uid\" = #{id}")
    void deleteUser(@Param("id") Integer id);

    @Select("select count(*) from BOOKMAN.\"deleted_user\"")
    Integer getDeletedUserCount();

    List<User> getPagedDeletedUsers(@Param("start")Integer start, @Param("end")Integer end);

    @Select("select * from BOOKMAN.\"deleted_user\" where \"uid\" = #{id}")
    User findDeletedUserById(@Param("id")Integer id);

    @Select("select * from BOOKMAN.\"deleted_user\" where \"uname\" = #{uname}")
    User findDeletedUserByUsername(@Param("uname") String username);

    @Delete("delete from BOOKMAN.\"deleted_user\" where \"uid\" = #{id}")
    void permanentlyDeleteUser(@Param("id") Integer id);

    List<User> searchUser(@Param("keyword") String keyword);
}
