package org.example.booksys.service;

import org.example.booksys.entities.BorrowRecord;
import org.example.booksys.entities.BorrowRecordResponse;
import org.example.booksys.entities.PageResult;

import java.util.List;

public interface BorrowRecordService {

    List<BorrowRecord> getBorrowRecords(Integer start, Integer end);

    PageResult<BorrowRecord> getBorrowRecordsByBookId(Integer bookId, Integer start, Integer end);

    PageResult<BorrowRecord> getBorrowRecordsByUserId(Integer userId, Integer start, Integer end);

    PageResult<BorrowRecordResponse> getFullBorrowRecords(Integer start, Integer end);

    PageResult<BorrowRecordResponse> getFullBorrowRecordsByBookId(Integer bookId, Integer start, Integer end);

    PageResult<BorrowRecordResponse> getFullBorrowRecordsByUserId(Integer userId, Integer start, Integer end);

    Boolean borrowBook(Integer bookId, Integer userId);

    Boolean returnBook(Integer bookId, Integer userId);
}
