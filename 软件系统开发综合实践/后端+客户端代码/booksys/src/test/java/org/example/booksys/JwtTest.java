package org.example.booksys;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import org.example.booksys.utils.HashPassword;
import org.junit.jupiter.api.Test;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

public class JwtTest {
    String tokenTest = "eyJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ0ZXN0IiwiZXhwIjoxNzQ0MjE0ODExLCJpYXQiOjE3NDQyMTM4MTExMjl9.3Cp_VuyuQGvv5hqrD5oy9E49-w30QQJhPaeIYwyaBhc";

    @Test
    public void testGenerateToken() {
        Map<String, Object> claims = new HashMap<>();
        claims.put("sub", "test");
        claims.put("iat", System.currentTimeMillis());
        claims.put("exp", System.currentTimeMillis() + 864000*1000);

        tokenTest = Jwts.builder()
                .signWith(SignatureAlgorithm.HS256, "LsW8261San25027JiUO4==")
                .addClaims(claims)
                .setExpiration(new Date(System.currentTimeMillis() + 1000*1000))
                .compact();
        System.out.println(tokenTest);
    }

    @Test
    public void testParseToken() {
        Claims claims = Jwts.parser().setSigningKey("MTE0NTE0MTkxOTgxMA==")
                .parseClaimsJws(tokenTest).getBody();
        System.out.println(claims);
    }

    @Test
    public void testHash() {
        String salt = "0beXsXDkINpM3yP3";
        String password = "826132";
        String hashed = HashPassword.hashPassword(password, salt);
        System.out.println(hashed);
    }
}
