package org.example.booksys.mapper;

import org.apache.ibatis.jdbc.SQL;
import org.example.booksys.entities.User;

public class UserSqlProvider {
    public String addUser(User user) {
        return new SQL() {{
            INSERT_INTO("BOOKMAN.\"user\"");
            VALUES("\"uname\"", "#{uname}");
            VALUES("\"email\"", "#{email}");
            VALUES("\"salt\"", "#{salt}");
            VALUES("\"register_time\"", "#{registerTime}");
            VALUES("\"last_login_time\"", "#{lastLoginTime}");
            VALUES("\"slogan\"", "#{slogan}");
            VALUES("\"hash_password\"", "#{hashPassword}");
            VALUES("\"enable_after\"", "#{enableAfter}");
            VALUES("\"group\"", "#{group}");
        }}.toString();
    }

    public String updateUser(User user) {
        return new SQL(){{
            UPDATE("BOOKMAN.\"user\"");
            SET("\"uid\" = #{uid}");
            SET("\"uname\" = #{uname}");
            SET("\"email\" = #{email}");
            SET("\"salt\" = #{salt}");
            SET("\"register_time\" = #{registerTime}");
            SET("\"last_login_time\" = #{lastLoginTime}");
            SET("\"slogan\" = #{slogan}");
            SET("\"hash_password\" = #{hashPassword}");
            SET("\"enable_after\" = #{enableAfter}");
            SET("\"group\" = #{group}");
            WHERE("\"uid\" = #{uid}");
        }}.toString();
    }
}
