package org.example.booksys.entities;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class LoginData {
    public String uname;
    public String avatar;
    public String email;
    public String token;
    public String enableAfter;
    public Boolean isAdmin;
    public Integer uid;
}
