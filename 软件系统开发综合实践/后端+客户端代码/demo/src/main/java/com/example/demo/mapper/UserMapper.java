package com.example.demo.mapper;

import com.example.demo.pojo.User;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface UserMapper {

    @Select("select uid, uname, email, password from user")
    public List<User> findAll();

    @Select("select * from user where uname = #{uname}")
    User findByUname(@Param("uname") String uname);
}
