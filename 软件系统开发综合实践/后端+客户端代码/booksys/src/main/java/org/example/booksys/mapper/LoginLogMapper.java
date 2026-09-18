package org.example.booksys.mapper;

import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.example.booksys.entities.LoginLog;

import java.util.List;

@Mapper
public interface LoginLogMapper {

    List<LoginLog> pageFindLog(@Param("start")Integer start, @Param("end")Integer end);

    void insertLog(@Param("log") LoginLog log);

    Integer getLogCount();
}
