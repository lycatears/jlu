package org.example.booksys.controller;

import org.example.booksys.entities.Book;
import org.example.booksys.entities.Result;
import org.example.booksys.service.BookService;
import org.example.booksys.service.BorrowRecordService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
public class BorrowRecordController {
    @Autowired
    BorrowRecordService borrowRecordService;

    @Autowired
    BookService bookService;

    @GetMapping("/api/record")
    public Result getAllRecords(@RequestParam Integer start, @RequestParam Integer end) {
        return Result.success(borrowRecordService.getFullBorrowRecords(start, end));
    }

    @GetMapping("/api/record/user")
    public Result getRecordsByUser(@RequestParam Integer userId, @RequestParam Integer start, @RequestParam Integer end) {
        return Result.success(borrowRecordService.getFullBorrowRecordsByUserId(userId, start, end));
    }

    @GetMapping("/userapi/record/user")
    public Result userGetRecordsByUser(@RequestParam Integer userId, @RequestParam Integer start, @RequestParam Integer end) {
        return getRecordsByUser(userId, start, end);
    }

    @GetMapping("/api/record/book")
    public Result getRecordsByBook(@RequestParam Integer bookId, @RequestParam Integer start, @RequestParam Integer end) {
        return Result.success(borrowRecordService.getFullBorrowRecordsByBookId(bookId, start, end));
    }

    @GetMapping("/userapi/record/book")
    public Result userGetRecordsByBook(@RequestParam Integer bookId, @RequestParam Integer start, @RequestParam Integer end) {
        return getRecordsByBook(bookId, start, end);
    }

    @PostMapping("/api/record")
    public Result borrow(@RequestParam Integer userId, @RequestParam Integer bookId) {
        Book book = bookService.getBook(bookId);
        if (book.bookStock <= 0) {
            return Result.error("库存不足！");
        }
        Boolean res = borrowRecordService.borrowBook(bookId, userId);
        if (!res) {
            return Result.error("您已经借过该书，请勿重复借阅！");
        } else {
            return Result.success();
        }
    }

    @PostMapping("/userapi/record")
    public Result userBorrow(@RequestParam Integer userId, @RequestParam Integer bookId) {
        return borrow(userId, bookId);
    }

    @PutMapping("/api/record")
    public Result returnBook(@RequestParam Integer userId, @RequestParam Integer bookId) {
        Boolean res = borrowRecordService.returnBook(bookId, userId);
        if (!res) {
            return Result.error("您未借过该书！");
        } else {
            return Result.success();
        }
    }

    @PutMapping("/userapi/record")
    public Result userReturnBook(@RequestParam Integer userId, @RequestParam Integer bookId) {
        return returnBook(userId, bookId);
    }
}
