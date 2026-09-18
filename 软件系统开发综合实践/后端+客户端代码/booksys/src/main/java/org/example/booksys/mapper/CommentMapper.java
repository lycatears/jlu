package org.example.booksys.mapper;

import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.example.booksys.entities.Comment;
import org.example.booksys.entities.CommentResponse;

import java.util.List;

@Mapper
public interface CommentMapper {
    List<Comment> findCommentByBookId(Integer bookId, Integer start, Integer end);

    // 根据userId分页查询评论
    List<Comment> findCommentByUserId(Integer userId, Integer start, Integer end);

    Integer getBookCommentCount(Integer bookId);

    Integer getUserCommentCount(Integer userId);

    Integer getCommentsCount();

    List<CommentResponse> getAllComments(Integer start, Integer end);

    List<CommentResponse> getAllDeletedComments(Integer start, Integer end);

    void addComment(Comment comment);

    @Select("select COMMENT_ID.nextval from dual")
    Integer getNextCommentId();

    @Delete("delete from BOOKMAN.\"comments\" where \"comment_id\" = #{commentId}")
    void deleteComment(Integer commentId);

    @Delete("delete from BOOKMAN.\"deleted_comments\" where \"comment_id\" = #{commentId}")
    void permanentlyDeleteComment(Integer commentId);

    @Select("select * from \"deleted_comments\" where \"comment_id\" = #{commentId}")
    List<Comment> getDeletedCommentById(Integer commentId);

    // 计算某本书的平均评分
    @Select("SELECT AVG(\"rating\") as rating FROM BOOKMAN.\"comments\" WHERE \"book_id\" = #{bookId}")
    Double calculateAverageRatingByBookId(@Param("bookId") Integer bookId);

    @Select("select max(\"floor_id\") + 1 as next from BOOKMAN.\"comments\" where \"book_id\" = #{bookId}")
    Integer getNextFloorId(Integer bookId);
}
