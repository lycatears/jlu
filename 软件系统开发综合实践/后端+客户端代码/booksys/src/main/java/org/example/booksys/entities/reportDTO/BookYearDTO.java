package org.example.booksys.entities.reportDTO;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class BookYearDTO {
    public Integer year;
    public Integer bookCount;
}
