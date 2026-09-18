package org.example.booksys.service;

import org.apache.ibatis.annotations.Param;
import org.example.booksys.entities.Book;
import org.example.booksys.entities.NewBook;
import org.example.booksys.entities.Tag;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

public interface BookService {

    Book getBook(Integer id);

    List<Book> getPagedBooks(Integer start, Integer end);

    Integer getBooksCount();

    void addBook(NewBook book);

    void updateBook(Book book);

    void deleteBook(Integer id);

    @Transactional
    void addBookWithTags(NewBook book, List<Integer> tags);

    List<Tag> getAllTags();

    void updateTags(Book book);

    @Transactional
    void recoverDeletedBook(Integer bookId);

    List<Book> getPagedDeletedBooks(Integer start, Integer end);

    void permanentlyDeleteBook(Integer bookId);

    List<Book> searchBooks(String keyword);
}
