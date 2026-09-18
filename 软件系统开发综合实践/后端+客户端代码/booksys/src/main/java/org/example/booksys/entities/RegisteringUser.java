package org.example.booksys.entities;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class RegisteringUser {
    public String uname;
    public String password;
    public String email;
}
