package org.example.booksys.entities;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class NewBook {
    public Integer bookId;
    public String bookTitle;
    public String bookIsbn;
    public String bookAuthor;
    public String bookYear;
    public Integer bookStock;
    public String bookStatus;

    public String createTime;
    public String description;
    public List<Integer> tags;

    public static NewBook fromBook(Book book) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

        NewBook nb = new NewBook();
        nb.bookId = book.bookId;
        nb.bookAuthor = book.bookAuthor;
        nb.bookTitle = book.bookTitle;
        nb.bookIsbn = book.bookIsbn;
        nb.bookStock = book.bookStock;
        nb.bookStatus = book.bookStatus;
        nb.bookYear = book.bookYear;
        nb.createTime = dateFormat.format(book.createTime);
        nb.description = book.description;
        nb.tags = new ArrayList<>();
        for (Tag tag : book.tags) {
            nb.tags.add(tag.tagId);
        }

        return nb;
    }
}
