package org.example.booksys.service.impl;

import org.example.booksys.entities.Book;
import org.example.booksys.entities.BorrowRecord;
import org.example.booksys.entities.BorrowRecordResponse;
import org.example.booksys.entities.PageResult;
import org.example.booksys.mapper.BorrowRecordMapper;
import org.example.booksys.service.BookService;
import org.example.booksys.service.BorrowRecordService;
import org.example.booksys.utils.TimeString;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class BorrowRecordServiceImpl implements BorrowRecordService {
    @Autowired
    BorrowRecordMapper borrowRecordMapper;

    @Autowired
    BookService bookService;

    @Override
    public List<BorrowRecord> getBorrowRecords(Integer start, Integer end) {
        return borrowRecordMapper.selectAllBorrowRecords(start, end);
    }

    @Override
    public PageResult<BorrowRecord> getBorrowRecordsByBookId(Integer bookId, Integer start, Integer end) {
        PageResult<BorrowRecord> pr = new PageResult<>();
        pr.rows = borrowRecordMapper.selectBorrowRecordsByBookId(bookId, start, end);
        pr.count = borrowRecordMapper.getBorrowRecordsCountByBookId(bookId);
        return pr;
    }

    @Override
    public PageResult<BorrowRecord> getBorrowRecordsByUserId(Integer userId, Integer start, Integer end) {
        PageResult<BorrowRecord> pr = new PageResult<>();
        pr.rows = borrowRecordMapper.selectBorrowRecordsByUserId(userId, start, end);
        pr.count = borrowRecordMapper.getBorrowRecordsCountByUserId(userId);
        return pr;
    }

    @Override
    public PageResult<BorrowRecordResponse> getFullBorrowRecords(Integer start, Integer end) {
        PageResult<BorrowRecordResponse> pr = new PageResult<>();
        pr.rows = borrowRecordMapper.selectAllFullBorrowRecords(start, end);
        pr.count = borrowRecordMapper.getAllBorrowRecordsCount();
        return pr;
    }

    @Override
    public PageResult<BorrowRecordResponse> getFullBorrowRecordsByBookId(Integer bookId, Integer start, Integer end) {
        PageResult<BorrowRecordResponse> pr = new PageResult<>();
        pr.rows = borrowRecordMapper.selectFullBorrowRecordsByBookId(bookId, start, end);
        pr.count = borrowRecordMapper.getBorrowRecordsCountByBookId(bookId);
        return pr;
    }

    @Override
    public PageResult<BorrowRecordResponse> getFullBorrowRecordsByUserId(Integer userId, Integer start, Integer end) {
        PageResult<BorrowRecordResponse> pr = new PageResult<>();
        pr.rows = borrowRecordMapper.selectFullBorrowRecordsByUserId(userId, start, end);
        pr.count = borrowRecordMapper.getBorrowRecordsCountByUserId(userId);
        return pr;
    }

    @Override
    @Transactional
    public Boolean borrowBook(Integer bookId, Integer userId) {
        List<BorrowRecord> ls = borrowRecordMapper.getBorrowRecordsNotReturned(userId, bookId);
        if (!ls.isEmpty()) {
            return false;
        } else {
            Book book = bookService.getBook(bookId);
            book.bookStock--;
            bookService.updateBook(book);
            Integer nextId = borrowRecordMapper.getNextBorrowRecordId();
            borrowRecordMapper.insertBorrowRecord(nextId, bookId, userId, TimeString.getCurrentTimeString());
            return true;
        }
    }

    @Override
    @Transactional
    public Boolean returnBook(Integer bookId, Integer userId) {
        List<BorrowRecord> ls = borrowRecordMapper.getBorrowRecordsNotReturned(userId, bookId);
        if (ls.isEmpty()) {
            return false;
        } else {
            Book book = bookService.getBook(bookId);
            book.bookStock++;
            bookService.updateBook(book);
            borrowRecordMapper.updateBorrowRecord(ls.get(0).recordId, TimeString.getCurrentTimeString());
            return true;
        }
    }
}
