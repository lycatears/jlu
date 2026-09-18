package org.example.booksys.service.impl;

import org.example.booksys.entities.Book;
import org.example.booksys.entities.NewBook;
import org.example.booksys.entities.Tag;
import org.example.booksys.mapper.BookMapper;
import org.example.booksys.service.BookService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

@Service
public class BookServiceImpl implements BookService {
    @Autowired
    BookMapper bookMapper;

    @Override
    public Book getBook(Integer id) {
        return bookMapper.getBook(id);
    }

    @Override
    public List<Book> getPagedBooks(Integer start, Integer end) {
        return bookMapper.getPagedBooks(start, end);
    }

    @Override
    public Integer getBooksCount() {
        return bookMapper.getBooksCount();
    }

    @Override
    public void addBook(NewBook book) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        if (book.bookStatus == null) {
            book.bookStatus = "OK";
        }
        if (book.createTime == null) {
            book.createTime = dateFormat.format(new Date());
        }
        if (book.bookId == null) {
            book.bookId = bookMapper.getNextBookId();
        }
        bookMapper.addBook(book);
    }

    @Override
    public void updateBook(Book book) {
        bookMapper.updateBook(book);
    }

    @Override
    public void deleteBook(Integer id) {
        bookMapper.deleteBook(id);
    }

    @Override
    public void addBookWithTags(NewBook book, List<Integer> tags) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        if (book.bookStatus == null) {
            book.bookStatus = "OK";
        }
        if (book.createTime == null) {
            book.createTime = dateFormat.format(new Date());
        }
        Integer bookId = bookMapper.getNextBookId();
        book.bookId = bookId;
        bookMapper.addBook(book);

        if (book.tags != null && !book.tags.isEmpty()) {
            for (Integer tagId : tags) {
                bookMapper.addBookTags(bookId, tagId);
            }
        }

    }

    @Override
    public List<Tag> getAllTags() {
        return bookMapper.getAllTags();
    }

    @Override
    public void updateTags(Book book) {
        bookMapper.deleteBookTags(book.bookId);
        if (book.tags != null && !book.tags.isEmpty()) {
            for (Tag tag : book.tags) {
                bookMapper.addBookTags(book.bookId, tag.tagId);
            }
        }
    }

    @Override
    public void recoverDeletedBook(Integer bookId) {
        Book book = bookMapper.getDeletedBook(bookId);
        bookMapper.permanentDeleteBook(bookId);
        if (book.createTime == null) {
            book.createTime = new Date();
        }
        bookMapper.addBook(NewBook.fromBook(book));
    }

    @Override
    public List<Book> getPagedDeletedBooks(Integer start, Integer end) {
        return bookMapper.getPagedDeletedBooks(start, end);
    }

    @Override
    public void permanentlyDeleteBook(Integer bookId) {
        bookMapper.permanentDeleteBook(bookId);
    }

    @Override
    public List<Book> searchBooks(String keyword) {
        return bookMapper.searchBooks(keyword);
    }

}
