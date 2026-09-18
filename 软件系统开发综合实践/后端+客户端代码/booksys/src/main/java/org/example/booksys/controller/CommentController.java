package org.example.booksys.controller;

import org.example.booksys.entities.Comment;
import org.example.booksys.entities.CommentResponse;
import org.example.booksys.entities.PageResult;
import org.example.booksys.entities.Result;
import org.example.booksys.service.BookService;
import org.example.booksys.service.CommentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
public class CommentController {
    @Autowired
    private CommentService commentService;

    @Autowired
    private BookService bookService;

    // 获取图书评论
    @GetMapping("/api/comment/book/{bookId}")
    public Result getBookComments(
            @PathVariable Integer bookId,
            @RequestParam(defaultValue = "1") Integer start,
            @RequestParam(defaultValue = "10") Integer end) {

        List<Comment> comments = commentService.getCommentsByBookId(bookId, start, end);
        PageResult<Comment> pr = new PageResult<>();
        pr.rows = comments;
        pr.count = commentService.getCommentsCountByBookId(bookId);

        return Result.success(pr);
    }

    @GetMapping("/userapi/comment/book/{bookId}")
    public Result userGetBookComments(
            @PathVariable Integer bookId,
            @RequestParam(defaultValue = "1") Integer start,
            @RequestParam(defaultValue = "10") Integer end) {

        return getBookComments(bookId, start, end);
    }

    @GetMapping("/api/comment/user/{userId}")
    public Result getUserComments(
            @PathVariable Integer userId,
            @RequestParam(defaultValue = "1") Integer start,
            @RequestParam(defaultValue = "10") Integer end) {

        List<Comment> comments = commentService.getCommentsByUserId(userId, start, end);
        PageResult<Comment> pr = new PageResult<>();
        pr.rows = comments;
        pr.count = commentService.getCommentsCountByUser(userId);

        return Result.success(pr);
    }

    @GetMapping("/userapi/comment/user/{userId}")
    public Result userGetUserComments(
            @PathVariable Integer userId,
            @RequestParam(defaultValue = "1") Integer start,
            @RequestParam(defaultValue = "10") Integer end) {

        return getUserComments(userId, start, end);
    }

    @GetMapping("/api/comment/rating/{bookId}")
    public Result getBookRating(@PathVariable Integer bookId) {
        Map<String, Object> res = new HashMap<>();
        Double rating = commentService.getBookAverageRating(bookId);
        String title = bookService.getBook(bookId).bookTitle;
        res.put("rating", rating);
        res.put("title", title);
        return Result.success(res);
    }

    @GetMapping("/userapi/comment/rating/{bookId}")
    public Result userGetBookRating(@PathVariable Integer bookId) {
        return getBookRating(bookId);
    }

    @PostMapping("/api/comment")
    public Result addComment(@RequestBody Comment comment) {
        Boolean res = commentService.addComment(comment.userId, comment.bookId, comment.rating, comment.createTime, comment.context);
        if (res) {
            return Result.success();
        } else {
            return Result.error("您的发言含有违规内容，请修改后重试");
        }
    }

    @PostMapping("/userapi/comment")
    public Result userAddComment(@RequestBody Comment comment) {
        return addComment(comment);
    }

    @DeleteMapping("/api/comment/{commentId}")
    public Result deleteComment(@PathVariable Integer commentId) {
        commentService.deleteComment(commentId);
        return Result.success();
    }

    @GetMapping("/api/comment")
    public Result getAllComments(@RequestParam Integer start, @RequestParam Integer end) {
        List<CommentResponse> ls = commentService.getAllComments(start, end);
        PageResult<CommentResponse> pr = new PageResult<>();
        pr.rows = ls;
        pr.count = commentService.getCommentsCount();
        return Result.success(pr);
    }

    @GetMapping("/api/deletedComment")
    public Result getAllDeletedComments(@RequestParam Integer start, @RequestParam Integer end) {
        List<CommentResponse> ls = commentService.getAllDeletedComments(start, end);
        PageResult<CommentResponse> pr = new PageResult<>();
        pr.rows = ls;
        pr.count = commentService.getCommentsCount();
        return Result.success(pr);
    }

    @DeleteMapping("/api/deletedComment/{commentId}")
    public Result deleteDeletedComment(@PathVariable Integer commentId) {
        commentService.permanentlyDeleteComment(commentId);
        return Result.success();
    }

    @PostMapping("/api/deletedComment/{commentId}")
    public Result recoverDeletedComment(@PathVariable Integer commentId) {
        commentService.recoverDeletedComment(commentId);
        return Result.success();
    }
}
