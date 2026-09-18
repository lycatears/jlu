package org.example.booksys;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.ServletComponentScan;
import org.springframework.cache.annotation.EnableCaching;
import org.springframework.scheduling.annotation.EnableScheduling;

@ServletComponentScan
@SpringBootApplication
@EnableCaching
@EnableScheduling
public class BooksysApplication {

    public static void main(String[] args) {
        SpringApplication.run(BooksysApplication.class, args);
    }

}
