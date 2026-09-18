package org.example.booksys.entities;

import lombok.Data;

import java.util.List;

@Data
public class AbuseDetectionRequest {
    private List<String> texts;

    public AbuseDetectionRequest(List<String> texts) {
        this.texts = texts;
    }

    // Getter 和 Setter
    public List<String> getTexts() {
        return texts;
    }

    public void setTexts(List<String> texts) {
        this.texts = texts;
    }
}