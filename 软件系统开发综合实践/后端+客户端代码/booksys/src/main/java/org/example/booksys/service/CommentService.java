package org.example.booksys.service;

import org.example.booksys.entities.Comment;
import org.example.booksys.entities.CommentResponse;

import java.util.List;

public interface CommentService {

    List<Comment> getCommentsByBookId(Integer bookId, Integer start, Integer end);

    List<Comment> getCommentsByUserId(Integer userId, Integer start, Integer end);

    Boolean addComment(Integer userId, Integer bookId, Integer rating,
                       String createTime, String context);

    Double getBookAverageRating(Integer bookId);

    Integer getCommentsCountByBookId(Integer bookId);

    Integer getCommentsCountByUser(Integer userId);

    Integer getCommentsCount();

    void deleteComment(Integer commentId);

    void permanentlyDeleteComment(Integer commentId);

    List<CommentResponse> getAllComments(Integer start, Integer end);

    List<CommentResponse> getAllDeletedComments(Integer start, Integer end);

    void recoverDeletedComment(Integer commentId);
}
