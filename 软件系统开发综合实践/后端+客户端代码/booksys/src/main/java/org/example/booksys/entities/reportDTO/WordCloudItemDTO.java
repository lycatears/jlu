package org.example.booksys.entities.reportDTO;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class WordCloudItemDTO {
    public String name;
    public Integer value;

    public WordCloudItemDTO(String name, Integer value) {
        this.name = name;
        this.value = value;
    }
}