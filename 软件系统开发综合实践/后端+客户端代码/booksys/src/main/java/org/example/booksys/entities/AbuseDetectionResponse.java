package org.example.booksys.entities;

import lombok.Data;

import java.util.List;

@Data
public class AbuseDetectionResponse {
    private List<Integer> predictions;
    private List<List<Double>> probabilities;

    // Getter 和 Setter
    public List<Integer> getPredictions() {
        return predictions;
    }

    public void setPredictions(List<Integer> predictions) {
        this.predictions = predictions;
    }

    public List<List<Double>> getProbabilities() {
        return probabilities;
    }

    public void setProbabilities(List<List<Double>> probabilities) {
        this.probabilities = probabilities;
    }
}