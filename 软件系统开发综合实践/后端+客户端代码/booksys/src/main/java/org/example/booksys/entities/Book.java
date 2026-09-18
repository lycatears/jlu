package org.example.booksys.entities;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;
import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Book {
    public Integer bookId;
    public String bookTitle;
    public String bookIsbn;
    public String bookAuthor;
    public String bookYear;
    public Integer bookStock;
    public String bookStatus;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    public Date createTime;
    public String description;
    public List<Tag> tags;
}
