package org.example.booksys.mapper;

import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.example.booksys.entities.Book;
import org.example.booksys.entities.NewBook;
import org.example.booksys.entities.Tag;

import java.util.List;

@Mapper
public interface BookMapper {

    List<Book> getPagedBooks(Integer start, Integer end);

    Integer getBooksCount();

    Book getBook(Integer id);

    void addBook(NewBook book);

    void updateBook(Book book);

    @Delete("delete from BOOKMAN.\"book\" where \"book_id\" = #{id}")
    void deleteBook(Integer id);

    void addBookTags(@Param("bookId")Integer bookId, @Param("tagId") Integer tagId);

    @Select("select \"tag_id\", \"tag_name\" from BOOKMAN.\"tags\"")
    List<Tag> getAllTags();

    @Select("select \"BOOK_ID\".nextval from dual")
    Integer getNextBookId();

    void deleteBookTags(@Param("bookId")Integer bookId);

    @Delete("delete from BOOKMAN.\"deleted_book\" where \"book_id\" = #{bookId}")
    void permanentDeleteBook(@Param("bookId")Integer bookId);

    List<Book> getPagedDeletedBooks(Integer start, Integer end);

    Book getDeletedBook(Integer id);

    @Select("SELECT \"book_id\", \"book_title\", \"book_isbn\", \"book_author\", \"book_year\", \"stock\" book_stock, \"description\" FROM BOOKMAN.\"book\" WHERE \"book_title\" LIKE '%' || #{keyword} || '%'")
    List<Book> searchBooks(@Param("keyword") String keyword);
}