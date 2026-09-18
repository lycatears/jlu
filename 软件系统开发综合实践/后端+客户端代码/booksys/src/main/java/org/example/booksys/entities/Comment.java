package org.example.booksys.entities;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Comment {
    public Integer commentId;
    public Integer userId;
    public Integer bookId;
    public Integer rating;
    public String context;
    public String createTime;
    public Integer floorId;
}
