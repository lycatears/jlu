package org.example.booksys.entities.reportDTO;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class BookTagCountDTO {
    public String tagName;
    public Integer tagCount;
}

/**
 * SELECT COUNT(*), bt."tag_id"
 * FROM BOOKMAN."book_tag" bt
 * LEFT JOIN BOOKMAN."tags" t ON bt."tag_id" = t."tag_id"
 * GROUP BY bt."tag_id";
 */