package org.example.booksys.controller;

import org.example.booksys.entities.*;
import org.example.booksys.service.BookService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin
public class BookController {
    @Autowired
    BookService bookService;

    @GetMapping("/api/book/{book_id}")
    public Result getBook(@PathVariable(value = "book_id") Integer book_id) {
        Book book = bookService.getBook(book_id);
        return Result.success(book);
    }

    @GetMapping("/userapi/book/{book_id}")
    public Result userGetBook(@PathVariable(value = "book_id") Integer book_id) {
        return getBook(book_id);
    }

    @GetMapping("/api/book")
    public Result getPagedBooks(@RequestParam Integer start, @RequestParam Integer end) {
        PageResult<Book> books = new PageResult<>();
        books.count = bookService.getBooksCount();
        books.rows = bookService.getPagedBooks(start, end);
        return Result.success(books);
    }

    @GetMapping("/userapi/book")
    public Result userGetPagedBooks(@RequestParam Integer start, @RequestParam Integer end) {
        return getPagedBooks(start, end);
    }

    @PostMapping("/api/book")
    public Result addBook(@RequestBody NewBook book) {
        if (book.tags == null || book.tags.isEmpty()) {
            bookService.addBook(book);
        } else {
            bookService.addBookWithTags(book, book.tags);
        }
        return Result.success();
    }

    @PutMapping("/api/book")
    public Result updateBook(@RequestBody Book book) {
        bookService.updateBook(book);
        return Result.success();
    }

    @DeleteMapping("/api/book/{book_id}")
    public Result deleteBook(@PathVariable(value = "book_id") Integer book_id) {
        bookService.deleteBook(book_id);
        return Result.success();
    }

    @GetMapping("/api/tags")
    public Result getTags() {
        List<Tag> tags = bookService.getAllTags();
        return Result.success(tags);
    }

    @GetMapping("/userapi/tags")
    public Result userGetTags() {
        return getTags();
    }

    @PostMapping("/api/tags")
    public Result setTag(@RequestBody Book book) {
        bookService.updateTags(book);
        return Result.success();
    }

    @GetMapping("/api/deletedBook")
    public Result getPagedDeletedBooks(Integer start, Integer end){
        List<Book> lb = bookService.getPagedDeletedBooks(start, end);
        PageResult<Book> pr = new PageResult<>();
        pr.rows = lb;
        return Result.success(pr);
    }

    @PostMapping("/api/deletedBook/{bookId}")
    public Result recoverBook(@PathVariable(value = "bookId") Integer bookId){
        bookService.recoverDeletedBook(bookId);
        return Result.success();
    }

    @DeleteMapping("/api/deletedBook/{bookId}")
    public Result permanentlyDeleteBook(@PathVariable(value = "bookId") Integer bookId){
        bookService.permanentlyDeleteBook(bookId);
        return Result.success();
    }

    @GetMapping("/api/book/search")
    public Result searchBook(@RequestParam String keyword) {
        List<Book> ls = bookService.searchBooks(keyword);
        PageResult<Book> pr = new PageResult<>();
        pr.rows = ls;
        pr.count = ls.size();
        return Result.success(pr);
    }

    @GetMapping("/userapi/book/search")
    public Result userSearchBook(@RequestParam String keyword) {
        return searchBook(keyword);
    }
}
