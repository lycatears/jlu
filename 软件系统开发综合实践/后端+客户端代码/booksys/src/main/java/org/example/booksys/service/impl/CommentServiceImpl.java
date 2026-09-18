package org.example.booksys.service.impl;

import org.example.booksys.entities.Comment;
import org.example.booksys.entities.CommentResponse;
import org.example.booksys.mapper.CommentMapper;
import org.example.booksys.service.AbuseDetectionService;
import org.example.booksys.service.CommentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class CommentServiceImpl implements CommentService {
    @Autowired
    private CommentMapper commentMapper;

    @Autowired
    private AbuseDetectionService abuseDetectionService;

    public List<Comment> getCommentsByBookId(Integer bookId, Integer start, Integer end) {
        return commentMapper.findCommentByBookId(bookId, start, end);
    }

    // 根据userId分页查询评论
    @Override
    public List<Comment> getCommentsByUserId(Integer userId, Integer start, Integer end) {
        return commentMapper.findCommentByUserId(userId, start, end);
    }

    public Integer getCommentsCountByBookId(Integer bookId) {
        return commentMapper.getBookCommentCount(bookId);
    }

    public Integer getCommentsCountByUser(Integer userId) {
        return commentMapper.getUserCommentCount(userId);
    }

    public Integer getCommentsCount() {
        return commentMapper.getCommentsCount();
    }

    @Override
    public void deleteComment(Integer commentId) {
        commentMapper.deleteComment(commentId);
    }

    @Override
    public void permanentlyDeleteComment(Integer commentId) {
        commentMapper.permanentlyDeleteComment(commentId);
    }

    @Override
    public List<CommentResponse> getAllComments(Integer start, Integer end) {
        return commentMapper.getAllComments(start, end);
    }

    @Override
    public List<CommentResponse> getAllDeletedComments(Integer start, Integer end) {
        return commentMapper.getAllDeletedComments(start, end);
    }

    @Override
    @Transactional
    public void recoverDeletedComment(Integer commentId) {
        Comment comment = commentMapper.getDeletedCommentById(commentId).get(0);
        if (comment != null) {
            commentMapper.permanentlyDeleteComment(commentId);
            commentMapper.addComment(comment);
        }
    }

    public Boolean addComment(Integer userId, Integer bookId, Integer rating,
                              String createTime, String context) {
        // 检查是否包含违规内容
        if (abuseDetectionService.isAbusive(context)) {
            return false;
        }

        // 创建新评论
        Comment comment = new Comment();
        comment.commentId = commentMapper.getNextCommentId();
        comment.userId = userId;
        comment.bookId = bookId;
        comment.rating = rating;
        comment.createTime = createTime;
        comment.context = context;
        Integer next = commentMapper.getNextFloorId(bookId);
        if (next == null) {
            next = 1;
        }
        comment.floorId = next;

        // 保存到数据库
        commentMapper.addComment(comment);

        return true;
    }

    @Cacheable(value = "bookRatings", key = "#bookId")
    public Double getBookAverageRating(Integer bookId) {
        Double rating = commentMapper.calculateAverageRatingByBookId(bookId);
        return rating != null ? rating : 0.0;
    }

    @Scheduled(cron = "0 0 0 * * ?")  // 每天0点执行
    public void refreshCache() {
        clearCache();
    }

    @CacheEvict("bookRatings")
    public void clearCache() {
        System.out.println("清空词云缓存");
    }
}
