package org.example.booksys.entities;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Tag {
    public Integer tagId;
    public String tagName;

    // Getter & Setter
}
