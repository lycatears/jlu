package org.example.booksys.utils;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class TimeString {

    public static String getCurrentTimeString(){
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        return formatter.format(LocalDateTime.now());
    }
}
