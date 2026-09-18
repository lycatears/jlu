package org.example.booksys.mapper;

import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.example.booksys.entities.BorrowRecord;
import org.example.booksys.entities.BorrowRecordResponse;

import java.util.List;

@Mapper

public interface BorrowRecordMapper {
    // 分页查询所有借书记录
    List<BorrowRecord> selectAllBorrowRecords(@Param("start") Integer start, @Param("end") Integer end);

    List<BorrowRecordResponse> selectAllFullBorrowRecords(@Param("start") Integer start, @Param("end") Integer end);

    // 根据userId分页查询该用户的借书记录
    List<BorrowRecord> selectBorrowRecordsByUserId(@Param("userId") Integer userId, @Param("start") Integer start, @Param("end") Integer end);

    List<BorrowRecordResponse> selectFullBorrowRecordsByUserId(@Param("userId") Integer userId, @Param("start") Integer start, @Param("end") Integer end);

    // 根据bookId分页查询该书的借书记录
    List<BorrowRecord> selectBorrowRecordsByBookId(@Param("bookId") Integer bookId, @Param("start") Integer start, @Param("end") Integer end);

    List<BorrowRecordResponse> selectFullBorrowRecordsByBookId(@Param("bookId") Integer bookId, @Param("start") Integer start, @Param("end") Integer end);

    // 插入一条借书记录（归还日期留空）
    void insertBorrowRecord(@Param("recordId") Integer recordId, @Param("bookId") Integer bookId, @Param("userId") Integer userId, @Param("borrowDate") String borrowDate);

    // 更新借书记录，记录下归还日期
    void updateBorrowRecord(@Param("recordId") Integer recordId, @Param("returnDate") String returnDate);

    @Select("select count(*) from BOOKMAN.\"borrow_record\"")
    Integer getAllBorrowRecordsCount();

    @Select("select count(*) recordCount from BOOKMAN.\"borrow_record\" where \"user_id\" = #{userId}")
    Integer getBorrowRecordsCountByUserId(@Param("userId") Integer userId);

    @Select("select count(*) recordCount from BOOKMAN.\"borrow_record\" where \"book_id\" = #{bookId}")
    Integer getBorrowRecordsCountByBookId(@Param("bookId") Integer bookId);

    @Select("select * from BOOKMAN.\"borrow_record\" where \"book_id\" = #{bookId} and \"user_id\" = #{userId} and \"return_date\" is null")
    List<BorrowRecord> getBorrowRecordsNotReturned(@Param("userId") Integer userId, @Param("bookId") Integer bookId);

    @Select("select borrow_record_id.nextval from dual")
    Integer getNextBorrowRecordId();
}