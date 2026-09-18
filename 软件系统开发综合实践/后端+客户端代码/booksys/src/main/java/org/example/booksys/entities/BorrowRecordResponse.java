package org.example.booksys.entities;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class BorrowRecordResponse {
    public Integer recordId;
    public Integer bookId;
    public Integer userId;
    public String borrowDate;
    public String returnDate;
    public String bookTitle;
    public String uname;
}
